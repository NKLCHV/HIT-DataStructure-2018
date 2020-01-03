#include <stdio.h>
#include <stdlib.h>

#define MAX 100
struct node {
    long data;
    struct node *lchild;
    struct node *rchild;
};
typedef struct node *TREE;

void pre_create_1(TREE *root);
void pre_create_2(TREE *root);
void mid_create_1(TREE *root);
void mid_create_2(TREE *root);
void pre_order_1(TREE root);
void pre_order_2(TREE root);
void mid_order_1(TREE root);
void mid_order_2(TREE root);
void back_order_1(TREE root);
void back_order_2(TREE root);
void level_order(TREE root);
int check_full(TREE root);

int main() {
    while (1) {
        TREE tree;
        tree = (TREE) malloc(sizeof(struct node));
        char choose_1, choose_2;
        printf("A.pre_create_1  B.mid_create_1  C.pre_create_2  D.mid_create_2\n");
        scanf("%c", &choose_1);
        if (choose_1 == 'A' || choose_1 == 'a')
            pre_create_1(&tree);
        else if (choose_1 == 'B' || choose_1 == 'b')
            mid_create_1(&tree);
        else if (choose_1 == 'C' || choose_1 == 'c')
            pre_create_2(&tree);
        else if (choose_1 == 'D' || choose_1 == 'd')
            mid_create_2(&tree);
        else
            continue;

        printf("A.pre_order_1  B.pre_order_2  C.mid_order_1  D.mid_order_2  E.back_order_1  F.back_order_2  G.level_order\n");
        getchar();
        scanf("%c", &choose_2);
        if (choose_2 == 'A' || choose_2 == 'a')
            pre_order_1(tree);
        else if (choose_2 == 'B' || choose_2 == 'b')
            pre_order_2(tree);
        else if (choose_2 == 'C' || choose_2 == 'c')
            mid_order_1(tree);
        else if (choose_2 == 'D' || choose_2 == 'd')
            mid_order_2(tree);
        else if (choose_2 == 'E' || choose_2 == 'e')
            back_order_1(tree);
        else if (choose_2 == 'F' || choose_2 == 'f')
            back_order_2(tree);
        else if (choose_2 == 'G' || choose_2 == 'g')
            level_order(tree);
        else
            continue;

        if (check_full(tree) == 1)
            printf("It's a full tree.\n");
        else
            printf("It isn't a full tree.\n");
        getchar();
        printf("\nDo you want to continue? (y/n) \n");
        if (getchar() == 'n')
            break;
        getchar();
    }
    return 0;
}

void pre_create_1(TREE *root) {
    *root = (TREE) malloc(sizeof(struct node));
    printf("please input data if you input 0,it means an end.\n");
    long x;
    scanf("%ld", &x);
    if (x == 0)
        *root = NULL;
    else {
        (*root)->data = x;
        pre_create_1(&((*root)->lchild));
        pre_create_1(&((*root)->rchild));
    }
}

void pre_create_2(TREE *root) {
    struct node *str[MAX];
    int i, j;
    long x;
    TREE tmp;
    printf("please input the number of nodes and data in order\n");
    scanf("%d,%ld", &i, &x);

    while (i != 0 && x != 0) {
        tmp = (TREE) malloc(sizeof(struct node));
        tmp->data = x;
        tmp->lchild = NULL;
        tmp->rchild = NULL;
        str[i] = tmp;
        if (i == 1)
            *root = tmp;
        else {
            j = i / 2;
            if (i % 2 == 0)
                str[j]->lchild = tmp;
            else
                str[j]->rchild = tmp;
        }
        printf("please input the number of nodes and data in order\n");
        scanf("%d,%ld", &i, &x);
    }
}

void mid_create_1(TREE *root) {
    *root = (TREE) malloc(sizeof(struct node));
    printf("please input data if you input 0,it means an end.\n");
    long x;
    scanf("%ld", &x);

    if (x == 0)
        *root = NULL;
    else {
        mid_create_1(&((*root)->lchild));
        (*root)->data = x;
        mid_create_1(&((*root)->rchild));
    }
}

void mid_create_2(TREE *root) {
    struct node *str[MAX];
    int i, j;
    long x;
    TREE tmp;
    printf("please input the number of nodes and data in order\n");
    scanf("%d,%ld", &i, &x);
    while (i != 0 && x != 0) {
        tmp = (TREE) malloc(sizeof(struct node));
        tmp->data = x;
        tmp->lchild = NULL;
        tmp->rchild = NULL;
        str[i] = tmp;
        if (i == 1)
            *root = tmp;
        else {
            j = i / 2;
            if (i % 2 == 0)
                str[j]->rchild = tmp;
            else
                str[j]->lchild = tmp;
        }
        printf("please input the number of nodes and data in order\n");
        scanf("%d,%ld", &i, &x);
    }
}

void pre_order_1(TREE root) {
    if (root != NULL) {
        printf("%ld\t", root->data);
        pre_order_1(root->lchild);
        pre_order_1(root->rchild);
    }
}

void pre_order_2(TREE root) {
    int top = -1;
    TREE str[MAX];
    while (root != NULL || top != -1) {
        while (root != NULL) {
            printf("%ld\t", root->data);
            str[++top] = root;
            root = root->lchild;
        }
        if (top != -1) {
            root = str[top--];
            root = root->rchild;
        }
    }
}

void mid_order_1(TREE root) {
    if (root != NULL) {
        mid_order_1(root->lchild);
        printf("%ld\t", root->data);
        mid_order_1(root->rchild);
    }
}

void mid_order_2(TREE root) {
    int top = -1;
    TREE str[MAX];
    while (root != NULL || top != -1) {
        while (root != NULL) {
            str[++top] = root;
            root = root->lchild;
        }
        if (top != -1) {
            root = str[top--];
            printf("%ld\t", root->data);
            root = root->rchild;
        }
    }
}

void back_order_1(TREE root) {
    if (root != NULL) {
        back_order_1(root->lchild);
        back_order_1(root->rchild);
        printf("%ld\t", root->data);
    }
}

void back_order_2(TREE root) {
    TREE pre, p;
    int top = -1;
    TREE str[MAX];
    p = root;
    while (p != NULL || top != -1) {
        while (p != NULL) {
            str[++top] = p;
            pre = p->rchild;
            p = p->lchild;
            if (p == NULL)
                p = pre;
        }
        p = str[top--];
        printf("%ld\t", p->data);
        if (top != -1 && str[top]->lchild == p)
            p = str[top]->rchild;
        else
            p = NULL;
    }
}

void level_order(TREE root) {
    int top = 0, tail = 0;
    TREE Q[100];
    if (root == NULL)
        return;
    Q[++tail] = root;
    TREE q;
    q = (TREE) malloc(sizeof(struct node));
    while (top != tail) {
        q = Q[++top];
        printf("%ld\t", q->data);
        if (q->lchild != NULL)
            Q[++tail] = q->lchild;
        if (q->rchild != NULL)
            Q[++tail] = q->rchild;
    }
}

int check_full(TREE root) {
    int top = 0, tail = 0;
    int s[MAX], i = 0, j = 0;
    TREE Q[MAX];
    if (root == NULL)
        return 1;
    Q[++tail] = root;
    TREE q;
    q = (TREE) malloc(sizeof(struct node));
    while (top != tail) {
        q = Q[++top];
        if (q->lchild != NULL) {
            Q[++tail] = q->lchild;
            s[i++] = 1;
        } else {
            s[i++] = 0;
        }

        if (q->rchild != NULL) {
            Q[++tail] = q->rchild;
            s[i++] = 1;
        } else {
            s[i++] = 0;
        }
    }

    for(j=0;j<i;j++)
        printf("%d",s[j]);
    int flag1 = 1, flag2 = 0;
    for (j = 0; j < i; j++) {
        if (flag2 == 0 && s[j] == 0) {
            flag1 = 0;
        }
        if (flag1 == 0 && s[j] == 1) {
            flag2 = 1;
        }
    }
    if (flag1 == 0 && flag2 == 1)
        return 0;
    else
        return 1;
}