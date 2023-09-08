#include "../include/header.h"
#include "../../common/dataStruct.h"
#include "../include/semun.h"

void* main(void *arg){
	printf("%s Begin.\n", __func__);
	printf("%s Process id : %d\n", __func__, getpid());
	int fd = open("../Server/myfifo", O_WRONLY);
	Request req;
	req.pid = getpid();
	req.oper = '/';
	req.oprd1 = 5;
	req.oprd2 = 5;
	Result res;
	
	//Semaphore
	int sem_id = semget(SEMKEY, 1, 0666 | IPC_CREAT);
	if(sem_id < 0){
        	perror("semget"); exit(11);
    	}
	union semun u;
    	u.val = 1;
	if(semctl(sem_id, 0, SETVAL, u) < 0){
	        perror("semctl"); exit(12);
    	}
	if(semop(sem_id, &p, 1) < 0){
                perror("semop p"); exit(13);
        }

	//Critical Section start
	int ret = write(fd, &req, sizeof(Request));
	printf("%s Written : %d bytes\n",__func__, ret);	
	//Critical Section end

	if(semop(sem_id, &v, 1) < 0){
                perror("semop p"); exit(14);
        }
	if(semctl(sem_id, 0, IPC_RMID, u) < 0){
                perror("semctl"); exit(12);
        }
	int keyk = msgget(MSGKEY, 0666 | IPC_CREAT);
	msgrcv(keyk, &res, sizeof(res), res.pid, 0);
	printf("Pid Client side : %ld\n", res.pid);
	printf("Value Client side : %.2f\n", res.result);
	//close(fd);
	printf("%s End.\n", __func__);
	return (void*)0;
}

