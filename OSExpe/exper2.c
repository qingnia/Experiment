#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAXLINE	64
#define	PRO_COUNT	5
#define	RS_COUNT	3

int main(int argc, char* argv[])
{
	FILE* file;
	int resou[PRO_COUNT][RS_COUNT * 3 + 1] = { 0 };
	int reloc_r[RS_COUNT] = { 0 };
	int sequeue[PRO_COUNT];
	int i = 0;
	int stat = 0;
	if(1 == argc)
		file = fopen("input", "r");
	else
		file = fopen(argv[1], "r");
	char buf[MAXLINE];
	for(; i < RS_COUNT; i++)
	{
		printf("input relocate r%d: ", i + 1);
		scanf("%d", reloc_r + i);
	}
	fgets(buf, MAXLINE, file);
	fgets(buf, MAXLINE, file);
	for(i = 0; i < PRO_COUNT; i++)
	{
		memset(buf, 0, MAXLINE);
		if(NULL == fgets(buf, MAXLINE, file))
		{
			break;
		}
		sscanf(buf + 2, "%5d%3d%3d%5d%3d%3d%5d%3d%3d", resou[i] + 1, resou[i] + 2, resou[i] + 3, resou[i] + 4, resou[i] + 5, resou[i] + 6, resou[i] + 7, resou[i] + 8, resou[i] + 9);
		resou[i][0] = 0;
	}
	i = 0;
	int no = 0;
	int count = 0;
	while(1)
	{
		sleep(1);
		printf("%d, allo:%d, %d, %d, need:%d, %d, %d, relo:%d, %d, %d\n",i, resou[i][4], resou[i][5], resou[i][6], resou[i][7], resou[i][8], resou[i][9], reloc_r[0], reloc_r[1], reloc_r[2]);
		if(0 == resou[i][0])
		{
			if(resou[i][7] <= reloc_r[0] && resou[i][8] <= reloc_r[1] && resou[i][9] <= reloc_r[2])
			{
				sequeue[no] = i;
				no++;
				resou[i][0] = 1;
				reloc_r[0] += resou[i][4];
				reloc_r[1] += resou[i][5];
				reloc_r[2] += resou[i][6];
				count = 0;
				printf("i get\n");
			}
			else
			{
				printf("i can not get\n");
				count++;
			}
		}
		if(i == PRO_COUNT - 1)
			i = 0;
		else
			i++;
		printf("count: %d\n", count);
		int j = 0;
		for(j = 0; j < PRO_COUNT; j++)
		{
			if(resou[j][0])
				continue;
			else
				break;
		}
		if(j == PRO_COUNT)
//		if(resou[0][0] && resou[1][0] && resou[2][0] && resou[3][0])
		{
			stat = 1;
			break;
		}
		else if(count >= PRO_COUNT)		
		{
			stat = 0;
			break;
		}
	}
	if(stat)
	{
		printf("sucess!\n");
		for(i = 0; i < PRO_COUNT; i++)
		{
			printf("%d ", sequeue[i]);
		}
	}
	else
	{
		printf("dead lock!\n");
	}
	return 0;
}
