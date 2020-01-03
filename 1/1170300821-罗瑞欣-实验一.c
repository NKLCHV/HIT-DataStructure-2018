#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024

double aa, ii = 0, bb;   //�����ں�׺���ʽ����ʾ��һ������

void InNum(double *numb, int * topn, double num);                //��ѹջ
void InOper(char * oper, int *topo, char ch);                  //����ѹջ
int CompOper(char *oper, int *topo, char ch);                   //�Ƚ����ȼ�
void Calculate(double *numb, char *oper, int *topn, int *topo);  //����

int main()
{
	while (1) 
	{
		double numb[MAX_SIZE] = { 0 };
		char oper[MAX_SIZE] = { 0 };

		int topo = -1;     //��ʼ������ջ�ͷ���ջ��ջ֡
		int  topn = -1;

		char *str = (char *)malloc(sizeof(char) * 100);
		scanf("%s", str);   //�����ڴ沢���������ַ���

		char* temp;
		char *tep=str;      //��Ƕ����ַ�����ʼλ��
		char dest[1024];    //�����ʾ���ֵ��ַ���������ת��
		double number = 0;
		ii = 0;             //��ǵ�һ�����֣�������ʾ��׺���ʽ
		int i = 0, k = 0;
		while (*str != '\0')
		{
			temp = dest;

			if (*str == '-' && (*(str - 1) == '(' || str==tep))   //�ж��Ƿ��Ǹ��������ǵ�һ�����Ǹ������������
			{
				*temp = *str;
				str++;
				temp++;
			}

			while ((*str >= '0' && *str <= '9') || *str == '.')  //�ж��Ƿ������֣�������С�������
			{
				*temp = *str;
				str++;
				temp++;
			}
			if (*str != '(' && *(temp - 1) != '\0')
			{
				*temp = '\0';              
				number = atof(dest);		//����stdlib.h�еĺ���atof���Զ����ַ���ת����double����������
				if (ii == 0)
					printf("%.2lf ", number);  //��׺���ʽ��ӡ��һ������
				ii++;
				bb = number;
				InNum(numb, &topn, number);    //������ѹ��ջ
			}

			while (1)                         //�ж����ֳ�ջ�ͷ�����ջ����
			{
				i = CompOper(oper, &topo, *str);  //�ж��������ȼ�

				if (i == 0)
				{
					InOper(oper, &topo, *str);    //������ջ
					break;
				}
				else if (i == 1)
				{
					str++;
				}
				else if (i == -1)
				{
					Calculate(numb, oper, &topn, &topo);  //���м��㣬ͬʱ��ӡ���㲿�ֺ�׺���ʽ
				}
			}

			str++;
		}

		printf("\nnum = %lf\n", numb[0]);    //��ʾ������
	}
	system("pause");
	return 0;
}

void InNum(double *numb, int * topn, double num)  //������ջ
{
	(*topn)++;
	numb[*topn] = num;
}

void InOper(char * oper, int *topo, char ch)    //�������ջ
{
	(*topo)++;
	oper[*topo] = ch;
}

int CompOper(char *oper, int *topo, char ch)  //�Ƚ��������ȼ����������ţ�
{
	if ((oper[*topo] == '-' || oper[*topo] == '+') && (ch == '*' || ch == '/' || ch == '%'))  //��������������ȼ�Ϊ0
	{
		return 0;
	}
	else if (*topo == -1 || ch == '(' || (oper[*topo] == '(' && ch != ')'))  //���������ţ����ȼ�Ϊ0
	{
		return 0;
	}
	else if (oper[*topo] == '(' && ch == ')')		//���������ţ�ͬʱ���������ţ����ȼ�Ϊ1
	{
		(*topo)--;
		return 1;
	}
	else               //����������ȼ�Ϊ-1
	{
		return -1;
	}
}
