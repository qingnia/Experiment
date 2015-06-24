#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(int argc, char* argv[])
{
	if(2 != argc)
	{
		printf("argument is wrong!");
		return 1;
	}
	char dydName[20] = { 0 };
	char dysName[20] = { 0 };
	char varName[20] = { 0 };
	char proName[20] = { 0 };
	sprintf(dydName, "%s.dyd", argv[1]);
	sprintf(dysName, "%s.dys", argv[1]);
	sprintf(varName, "%s.var", argv[1]);
	sprintf(proName, "%s.pro", argv[1]);
	FILE* dydFile = fopen(dydName, "r");
	FILE* dysFile = fopen(dysName, "w+");
	FILE* varFile = fopen(varName, "w+");
	FILE* proFile = fopen(proName, "w+");
	gram_analysis(dydFile, dysFile, varFile, proFile);
}
