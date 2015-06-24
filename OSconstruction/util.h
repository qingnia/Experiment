#ifndef UTIL_H
#define UTIL_H

#include "queue.h"
#define	ADD	1
#define MUL	2
/*
void* IF(void* addr)
{
	int* ret = (int*)malloc(2 * sizeof(int));
}
*/

void ID(struct Queue* q, int** ad_val)
{
	getQueue(q, *ad_val);
	getQueue(q, *ad_val + 1);
}

int EX(int* ad_val)
{
	return *ad_val + *(ad_val + 1);
}

void MEM(struct Queue* q, int ret)
{
	subQueue(q, ret);
}

void getVal(Queue* q, int** val)
{
	getQueue(q, *val);
}

int EEX(int operation, int* val)
{
	switch(operation)
	{
		case ADD :
			return *val + *(val + 1);
			break;
		case MUL :
			return *val * *(val + 1);
			break;
	}
	return -1;
}

int execMul(int n, Queue* head1, Queue* head2, Queue* addQueue)
{
	int* mul_val = (int*)calloc(2, sizeof(int));
	int hasEX = 0;
	int hasIF = 0;
	int ret = 0;
	int count = 1;
	while(1)
	{
		printf("%d : \n", count);
		if(1 == hasEX)
		{
			printf("store %d\n", ret);
			MEM(addQueue, ret);
			hasEX = 0;
		}
		if(1 == hasIF)
		{
			printf("mul %d, %d\n", *mul_val, *(mul_val + 1));
			ret = EEX(MUL, mul_val);
			hasIF = 0;
			hasEX = 1;
		}
		if(n >0)
		{
			getQueue(head1, mul_val);
			getQueue(head2, (mul_val + 1));
			hasIF = 1;
			n--;
		}
		printf("\n");
		count++;
		if(0 == n && 0 == hasIF && 0 == hasEX)
			break;
	}
	return count;
}

int execAdd(int n, Queue* addQueue, int* result, int i)
{
	int temp = i;
	int* ad_val = (int*)calloc(2, sizeof(int));
	int hasIF, hasID, hasEX, wait, ret;
	hasIF = hasID = hasEX = wait = ret = 0;
	int count = 0;
	while(1)
	{
		printf("%d\n", temp + count);
		if(1 == hasEX)
		{
			printf("store %d\n", ret);
			MEM(addQueue, ret);
			wait = 1;
			hasEX = 0;
		}
		if(1 == hasID)
		{
			printf("add %d, %d\n", *ad_val, *(ad_val + 1));
			ret = EEX(ADD, ad_val);
			hasID = 0;
			hasEX = 1;
		}
		if(1 == hasIF)
		{
			ID(addQueue, &ad_val);
			printf("get %d, %d\n", *ad_val, *(ad_val + 1));
			hasIF = 0;
			hasID = 1;
		}
		if(n >= 2)
		{
			hasIF = 1;
			n -= 2;
		}
		if(1 == wait)
		{
			n += 1;
			wait = 0;
		}
		printf("\n");
		count++;
		if(0 == hasIF && 0 == hasID && 0 == hasEX)
			if(2 == n)
				continue;
			else
				break;
	}
	*result = ret;
	return count;
}

int dynamStreamLine(int add_n, int mul_n, Queue* head1, Queue* head2, Queue* addQueue, int* result)
{
	int* mul_val = (int*)calloc(2, sizeof(int));
	int* add_val = (int*)calloc(2, sizeof(int));
	int hasADD_EX = 0;
	int hasMUL_EX = 0;
	int hasID = 0;
	int hasIF = 0;
	int isADD = 0;
	int isMUL = 0;

	int count = 0;
	int wait = 0;
	int add_ret = 0;
	int mul_ret = 0;
	while(1)
	{
		printf("%d:\n", ++count);
		if(1 == hasADD_EX)
		{
			printf("strore add result: %d\n", add_ret);
			MEM(addQueue, add_ret);
			hasADD_EX = 0;
			if(1 == hasMUL_EX)
			{
				add_n++;
				continue;
			}
			else
				wait = 1;
		}
		else if(1 == hasMUL_EX)
		{
			printf("strore mul_result: %d\n", mul_ret);
			MEM(addQueue, mul_ret);
			hasMUL_EX = 0;
			wait = 1;
		}
		if(1 == hasID)
		{
			printf("add %d, %d\n", *add_val, *(add_val + 1));
			add_ret = EEX(ADD, add_val);
			hasID = 0;
			hasADD_EX = 1;
		}
		if(1 == hasIF)
		{
			if(1 == isADD)
			{
				ID(addQueue, &add_val);
				printf("get %d, %d from add queue\n", *add_val, *(add_val + 1));
				hasIF = 0;
				hasID = 1;
				isADD = 0;
			}
			if(1 == isMUL)
			{
				getQueue(head1, mul_val);
				getQueue(head2, (mul_val + 1));
				printf("get %d, %d from mul queue\n", *mul_val, *(mul_val + 1));
				printf("mul %d, %d\n", *mul_val, *(mul_val + 1));
				mul_ret = EEX(MUL, mul_val);
				hasIF = 0;
				hasMUL_EX = 1;
				isMUL = 0;
			}
		}
		if(add_n >= 2)
		{
			hasIF = 1;
			isADD = 1;
			add_n -= 2;
			printf("next instruction is add\n");
		}
		else if(mul_n >= 1)
		{
			hasIF = 1;
			isMUL = 1;
			mul_n -= 1;
			printf("next instruction is mul\n");
		}
		if(1 == wait)
		{
			add_n += 1;
			wait = 0;
		}
		printf("\n");
		if(0 == hasIF && 0 == hasID && 0 == hasADD_EX && 0 == hasMUL_EX && 0 == mul_n && 1 == add_n)
			break;
//		else
//			printf("IF:%d, ID:%d, ADD_EX:%d, MUL_EX:%d\n", hasIF, hasID, hasADD_EX, hasMUL_EX);
	}
	*result = add_ret;
	free(add_val);
	free(mul_val);
	return count;
}
/*
void* read(void* addr)
{
	int input = 0;
	scanf("%d", &input);
	subQueue((struct Queue*)addr);
	return NULL;
}
*/

#endif
