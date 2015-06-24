#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/* 前半部分是词法分析，后半部分是语法分析。
 * 全写到头文件里面了，以后不回了，以后要分头文件和源文件，要不然自己看这都头疼。
 * 所有东西都是尽量按照PPT里面那个文法的状态机做的
 * 语法分析因为不知道文件里都写什么，所有都是空的，也没办法检测错误了。。
 * 词法分析已经把大写字母过滤掉了。
 * 但是因为大部分条件判断都没有else，如果有其他的错误估计也还是检测不出来。。
 */

//判断是否是小写字母
int isA(int c)
{
	if(c >= 'a' && c <= 'z')
		return 1;
	else
		return 0;
}
//判断是否是小写字母或者数字
int isAandN(int c)
{
	if((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		return 1;
	else
		return 0;
}
//判断是否是大写字母（根据要求的词法，大写字母不能识别。之前我没考虑，只能这样修修补补）
int isCapA(int c)
{
	if(c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}
//判断是否是数字
int isN(int c)
{
	if(c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}
//根据每个词的第一个字符选择文法，然后进入状态机
int getState(char c)
{
	//返回值ret是文法状态
	int ret = 0;
	if('\n' == c)
		ret = 0;
	else if(' ' == c || '\t' == c)
		ret = 2;
	else if(isAandN(c))
		ret = 1;
	else if(isN(c))
		ret = 3;
	//此处过滤掉大写字母
	else if(isCapA(c))
		ret = -1;
	else
		switch(c)
		{
			case '=':
				ret = 5;
				break;
			case '-':
				ret = 6;
				break;
			case '*':
				ret = 7;
				break;
			case '(':
				ret = 8;
				break;
			case ')':
				ret = 9;
				break;
			case '<':
				ret = 10;
				break;
			case '>':
				ret = 14;
				break;
			case ':':
				ret = 17;
				break;
			case ';':
				ret = 20;
				break;
			default:
				ret = 21;
		}
	return ret;
}
//每个词都有种别，读入词，然后用getClass判断种别
int getClass(int state, char* word)
{
	int ret = 0;			//返回值ret是种别
	//通过之前的文法状态机的结束状态做预处理，效率会稍有提高
	switch(state)
	{
		case 1:
			if(!strncmp(word, "begin", 5))
				ret = 1;
			else if(!strncmp(word, "end", 3))
				ret = 2;
			else if(!strncmp(word, "integer", 7))
				ret = 3;
			else if(!strncmp(word, "if", 2))
				ret = 4;
			else if(!strncmp(word, "then", 4))
				ret = 5;
			else if(!strncmp(word, "else", 4))
				ret = 6;
			else if(!strncmp(word, "function", 7))
				ret = 7;
			else if(!strncmp(word, "read", 4))
				ret = 8;
			else if(!strncmp(word, "write", 5))
				ret = 9;
			else if(isN(word[0]))
				ret = 10;
			else 
				ret = 11;
		case 5://'='
			ret = 12;
			break;
		case 6://'-'
			ret = 18;
			break;
		case 7://'*'
			ret = 19;
			break;
		case 8://'('
			ret = 21;
			break;
		case 9://')'
			ret = 22;
			break;
		case 10://'<'
			ret = 15;
			break;
		case 11://'<='
			ret = 14;
			break;
		case 12://'<>'
			ret = 13;
			break;
		case 14://'>'
			ret = 17;
			break;
		case 15://'>='
			ret = 16;
			break;
		case 17://:
			break;
		case 18://':='
			ret = 20;
			break;
		case 20://';'
			ret = 23;
			break;
	}
	return ret;
}

//词法分析器的主函数
int lex_Analysis(FILE* pasFile, FILE* dydFile, FILE* errFile)
{
	int line_number = 0;					//记录行号
	int state = 0;						//文法状态机的当前状态
	char* sentence = (char*)malloc(64 * sizeof(char));	//一次读取一行
	char* word = (char*)malloc(20 * sizeof(char));		//每次状态机结束会得到一个词
	memset(sentence, 0, 64 * sizeof(char));
	memset(word, ' ', 16 * sizeof(char));
	word[16] = 0;
	while(NULL != fgets(sentence, 64, pasFile))
	{
		line_number++;
		printf("get sentence: %s\n", sentence);		//所有的printf都是debug的时候用到
//		sleep(1);
		int index = 0;
		int writptr = 0;
		while('\n' != sentence[index])
		{
			writptr = 0;
			state = getState(sentence[index]);
			if(0 == state)				//文件结束符EOF
				break;
			else if(2 == state)			//换行符\n
			{
				index++;
				continue;
			}
			else if(-1 == state)			//大写字母会写入err
			{
				fprintf(errFile, "line: %d, can't recognize %c\n", line_number, sentence[index]);
				fprintf(dydFile, "\n");
				index++;
				continue;
			}
			while(' ' != sentence[index] || '\n' != sentence[index])	
			{
				/*	用状态机读词，
				 *	这样即使不同关键词之间没有空格，
				 *	在词法分析时也会自动分离，
				 *	因为文法都有终结符。
				 *	如（n），会被判断为三个词
				 */
				printf("sentence[%d] is %c, state is %d\n", index, sentence[index], state);
				int isbreak = 0;		//跳出循环标识符，没有空格和换行的情况下，用isbreak判断当前文法是否遇到终结符
				word[writptr] = sentence[index];
				writptr++;
				switch(state)
				{
					case 0:
						break;
					case 1:
						if(!isAandN(sentence[index + 1]))
						{
							printf("should break\n");
							isbreak = 1;		
						}
						break;
					case 3:
						if(!isN(sentence[index + 1]))
							isbreak = 1;
						break;
					case 10:
						if('=' == sentence[index + 1])
							state = 11;
						else if('>' == sentence[index + 1])
							state = 12;
						else
							isbreak = 1;
						break;
					case 14:
						if('=' == sentence[index + 1])
							state = 15;
						else
							isbreak = 1;
						break;
					case 17:
						if('=' == sentence[index + 1])
							state = 18;
						else
						{
							state = -1;
							isbreak = 1;
						}
						break;
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
					case 11:
					case 12:
					case 18:
					case 20:
						isbreak = 1;
						break;
					default:
						state = -1;
						break;
				}
				index++;
				if(1 == isbreak)
					break;
				printf("end loop\n");
			}
			int word_class = getClass(state, word);
			printf("%s%d\n", word, word_class);
			//每次读完一个词，都写入dyd文件，并换行
			fprintf(dydFile, "%s%d\n", word, word_class);
			memset(word, ' ', 16 * sizeof(char));
			word[16] = 0;
		}
		//读完一行写入一个换行符
		fprintf(dydFile, "EOLN            24\n");
	}
	//文件全部读完写入文件终结符
	fprintf(dydFile, "EOF             25");
	printf("lex_analysis sucess!\n");
	//释放内存
	free(sentence);
	free(word);
	return 0;
}
/*	以上是词法分析内容，已经全部编译运行过。
 *	下面是语法分析的内容，只虽然也编译运行了，
 *	但是写代码的时候不清楚几个文件都是干嘛的，
 *	所以就没有fprintf，现在也没有思路。。。
 */

//每次读取一个单词，并且读出它的种别，设计有些复杂，因为之前一行有多个词，
//但是改过之后的词法分析每行只有一个词，所以其实可以用一个sscanf搞定。。。。我懒，，
int getWord(char* source, char* des, int* word_class)
{
	if(NULL == source || NULL == des || NULL == word_class)
		return -1;
	int index = 0;
	while(' ' != source[index])
	{
		des[index] = source[index];
		index++;
	}
	if(strncmp(source, "EOLN", 4))
		return 1;
	if(strncmp(source, "EOF", 3))
		return 2;
	scanf(source + 16, "%d", word_class);
	return 0;
}

//从begin开始到end,判断一个完整程序段的语法，
//如果内部定义函数的话会变成递归调用
void block(FILE* dydFile, FILE* dysFile, FILE* varFile, FILE* proFile, char* sentence)
{
	char* word = (char*)malloc(16 * sizeof(char));
	int block_state = 0;
	int word_class = 0;
	int isEnd = 0;
	do
	{
		memset(word, 0, 16 * sizeof(char));
		int ret = getWord(sentence, word, &word_class);
		if(1 == ret)
			continue;
		if(2 == ret)
			printf("error\n");
		switch(block_state)
		{
			case 0:
				if(1 == word_class)
					block_state = 1;
				else
					printf("no begin! error\n");
				break;
			case 1:
				if(3 == word_class)
					block_state = 2;
				else if(2 == word_class)
					isEnd = 1;
				else
					printf("error: expected integer\n");
				break;
			case 2:
				if(10 == word_class)
					block_state = 3;
				else if(7 == word_class)
					block_state = 3;
				else
					printf("error: expected val name or function\n");
				break;
			case 3:
				if(23 == word_class)
					block_state = 1;
				else
					printf("error: expected ';'\n");
			case 4:
				if(10 == word_class)
					block_state = 5;
				else
					printf("error: expected val name\n");
				break;
			case 5:
				if(21 == word_class)
					block_state = 6;
				else
					printf("error: expected '('\n");
				break;
			case 6:
				if(10 == word_class)
					block_state = 7;
				else
					printf("error:expected val name\n");
				break;
			case 7:
				if(22 == word_class)
					block_state = 8;
				else
					printf("error: expected ')'\n");
				break;
			case 8:
				if(23 == word_class)
				{
					//如果定义函数的话这里递归调用。
					block(dydFile, dysFile, varFile, proFile, sentence);
					block_state = 3;
				}
				else
					printf("error: expected ';'\n");
				break;
		}
		memset(sentence, 0, 20 * sizeof(char));
		if(isEnd)
			break;
	}while(NULL != fgets(sentence, 20, dydFile));
	free(word);
}

//这个注释掉的函数我也忘了是干嘛用的了。。。。
/*
void assig(FILE* dydFile, FILE* dysFile, FILE* varFile, FILE* proFile)
{
	char* sentence = (char*)malloc(20 * sizeof(char));
	char* word = (char*)malloc(16 * sizeof(char));
	memset(sentence, 0, 20 * sizeof(cahr));
	int word_class;
	while(NULL != fgets(dydFile, 20, sentence))
	{
		memset(word, 0, 16 * sizeof(char));
		int ret = getWord(sentence, word, &word_class, &index);
		if(1 == ret)
			continue;
		if(2 == ret)
		{
			printf("error\n");
			return;
		}
		if(20 == word_class)
			algo();
		memset(sentence, 20, 20 * sizeof(char));
	}
}
*/

//算数表达式的语法分析，
//算数表达式可能通过（）嵌套，
//所以也有可能递归调用
void arith_expre(FILE* dydFile, FILE* dysFile, FILE* varFile, FILE* proFile)
{
	int isEnd = 0;
	int arith_state = 0;
	int word_class = 0;
	char* word = (char*)malloc(16 * sizeof(char));
	char* sentence = (char*)malloc(20 * sizeof(char));
	memset(sentence, 0, 20 * sizeof(char));
	while(NULL != fgets(sentence, 20, dydFile))
	{
		memset(word, 0, 16 * sizeof(char));
		getWord(sentence, word, &word_class);
		switch(arith_state)
		{
			case 0:
				if(10 == word_class || 11 == word_class)
					arith_state = 3;
				else if(10 == word_class)
					arith_state = 1;
				break;
			case 1:
				if(21 == word_class)
				{
					//如果是'（'则递归调用，结束后状态值设为2
					arith_expre(dydFile, dysFile, varFile, proFile);
					arith_state = 2;
				}
				break;
			case 2:
				//既然有'('肯定有'）'
				if(22 == word_class)
					arith_state = 3;
				break;
			case 3:
				//即使消除左递归了还是要不停的执行状态机 ，直到';'或者‘then’
				if(19 == word_class || 18 == word_class)
					arith_state = 0;
				else if(23 == word_class ||5 == word_class)
					isEnd = 1;
				break;
		}
		memset(sentence, 0, 20 * sizeof(char));
		if(isEnd)
			break;
	}
	free(word);
	free(sentence);
}

//执行语句
//执行语句但疼，有时候跳到算数表达式，有时候跳到条件表达式
//条件表达式还要再跳到算数表达式或者执行表达式。。
void exec(FILE* dydFile, FILE* dysFile, FILE* varFile, FILE* proFile, char* sentence)
{
	char* word = (char*)malloc(16 * sizeof(char));
	int word_class = 0;
	int exec_state = 0;
	int isEnd = 0;
	do
	{
		memset(word, 0 , 16 * sizeof(char));
		int ret = getWord(sentence, word, &word_class);
		if(1 == ret)
			continue;
		if(2 == ret)
		{
			printf("error\n");
			return ;
		}
		switch(exec_state)
		{
			case 0:
				//读语句和写语句在文法上类似，所以就放到一起
				if(8 == word_class || 9 == word_class)
					exec_state = 10;
				//赋值语句肯定是以变量，即标识符为开始
				if(10 == word_class)
//					assig(dydFile, dysFile, varFile, proFile, sentence);
					exec_state = 2;
				//条件语句开头是if。
				if(4 == word_class)
					exec_state = 30;	
				if(2 == word_class)
					isEnd = 1;
				exec_state = 1;
				break;
			case 10:  //读语句和写语句后面都是（标识符）
				 //先看‘（’
				if(21 == word_class)
					exec_state = 11;
				break;
			case 11: //然后是标识符
				if(10 == word_class)
					exec_state = 12;
				break;
			case 12: //最后是‘）’，读写语句结束
				if(22 == word_class)
					exec_state = 0;
				break;
			case 2:	//赋值语句的文法，有：=，然后跳转到算数表达式
				if(20 == word_class)
				{
					//算数表达式
					arith_expre(dydFile, dysFile, varFile, proFile);
					exec_state = 0;
				}
				break;
			case 30://条件表达式，也要跳到算数表达式
				if(11 < word_class && 18 > word_class)
				{
					arith_expre(dydFile, dysFile, varFile, proFile);
					exec_state = 31;
				}
				break;
			case 31://then
				if(5 == word_class)
				{
					exec(dydFile, dysFile, varFile, proFile, sentence);
					exec_state = 32;
				}
				break;
			case 32://else
				if(6 == word_class)
				{
					exec(dydFile, dydFile, varFile, proFile, sentence);
					exec_state = 0;
				}
				break;
		}
		memset(sentence, 0, 20 * sizeof(char));
		if(isEnd)
			break;
	}while(NULL != fgets(sentence, 20, dydFile));
	free(word);
}

//语法分析的主函数
//这个主函数其实价值已经不大了，
//基本全被包含到block里了。
//但是有个类似main函数的判断感觉上还是好一点。就没想改了。
int gram_analysis(FILE* dydFile, FILE* dysFile, FILE* varFile, FILE* proFile)
{
	char* sentence = (char*)malloc(20 * sizeof(char));
	char* word = (char*)malloc(16 * sizeof(char));
	memset(sentence, 0, 20 * sizeof(char));
	int word_class = 0;
	int main_state = 0;
	while(NULL != fgets(sentence, 20, dydFile))
	{
		memset(word, 0, 16 * sizeof(char));
		int state = 0;
		state = getWord(sentence, word, &word_class);
		if(1 == state)		//换行符
			continue;
		if(2 == state)		//结束符
			break;
		if(!state && !main_state)
		{
			//都是从begin开始的，程序段的文法
			//先是说明语句表
			block(dydFile, dysFile, varFile, proFile, sentence);
			main_state = 1;
		}
		else if(!state && main_state)
			//然后是执行语句表
			exec(dydFile, dysFile, varFile, proFile, sentence);
		memset(sentence, 0, 20 * sizeof(char));
	}
	free(sentence);
	free(word);
	return 0;
}
