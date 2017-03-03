#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

__thread int var = 8;

void *func0(void *arg){
	++var;
	printf("func0:%d\n", var);
}

void *func1(void *arg){
	usleep(3);
	++var;
	printf("func1:%d\n", var);
}


int main(){

	pthread_t p0, p1;
	int i=0;
	pthread_create(&p0, NULL,  func0, NULL);
	pthread_create(&p1, NULL,  func1, NULL);
	
	pthread_join(p0, NULL);
	pthread_join(p1, NULL);
	return 0;
}
