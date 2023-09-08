#include"header.h"
#include"declarations.h"

void* exitfunc(void *arg){
	printf("%s Begin.\n", __func__);
	if(strncmp((char*)arg, "success", 7) == 0)
		exit(EXIT_SUCCESS);
	else if(strncmp((char*)arg, "failure", 7))
		exit(EXIT_FAILURE);
	printf("%s End.\n", __func__);
	return (void*)0;
}

