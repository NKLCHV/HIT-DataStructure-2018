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

typedef struct {//���еĽṹ
    int front;//��һ�����ݵ��±�
    int engline;//���һ�����ݵ��±�
    int data[Max];//��������
} Queue;

typedef struct {//ջ�ṹ
    int data[Max];//��������
    int top;//ջ���±�
} Stack;
//ȫ��
Stack S;
int visited[Max];
int dfn[Max];
int count;

//��ʼ������
void MakeNull(Queue *Q) {
    Q->front = 0;
    Q->engline = 0;
}

//���ݽ���
void EnQueue(int k, Queue *Q) {
    if (Q->engline < Max) {
        if (Q->front == Q->engline)
            MakeNull(Q);//��ʼ��
        Q->data[Q->engline] = k;//�������
        Q->engline++;
    } else
        return;//�����ͷ���
}

//���ݳ���
int DeQueue(Queue *Q) {
    if (Q->front == Q->engline)//����ӿ�
        return 0xffffffff;
    else {
        Q->front++;//����
        return Q->data[Q->front - 1];
    }
}

//��ʼ��ջ
void StavkInti() {
    S.top = -1;
}

//���ջ�Ƿ�Ϊ��
int StackEmpty() {
    if (S.top == -1)
        return 1;
    else
        return 0;
}

//���ջ�Ƿ�Ϊ��
int StackFull() {
    if (S.top == Max - 1)
        return 1;
    else
        return 0;
}

//������ջ
void StackPush(int element) {
    if (!StackFull()) {//���ջ�Ƿ���
        S.top++;//��ջ
        S.data[S.top] = element;
    } else {
        printf("FULL!\n");
    }
}

//���ݳ�ջ
void StackPop() {
    if (!StackEmpty()) {//���ջ�Ƿ�Ϊ��
        S.top--;//��ջ
    } else {
        printf("EMPTY!\n");
    }
}

//ȡջ������
int StackTop() {
    if (!StackEmpty())//���ջ�Ƿ�Ϊ��
        return S.data[S.top];
    else
        printf("EMPTY!\n");
}

//ɾ��ջ������
void StackDestroy() {
    S.top = -1;
}


//Create the graph by matrix
void Create_Matrix(MTgraph *GM) {
    int i, j, k, m;
    printf("Please input the numbers of vertexes and edges (X,Y) :");
    scanf("%d,%d", &GM->numV, &GM->numE);//���붥�����ͱ���
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
    for (k = 0; k < GM->numE; k++) {//�ֱ�����������ͱߵĳ���
        scanf("%d,%d,%d", &i, &j, &m);
        GM->Edge[i][j] = m;
        GM->Edge[j][i] = m;
    }
}

//Create the graph by adjacency list
void Create_List(Adjgraph *GA) {
    int i, j = 0, w = 0, k;
    EdgeNode *e;//���붥�����ͱ���
    printf("Please input the numbers of vertexes and edges (X,Y) :");
    scanf("%d,%d", &(GA->numV), &(GA->numE));
    //Read the data of nodes
    for (i = 0; i < GA->numV; i++) {
        printf("Please the data of the node %d:", i + 1);
        scanf("%d", &GA->vexlist[i].vertex);//����ڵ�����
        GA->vexlist[i].firstedge = NULL;//���ָ��
    }
    printf("Please input the edges (X,Y,Z) :");
    for (k = 0; k < GA->numE; k++) {
        scanf("%d,%d,%d", &i, &j, &w);//�ֱ�����������ͱߵĳ���
        e = (EdgeNode *) malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->cost = w;
        e->next = GA->vexlist[j].firstedge;
        GA->vexlist[j].firstedge = e;//�������ڽڵ�
    }
}

//���ڽӾ����ʽת��Ϊ�ڽӱ�
void Change_M2A(MTgraph *GM, Adjgraph *GA) {
    int i;
    int j;
    GA->numE = GM->numE;//�ڵ����ͱ���
    GA->numV = GM->numV;
    EdgeNode *p;
    for (i = 0; i < GA->numV; i++) {//����ڵ������
        GA->vexlist[i].vertex = GM->Vertices[i];
        GA->vexlist[i].firstedge = NULL;//��ʼ��ָ��
    }
    for (i = 0; i < GM->numV; i++) {
        for (j = 0; j < GM->numV; j++) {
            if (GM->Edge[i][j] == 1) {//�����ڽӾ���
                p = (EdgeNode *) malloc(sizeof(EdgeNode));
                p->next = GA->vexlist[i].firstedge;
                GA->vexlist[i].firstedge = p;//�����ڽӵĽڵ�
                p->cost = 1;
                p->adjvex = j;
            }
        }
    }
}

void Change_A2M(MTgraph *GM, Adjgraph *GA) {
    int i, j;
    GM->numV = GA->numV;//�������ͱ���
    GM->numE = GA->numE;
    EdgeNode *p;
    for (i = 0; i < GA->numV; i++) {//����ڵ���Ϣ
        GM->Vertices[i] = GA->vexlist[i].vertex;
        for (j = 0; j < GA->numV; j++) {//��ʼ���ڽӾ���
            GM->Edge[i][j] = 0;
        }
        p = GA->vexlist[i].firstedge;//�ҵ����ڽڵ�
        while (p) {
            GM->Edge[i][p->adjvex] = 1;
            p = p->next;
        }
    }
}

//������ȵݹ����
void MDFS1(MTgraph *GM, int i) {
    int j;
    printf("The data in node[%d] is %d\n", i + 1, GM->Vertices[i]);
    visited[i] = 1;//���Ϊ�Ѿ���
    dfn[i] = count++;
    for (j = 0; j < GM->numV; j++)//������������
        if (GM->Edge[i][j] != 0 && !visited[j])
            MDFS1(GM, j);//���ڽӵ㿪ʼ�ݹ�
}

//������ȵݹ����
void DFS_M_1(MTgraph *GM) {
    int i = 0;
    count = 1;
    for (i = 0; i < GM->numV; i++)
        visited[i] = 0;//��ʼ����������
    for (i = 0; i < GM->numV; i++)
        if (!visited[i])//���ε��ñ�������
            MDFS1(GM, i);
}

//������ȷǵݹ����
void MDFS2(MTgraph *GM, int x) {
    StavkInti();//��ʼ��ջ
    printf("The data in node[%d] is %d\n", x + 1, GM->Vertices[x]);
    visited[x] = 1;//���Ϊ�Ѿ����õ�
    StackPush(x);//���õ���ջ
    while (!StackEmpty()) {
        int data;
        int i;
        data = StackTop();
        //StackPop();
        for (i = 0; i < GM->numV; i++) {//���α�������
            if (GM->Edge[data][i] != 0 && visited[i] != 1) {//���������δ����
                printf("The data in node[%d] is %d\n", i + 1, GM->Vertices[i]);
                visited[i] = 1;//���Ϊ�Ѿ���
                StackPush(i);//���õ���ջ
                break;//�Ӹõ㿪ʼѰ���ڽӽڵ�
            }
        }
        if (i == GM->numV)
            StackPop();//�����󽫽ڵ��ջ
    }
}

//������ȷǵݹ����
void DFS_M_2(MTgraph *GM) {
    int i = 0;
    count = 1;
    for (i = 0; i < GM->numV; i++)
        visited[i] = 0;//��ձ�������
    for (i = 0; i < GM->numV; i++)
        if (!visited[i])//�������α���
            MDFS2(GM, i);
}

//������ȵݹ����
void ADFS1(Adjgraph *GA, int i) {
    EdgeNode *p;
    printf("The data in node[%d] is %d\n", i + 1, GA->vexlist[i].vertex);
    visited[i] = 1;//���Ϊ�Ѿ���
    dfn[i] = count++;
    p = GA->vexlist[i].firstedge;//�ҵ��ڽӵĽڵ�
    while (p) {
        if (!visited[p->adjvex])
            ADFS1(GA, p->adjvex);//�ݹ鵽��һ���ڵ�
        p = p->next;
    }
}

//������ȵݹ����
void DFS_A_1(Adjgraph *GA) {
    int i = 0;
    count = 1;
    for (i = 0; i < GA->numV; i++)
        visited[i] = 0;//��ʼ����������
    for (i = 0; i < GA->numV; i++)
        if (!visited[i])//�������нڵ�
            ADFS1(GA, i);
}

//������ȷǵݹ����
void ADFS2(Adjgraph *GA, int i) {
    int j;
    int top = -1;
    int stack[20];
    visited[i] = 1;//���Ϊ�Ѿ���
    dfn[i] = count++;
    stack[++top] = i;//���ڵ���ջ
    EdgeNode *p;
    while (top != -1) {
        j = stack[top--];
        printf("The data in node[%d] is %d\n", j + 1, GA->vexlist[j].vertex);
        dfn[j] = count++;
        p = GA->vexlist[j].firstedge;//�ҵ����ڽڵ�
        while (p != NULL && !visited[p->adjvex]) {
            stack[++top] = p->adjvex;//������ڵ���ջ
            visited[p->adjvex] = 1;//����Ѿ���
            p = p->next;//�����ڽڵ�
        }
    }
}

//������ȷǵݹ����
void DFS_A_2(Adjgraph *GA) {
    int i = 0;
    count = 1;
    for (i = 0; i < GA->numV; i++)
        visited[i] = 0;//��ʼ����������
    for (i = 0; i < GA->numV; i++)
        if (!visited[i])
            ADFS2(GA, i);//�������нڵ�
}

//������ȱ���
void MBFS(MTgraph *GM, int i) {
    int j, k;
    Queue *Q = (Queue *) malloc(sizeof(Queue));
    MakeNull(Q);//��ʼ������

    printf("The data in node[%d] is %d\n", i + 1, GM->Vertices[i]);
    visited[i] = 1;//���Ϊ�Ѿ���
    EnQueue(i, Q);//���ڵ����
    while (Q->front != Q->engline) {
        k = DeQueue(Q);//����
        for (j = 0; j < GM->numV; j++) {
            if (GM->Edge[k][j] && !visited[j]) {//�鿴������
                printf("The data in node[%d] is %d\n", j + 1, GM->Vertices[j]);
                visited[j] = 1;
                EnQueue(j, Q);//�鿴���ڽڵ����
            }
        }
    }
}

//������ȱ���
void BFS_M(MTgraph *GM) {
    int i = 0;
    count = 1;
    for (i = 0; i < GM->numV; i++)
        visited[i] = 0;//��ʼ����������
    for (i = 0; i < GM->numV; i++)
        if (!visited[i])
            MBFS(GM, i);//�������нڵ�
}

void ABFS(Adjgraph *GA, int i) {
    int k;
    EdgeNode *p;
    Queue *Q = (Queue *) malloc(sizeof(Queue));
    MakeNull(Q);//��ʼ������

    printf("The data in node[%d] is %d\n", i + 1, GA->vexlist[i].vertex);
    visited[i] = 1;//���Ϊ�Ѿ���
    EnQueue(i, Q);//���ڵ����
    while (Q->front != Q->engline) {
        k = DeQueue(Q);//����
        p = GA->vexlist[k].firstedge;
        while (p) {
            if (!visited[p->adjvex]) {
                printf("The data in node[%d] is %d\n", p->adjvex, GA->vexlist[p->adjvex].vertex);
                visited[p->adjvex] = 1;
                EnQueue(p->adjvex, Q);//�鿴���ڽڵ�
            }
            p = p->next;
        }
    }
}

void BFS_A(Adjgraph *GA) {
    int i = 0;
    count = 1;
    for (i = 0; i < GA->numV; i++)
        visited[i] = 0;//��ʼ����������
    for (i = 0; i < GA->numV; i++)
        if (!visited[i])//�������нڵ�
            ABFS(GA, i);
}

//���ļ����ȡ�ڽӾ���
void ReadFile_M(MTgraph *GM) {
    int i, j, k, m;
    FILE *fid = fopen("txt_out_m.txt", "r");
    if (fid == NULL) {//���ļ�
        printf("Open %s failed!", "txt_out_m.txt");
        return;
    }
    //��ȡ�ڵ����ͱ���
    fscanf(fid, "%d,%d\n", &GM->numV, &GM->numE);
    for (i = 0; i < GM->numV; i++)//��ȡ�ڵ���Ϣ
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

//���ļ���ȡ�ڽӱ�
void ReadFile_A(Adjgraph *GA) {
    int i, j = 0, w = 0, k;
    EdgeNode *e;
    FILE *fid = fopen("txt_out_a.txt", "r");
    if (fid == NULL) {//���ļ�
        printf("Open %s failed", "txt_out_a.txt");
        return;
    }
    fscanf(fid, "%d,%d\n", &(GA->numV), &(GA->numE));
    //Read the data of nodes
    for (i = 0; i < GA->numV; i++) {
        fscanf(fid, "%d ", &GA->vexlist[i].vertex);
        GA->vexlist[i].firstedge = NULL;//��ʼ��ָ��
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
    MTgraph *GM = (MTgraph *) malloc(sizeof(MTgraph));//�����ڽӱ���ڽӾ���
    Adjgraph *GA = (Adjgraph *) malloc(sizeof(Adjgraph));

    int choice1, choice2, x = 0;
    char C;
    while (1) {
        do {//ѡ����ͼ�ķ�ʽ
            printf("1.create by matrix \n2.create by Adjacency\n3.read from matrix file \n4.read from adjacency file \n");
            scanf("%d", &choice1);
            getchar();
        } while (choice1 != 1 && choice1 != 2 && choice1 != 3 && choice1 != 4);
        //system("cls");

        if (choice1 == 1)//����ѡ��ͼ
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
        scanf("%c", &C);//�Ƿ�ת������ṹ

        do {//ѡ�������ʽ
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

        if (choice1 == 1) {//���ݴ���ṹ�ͱ�����ʽ����
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

