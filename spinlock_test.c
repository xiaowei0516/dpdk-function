#include "spinlock.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static num =0; 
rte_spinlock_t retlock;

void *testfunc(void *arg)
{
    int i=0,t;
    for(i=0;i<20000;i++)
    {   
        rte_spinlock_lock(&retlock);
        num++;
        rte_spinlock_unlock(&retlock);
    }
}

int main()
{
	rte_spinlock_init(&retlock);

    pthread_t thread[20];
    int i;
    for(i=0;i<20;i++)
    {
        pthread_create(&thread[i],NULL,(void*)testfunc,NULL);
    }
    for(i=0;i<20;i++)
    {
        pthread_join(thread[i],NULL);
    }
    printf("%d\n",num);
 }
