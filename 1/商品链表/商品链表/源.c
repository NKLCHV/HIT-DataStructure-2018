#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN sizeof(GOODS)
#define FILENAME_LEN 10
#define FORMAT   "     %3d %10s %10s %6d %10d %10d    %s/n"    //显示格式
#define FORMAT2  "%s %s %d %d %d %d %s/n"   //存贮格式
#define NULL 0
#define TRUE 1
#define FALSE 0
#define ERROR 0

//商品的定义
struct goods     //定义
{
	char trademark[12];           //品牌
	char name[12];                //名称
	int number;                   //数量
	int money;                    //单价
	char user[20];               //操作用户
	unsigned long int editime;    //编辑时间
	unsigned long int overtime;   //过期时间
	struct goods *pNext;
};

typedef struct goods GOODS;

/*初始化*/

GOODS *Creat();
GOODS *Delete(GOODS *phead, int numSelect);
GOODS *Edit(GOODS *phead, int numSelect);
GOODS *Read();

GOODS *ph = NULL;

char Welcome();

void Add(GOODS *phead);
void Show(GOODS *phead);
void Save(GOODS *phead);
void FoundGoods(GOODS *phead, int number);
void OverGoods(GOODS *phead);
void Check();

char user[20];

// Main()函数
void main()
{
	char select;
	int searchMin, searchMax;
	int num_c, number;
	int t;
	t = getTime(0);

	printf(" * ===================================================================== *");
	printf("/n *                                                                       *");
	printf("/n *                     欢迎使用[家电库存]管理系统 (v1.3)                 *");
	printf("/n *                                                                       *");
	printf("/n *                            毛佳茗 06030706                            *");
	printf("/n *                             www.i1984.com                             *");
	printf("/n *                                                                       *");
	printf("/n *                                                                       *");
	printf("/n *                     当前系统日期：%d年%2d月%2d日                      *", t / 10000, t % 10000 / 100, t % 100);
	printf("/n *                                                                       *");
	Check();

SELECT: select = Welcome(); //主界面
	switch (select)
	{

	case '1':
		ph = Read();
		system("cls");
		printf(" * ===================================================================== *");
		printf("/n * 当前状态:已经读入数据文件！                                           */n");
		break;

	case '2':
		Add(ph);
		system("cls");
		Show(ph);
		break;

	case '3':
		system("cls");
		Show(ph);
		if (ph != NULL)
		{
			printf("/n /1 请输入您要修改的商品编号:");
			scanf("%d", &num_c);
			ph = Edit(ph, num_c);
		}
		break;

	case '4':
		printf("/n /1 请输入您要删除的商品编号:");
		scanf("%d", &num_c);
		ph = Delete(ph, num_c);
		break;

	case '5':
		system("cls");
		Show(ph);
		break;

	case '6':
		Save(ph);
		break;

	case '7':
		printf("/n /2 请输入要查询商品的最低价格:");
		scanf("%d", &searchMin);
		printf("/n /1 请输入要查询商品的最高价格:");
		scanf("%d", &searchMax);
		system("cls");
		FoundGoods(ph, searchMax, searchMin);
		break;

	case '8':
		if (ph == NULL)
		{
			ph = Creat();
			system("cls");
			Show(ph);
		}
		else
		{
			system("cls");
			printf(" * ===================================================================== *");
			printf("/n * 当前状态:数据已经从文件读入，并且存在，需要创建，请重启本软件！       */n");
		}
		break;

	case '9':
		system("cls");
		OverGoods(ph);
		break;

	case '0':
		exit(0);

	default :
		system("pause");
		system("cls");
		printf(" * ===================================================================== *");
		printf("/n * 当前状态:请您重新选择！                                               */n");
		break;
	}
	goto SELECT;
}


// 密码认证
void Check()
{
	int check;
	char  pin1[] = "admin";                                         //此处设定用户口令
	char  pin[20];
aga:
	printf("/n * ===================================================================== *");
	printf("/n *                                                                       *");
	printf("/n *                               [ 登 录 ]                               *");
	printf("/n *                                                                       *");
	printf("/n * ===================================================================== *");
	printf("/n /1 请输入帐号:");
	scanf("%s", user);
	printf(" /2 请输入密码:");
	scanf("%s", pin);
	check = strcmp(pin, pin1);
	if (check != 0)
	{
		system("cls");
		printf(" * ===================================================================== *");
		printf("/n * 当前状态:密码有误，请重新输入!                                        *");
		goto aga;
	}
	else system("cls");
}


// Welcome() 主界面

char Welcome()
{
	int num_c;
	char select;
	_flushall();
	printf(" * ===================================================================== *");
	printf("/n *                        [家电库存]管理系统 (v1.3)                      *");
	printf("/n * ===================================================================== *");
	printf("/n * 1.载入 2.添加 3.修改 4.删除 5.列表 6.保存 7.查找 8.新建 9.过期 0.退出 *");
	printf("/n * ===================================================================== *");
	printf("/n /2 请输入您的选择：");
	scanf("%c", &select);
	return select;
}

// 获取系统时间，此方法在C语言课程设计时编写，可能有较多不完善
int getTime()
{
	long int datatime;
	time_t t;
	struct tm *tm;
	char timea[30];
	t = time(NULL);
	tm = localtime(&t);
	strcpy(timea, asctime(tm));
	datatime = (timea[20] - 48) * 10000000 + (timea[21] - 48) * 1000000 + (timea[22] - 48) * 100000 + (timea[23] - 48) * 10000 + (timea[8] - 48) * 10 + (timea[9] - 48);
	if (timea[4] == 'J'&&timea[5] == 'a') datatime += 1 * 100;
	if (timea[4] == 'F') datatime += 2 * 100;
	if (timea[4] == 'M'&&timea[6] == 'r') datatime += 3 * 100;
	if (timea[4] == 'A'&&timea[5] == 'p') datatime += 4 * 100;
	if (timea[4] == 'M'&&timea[6] == 'y') datatime += 5 * 100;
	if (timea[4] == 'J'&&timea[6] == 'n'&&timea[5] == 'u') datatime += 6 * 100;
	if (timea[4] == 'J'&&timea[6] == 'l'&&timea[5] == 'u') datatime += 7 * 100;
	if (timea[4] == 'A'&&timea[6] == 'g') datatime += 8 * 100;
	if (timea[4] == 'S') datatime += 9 * 100;
	if (timea[4] == 'O') datatime += 10 * 100;
	if (timea[4] == 'N') datatime += 11 * 100;
	if (timea[4] == 'D') datatime += 12 * 100;
	return datatime;
}


// 显示
void Show(GOODS *phead)
{
	GOODS *pnum_c;
	int numtemp = 1;
	pnum_c = phead;

	if (pnum_c == NULL)
	{
		printf(" * ===================================================================== *");
		printf("/n * 当前状态:数据为空或没有数据，请确认后再选择！                         */n");
	}
	else
	{
		printf(" _________________________________________________________________________/n");
		printf("/n     编号      品牌       名称   单价       数量   修改日期    操作者/n/n");
		do
		{
			printf(FORMAT, numtemp++, pnum_c->trademark, pnum_c->name, pnum_c->money, pnum_c->number, pnum_c->editime, pnum_c->user);
			pnum_c = pnum_c->pNext;
		} while (pnum_c != NULL);
	}
}

// 新建
GOODS *Creat(void)
{
	GOODS *ph = NULL, *p1 = NULL, *p2 = NULL;
	p1 = (GOODS *)malloc(LEN);

	if (p1 == NULL)
	{
		printf("/n /2 创建数据库不成功，请重试！/n");
	}
	else
	{
		p2 = p1;
		ph = p1;
		p2->pNext = NULL;
		getchar();
		printf("/n /1 请输入商品品牌(5个字内):");
		gets(p1->trademark);
		printf("/n /2 请输入商品名称(5个字内):");
		gets(p1->name);
		printf("/n /1 请输入商品单价和数量(用空格分开):");
		scanf("%d%d", &p1->money, &p1->number);
		printf("/n /2 请输入商品过期日期(如:20050901):");
		scanf("%d", &p1->overtime);
		strcpy(p1->user, user);
		p1->editime = getTime(1);
		_flushall();
	}
	return(ph);
}

//删除

GOODS *Delete(GOODS *phead, int numSelect)
{
	GOODS *p1 = NULL, *p2 = NULL;
	int numtemp, j = 0;
	p1 = phead;
	if (numSelect != 1)
	{
		if (phead == NULL)
		{
			printf("/n /2 数据为空没有数据可以删除！/n");
		}
		else
		{
			while (p1->pNext != NULL && j < numSelect - 2)
			{
				++j;
				p1 = p1->pNext;
			}
			if (p1->pNext == NULL || j > numSelect - 2) return ERROR;
			p2 = p1->pNext;
			p1->pNext = p2->pNext;
			free(p2);
		}
	}
	else
	{
		p2 = p1->pNext; phead = p2; free(p1);
	}
	system("cls");
	printf(" * ===================================================================== *");
	printf("/n * 当前状态:已经删除相应商品信息！                                       */n");
	return phead;
}


GOODS *Edit(GOODS *phead, int numSelect)
{
	GOODS *p1 = NULL, *p2 = NULL;
	int numtemp, j = 0;
	p1 = phead;
	if (numSelect != 1)
	{
		if (phead == NULL)
		{
			printf("/n /2 数据为空没有数据可以删除！/n");
		}
		else
		{
			while (p1->pNext != NULL && j < numSelect - 2)
			{
				++j;
				p1 = p1->pNext;
			}
			if (p1->pNext == NULL || j > numSelect - 2) return ERROR;
			p2 = p1->pNext;
		}
	}
	else
	{
		p2 = p1;
	}
	printf("/n /2 请输入%s%s的新单价和新数量(用空格分开):", p2->trademark, p2->name);
	scanf("%d%d", &p2->money, &p2->number);
	printf("/n /2 请输入新的过期日期(如:20050901):");
	scanf("%d", &p2->overtime);
	system("cls");
	printf(" * ===================================================================== *");
	printf("/n * 当前状态:已经成功修改相应商品信息！                                   */n");
	return phead;
}

// 查找

void FoundGoods(GOODS *phead, int max, int min)
{
	GOODS *pnum_c = NULL;
	int temp = FALSE;
	int numtemp = 1;

	pnum_c = phead;

	if (pnum_c == NULL)
	{
		printf(" * ===================================================================== *");
		printf("/n * 当前状态:数据为空或没有数据可查找！                                   */n");
	}
	else
	{
		printf(" _________________________________________________________________________/n");
		printf("/n     编号      品牌       名称   单价       数量   修改日期    操作者/n/n");
		while (pnum_c != NULL)
		{
			if ((min < (pnum_c->money)) && (max > (pnum_c->money)))
			{
				printf(FORMAT, numtemp++, pnum_c->trademark, pnum_c->name, pnum_c->money, pnum_c->number, pnum_c->editime, pnum_c->user);
				temp = TRUE;
			}
			pnum_c = pnum_c->pNext;
		}
		if (!temp)
		{
			system("cls");
			printf(" * ===================================================================== *");
			printf("/n * 当前状态:没有找到相应的商品，请确认！                                 */n");
		}
	}
}

// 添加
void Add(GOODS *phead)
{
	GOODS *p1 = NULL, *p2 = NULL, *pInsert = NULL, *p = NULL;
	int temp;
	int payInsert;
	p = p2 = p1 = phead;
	if (p2 == NULL) { printf("/n数据为空没有数据可以打印/n"); }
	else
	{
		pInsert = (GOODS *)malloc(LEN);
		_flushall();
		printf("/n /2 请输入商品品牌(5个字内):");
		gets(pInsert->trademark);
		printf("/n /1 请输入商品名称(5个字内):");
		gets(pInsert->name);
		printf("/n /2 请输入商品单价和数量(用空格分开):");
		scanf("%d%d", &pInsert->money, &pInsert->number);
		printf("/n /1 请输入商品过期日期(如:20050901):");
		scanf("%d", &pInsert->overtime);
		strcpy(pInsert->user, user);
		pInsert->editime = getTime(1);
		_flushall();
		payInsert = pInsert->money;
		if ((p->pNext == NULL) && (payInsert >= p2->money))   //单商品时
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

// 保存
void Save(GOODS *phead)
{
	FILE *fp = NULL;
	char fileName[FILENAME_LEN];
	GOODS *p1 = phead;
	int listLen = 0;

	if (phead == NULL)
	{
		printf("/n /2 数据为空没有数据可以保存，请确认后重新选择此功能！/n");
	}
	else
	{
		while (p1)
		{
			p1 = p1->pNext;
			listLen++;
		}

		printf("/n /2 请输入保存文件名,以txt方式(*.txt):");
		_flushall();
		gets(fileName);
		if ((fp = fopen(fileName, "w")) == NULL)
		{
			printf("/n /2 打开文件失败！/n");
			exit(0);
		}
		p1 = phead;
		while (p1 != NULL)
		{
			if (!fprintf(fp, FORMAT2, p1->trademark, p1->name, p1->money, p1->number, p1->editime, p1->overtime, p1->user))
			{
				printf("/n /2 读入文件出错！/n");
			}
			p1 = p1->pNext;
		}
		fclose(fp);
	}
	system("cls");
	printf(" * ===================================================================== *");
	printf("/n * 当前状态:数据文件已经保存！                                           */n");
}

// 查找

void OverGoods(GOODS *phead)
{
	GOODS *pnum_c = NULL;
	int temp = FALSE;
	int numtemp = 1;
	int timenow, num;

	pnum_c = phead;

	timenow = getTime(0);

	if (pnum_c == NULL)
	{
		printf(" * ===================================================================== *");
		printf("/n * 当前状态:数据为空或没有数据，请确认！                                 */n");
	}
	else
	{
		printf(" _________________________________________________________________________/n");
		printf("/n     编号      品牌       名称   单价       数量   过期日期    操作者/n/n");
		while (pnum_c != NULL)
		{
			if (timenow > (pnum_c->overtime))
			{
				printf(FORMAT, numtemp, pnum_c->trademark, pnum_c->name, pnum_c->money, pnum_c->number, pnum_c->overtime, pnum_c->user);
				temp = TRUE;
			}
			numtemp++;
			pnum_c = pnum_c->pNext;
		}
		if (!temp)
		{
			system("cls");
			printf(" * ===================================================================== *");
			printf("/n * 当前状态:没有找到过期的商品！                                         */n");
		}
		else
		{
			printf("/n /1 请输入您要删除的商品编号:");
			scanf("%d", &num);
			ph = Delete(ph, num);
		}
	}
}

// 读入文件
GOODS *Read(void)
{
	FILE *fp = NULL;
	char fileName[FILENAME_LEN];
	GOODS *p1 = NULL, *p2 = NULL, *ph = NULL;

	printf("/n /1 请输入您要打开的数据库文件名,以txt方式(*.txt):");
	_flushall();
	gets(fileName);

	if ((fp = fopen(fileName, "r")) == NULL)
	{
		printf("/n /2 打开文件失败,请确认后重新启动本软件！/n/n/n");
		exit(0);
	}

	p1 = (GOODS *)malloc(LEN);
	p2 = p1;
	ph = p1;
	ph->pNext = NULL;

	while (!feof(fp))
	{
		if (!fscanf(fp, FORMAT2, &p1->trademark, &p1->name, &p1->money, &p1->number, &p1->editime, &p1->overtime, &p1->user))
			printf("/n /2 读入文件出错，可能文件为空，或文件不存在!/n");

		p2 = p1;
		p1 = (GOODS *)malloc(LEN);
		p2->pNext = p1;

	}
	p2->pNext = NULL;
	free(p1);
	p1 = NULL;
	return ph;
}
