#include <stdio.h>
#include <stdlib.h>
#include "lru.h"
#include "fifo.h"

void initDirQueue(Queue* dirQueue)
{
	int length = 0;
	int i = 0;
	int dir = 0;
	printf("input direction length:");
	scanf("%d", &length);
	for(; i < length; i++)
	{
		printf("input %d direction index:", i);
		scanf("%d", &dir);
		subQueue(dirQueue, dir);
	}
}

int main(int argc, char* argv[])
{
	Queue* dirQueue = (Queue*)malloc(sizeof(Queue));
	initDirQueue(dirQueue);
	int n = 0;
	int i = 0;
	printf("input n:");
	scanf("%d", &n);
	fifo** array_f = (fifo**)calloc(n, sizeof(fifo*));
	lru** array_l = (lru**)calloc(n, sizeof(lru*));
	for(; i < n; i++)
	{
		array_f[i] = create_FIFO(i + 1);
		array_l[i] = create_LRU(i + 1);
	}
	int length = dirQueue->x;
	int j = 0;
	int cur_index = 0;
	for(i = 0; i < length; i++)
	{
		getQueue(dirQueue, &cur_index);
		printf("the %d dir: get %d\n", i, cur_index);
		int j = 0;
		for(; j < n; j++)
		{
			printf("\nn = %d:\n", j);
			nextPage_FIFO(array_f[j], cur_index);
			nextPage_LRU(array_l[j], cur_index);
//			printf("%d:   fifo count: %d, lru count: %d\n", i, array_f[i]->count, array_l[i]->count);
		}
		printf("\n");
	}
	printf("over\n");
	for(i = 0; i < n; i++)
	{
		printf("%d:   fifo count: %d, lru count: %d\n", i, array_f[i]->count, array_l[i]->count);
	}
	return 0;
}
