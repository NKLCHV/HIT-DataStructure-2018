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
struct heap/*�ѽṹ*/
{
    struct node * number[maxn];
    int length;
};
struct heap * Q=new struct heap;
void BuildMatrix()/*��ȡ�������ݣ������ڽӾ����ʾ��ͼ*/
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
void MaxHeapify(struct heap * q,int k)/*ά���ѵ�����*/
{
    int leftp=k*2;
    int rightp=k*2+1;
    int min=k;
    if(rightp<=q->length&&q->number[rightp]->key<q->number[min]->key&&q->number[rightp]->key<q->number[leftp]->key)
    /*����ý���������ҽ������ұȸ��ڵ�С����ô�ͽ�������ڵ�����С�Ľ�㽻��*/
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
        MaxHeapify(q,min);/*����֮������һ����Ϊ���ڵ�ݹ�ά���ѵ�����*/
    }
}
BuildHeap(struct heap * p)/*����*/
{
    for(int i=p->length;i>=1;i--)
    {
        MaxHeapify(p,i);
    }
}
struct node * Extract(struct heap * p)/*��С���ȶ���*/
{
    struct node * temp=p->number[1];/*ȡ����С��Ԫ��*/
    Exchange(&(p->number[1]),&(p->number[p->length]));
    --p->length;
    MaxHeapify(p,1);/*��ʣ�µ�Ԫ������С�ķ��ڶ���ͷ*/
    return temp;
}
struct node * verlist[maxn];
void Prim(int k)
{
    for(int i=1;i<=v;++i)/*��ʼ��*/
    {
        verlist[i]=new struct node;
        verlist[i]->order=i;
        verlist[i]->last=NULL;
        verlist[i]->key=10000;/*key�д�ŵ��Ǹý�㵽����Ȩ����С�ıߵ�Ȩ��*/
        Q->number[i]=verlist[i];
    }
    Q->number[k]->key=0;/*�ӽ��k��ʼ������С������*/
    Q->length=v;
    BuildHeap(Q);
    while(Q->length)/*ѭ��ֱ�����еĽ��������뵽����*/
    {
        struct node * u=Extract(Q);/*̰��ѡ���������������С�ı�*/
         for(int i=1;i<=v;++i)
            a[i][u->order]=0;
        for(int i=1;i<=v;++i)/*����ý��󣬸���������ý����������keyֵ*/
        {
           if(a[u->order][i]!=0&&a[u->order][i]<verlist[i]->key)
           {
               verlist[i]->last=u;/*��¼���ɵı�*/
               verlist[i]->key=a[u->order][i];
               BuildHeap(Q);/*����ά���ѵ�����*/
           }
        }
    }
}
int main()
{
     BuildMatrix();
     Prim(3);/*�ӽ��3��ʼִ��Prim�㷨*/
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



