#include "queue.h"
#include "util.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
	int n = 0;
	int i = 0;
	int input = 0;
	scanf("%d", &n);
	struct Queue* head = (struct Queue*)malloc(sizeof(struct Queue));
	memset(head, 0, sizeof(struct Queue));
	createQueue(head);
	for(i = 0; i < n; i++)
	{
		scanf("%d", &input);
		subQueue(head, input);
	}
	int count = 0;
	int hasIF = 0;
	int hasID = 0;
	int hasEX = 0;
	int wait = 0;
	int* ad_val = (int*)malloc(2 * sizeof(ad_val));
	int ret = 0;
	while(1)
	{
		printf("%d:\n", count + 1);
		if(1 == hasEX)
		{
			printf("store %d\n", ret);
			MEM(head, ret);
			wait = 1;
			hasEX = 0;
		}
		if(1 == hasID)
		{
			printf("add %d, %d\n", *ad_val, *(ad_val + 1));
			ret = EX(ad_val);
			hasID = 0;
			hasEX = 1;
		}
		if(1 == hasIF)
		{
			ID(head, &ad_val);
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
	printf("Result is:%d\n", ret);
	printf("count is:%d\n", count);
	free(head);
	free(ad_val);
}
