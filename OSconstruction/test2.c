#include "queue.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int n = 0;
	int i = 0;
	int input1 = 0;
	int input2 = 0;
	int result = 0;
	scanf("%d", &n);
	struct Queue* head = (struct Queue*)calloc(3, sizeof(struct Queue));
	createQueue(&head[0]);
	createQueue(&head[1]);
	createQueue(&head[2]);
	for(i = 0; i < n; i++)
	{
		printf("input %d\n", n);
		scanf("%d", &input1);
		scanf("%d", &input2);
		subQueue(&head[0], input1);
		subQueue(&head[1], input2);
	}
	i = 0;
	int* val = (int*)calloc(2, sizeof(int));
	i += execMul(n, &head[0], &head[1], &head[2]);
	i += execAdd(n, &head[2], &result, i);
	printf("Resule is: %d\n", result);
	printf("count is: %d\n", i);
	free(head);
	return 0;
}
