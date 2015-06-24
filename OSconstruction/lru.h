#ifndef	LRU_H
#define LRU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
typedef	struct LRU
{
	int	count;
	int	n;
	Queue*	head;
}lru;

lru* create_LRU(int n)
{
	lru* ret = (lru*)malloc(sizeof(lru));
	memset(ret, 0, sizeof(lru));
	ret->n = n;
	ret->count = 0;
	ret->head = (Queue*)malloc(sizeof(Queue));
	createQueue(ret->head);
	return ret;
}

int nextPage_LRU(lru* lru, int index)
{
	int ret = 1;
	if(!Queue_value_MoveToHead(lru->head, index))
	{
		printf("lru: get %d\n", index);
		lru->count++;
		ret = 0;
	}
	else if(lru->n > lru->head->x)
	{
		subQueue(lru->head, index);
		printf("lru: can't get %d, n: %d, length:%d, append to queue\n", index, lru->n, lru->head->x);
		lru->count += 100;
		ret = 0;
	}
	else
	{
		subQueue(lru->head, index);
		int replacement = 0;
		getQueue(lru->head, &replacement);
		printf("lru: can't get %d, replacement %d\n", index, replacement);
		lru->count += 100;
		ret = 0;
	}
	return ret;
}

#endif
