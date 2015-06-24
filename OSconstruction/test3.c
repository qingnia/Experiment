#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "util.h"

int main(int argc, char* argv[])
{
	int add_n = 0;
	int mul_n = 0;
	int i = 0;
	int input1 = 0;
	int input2 = 0;
	printf("add value count: ");
	scanf("%d", &add_n);
	printf("mul value count: ");
	scanf("%d", &mul_n);
	Queue* head = (struct Queue*)calloc(3, sizeof(Queue));
	createQueue(&head[0]);
	createQueue(&head[1]);
	createQueue(&head[2]);
	for(i = 1; i <= add_n; i++)
	{
		printf("add %d: ", i);
		scanf("%d", &input1);
		subQueue(&head[2], input1);
	}
	for(i = 1; i <= mul_n; i++)
	{
		printf("input %d:", i);
		scanf("%d", &input1);
		scanf("%d", &input2);
		subQueue(&head[0], input1);
		subQueue(&head[1], input2);
	}
	i = dynamStreamLine(add_n, mul_n, &head[0], &head[1], &head[2], &input2);
	printf("count is %d\n", i);
	printf("result is %d\n", input2);
}
