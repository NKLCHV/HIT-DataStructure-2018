#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024

double aa, ii=0,bb;
double a[30];
char b[30];
int xi = 29, xj = 0;

void InNum(double *numb, int * topn, double num);                //数压栈
void InOper(char * oper, int *topo, char ch);                  //符号压栈
int CompOper(char *oper, int *topo, char ch);                   //比较优先级
void Calculate(double *numb, char *oper, int *topn, int *topo);  //计算

int main()
{
	double numb[MAX_SIZE] = { 0 };
	char oper[MAX_SIZE] = { 0 };

	int topo = -1;
	int  topn = -1;

	char *str = (char *)malloc(sizeof(char) * 100);
	scanf("%s", str);

	char* temp;
	char dest[1024];
	double number = 0;
	ii = 0;
	int i = 0, k = 0;
	while (*str != '\0')
	{
		temp = dest;

		if (*str == '-' && *(str - 1) == '(')
		{
			*temp = *str;
			str++;
			temp++;
		}

		while ((*str >= '0' && *str <= '9') || *str == '.')
		{
			*temp = *str;
			str++;
			temp++;
		}
		if (*str != '(' && *(temp - 1) != '\0')
		{

			*temp = '\0';
			number = atof(dest);
			if (ii == 0)
				printf("%.2lf ",number);
			ii++;
			bb = number;
			InNum(numb, &topn, number);
		}

		while (1)
		{
			i = CompOper(oper, &topo, *str);

			if (i == 0)
			{
				InOper(oper, &topo, *str);
				break;
			}
			else if (i == 1)
			{
				str++;
			}
			else if (i == -1)
			{
				Calculate(numb, oper, &topn, &topo);
			}
		}

		str++;
	}

	/*
	for(int i=xi+1;i<30;i++)
		printf("%.2lf ",a[i]);
	printf("%.2lf ",aa);
	for(int j=0;j<=xj;j++)
		printf("%c ",b[j]);
	*/
	printf("\nnum = %lf\n", numb[0]);

	//system("pause");
	return 0;
}

void InNum(double *numb, int * topn, double num)
{
	(*topn)++;
	numb[*topn] = num;
}

void InOper(char * oper, int *topo, char ch)
{
	(*topo)++;
	oper[*topo] = ch;
}

int CompOper(char *oper, int *topo, char ch)
{

	if ((oper[*topo] == '-' || oper[*topo] == '+') && (ch == '*' || ch == '/' || ch == '%'))
	{
		return 0;
	}
	else if (*topo == -1 || ch == '(' || (oper[*topo] == '(' && ch != ')'))
	{
		return 0;
	}
	else if (oper[*topo] == '(' && ch == ')')
	{
		(*topo)--;
		return 1;
	}
	else
	{
		return -1;
	}
}

void Calculate(double *numb, char *oper, int *topn, int *topo)
{
	if (oper[*topo] == '+' || oper[*topo] == '-' || oper[*topo] == '*' || oper[*topo] == '/' || oper[*topo] == '%')
	{
		if (ii == 1)
			printf("%.2lf ", aa);
		else
		{
			printf("%.2lf ", bb);
		}
			printf("%c ", oper[*topo]);

		/*
		b[xj]=oper[*topo];
		xj++;
		a[xi]=numb[*topn-1];
		xi--;
		*/
	}

	if (oper[*topo] == '+')
		numb[*topn - 1] = numb[*topn] + numb[*topn - 1];
	else if (oper[*topo] == '-')
		numb[*topn - 1] = numb[*topn - 1] - numb[*topn];
	else if (oper[*topo] == '*')
		numb[*topn - 1] = numb[*topn - 1] * numb[*topn];
	else if (oper[*topo] == '/')
		numb[*topn - 1] = numb[*topn - 1] / numb[*topn];
	else if (oper[*topo] == '%')
		numb[*topn - 1] = (((int)(numb[*topn - 1] * 10)) % ((int)(numb[*topn] * 10))) / 10.0;

	(*topn)--;
	(*topo)--;
}
