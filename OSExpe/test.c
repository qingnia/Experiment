#include <stdio.h>

int main(int argc, char* argv[])
{
	int m1 = 0;
       	int m2 = 0;
	printf("%3d, %3d, %3d", 123, 456, 789);
	scanf("%d", &m1);
	scanf("%3d", &m2);
	printf("%d, %d", m1, m2);
	return 0;
}
