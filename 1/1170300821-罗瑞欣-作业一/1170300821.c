#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct goods
{
	int mark;                     //编号
	char trade[12];
	char name[12];
	int number;                   //数量
	int money;                    //价格
	struct goods *pNext;
};

typedef struct goods Goods;

Goods *Creat();		//建立新商品链表表头
Goods *Delete(Goods *phead, int numSelect);		//删除元素
Goods *Edit(Goods *phead, int numSelect);		//修改商品信息
Goods *Read();		//读取文件
Goods *ph = NULL;

int Menu();

void Add(Goods *phead);			//插入元素
void Show(Goods *phead);		//显示所有商品
void Save(Goods *phead);		//保存到文件
void FindGoods(Goods *phead, int number);		//查找商品
void Sort(Goods * head);		//冒泡排序

int main()
{
	int choise;
	int number;

	while (1)			//执行程序
	{
		choise = Menu();		//显示菜单，读取选择
		switch (choise)
		{

		case 1:
			ph = Read();		//读取已有文件
			system("cls");
			printf("--------------------------------------------------------------------");
			printf("\n 已经读入数据文件\n");
			break;

		case 2:
			Add(ph);		//插入元素
			system("cls");
			Show(ph);		//显示所有商品信息
			break;

		case 3:
			system("cls");
			Show(ph);
			if (ph != NULL)
			{
				printf("\n 请输入您要修改的商品编号:");
				scanf("%d", &number);
				ph = Edit(ph, number);		//修改信息
			}
			Sort(ph);		//将修改后的商品信息重新排序
			Show(ph);
			break;

		case 4:
			printf("\n 请输入您要删除的商品编号:");
			scanf("%d", &number);
			ph = Delete(ph, number);		//删除某个商品
			break;

		case 5:
			system("cls");
			Show(ph);                       //显示信息
			break;

		case 6:
			Save(ph);						//保存信息
			break;

		case 7:
			printf("\n 请输入查询商品的序号：");
			scanf("%d", &number);
			system("cls");
			FindGoods(ph, number);			//查找商品
			break;

		case 8:
			if (ph == NULL)
			{
				ph = Creat();
				system("cls");			//新建一个商品链表表头
				Show(ph);
			}
			else
			{
				system("cls");
				printf("--------------------------------------------------------------------");
				printf("\n 数据已经从文件读入\n");
			}
			break;

		case 0:
			exit(0);				//退出

		default:
			system("pause");
			system("cls");
			printf("--------------------------------------------------------------------");
			printf("\n 请您重新选择！ \n");
			break;
		}
	}
	return 0;
}

int Menu()					//打印菜单，并传回选择结果
{
	int select;
	_flushall();
	printf("--------------------------------------------------------------------");
	printf("\n                         商品管理系统                             ");
	printf("\n -------------------------------------------------------------------- ");
	printf("\n  1.载入 2.添加 3.修改 4.删除 5.列表 6.保存 7.查找 8.新建  0.退出 ");
	printf("\n --------------------------------------------------------------------");
	printf("\n 请输入选项：");
	scanf("%d", &select);
	return select;
}

void Show(Goods *phead)			//显示所有商品信息
{
	Goods *pnum_c;
	int numtemp = 1;
	pnum_c = phead;

	if (pnum_c == NULL)
	{
		printf(" --------------------------------------------------------------------");
		printf("\n 数据为空或没有数据\n");
	}
	else
	{
		printf(" ___________________________________________________________________\n");
		printf("\n      编号      品牌      名称        单价       数量      \n\n");
		do
		{
			pnum_c->mark = numtemp++;		//在遍历的同时，给商品编号赋值，简化不必要过程
			printf("     %3d %10s %10s    %6d %10d \n", pnum_c->mark, pnum_c->trade, pnum_c->name, pnum_c->money, pnum_c->number);
			pnum_c = pnum_c->pNext;
		} while (pnum_c != NULL);
	}
}

Goods *Creat(void)			//建立新商品链表表头
{
	Goods *ph = NULL, *p1 = NULL, *p2 = NULL;
	p1 = (Goods *)malloc(sizeof(Goods));		//申请内存

	if (p1 == NULL)		//检验是否安全
	{
		printf("\n 创建数据库不成功，请重试！\n");
	}
	else			//填入数据
	{
		p2 = p1;
		ph = p1;
		p2->pNext = NULL;
		getchar();
		printf("\n 请输入商品品牌:");
		scanf("%s", p1->trade);
		printf("\n 请输入商品名称:");
		scanf("%s", p1->name);
		printf("\n 请输入商品单价和数量:");
		scanf("%d %d", &p1->money, &p1->number);
		_flushall();
	}
	return(ph);
}

Goods *Delete(Goods *phead, int num)	//删除某个节点
{
	Goods *p1 = NULL, *p2 = NULL;
	int j = 0;
	p1 = phead;
	if (num != 1)
	{
		if (phead == NULL)			//安全检查
		{
			printf("\n 数据为空没有数据可以删除！\n");
		}
		else
		{
			while (p1->pNext != NULL && j < num - 2)
			{
				++j;
				p1 = p1->pNext;			//把指针移动到目标位置
			}
			if (p1->pNext == NULL || j > num - 2) return 0;
			p2 = p1->pNext;				//修改指针，将目标节点从表中剔除
			p1->pNext = p2->pNext;
			free(p2);
		}
	}
	else
	{
		p2 = p1->pNext; phead = p2; free(p1);//修改指针，将目标节点从表中剔除
	}
	system("cls");
	printf("--------------------------------------------------------------------");
	printf("\n 已经删除相应商品信息!\n");
	return phead;
}

Goods *Edit(Goods *phead, int numSelect)		//修改某个商品的信息
{
	Goods *p1 = NULL, *p2 = NULL;
	int j = 0;
	p1 = phead;
	if (numSelect != 1)
	{
		if (phead == NULL)
		{
			printf("\n  数据为空! \n");
		}
		else			//寻找目标节点
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
	printf("\n 请输入%s %s的新单价和新数量:", p2->trade, p2->name);//修改信息
	scanf("%d %d", &p2->money, &p2->number);
	system("cls");
	printf("--------------------------------------------------------------------");
	printf("\n 已经成功修改相应商品信息！\n");
	return phead;
}

void FindGoods(Goods *phead, int number)//查找商品
{
	Goods *pnum_c = NULL;
	int temp = 0;
	int numtemp = 1;

	pnum_c = phead;

	if (pnum_c == NULL)
	{
		printf("--------------------------------------------------------------------");
		printf("\n 数据为空！\n");
	}
	else
	{
		printf("_________________________________________________________________________\n");
		printf("\n    编号     品牌??    名称   单价      数量  \n\n");
		while ((pnum_c != NULL) && (temp != 1))//按编号遍历查找
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
			printf("\n 没有找到相应的商品！\n");
		}
	}
}

void Add(Goods *phead)				//增加节点
{
	Goods *p1 = NULL, *p2 = NULL, *pInsert = NULL, *p = NULL;
	int payInsert;
	p = p2 = p1 = phead;
	if (p2 == NULL) { printf("\n数据为空\n"); }
	else			//输入新节点的信息
	{
		pInsert = (Goods *)malloc(sizeof(Goods));
		_flushall();
		printf("\n 请输入商品品牌:");
		scanf("%s", pInsert->trade);
		printf("\n 请输入商品名称:");
		scanf("%s", pInsert->name);
		printf("\n 请输入商品单价和数量:");
		scanf("%d %d", &pInsert->money, &pInsert->number);
		_flushall();
		payInsert = pInsert->money;
		if ((p->pNext == NULL) && (payInsert >= p2->money))//比较价格，将新节点插入表的合适位置
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

void Save(Goods *phead)			//将表保存到文件中
{
	FILE *fp = NULL;
	char fileName[10];
	Goods *p1 = phead;
	int listLen = 0;

	if (phead == NULL)
	{
		printf("\n 数据为空没有数据可以保存！\n");
	}
	else
	{
		while (p1)
		{
			p1 = p1->pNext;
			listLen++;
		}

		printf("\n 请输入保存文件名(*.txt):");
		_flushall();
		scanf("%s", fileName);			//打开文件操作
		if ((fp = fopen(fileName, "w")) == NULL)
		{
			printf("\n 打开文件失败！\n");
			exit(0);
		}
		p1 = phead;
		while (p1 != NULL)
		{								//按一定格式，按顺序保存数据
			if (!fprintf(fp, " %s %s %d %d \n", p1->trade, p1->name, p1->money, p1->number))
			{
				printf("\n 读入文件出错！\n");
			}
			p1 = p1->pNext;
		}
		fclose(fp);
	}
	system("cls");
	printf("--------------------------------------------------------------------");
	printf("\n 数据文件已经保存！\n");
}

Goods *Read(void)			//读取文件中的数据
{
	FILE *fp = NULL;
	char fileName[10];
	Goods *p1 = NULL, *p2 = NULL, *ph = NULL;

	printf("\n 请输入您要打开的数据库文件名(*.txt):");
	_flushall();
	scanf("%s", fileName);

	if ((fp = fopen(fileName, "r")) == NULL)
	{
		printf("\n 打开文件失败！\n\n\n");
		exit(0);
	}

	p1 = (Goods *)malloc(sizeof(Goods));
	p2 = p1;
	ph = p1;
	ph->pNext = NULL;

	while (!feof(fp))				//按格式依次读取数据
	{
		if (!fscanf(fp, " %s %s %d %d \n", &p1->trade, &p1->name, &p1->money, &p1->number))
			printf("\n 读入文件出错!\n");

		p2 = p1;
		p1 = (Goods *)malloc(sizeof(Goods));
		p2->pNext = p1;

	}
	p2->pNext = NULL;
	free(p1);
	p1 = NULL;
	return ph;
}

void Sort(Goods * head)			//冒泡排序，对链表节点按价格排序
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