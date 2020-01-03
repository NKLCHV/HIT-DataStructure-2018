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
//折半
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
BST SearchBST(keytype k, BST F);//查找
void InsertBST(int R, BST *F);//插入
BST CreateBST1(void);//建立BST树
BST CreateBST2(void);//
int Deletemin(BST *F);//删除最小
void DeleteB(keytype k, BST *F);//
//折半查找
void CreatBin1(void);//
void CreatBin2(BST F);//
int BinSearch1(keytype k);//非递归折半查找
int BinSearch2(int low, int up, keytype k);//递归折半查找
//查找测试模块
void Time(int x);//时间测量模块
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
    if (p == NULL || k == p->data) { /* 递归终止条件 */
        counter++;
        return p;
    }
    if (p->rchild == NULL && p->lchild == NULL && p->data != k)
        return NULL;
    if (k < p->data) {
        counter++;
        return (SearchBST(k, p->lchild)); /* 查找左子树 */
    } else {
        counter++;
        return (SearchBST(k, p->rchild)); /* 查找右子树 */
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
} //若R.key==F->data.key,则返回

BST CreateBST1(void) {
    BST F = NULL; //初始时F为空
    int R = 1;
    int i;
    for (i = 1; i < 1024; i++) {  //假设key=0是输入结束标志
        InsertBST(R, &F);//插入记录R
        R = i * 2 + 1;
    }
    return F;//返回建立的二叉查找树的根
}

BST CreateBST2(void) {
    BST F = NULL; //初始时F为空
    int R = str[0];
    int i;
    for (i = 1; i <= 1024; i++) {  //假设key=0是输入结束标志
        InsertBST(R, &F);//插入记录R
        R = str[i];
    }
    return F;//返回建立的二叉查找树的根
}

int Deletemin(BST *F) {/*删除F的最小结点*/
    int tmp;
    BST p;
    if ((*F)->lchild == NULL) {//是最小元
        p = *F;
        tmp = (*F)->data;
        *F = (*F)->rchild; //右链继承
        //delete p;
        return tmp;
    } else//左子树不空，最小结点在左子树上
        return (Deletemin((*F)->lchild));//在左子树上递归地删除
}

void DeleteB(keytype k, BST *F) {
    if (F != NULL)
        if (k < (*F)->data)
            DeleteB(k, &((*F)->lchild));
        else if (k > (*F)->data)
            DeleteB(k, &((*F)->rchild));
        else {//( k==F->data.key
            if ((*F)->rchild == NULL)
                *F = (*F)->lchild;//右链继承,包括叶
            else if ((*F)->lchild == NULL)
                *F = (*F)->rchild;//右链继承,包括叶
            else //有两棵子树
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
} /*  F必须是顺序有序表(此处为增序);时间复杂度 :?(log2 n)  */

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
} /*  F必须是顺序有序表(此处为增序);时间复杂度 :?(log2 n)  */

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
