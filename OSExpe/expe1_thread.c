#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "util.h"
#define N 4
#define PROD_NUM 10
#define CONS_NUM 2

int main(int argc, char* argv[])
{
	int i = 0;
	int prod_ip[PROD_NUM] = { 0 };
	int cons_ip[CONS_NUM] = { 0 };
	void *p1, *p2;
	pthread_t* p = (pthread_t*)calloc(PROD_NUM + CONS_NUM, sizeof(pthread_t));
	pthread_mutex_init(&s.mutex, 0);
	s.count = 0;
	sem_init(&s.empty, 0, N);
	sem_init(&s.full, 0, 0);
	for(i = 0; i < PROD_NUM; i++)
	{
		prod_ip[i] = i;
		pthread_create((p + i), NULL, producer, (void*)(prod_ip + i));
	}
	for(i = 0; i < CONS_NUM; i++)
	{
		cons_ip[i] = i;
		pthread_create((p + i + PROD_NUM), NULL, consumer, (void*)(cons_ip + i));
	}
	for(i = 0; i < CONS_NUM + 1; i++)
	{
		pthread_join(*(p + i), p2);
	}
	printf("exit\n");
	exit(0);
}
