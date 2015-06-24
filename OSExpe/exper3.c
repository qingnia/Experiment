#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	DIR_LEN 32

int main(int argc, char* argv[])
{
	int page_log, page_count, page_level, log_dir;
	int inner_dir = 0;
	int page_dir = 0;
	printf("input page_log count: ");
	scanf("%d", &page_log);
	printf("input page count: ");
	scanf("%d", &page_count);
	printf("input page_level: ");
	scanf("%d", &page_level);
	printf("input log_dir: ");
	scanf("%x", &log_dir);
	int page_len = 0;
	page_len = page_count / page_log;
	int page_len_b = 0;
	while(page_len > 1)
	{
		page_len = page_len >> 1;
		page_len_b++;
	}
	printf("page_len_b: %d\n", page_len_b);
	int* page_der = (int*)malloc(page_level * sizeof(int));
	memset(page_der, 0, page_level * sizeof(int));
	int i = 0;
	int inner_len = DIR_LEN - page_len_b * page_level;
	printf("inner_len: %d\n", inner_len);
	for(i = 0; i < inner_len; i++)
	{
		int m = 1 << i;
		inner_dir += (1 << i);
	}
	inner_dir = inner_dir & log_dir;
	printf("inner_dir: %x\n", inner_dir);
	for(i = 0; i < page_len_b; i++)
	{
		int j = 0;
		for(; j < page_level; j++)
		{
			page_der[j] += 1 << i;
		}
	}
	page_dir = log_dir >> inner_len;
	for(i = 1; i <= page_level; i++)
	{
		page_der[page_level - i] = page_der[page_level - i] & page_dir;
		page_dir = page_dir >> page_len_b;
	}
	int start_dir = 0;
	for(i = 0; i < page_level; i++)
	{
		start_dir = start_dir << page_len_b;
		printf("level%d page der: %x\n", i + 1, page_der[i]);
		printf("level%d address is %x\n", i + 1, start_dir + page_der[i]);
		start_dir = 0;
		scanf("%d", &start_dir);
	}
	printf("physics block: %x, der: %x\n", start_dir, inner_dir);
	free(page_der);
	return 0;
}
