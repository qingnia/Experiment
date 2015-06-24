#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "util.h"

#define N 5

int main(int argc, char* argv[])
{
	int ip[20] = { 0 };
	pid_t* p = (pid_t*)calloc(20, sizeof(pid_t));
	int i = 0;
	i = 0;
	pthread_mutex_init(&s.mutex, 0);
	sem_init(&s.empty, 1, N);
	sem_init(&s.full, 1, 0);
	for(i = 0; i < 20; i++)
	{
		switch((p[i] = fork()))
		{
		case -1:
			printf("fork error!");
			exit(-1);
		case 0:
			{
				ip[i] = i;
//				long int r = rand();
//				printf("child%ld\n", r);
//				if(0 == r % 2)
				if(i < 8)
				{
					printf("new producer!%d\n", p[i]);
					producer((void*)(ip + i));
				}
				else
				{
					printf("new consumer!%d\n\n", p[i]);
					consumer((void*)(ip + i));
				}
			}
		default :
			printf("%d\n", p[i]);
			break;
		}
	}
	wait();
}
