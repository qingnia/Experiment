#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i = 0;
	for(; i < 10; i++)
	{
		int m = random() % 10;
		printf("%d: %d\n", i, m);
	}
	return 0;
}
