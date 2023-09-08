#include"header.h"
#include"declarations.h"
#include"../common/dataStruct.h"

void* main(void *arg){
	init();
	printf("%s Begin.\n", __func__);
	Infra *infra;
	infra = (Infra*)(*fp[1])(NULL);		//createInfra
	pthread_t tid;
	int ret = 0;
	while(1){	
		//(*fp[2])((void*)infra);			//processRequst
		ret = pthread_create(&tid, NULL, fp[2], (void*)infra);
		if (ret != 0){
                	perror("pthread_create");
	                exit(EXIT_FAILURE);
        	}
		pthread_join(tid, NULL);
	}
	printf("%s End.\n", __func__);
	return (void*)0;
}

