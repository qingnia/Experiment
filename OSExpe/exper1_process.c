#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>

union semun
{
	int	val;
	struct 	semid_ds *buf;
	unsigned short *array;
};

static int set_semvalue(int sem_id, int val)
{
	union semun sem_union;
	sem_union.val = val;
	if(-1 == semctl(sem_id, 0, SETVAL, sem_union))
	{
		printf("set semphore value failed\n");
		return 0;
	}
	return 1;
}

static int get_semvalue(int sem_id)
{
	return semctl(sem_id, 0, GETVAL, NULL);
}

static void del_semvalue(int sem_id)
{
	union semun sem_union;
	if(-1 == semctl(sem_id, 0, IPC_RMID, sem_union))
		fprintf(stderr, "del error\n");
}

static int semaphore_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if(-1 == semop(sem_id, &sem_b, 1))
	{
		printf("P failed\n");
		return -1;
	}
	return 0;
}

static int semaphore_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if(-1 == semop(sem_id, &sem_b, 1))
	{
		printf("V failed\n");
		return -1;
	}
	return 0;
}

int producer(int full, int empty)
{
	int i = 0;
	for(; i < 5; i++)
	{
		sleep(1);
		semaphore_p(empty);
		printf("prodecer%d, full:%d, empty:%d\n", getpid(), get_semvalue(full), get_semvalue(empty));
		semaphore_v(full);
	}
	exit(1);
}

int consumer(int full, int empty)
{
	int i = 0;
	for(; i < 5; i++)
	{
		semaphore_p(full);
		printf("consumer%d\n", getpid());
		semaphore_v(empty);
		sleep(1);
	}
	exit(2);
}

int main(int argc, char* argv[])
{
	key_t key1, key2;
	int full, empty, i;
	struct sembuf sb;
	key1 = ftok(".", 'a');
	full = semget(key1, 2, 0666|IPC_CREAT);
	key2 = ftok(".", 'b');
	empty = semget(key2, 2, 0666|IPC_CREAT);
	printf("key1:%o, key2:%o, %d, %d\n", key1, key2, full, empty);
	set_semvalue(full, 0);
	set_semvalue(empty, 3);
	printf("full value:%d, empty value:%d\n", get_semvalue(full), get_semvalue(empty));
	pid_t* pid = (pid_t*)calloc(10, sizeof(pid_t));
	for(i = 0; i < 10; i++)
	{
		*(pid + i) = fork();
		if(*(pid + i) < 0)
		{
			fprintf(stderr, "fork error\n");
			exit(-1);
		}
		if(*(pid + i) == 0)
		{
			if(i < 4)
				producer(full, empty);
			else
				consumer(full, empty);
		}
		else
		{
			waitpid();
		}
	}
	return 0;
}


