#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=20;
int a[maxn][maxn];
int v,sum=0;
struct node
{
    struct headnode * head;
    struct node * next;
    int order;
};
struct headnode
{
    struct node * first;
    struct node * tail;
};
struct enode
{
    int left;
    int right;
    int key;
};
void BuildMatrix()/*读取输入数据，建立图的邻接矩阵表示*/
{
    FILE * fp=fopen("data1.txt","r");
    fscanf(fp,"%d",&v);
    for(int i=1; i<=v; ++i)
    {
        for(int j=1; j<=v; ++j)
            fscanf(fp,"%d",&a[i][j]);
    }
    fclose(fp);
}
struct node * MakeSet(int k)/*建立一个互不相交集合*/
{
    struct headnode * p=new struct headnode;
    struct node * q=new struct node;
    p->first=q;
    p->tail=q;
    q->order=k;
    q->head=p;
    q->next=NULL;
    return q;
};
void Union(struct node * u,struct node * v)
/*将两个互不相交集合合并成一个互不相交集合*/
{
    struct node * p=u->head->first;
    while(p->next)
    {
        p=p->next;
    }
    p->next=v->head->first;
    u->head->tail=v->head->tail;
    p=v->head->first;
    while(p)
    {
        p->head=u->head;
        p=p->next;
    }
}
struct node * FindSet(struct node * u)
/*在一个互不相交集合中寻找元素u*/
{
    return u->head->first;
}
int SortEdge(struct enode * e[])
/*对所有边按照权重进行排序
建立一个存放边的数组e[]*/
{
    int count=0;
    for(int i=1; i<=v; ++i)
    {
        for(int j=1; j<i; ++j)
        {
            if(a[i][j]!=0)/*建立一个存放所有边的数组*/
            {
                struct enode * p=new struct enode;
                p->left=i;
                p->right=j;
                p->key=a[i][j];
                e[++count]=p;
            }
        }
    }
    for(int i=2; i<=count; ++i)
    {
        for(int j=1; j<i; ++j)
        {
            if(e[i]->key<e[j]->key)
            {
                struct enode * temp=e[i];
                e[i]=e[j];
                e[j]=temp;
            }
        }
    }
    return count;
}
struct enode * minedge[maxn];
void Kruskal()
{
   struct node * ver[maxn];
   for(int i=1; i<=v; ++i)
     ver[i]=MakeSet(i);/*将每个结点都组织成一个互不相交的集合*/
    struct enode * e[maxn];
    int count=SortEdge(e);
    for(int i=1;i<=count;++i)
     {
        if(FindSet(ver[e[i]->left])!=FindSet(ver[e[i]->right]))
        {
            /*找到当前连接两个互不相交集合且权重最小的边*/
            sum++;
            minedge[sum]=e[i];
            Union(ver[e[i]->left],ver[e[i]->right]);
            /*将这两个集合合并*/
            struct node *p=ver[e[i]->right]->head->first;
            p=p->next;
        }
    }
}
int main()
{
    BuildMatrix();
    Kruskal();
    FILE * fp=fopen("trees.txt","a");
    for(int i=1;i<=sum;++i)
    {
        fprintf(fp,"%d,%d\n",minedge[i]->left,minedge[i]->right);
    }
    fclose(fp);
    return 0;
}
