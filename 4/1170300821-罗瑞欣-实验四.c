#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define keytype int

//BST
typedef struct celltype1 {
    int data;
    struct celltype1 *lchild, *rchild;
} BSTNode;
typedef BSTNode *BST;
//�۰�
typedef struct celltype2 {
    int data;
    struct celltype2 *next;
} LISTnode;
typedef LISTnode *LIST;
int List[2000];
int Up = 1023, Low = 0;

int str[1024];
int counter, last = 1023;
float C1, C2, C3, C4, C5, C6;

//BST
BST SearchBST(keytype k, BST F);//����
void InsertBST(int R, BST *F);//����
BST CreateBST1(void);//����BST��
BST CreateBST2(void);//
int Deletemin(BST *F);//ɾ����С
void DeleteB(keytype k, BST *F);//
//�۰����
void CreatBin1(void);//
void CreatBin2(BST F);//
int BinSearch1(keytype k);//�ǵݹ��۰����
int BinSearch2(int low, int up, keytype k);//�ݹ��۰����
//���Ҳ���ģ��
void Time(int x);//ʱ�����ģ��
void Create1(void);//
void Create2(void);//

void B(BST F) {
    if (!(F == NULL)) {
        B(F->lchild);
        printf("%d ", F->data);
        B(F->rchild);
    }
}

int main() {
    int x;

    Create1();
    Create2();
    //printf("Please input the number you want to :");
    //scanf("%d", &x);
    //BST F2 = CreateBST2();
    //DeleteB(2042 ,&F2);
    //B(F2);
    Time(1);

    return 0;
}

BST SearchBST(keytype k, BST F) {
    BSTNode *p = F;
    if (p == NULL || k == p->data) { /* �ݹ���ֹ���� */
        counter++;
        return p;
    }
    if (p->rchild == NULL && p->lchild == NULL && p->data != k)
        return NULL;
    if (k < p->data) {
        counter++;
        return (SearchBST(k, p->lchild)); /* ���������� */
    } else {
        counter++;
        return (SearchBST(k, p->rchild)); /* ���������� */
    }

}

void InsertBST(int R, BST *F) {
    if (*F == NULL) {
        *F = (BST) malloc(sizeof(BSTNode));
        (*F)->data = R;
        (*F)->lchild = NULL;
        (*F)->rchild = NULL;
    } else if (R < (*F)->data)
        InsertBST(R, &((*F)->lchild));
    else if (R > (*F)->data)
        InsertBST(R, &((*F)->rchild));
} //��R.key==F->data.key,�򷵻�

BST CreateBST1(void) {
    BST F = NULL; //��ʼʱFΪ��
    int R = 1;
    int i;
    for (i = 1; i < 1024; i++) {  //����key=0�����������־
        InsertBST(R, &F);//�����¼R
        R = i * 2 + 1;
    }
    return F;//���ؽ����Ķ���������ĸ�
}

BST CreateBST2(void) {
    BST F = NULL; //��ʼʱFΪ��
    int R = str[0];
    int i;
    for (i = 1; i <= 1024; i++) {  //����key=0�����������־
        InsertBST(R, &F);//�����¼R
        R = str[i];
    }
    return F;//���ؽ����Ķ���������ĸ�
}

int Deletemin(BST *F) {/*ɾ��F����С���*/
    int tmp;
    BST p;
    if ((*F)->lchild == NULL) {//����СԪ
        p = *F;
        tmp = (*F)->data;
        *F = (*F)->rchild; //�����̳�
        //delete p;
        return tmp;
    } else//���������գ���С�������������
        return (Deletemin((*F)->lchild));//���������ϵݹ��ɾ��
}

void DeleteB(keytype k, BST *F) {
    if (F != NULL)
        if (k < (*F)->data)
            DeleteB(k, &((*F)->lchild));
        else if (k > (*F)->data)
            DeleteB(k, &((*F)->rchild));
        else {//( k==F->data.key
            if ((*F)->rchild == NULL)
                *F = (*F)->lchild;//�����̳�,����Ҷ
            else if ((*F)->lchild == NULL)
                *F = (*F)->rchild;//�����̳�,����Ҷ
            else //����������
                (*F)->data = Deletemin(&((*F)->rchild));
        }
}

int BinSearch1(keytype k) {
    int low, up, mid;
    low = 0;
    up = last;
    //if(k==List[0])return 0;if(k==List[1023])return 1023;
    while (low <= up) {
        counter++;
        mid = (low + up) / 2;
        if (List[mid] == k) {
            counter++;
            return mid;
        } else if (List[mid] > k) {
            counter++;
            up = mid - 1;
        } else
            low = mid + 1;
    }
    return -1;
} /*  F������˳�������(�˴�Ϊ����);ʱ�临�Ӷ� :?(log2 n)  */

int BinSearch2(int low, int up, keytype k) {
    int mid;
    //if(k==List[0])return 0;if(k==List[1023])return 1023;
    if (low > up) {
        counter++;
        return -1;
    } else {
        counter++;
        mid = (low + up) / 2;
        if (k < List[mid]) {
            counter++;
            return BinSearch2(low, mid - 1, k);
        } else if (k > List[mid]) {
            counter++;
            return BinSearch2(mid + 1, up, k);
        } else
            return mid;
    }
} /*  F������˳�������(�˴�Ϊ����);ʱ�临�Ӷ� :?(log2 n)  */

void Create1(void) {
    FILE *fp = fopen("data1.txt", "w");
    int i = 0;
    for (i = 0; i < 2048; i++) {
        if (i % 2)
            fprintf(fp, "%d ", i);
    }
    fclose(fp);
}

void Create2(void) {
    FILE *fp = fopen("data2.txt", "w");
    int i, j = 0;
    int a, b, t;
    for (i = 0; i < 1024; i++)
        str[i] = 2 * i + 1;

    srand((unsigned) (time(NULL)));
    for (i = 0; i < 1024; i++) {
        a = rand() % 1024;
        b = rand() % 1024;
        t = str[a];
        str[a] = str[b];
        str[b] = t;
    }

    for (i = 0; i < 1024; i++) {
        fprintf(fp, "%d ", str[i]);
    }
    fclose(fp);
}

void CreatBin1(void) {
    int i = 1;
    for (i = 0; i < 1024; i++) {
        List[i] = i * 2 + 1;
    }
}

int z = 0;

void CreatBin2(BST F) {
    if (!(F == NULL)) {
        CreatBin2(F->lchild);
        List[z++] = F->data;
        CreatBin2(F->rchild);
    }
}

void Time(int x) {
    int R;

    BST F1 = CreateBST1();
    for (int i = 0; i < 1023; i++) {
        counter = 0;
        BST BSTf1 = SearchBST(2 * i + 1, F1);
        C1 = C1 + counter;
    }
    C1 = C1 / 1023;
    printf("BST1 used time is %f\n", C1);

    BST F2 = CreateBST2();
    for (int i = 0; i < 1023; i++) {
        counter = 0;
        BST BSTf2 = SearchBST(i * 2 + 1, F2);
        C2 = C2 + counter;
    }
    C2 = C2 / 1023;
    printf("BST2 used time is %f\n", C2);

    CreatBin1();
    for (int i = 0; i < 1023; i++) {
        counter = 0;
        R = BinSearch1(i * 2 + 1);
        C3 = C3 + counter;
    }
    C3 = C3 / 1023;
    printf("Bin11 used time is %f\n", C3);

    CreatBin2(F2);
    for (int i = 0; i < 1023; i++) {
        counter = 0;
        R = BinSearch1(i * 2 + 1);
        C4 = C4 + counter;
    }
    C4 = C4 / 1023;
    printf("Bin12 used time is %f\n", C4);

    CreatBin1();
    for (int i = 0; i < 1023; i++) {
        counter = 0;
        R = BinSearch2(Low, Up, 2 * i + 1);
        C5 = C5 + counter;
    }
    C5 = C5 / 1023;
    printf("Bin21 used time is %f\n", C5);

    CreatBin2(F2);
    for (int i = 0; i < 1023; i++) {
        counter = 0;
        R = BinSearch2(Low, Up, 2 * i + 1);
        C6 = C6 + counter;
    }
    C6 = C6 / 1023;
    printf("Bin22 used time is %f\n", C6);
}
