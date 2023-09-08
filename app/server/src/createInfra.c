#include"header.h"
#include"declarations.h"
#include"../common/dataStruct.h"

void* createInfra(void *arg){
	printf("%s Begin.\n", __func__);
	Infra *infra;
	//printf("%d",*infra->pipe);
	infra = (Infra*)malloc(sizeof(Infra));
	infra->pipe = (int*)malloc(sizeof(int)*2);
	if(infra->pipe == NULL){
		perror("malloc");
		free(infra->pipe);
		free(infra);
		(*fp[0])((void*)"failure");
	}
	key_t shrmk = 0;
	shrmk = shmget(SHMKEY, sizeof(Result), 0666 | IPC_CREAT);
	if(shrmk == -1){
		perror("shmget");
		close(*infra->pipe);
		close(*(infra->pipe+1));
		free(infra->pipe);
		shmctl(SHMKEY, IPC_RMID, 0);
		free(infra);
		system("ipcrm -a");
		(*fp[0])((void*)"failure");
	}
	infra->result = shmat(shrmk, NULL, 0);
	infra->msgq = msgget(MSGKEY, 0666 | IPC_CREAT);
	if(infra->msgq == -1){
		perror("msgget");
		close(*infra->pipe);
                close(*(infra->pipe+1));
		free(infra->pipe);
		shmdt(infra->result);
		shmctl(SHMKEY, IPC_RMID, 0);
		msgctl(MSGKEY, IPC_RMID, 0);
		free(infra);
		system("ipcrm -a");
		(*fp[0])((void*)"failure");
	}
	int ret = pipe(infra->pipe);

        if(ret == -1){
                perror("pipe");
                (*fp[0])((void*)"failure");
        }
	mkfifo("myfifo", 0666);

	printf("%s End.\n", __func__);
	return (void*)infra;
}

