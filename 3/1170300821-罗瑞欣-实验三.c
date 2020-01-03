#include <stdio.h>
#include <stdlib.h>

#define Max 100

//The definition of the adjacency matrix containing the weight
typedef struct {
    int Vertices[Max];  //vertex table
    int Edge[Max][Max]; //the adjacency matrix
    int numV;//numbers of vertexes and edges
    int numE;
} MTgraph;

//Adjacency list storage structure definition
typedef struct node {//vertex list node
    int adjvex;//Adjacent dot domain
    int cost;//weight
    struct node *next;
} EdgeNode;
typedef struct {//First edge node
    int vertex;//Vertex data field
    EdgeNode *firstedge;//Side chain head pointer
} VertexNode;
typedef struct {//Adjacency list
    VertexNode vexlist[Max];
    int numV;//numbers of vertexes and edges
    int numE;
} Adjgraph;

typedef struct {//队列的结构
    int front;//第一个数据的下标
    int engline;//最后一个数据的下标
    int data[Max];//储存数据
} Queue;

typedef struct {//栈结构
    int data[Max];//储存数据
    int top;//栈顶下标
} Stack;
//全局
Stack S;
int visited[Max];
int dfn[Max];
int count;

//初始化队列
void MakeNull(Queue *Q) {
    Q->front = 0;
    Q->engline = 0;
}

//数据进队
void EnQueue(int k, Queue *Q) {
    if (Q->engline < Max) {
        if (Q->front == Q->engline)
            MakeNull(Q);//初始化
        Q->data[Q->engline] = k;//数据入队
        Q->engline++;
    } else
        return;//队满就返回
}

//数据出队
int DeQueue(Queue *Q) {
    if (Q->front == Q->engline)//如果队空
        return 0xffffffff;
    else {
        Q->front++;//出队
        return Q->data[Q->front - 1];
    }
}

//初始化栈
void StavkInti() {
    S.top = -1;
}

//检查栈是否为空
int StackEmpty() {
    if (S.top == -1)
        return 1;
    else
        return 0;
}

//检查栈是否为满
int StackFull() {
    if (S.top == Max - 1)
        return 1;
    else
        return 0;
}

//数据入栈
void StackPush(int element) {
    if (!StackFull()) {//检查栈是否满
        S.top++;//入栈
        S.data[S.top] = element;
    } else {
        printf("FULL!\n");
    }
}

//数据出栈
void StackPop() {
    if (!StackEmpty()) {//检查栈是否为空
        S.top--;//出栈
    } else {
        printf("EMPTY!\n");
    }
}

//取栈顶数据
int StackTop() {
    if (!StackEmpty())//检查栈是否为空
        return S.data[S.top];
    else
        printf("EMPTY!\n");
}

//删除栈内数据
void StackDestroy() {
    S.top = -1;
}


//Create the graph by matrix
void Create_Matrix(MTgraph *GM) {
    int i, j, k, m;
    printf("Please input the numbers of vertexes and edges (X,Y) :");
    scanf("%d,%d", &GM->numV, &GM->numE);//读入顶点数和边数
    //Read the vertex information and create a vertex table
    for (i = 0; i < GM->numV; i++) {
        printf("Please the data of the node %d:", i + 1);
        scanf("%d", &GM->Vertices[i]);
    }
    //Initialize the adjacency matrix
    for (i = 0; i < GM->numV; i++) {
        for (j = 0; j < GM->numV; j++) {
            GM->Edge[i][j] = 0;
        }
    }
    //Read the edge and establish the adjacency matrix
    printf("Please input the edges (X,Y,Z) :");
    for (k = 0; k < GM->numE; k++) {//分别是两个顶点和边的长度
        scanf("%d,%d,%d", &i, &j, &m);
        GM->Edge[i][j] = m;
        GM->Edge[j][i] = m;
    }
}

//Create the graph by adjacency list
void Create_List(Adjgraph *GA) {
    int i, j = 0, w = 0, k;
    EdgeNode *e;//读入顶点数和边数
    printf("Please input the numbers of vertexes and edges (X,Y) :");
    scanf("%d,%d", &(GA->numV), &(GA->numE));
    //Read the data of nodes
    for (i = 0; i < GA->numV; i++) {
        printf("Please the data of the node %d:", i + 1);
        scanf("%d", &GA->vexlist[i].vertex);//读入节点数据
        GA->vexlist[i].firstedge = NULL;//清空指针
    }
    printf("Please input the edges (X,Y,Z) :");
    for (k = 0; k < GA->numE; k++) {
        scanf("%d,%d,%d", &i, &j, &w);//分别是两个顶点和边的长度
        e = (EdgeNode *) malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->cost = w;
        e->next = GA->vexlist[j].firstedge;
        GA->vexlist[j].firstedge = e;//加入相邻节点
    }
}

//将邻接矩阵格式转化为邻接表
void Change_M2A(MTgraph *GM, Adjgraph *GA) {
    int i;
    int j;
    GA->numE = GM->numE;//节点数和边数
    GA->numV = GM->numV;
    EdgeNode *p;
    for (i = 0; i < GA->numV; i++) {//读入节点的数据
        GA->vexlist[i].vertex = GM->Vertices[i];
        GA->vexlist[i].firstedge = NULL;//初始化指针
    }
    for (i = 0; i < GM->numV; i++) {
        for (j = 0; j < GM->numV; j++) {
            if (GM->Edge[i][j] == 1) {//遍历邻接矩阵
                p = (EdgeNode *) malloc(sizeof(EdgeNode));
                p->next = GA->vexlist[i].firstedge;
                GA->vexlist[i].firstedge = p;//加入邻接的节点
                p->cost = 1;
                p->adjvex = j;
            }
        }
    }
}

void Change_A2M(MTgraph *GM, Adjgraph *GA) {
    int i, j;
    GM->numV = GA->numV;//顶点数和边数
    GM->numE = GA->numE;
    EdgeNode *p;
    for (i = 0; i < GA->numV; i++) {//读入节点信息
        GM->Vertices[i] = GA->vexlist[i].vertex;
        for (j = 0; j < GA->numV; j++) {//初始化邻接矩阵
            GM->Edge[i][j] = 0;
        }
        p = GA->vexlist[i].firstedge;//找到相邻节点
        while (p) {
            GM->Edge[i][p->adjvex] = 1;
            p = p->next;
        }
    }
}

//深度优先递归遍历
void MDFS1(MTgraph *GM, int i) {
    int j;
    printf("The data in node[%d] is %d\n", i + 1, GM->Vertices[i]);
    visited[i] = 1;//标记为已经过
    dfn[i] = count++;
    for (j = 0; j < GM->numV; j++)//依次搜索各行
        if (GM->Edge[i][j] != 0 && !visited[j])
            MDFS1(GM, j);//从邻接点开始递归
}

//深度优先递归遍历
void DFS_M_1(MTgraph *GM) {
    int i = 0;
    count = 1;
    for (i = 0; i < GM->numV; i++)
        visited[i] = 0;//初始化遍历数组
    for (i = 0; i < GM->numV; i++)
        if (!visited[i])//依次调用遍历函数
            MDFS1(GM, i);
}

//深度优先非递归遍历
void MDFS2(MTgraph *GM, int x) {
    StavkInti();//初始化栈
    printf("The data in node[%d] is %d\n", x + 1, GM->Vertices[x]);
    visited[x] = 1;//标记为已经过该点
    StackPush(x);//将该点入栈
    while (!StackEmpty()) {
        int data;
        int i;
        data = StackTop();
        //StackPop();
        for (i = 0; i < GM->numV; i++) {//依次遍历各点
            if (GM->Edge[data][i] != 0 && visited[i] != 1) {//如果相邻且未经过
                printf("The data in node[%d] is %d\n", i + 1, GM->Vertices[i]);
                visited[i] = 1;//标记为已经过
                StackPush(i);//将该点入栈
                break;//从该点开始寻找邻接节点
            }
        }
        if (i == GM->numV)
            StackPop();//遍历后将节点出栈
    }
}

//深度优先非递归遍历
void DFS_M_2(MTgraph *GM) {
    int i = 0;
    count = 1;
    for (i = 0; i < GM->numV; i++)
        visited[i] = 0;//清空遍历数组
    for (i = 0; i < GM->numV; i++)
        if (!visited[i])//各点依次遍历
            MDFS2(GM, i);
}

//深度优先递归遍历
void ADFS1(Adjgraph *GA, int i) {
    EdgeNode *p;
    printf("The data in node[%d] is %d\n", i + 1, GA->vexlist[i].vertex);
    visited[i] = 1;//标记为已经过
    dfn[i] = count++;
    p = GA->vexlist[i].firstedge;//找到邻接的节点
    while (p) {
        if (!visited[p->adjvex])
            ADFS1(GA, p->adjvex);//递归到下一个节点
        p = p->next;
    }
}

//深度优先递归遍历
void DFS_A_1(Adjgraph *GA) {
    int i = 0;
    count = 1;
    for (i = 0; i < GA->numV; i++)
        visited[i] = 0;//初始化遍历数组
    for (i = 0; i < GA->numV; i++)
        if (!visited[i])//遍历所有节点
            ADFS1(GA, i);
}

//深度优先非递归遍历
void ADFS2(Adjgraph *GA, int i) {
    int j;
    int top = -1;
    int stack[20];
    visited[i] = 1;//标记为已经过
    dfn[i] = count++;
    stack[++top] = i;//将节点入栈
    EdgeNode *p;
    while (top != -1) {
        j = stack[top--];
        printf("The data in node[%d] is %d\n", j + 1, GA->vexlist[j].vertex);
        dfn[j] = count++;
        p = GA->vexlist[j].firstedge;//找到相邻节点
        while (p != NULL && !visited[p->adjvex]) {
            stack[++top] = p->adjvex;//将这个节点入栈
            visited[p->adjvex] = 1;//标记已经过
            p = p->next;//到相邻节点
        }
    }
}

//深度优先非递归遍历
void DFS_A_2(Adjgraph *GA) {
    int i = 0;
    count = 1;
    for (i = 0; i < GA->numV; i++)
        visited[i] = 0;//初始化遍历数组
    for (i = 0; i < GA->numV; i++)
        if (!visited[i])
            ADFS2(GA, i);//遍历所有节点
}

//广度优先遍历
void MBFS(MTgraph *GM, int i) {
    int j, k;
    Queue *Q = (Queue *) malloc(sizeof(Queue));
    MakeNull(Q);//初始化队列

    printf("The data in node[%d] is %d\n", i + 1, GM->Vertices[i]);
    visited[i] = 1;//标记为已经过
    EnQueue(i, Q);//将节点入队
    while (Q->front != Q->engline) {
        k = DeQueue(Q);//出队
        for (j = 0; j < GM->numV; j++) {
            if (GM->Edge[k][j] && !visited[j]) {//查看整个行
                printf("The data in node[%d] is %d\n", j + 1, GM->Vertices[j]);
                visited[j] = 1;
                EnQueue(j, Q);//查看相邻节点的行
            }
        }
    }
}

//广度优先遍历
void BFS_M(MTgraph *GM) {
    int i = 0;
    count = 1;
    for (i = 0; i < GM->numV; i++)
        visited[i] = 0;//初始化遍历数组
    for (i = 0; i < GM->numV; i++)
        if (!visited[i])
            MBFS(GM, i);//遍历所有节点
}

void ABFS(Adjgraph *GA, int i) {
    int k;
    EdgeNode *p;
    Queue *Q = (Queue *) malloc(sizeof(Queue));
    MakeNull(Q);//初始化队列

    printf("The data in node[%d] is %d\n", i + 1, GA->vexlist[i].vertex);
    visited[i] = 1;//标记为已经过
    EnQueue(i, Q);//将节点入队
    while (Q->front != Q->engline) {
        k = DeQueue(Q);//出队
        p = GA->vexlist[k].firstedge;
        while (p) {
            if (!visited[p->adjvex]) {
                printf("The data in node[%d] is %d\n", p->adjvex, GA->vexlist[p->adjvex].vertex);
                visited[p->adjvex] = 1;
                EnQueue(p->adjvex, Q);//查看相邻节点
            }
            p = p->next;
        }
    }
}

void BFS_A(Adjgraph *GA) {
    int i = 0;
    count = 1;
    for (i = 0; i < GA->numV; i++)
        visited[i] = 0;//初始化遍历数组
    for (i = 0; i < GA->numV; i++)
        if (!visited[i])//遍历所有节点
            ABFS(GA, i);
}

//从文件里读取邻接矩阵
void ReadFile_M(MTgraph *GM) {
    int i, j, k, m;
    FILE *fid = fopen("txt_out_m.txt", "r");
    if (fid == NULL) {//打开文件
        printf("Open %s failed!", "txt_out_m.txt");
        return;
    }
    //读取节点数和边数
    fscanf(fid, "%d,%d\n", &GM->numV, &GM->numE);
    for (i = 0; i < GM->numV; i++)//读取节点信息
        fscanf(fid, "%d ", &GM->Vertices[i]);
    //Initialize the adjacency matrix
    for (i = 0; i < GM->numV; i++) {
        for (j = 0; j < GM->numV; j++) {
            GM->Edge[i][j] = 0;
        }
    }
    //Read the edge and establish the adjacency matrix
    for (k = 0; k < GM->numE; k++) {
        fscanf(fid, "\n%d,%d,%d", &i, &j, &m);
        GM->Edge[i][j] = m;
        GM->Edge[j][i] = m;
    }
    fclose(fid);
}

//从文件读取邻接表
void ReadFile_A(Adjgraph *GA) {
    int i, j = 0, w = 0, k;
    EdgeNode *e;
    FILE *fid = fopen("txt_out_a.txt", "r");
    if (fid == NULL) {//打开文件
        printf("Open %s failed", "txt_out_a.txt");
        return;
    }
    fscanf(fid, "%d,%d\n", &(GA->numV), &(GA->numE));
    //Read the data of nodes
    for (i = 0; i < GA->numV; i++) {
        fscanf(fid, "%d ", &GA->vexlist[i].vertex);
        GA->vexlist[i].firstedge = NULL;//初始化指针
    }
    for (k = 0; k < GA->numE; k++) {
        fscanf(fid, "\n%d,%d,%d", &i, &j, &w);
        e = (EdgeNode *) malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->cost = w;
        e->next = GA->vexlist[j].firstedge;
        GA->vexlist[j].firstedge = e;
    }
    fclose(fid);
}

int main() {
    MTgraph *GM = (MTgraph *) malloc(sizeof(MTgraph));//建立邻接表和邻接矩阵
    Adjgraph *GA = (Adjgraph *) malloc(sizeof(Adjgraph));

    int choice1, choice2, x = 0;
    char C;
    while (1) {
        do {//选择建立图的方式
            printf("1.create by matrix \n2.create by Adjacency\n3.read from matrix file \n4.read from adjacency file \n");
            scanf("%d", &choice1);
            getchar();
        } while (choice1 != 1 && choice1 != 2 && choice1 != 3 && choice1 != 4);
        //system("cls");

        if (choice1 == 1)//根据选择建图
            Create_Matrix(GM);
        else if (choice1 == 2)
            Create_List(GA);
        else if (choice1 == 3) {
            ReadFile_A(GA);
            choice1 = 2;
        } else
            ReadFile_A(GA);

        //getchar();
        printf("Do you want to change the type of graph ?");
        scanf("%c", &C);//是否转换储存结构

        do {//选择遍历方式
            printf("1.recursive DFS \n2.non-recursive DFS \n3.BFS \n");
            scanf("%d", &choice2);
        } while (choice2 != 1 && choice2 != 2 && choice2 != 3);
        printf("\n%c\n", C);
        //system("cls");

        if (C == 'Y' || C == 'y') {
            if (choice1 == 1) {
                Change_M2A(GM, GA);
                choice1 = 2;
            } else {
                Change_A2M(GM, GA);
                choice1 = 1;
            }
        }

        if (choice1 == 1) {//根据储存结构和遍历方式遍历
            if (choice2 == 1) {
                DFS_M_1(GM);
            } else if (choice2 == 2) {
                DFS_M_2(GM);
            } else {
                BFS_M(GM);
            }
        } else {
            if (choice2 == 1) {
                DFS_A_1(GA);
            } else if (choice2 == 2) {
                DFS_A_2(GA);
            } else {
                BFS_A(GA);
            }
        }

        getchar();
        do {
            printf("Do you want to continue ? (Y/N)");
            scanf("%c", &C);
            //getchar();
        } while (C != 'Y' && C != 'y' && C != 'N' && C != 'n');
        if (C == 'N' || C == 'n')
            exit(0);
        //system("cls");
    }
    return 0;
}

