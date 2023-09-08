#ifndef MSGKEY
#define MSGKEY 1111
#endif

#ifndef SHMKEY
#define SHMKEY 2222
#endif

typedef struct{
        int pid;
        int oprd1;
        int oprd2;
        char oper;
}Request;

typedef struct{
	long pid;
	float result;
}Result;

typedef struct{
	int *pipe;
	char *fifo;
	Result *result;
	key_t msgq;
}Infra;

