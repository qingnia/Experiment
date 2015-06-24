#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char input[20] = "avc";
	int m = 0;
	printf("%16s%d", input, m);
	scanf("%-16s%d ", input, &m);
	printf("%s, %d", input, m);
	return 0;
}
