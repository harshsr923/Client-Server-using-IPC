#include"header.h"
#include"declarations.h"
#include"../common/dataStruct.h"
Infra *infra;

void handler(){
	close(*infra->pipe);
	close(*(infra->pipe+1));
	free(infra->pipe);
	shmdt(infra->result);
	shmctl(SHMKEY, IPC_RMID, 0);
	//system("ipcrm -a");
	msgctl(MSGKEY, IPC_RMID, 0);
	free(infra);
	printf("%s Successfully Terminate. All resources are free.\n",__func__);
	(*fp[0])((void*)"success");
}

void* processRequest(void *arg){
	signal(SIGINT, handler); 
	Request req;
	infra = (Infra*)arg;
	printf("%s Begin.\n", __func__);
	mkfifo("myfifo", 0666);
	int fd = open("myfifo", O_RDONLY);
        int ret = read(fd, &req, sizeof(Request));
	if(ret == -1){
		perror("read");
		(*fp[0])((void*)"failure");
	}
	printf("%s fd: %d\n",__func__, fd);
	printf("%s Read: %d bytes\n",__func__, ret);
	//close(fd);
	/*ret = pipe(infra->pipe);

	if(ret == -1){
                perror("pipe");
		(*fp[0])((void*)"failure");
        }
*/
	char strfd[2];
        sprintf(strfd, "%d", *infra->pipe);
	
	switch(fork()){
		case -1:
 	               	perror("read");
			(*fp[0])((void*)"failure");
			break;
		case 0:
			switch(req.oper){
				case '+':	
					execl("../Vender/adder", "adder", strfd, NULL);
					break;
				case '-':	
					execl("../Vender/subtractor", "subtractor", strfd, NULL);
					break;
				case '*':	
					printf("%s Fd : %s\n",__FILE__, strfd);
					execl("../Vender/multiplier", "multiplier", strfd, NULL);
					break;
				case '/':	
					execl("../Vender/divider", "divider", strfd, NULL);
					break;
				default:
					printf("Ivalid Operation");
			}
			break;
		default:
			printf("%s Parent details\n",__func__);
			
			//Thread Semaphore

			//WRITE IN PIPE

			write(*(infra->pipe+1), &req, sizeof(Request));
			wait(NULL);
			printf("%s Result SHM %d\n", __func__, infra->result->pid);
			Result res;
			
			//READ FROM SHM

			res.pid = infra->result->pid;
			res.result = infra->result->result;
			printf("%s Value Server side : %.2f\n", __func__, res.result);
		        
			// WRITE IN MSGQ

			msgsnd(infra->msgq, &res, sizeof(res),  0);
        }
	//close(*infra->pipe); // Harsh
	//close(*(infra->pipe+1)); // Harsh
//	sleep(1);
	close(fd);
	//exit(1);
	printf("%s End.\n", __func__);
	pthread_exit(NULL);
	//return (void*)0;
}

