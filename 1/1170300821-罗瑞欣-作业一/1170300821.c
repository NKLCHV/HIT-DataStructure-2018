#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct goods
{
	int mark;                     //���
	char trade[12];
	char name[12];
	int number;                   //����
	int money;                    //�۸�
	struct goods *pNext;
};

typedef struct goods Goods;

Goods *Creat();		//��������Ʒ�����ͷ
Goods *Delete(Goods *phead, int numSelect);		//ɾ��Ԫ��
Goods *Edit(Goods *phead, int numSelect);		//�޸���Ʒ��Ϣ
Goods *Read();		//��ȡ�ļ�
Goods *ph = NULL;

int Menu();

void Add(Goods *phead);			//����Ԫ��
void Show(Goods *phead);		//��ʾ������Ʒ
void Save(Goods *phead);		//���浽�ļ�
void FindGoods(Goods *phead, int number);		//������Ʒ
void Sort(Goods * head);		//ð������

int main()
{
	int choise;
	int number;

	while (1)			//ִ�г���
	{
		choise = Menu();		//��ʾ�˵�����ȡѡ��
		switch (choise)
		{

		case 1:
			ph = Read();		//��ȡ�����ļ�
			system("cls");
			printf("--------------------------------------------------------------------");
			printf("\n �Ѿ����������ļ�\n");
			break;

		case 2:
			Add(ph);		//����Ԫ��
			system("cls");
			Show(ph);		//��ʾ������Ʒ��Ϣ
			break;

		case 3:
			system("cls");
			Show(ph);
			if (ph != NULL)
			{
				printf("\n ��������Ҫ�޸ĵ���Ʒ���:");
				scanf("%d", &number);
				ph = Edit(ph, number);		//�޸���Ϣ
			}
			Sort(ph);		//���޸ĺ����Ʒ��Ϣ��������
			Show(ph);
			break;

		case 4:
			printf("\n ��������Ҫɾ������Ʒ���:");
			scanf("%d", &number);
			ph = Delete(ph, number);		//ɾ��ĳ����Ʒ
			break;

		case 5:
			system("cls");
			Show(ph);                       //��ʾ��Ϣ
			break;

		case 6:
			Save(ph);						//������Ϣ
			break;

		case 7:
			printf("\n �������ѯ��Ʒ����ţ�");
			scanf("%d", &number);
			system("cls");
			FindGoods(ph, number);			//������Ʒ
			break;

		case 8:
			if (ph == NULL)
			{
				ph = Creat();
				system("cls");			//�½�һ����Ʒ�����ͷ
				Show(ph);
			}
			else
			{
				system("cls");
				printf("--------------------------------------------------------------------");
				printf("\n �����Ѿ����ļ�����\n");
			}
			break;

		case 0:
			exit(0);				//�˳�

		default:
			system("pause");
			system("cls");
			printf("--------------------------------------------------------------------");
			printf("\n ��������ѡ�� \n");
			break;
		}
	}
	return 0;
}

int Menu()					//��ӡ�˵���������ѡ����
{
	int select;
	_flushall();
	printf("--------------------------------------------------------------------");
	printf("\n                         ��Ʒ����ϵͳ                             ");
	printf("\n -------------------------------------------------------------------- ");
	printf("\n  1.���� 2.��� 3.�޸� 4.ɾ�� 5.�б� 6.���� 7.���� 8.�½�  0.�˳� ");
	printf("\n --------------------------------------------------------------------");
	printf("\n ������ѡ�");
	scanf("%d", &select);
	return select;
}

void Show(Goods *phead)			//��ʾ������Ʒ��Ϣ
{
	Goods *pnum_c;
	int numtemp = 1;
	pnum_c = phead;

	if (pnum_c == NULL)
	{
		printf(" --------------------------------------------------------------------");
		printf("\n ����Ϊ�ջ�û������\n");
	}
	else
	{
		printf(" ___________________________________________________________________\n");
		printf("\n      ���      Ʒ��      ����        ����       ����      \n\n");
		do
		{
			pnum_c->mark = numtemp++;		//�ڱ�����ͬʱ������Ʒ��Ÿ�ֵ���򻯲���Ҫ����
			printf("     %3d %10s %10s    %6d %10d \n", pnum_c->mark, pnum_c->trade, pnum_c->name, pnum_c->money, pnum_c->number);
			pnum_c = pnum_c->pNext;
		} while (pnum_c != NULL);
	}
}

Goods *Creat(void)			//��������Ʒ�����ͷ
{
	Goods *ph = NULL, *p1 = NULL, *p2 = NULL;
	p1 = (Goods *)malloc(sizeof(Goods));		//�����ڴ�

	if (p1 == NULL)		//�����Ƿ�ȫ
	{
		printf("\n �������ݿⲻ�ɹ��������ԣ�\n");
	}
	else			//��������
	{
		p2 = p1;
		ph = p1;
		p2->pNext = NULL;
		getchar();
		printf("\n ��������ƷƷ��:");
		scanf("%s", p1->trade);
		printf("\n ��������Ʒ����:");
		scanf("%s", p1->name);
		printf("\n ��������Ʒ���ۺ�����:");
		scanf("%d %d", &p1->money, &p1->number);
		_flushall();
	}
	return(ph);
}

Goods *Delete(Goods *phead, int num)	//ɾ��ĳ���ڵ�
{
	Goods *p1 = NULL, *p2 = NULL;
	int j = 0;
	p1 = phead;
	if (num != 1)
	{
		if (phead == NULL)			//��ȫ���
		{
			printf("\n ����Ϊ��û�����ݿ���ɾ����\n");
		}
		else
		{
			while (p1->pNext != NULL && j < num - 2)
			{
				++j;
				p1 = p1->pNext;			//��ָ���ƶ���Ŀ��λ��
			}
			if (p1->pNext == NULL || j > num - 2) return 0;
			p2 = p1->pNext;				//�޸�ָ�룬��Ŀ��ڵ�ӱ����޳�
			p1->pNext = p2->pNext;
			free(p2);
		}
	}
	else
	{
		p2 = p1->pNext; phead = p2; free(p1);//�޸�ָ�룬��Ŀ��ڵ�ӱ����޳�
	}
	system("cls");
	printf("--------------------------------------------------------------------");
	printf("\n �Ѿ�ɾ����Ӧ��Ʒ��Ϣ!\n");
	return phead;
}

Goods *Edit(Goods *phead, int numSelect)		//�޸�ĳ����Ʒ����Ϣ
{
	Goods *p1 = NULL, *p2 = NULL;
	int j = 0;
	p1 = phead;
	if (numSelect != 1)
	{
		if (phead == NULL)
		{
			printf("\n  ����Ϊ��! \n");
		}
		else			//Ѱ��Ŀ��ڵ�
		{
			while (p1->pNext != NULL && j < numSelect - 2)
			{
				++j;
				p1 = p1->pNext;
			}
			if (p1->pNext == NULL || j > numSelect - 2) return 0;
			p2 = p1->pNext;
		}
	}
	else
	{
		p2 = p1;
	}
	printf("\n ������%s %s���µ��ۺ�������:", p2->trade, p2->name);//�޸���Ϣ
	scanf("%d %d", &p2->money, &p2->number);
	system("cls");
	printf("--------------------------------------------------------------------");
	printf("\n �Ѿ��ɹ��޸���Ӧ��Ʒ��Ϣ��\n");
	return phead;
}

void FindGoods(Goods *phead, int number)//������Ʒ
{
	Goods *pnum_c = NULL;
	int temp = 0;
	int numtemp = 1;

	pnum_c = phead;

	if (pnum_c == NULL)
	{
		printf("--------------------------------------------------------------------");
		printf("\n ����Ϊ�գ�\n");
	}
	else
	{
		printf("_________________________________________________________________________\n");
		printf("\n    ���     Ʒ��??    ����   ����      ����  \n\n");
		while ((pnum_c != NULL) && (temp != 1))//����ű�������
		{
			if (pnum_c->mark == number)
			{
				printf("     %3d %10s %10s %6d %10d \n", pnum_c->mark, pnum_c->trade, pnum_c->name, pnum_c->money, pnum_c->number);
				temp = 1;
			}
			pnum_c = pnum_c->pNext;
		}
		if (!temp)
		{
			system("cls");
			printf("--------------------------------------------------------------------");
			printf("\n û���ҵ���Ӧ����Ʒ��\n");
		}
	}
}

void Add(Goods *phead)				//���ӽڵ�
{
	Goods *p1 = NULL, *p2 = NULL, *pInsert = NULL, *p = NULL;
	int payInsert;
	p = p2 = p1 = phead;
	if (p2 == NULL) { printf("\n����Ϊ��\n"); }
	else			//�����½ڵ����Ϣ
	{
		pInsert = (Goods *)malloc(sizeof(Goods));
		_flushall();
		printf("\n ��������ƷƷ��:");
		scanf("%s", pInsert->trade);
		printf("\n ��������Ʒ����:");
		scanf("%s", pInsert->name);
		printf("\n ��������Ʒ���ۺ�����:");
		scanf("%d %d", &pInsert->money, &pInsert->number);
		_flushall();
		payInsert = pInsert->money;
		if ((p->pNext == NULL) && (payInsert >= p2->money))//�Ƚϼ۸񣬽��½ڵ�����ĺ���λ��
		{
			pInsert->pNext = NULL;
			p->pNext = pInsert;
		}
		else {
			if (payInsert <= p2->money)
			{
				pInsert->pNext = p1;
				ph = pInsert;
			}
			else
			{
				while ((payInsert > p2->money) && (p2->pNext != NULL)) { p = p2; p2 = p2->pNext; }
				if (payInsert < p2->money)
				{
					p2 = p;
					p1 = p->pNext;
					p2->pNext = pInsert;
					pInsert->pNext = p1;
				}
				else
				{
					p = p->pNext;
					p->pNext = pInsert; p = p->pNext;
					p->pNext = NULL;
				}
			}
		}
	}
}

void Save(Goods *phead)			//�����浽�ļ���
{
	FILE *fp = NULL;
	char fileName[10];
	Goods *p1 = phead;
	int listLen = 0;

	if (phead == NULL)
	{
		printf("\n ����Ϊ��û�����ݿ��Ա��棡\n");
	}
	else
	{
		while (p1)
		{
			p1 = p1->pNext;
			listLen++;
		}

		printf("\n �����뱣���ļ���(*.txt):");
		_flushall();
		scanf("%s", fileName);			//���ļ�����
		if ((fp = fopen(fileName, "w")) == NULL)
		{
			printf("\n ���ļ�ʧ�ܣ�\n");
			exit(0);
		}
		p1 = phead;
		while (p1 != NULL)
		{								//��һ����ʽ����˳�򱣴�����
			if (!fprintf(fp, " %s %s %d %d \n", p1->trade, p1->name, p1->money, p1->number))
			{
				printf("\n �����ļ�����\n");
			}
			p1 = p1->pNext;
		}
		fclose(fp);
	}
	system("cls");
	printf("--------------------------------------------------------------------");
	printf("\n �����ļ��Ѿ����棡\n");
}

Goods *Read(void)			//��ȡ�ļ��е�����
{
	FILE *fp = NULL;
	char fileName[10];
	Goods *p1 = NULL, *p2 = NULL, *ph = NULL;

	printf("\n ��������Ҫ�򿪵����ݿ��ļ���(*.txt):");
	_flushall();
	scanf("%s", fileName);

	if ((fp = fopen(fileName, "r")) == NULL)
	{
		printf("\n ���ļ�ʧ�ܣ�\n\n\n");
		exit(0);
	}

	p1 = (Goods *)malloc(sizeof(Goods));
	p2 = p1;
	ph = p1;
	ph->pNext = NULL;

	while (!feof(fp))				//����ʽ���ζ�ȡ����
	{
		if (!fscanf(fp, " %s %s %d %d \n", &p1->trade, &p1->name, &p1->money, &p1->number))
			printf("\n �����ļ�����!\n");

		p2 = p1;
		p1 = (Goods *)malloc(sizeof(Goods));
		p2->pNext = p1;

	}
	p2->pNext = NULL;
	free(p1);
	p1 = NULL;
	return ph;
}

void Sort(Goods * head)			//ð�����򣬶�����ڵ㰴�۸�����
{
	//printf("d");
	int t = 0;
	char tt[12] = { 0 };
	for (Goods* temp = head; temp->pNext != NULL; temp = temp->pNext)
	{
		for (Goods* p = temp->pNext; p->pNext != NULL; p = p->pNext)
		{
			if (p->money < temp->money)
			{
				t = p->money;
				p->money = temp->money;
				temp->money = t;

				t = p->number;
				p->number = temp->number;
				temp->number = t;

				strcpy(tt, p->name);
				strcpy(p->name, temp->name);
				strcpy(temp->name, tt);

				strcpy(tt, p->trade);
				strcpy(p->trade, temp->trade);
				strcpy(temp->trade, tt);
			}
		}
	}
}