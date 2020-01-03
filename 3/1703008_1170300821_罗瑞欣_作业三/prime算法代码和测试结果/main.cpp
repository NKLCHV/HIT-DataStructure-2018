#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=20;
int a[maxn][maxn];
int v;
struct node
{
    int order;
    int key;
    struct node * last;
};
struct heap/*堆结构*/
{
    struct node * number[maxn];
    int length;
};
struct heap * Q=new struct heap;
void BuildMatrix()/*读取输入数据，建立邻接矩阵表示的图*/
{
    FILE * fp=fopen("data1.txt","r");
    fscanf(fp,"%d",&v);
    for(int i=1;i<=v;++i)
    {
        for(int j=1;j<=v;++j)
            fscanf(fp,"%d",&a[i][j]);
    }
    fclose(fp);
}
void Exchange(struct node * * a,struct node * * b)
{
    struct node * c=*a;
    *a=*b;
    *b=c;
}
void MaxHeapify(struct heap * q,int k)/*维护堆的性质*/
{
    int leftp=k*2;
    int rightp=k*2+1;
    int min=k;
    if(rightp<=q->length&&q->number[rightp]->key<q->number[min]->key&&q->number[rightp]->key<q->number[leftp]->key)
    /*如果该结点的左结点或右结点存在且比根节点小，那么就将这个根节点与最小的结点交换*/
    {
        min=rightp;
    }
    if(leftp<=q->length&&q->number[leftp]->key<q->number[min]->key)
    {
        min=leftp;
    }
    if(min!=k)
    {
        Exchange(&(q->number[min]),&(q->number[k]));
        MaxHeapify(q,min);/*交换之后，以下一层结点为根节点递归维护堆的性质*/
    }
}
BuildHeap(struct heap * p)/*建堆*/
{
    for(int i=p->length;i>=1;i--)
    {
        MaxHeapify(p,i);
    }
}
struct node * Extract(struct heap * p)/*最小优先队列*/
{
    struct node * temp=p->number[1];/*取出最小的元素*/
    Exchange(&(p->number[1]),&(p->number[p->length]));
    --p->length;
    MaxHeapify(p,1);/*将剩下的元素中最小的放在队列头*/
    return temp;
}
struct node * verlist[maxn];
void Prim(int k)
{
    for(int i=1;i<=v;++i)/*初始化*/
    {
        verlist[i]=new struct node;
        verlist[i]->order=i;
        verlist[i]->last=NULL;
        verlist[i]->key=10000;/*key中存放的是该结点到树的权重最小的边的权重*/
        Q->number[i]=verlist[i];
    }
    Q->number[k]->key=0;/*从结点k开始构建最小生成树*/
    Q->length=v;
    BuildHeap(Q);
    while(Q->length)/*循环直至所有的结点均被加入到树中*/
    {
        struct node * u=Extract(Q);/*贪心选择连接树与结点的最小的边*/
         for(int i=1;i<=v;++i)
            a[i][u->order]=0;
        for(int i=1;i<=v;++i)/*加入该结点后，更新所有与该结点相连结点的key值*/
        {
           if(a[u->order][i]!=0&&a[u->order][i]<verlist[i]->key)
           {
               verlist[i]->last=u;/*记录生成的边*/
               verlist[i]->key=a[u->order][i];
               BuildHeap(Q);/*重新维护堆的性质*/
           }
        }
    }
}
int main()
{
     BuildMatrix();
     Prim(3);/*从结点3开始执行Prim算法*/
     FILE * fp=fopen("trees.txt","a");
     for(int i=1;i<10;++i)
     {
         if(verlist[i]->last!=NULL)
         {
             fprintf(fp,"%d,%d\n",verlist[i]->last->order,verlist[i]->order);
         }
     }
     fclose(fp);
    return 0;
}



