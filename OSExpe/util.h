#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

static pthread_mutex_t mutex;
static sem_t sema;
static struct
{
	pthread_mutex_t mutex;
	sem_t full;
	sem_t empty;
	int count;
	char* buf;
}s;

void* producer(void* p)
{
	while(1)
	{
		sem_wait(&s.empty);
		pthread_mutex_lock(&s.mutex);
		printf("Producer%d: count is %d, add by 1\n", *(int*)p, s.count);
		s.count++;
		pthread_mutex_unlock(&s.mutex);
		sem_post(&s.full);
		sleep(1);
	}
}

void* consumer(void* c)
{
	while(1)
	{
		sem_wait(&s.full);
		pthread_mutex_lock(&s.mutex);
		printf("Consumer%d: count is %d, minux by 1\n", *(int*)c, s.count)
;
		s.count--;
		pthread_mutex_unlock(&s.mutex);
		sem_post(&s.empty);
		sleep(2);
	}
}
