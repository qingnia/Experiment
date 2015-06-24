#include<stdio.h>
#include<stdlib.h>
#include "util.h"
/*
int analysis(FILE* pasFile, FILE* dydFile, FILE* errFile)
{
	int intdex = 0;
	stat = 0;
	int c = fgetc(file);
	char* word = (char*)malloc(16 * sizeof(char));
	memset(word, ' ', sizeof(16 * sizeof(char)));
	while(1)
	{
		if(isAandN(c))
			stat = 1;
		if(isN(c))
			stat = 3;
		if(0 == stat)
		{
			switch(c)
			{
				case '=' :
				{
					stat = 2;
					break;
				}
				case '<' :
				{
					break;
				}
				case '>' :
				{
					stat = 10;
					break;
				}
				case '-' :
				{
					stat = 13;
					break;
				}
				case '*' :
				{
					stat = 14;
					break;
				}
				case ':' :
				{
					stat = 15;
					break;
				}
				case '(' :
				{
					stat = 18;
					break;
				}
				case ')' :
				{
					stat = 19;
					break;
				}
				case ';' :
				{
					stat = 20;
					break;
				}
				default 
					stat = 21;
			}
		}
		else
			stat = getStat(stat, c);
		word[index] = c;
}
*/
int main(int argc, char* argv[])
{
	if(2 != argc)
	{
		printf("argument is wrong!");
		return 1;
	}
	char pasName[20] = { 0 };
	char dydName[20] = { 0 };
	char errName[20] = { 0 };
	sprintf(pasName, "%s.pas", argv[1]);
	sprintf(dydName, "%s.dyd", argv[1]);
	sprintf(errName, "%s.err", argv[1]);
	FILE* pasFile = fopen(pasName, "r");
	FILE* dydFile = fopen(dydName, "w+");
	FILE* errFile = fopen(errName, "w+");
	int ret = lex_Analysis(pasFile, dydFile, errFile);
	return 0;

}
