#include"header.h"
#include"declarations.h"

int init(void){
	printf("%s Begin.\n", __func__);
	fp[0] = exitfunc;
	fp[1] = createInfra;
	fp[2] = processRequest;
	printf("%s End.\n", __func__);
return 0;
}

