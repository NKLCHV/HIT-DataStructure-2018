#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024

double aa, ii = 0, bb;   //用于在后缀表达式中显示第一个数字

void InNum(double *numb, int * topn, double num);                //数压栈
void InOper(char * oper, int *topo, char ch);                  //符号压栈
int CompOper(char *oper, int *topo, char ch);                   //比较优先级
void Calculate(double *numb, char *oper, int *topn, int *topo);  //计算

int main()
{
	while (1) 
	{
		double numb[MAX_SIZE] = { 0 };
		char oper[MAX_SIZE] = { 0 };

		int topo = -1;     //初始化数字栈和符号栈的栈帧
		int  topn = -1;

		char *str = (char *)malloc(sizeof(char) * 100);
		scanf("%s", str);   //申请内存并存入输入字符串

		char* temp;
		char *tep=str;      //标记读入字符串起始位置
		char dest[1024];    //存入表示数字的字符串，用于转换
		double number = 0;
		ii = 0;             //标记第一个数字，用于显示后缀表达式
		int i = 0, k = 0;
		while (*str != '\0')
		{
			temp = dest;

			if (*str == '-' && (*(str - 1) == '(' || str==tep))   //判断是否是负数，考虑第一个数是负数和其他情况
			{
				*temp = *str;
				str++;
				temp++;
			}

			while ((*str >= '0' && *str <= '9') || *str == '.')  //判断是否是数字，并考虑小数的情况
			{
				*temp = *str;
				str++;
				temp++;
			}
			if (*str != '(' && *(temp - 1) != '\0')
			{
				*temp = '\0';              
				number = atof(dest);		//利用stdlib.h中的函数atof，自动将字符串转换成double的数据类型
				if (ii == 0)
					printf("%.2lf ", number);  //后缀表达式打印第一个数字
				ii++;
				bb = number;
				InNum(numb, &topn, number);    //将数字压入栈
			}

			while (1)                         //判断数字出栈和符号入栈条件
			{
				i = CompOper(oper, &topo, *str);  //判断运算优先级

				if (i == 0)
				{
					InOper(oper, &topo, *str);    //符号入栈
					break;
				}
				else if (i == 1)
				{
					str++;
				}
				else if (i == -1)
				{
					Calculate(numb, oper, &topn, &topo);  //进行计算，同时打印运算部分后缀表达式
				}
			}

			str++;
		}

		printf("\nnum = %lf\n", numb[0]);    //显示计算结果
	}
	system("pause");
	return 0;
}

void InNum(double *numb, int * topn, double num)  //数字入栈
{
	(*topn)++;
	numb[*topn] = num;
}

void InOper(char * oper, int *topo, char ch)    //运算符入栈
{
	(*topo)++;
	oper[*topo] = ch;
}

int CompOper(char *oper, int *topo, char ch)  //比较运算优先级（包括括号）
{
	if ((oper[*topo] == '-' || oper[*topo] == '+') && (ch == '*' || ch == '/' || ch == '%'))  //遇到运算符，优先级为0
	{
		return 0;
	}
	else if (*topo == -1 || ch == '(' || (oper[*topo] == '(' && ch != ')'))  //遇到左括号，优先级为0
	{
		return 0;
	}
	else if (oper[*topo] == '(' && ch == ')')		//遇到有括号，同时存在左括号，优先级为1
	{
		(*topo)--;
		return 1;
	}
	else               //其他情况优先级为-1
	{
		return -1;
	}
}
