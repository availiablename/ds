#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Max(ElementType num1, ElementType num2);
int Height(Position P);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
AVLTree Insert(ElementType X, AVLTree T);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);

int main(int argc, char *argv[]){
    AVLTree myTree = NULL;
    int key;

    FILE *fi = fopen(argv[1], "r");
    while(fscanf(fi, "%d", &key) != EOF){
        myTree = Insert(key, myTree);
    }
    fclose(fi);

    PrintInorder(myTree);
    printf("\n");

    DeleteTree(myTree);
    return 0;
}

int Max(ElementType num1, ElementType num2){
    if(num1 > num2)
        return num1;
    else
        return num2;
}

int Height(Position P){
    if(P == NULL)
        return -1;
    else
        return P->Height;
}

Position SingleRotateWithLeft(Position node){
    Position temp;
    temp = node->Left;

    node->Left = temp->Right;
    temp->Right = node;

    temp->Height = Max(Height(temp->Left), Height(temp->Right)) + 1;
    node->Height = Max(Height(node->Left), Height(node->Right)) + 1;

    return temp;
}

Position SingleRotateWithRight(Position node){
    Position temp;
    temp = node->Right;

    node->Right = temp->Left;
    temp->Left = node;

    temp->Height = Max(Height(temp->Left), Height(temp->Right)) + 1;
    node->Height = Max(Height(node->Left), Height(node->Right)) + 1;

    return temp;
}

Position DoubleRotateWithLeft(Position node){
    node->Left = SingleRotateWithRight(node->Left);

    return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node){
    node->Right = SingleRotateWithLeft(node->Right);

    return SingleRotateWithRight(node);
}

AVLTree Insert(ElementType X, AVLTree T){
    if(T == NULL){
        T = malloc(sizeof(struct AVLNode));
        T->Element = X;
        T->Left=T->Right=NULL;
    }
    else if(X < T->Element){
        T->Left = Insert(X, T->Left);
        if(Height(T->Left) - Height(T->Right) == 2){
            if(X < T->Left->Element){
                printf("There's node(%d) to be balanced! Do SingleRotateWithLeft!\n", T->Element);
                T = SingleRotateWithLeft(T);
            }
            else{
                printf("There’s node(%d) to be balanced! Do DoubleRotateWithLeft!\n", T->Element);
                T = DoubleRotateWithLeft(T);
            }
        }
    }
    else if(X > T->Element){
        T->Right = Insert(X, T->Right);
        if(Height(T->Right) - Height(T->Left) == 2){
            if(X > T->Right->Element){
                printf("There's node(%d) to be balanced! Do SingleRotateWithRight!\n", T->Element);
                T = SingleRotateWithRight(T);
            }
            else{
                printf("There's node(%d) to be balanced! Do DoubleRotateWithRight!\n", T->Element);
                T = DoubleRotateWithRight(T);
            }
        }
    }
    else{
        printf("Insertion Error: %d is already in the tree!\n", T->Element);
    }
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

void PrintInorder(AVLTree T){
    if(T == NULL)
        return;
    if(T->Left != NULL)
        PrintInorder(T->Left);
    printf("%d(%d) ", T->Element, T->Height);
    if(T->Right != NULL)
        PrintInorder(T->Right);
}

void DeleteTree(AVLTree T){
    if(T == NULL)
        return;
    if(T->Left != NULL)
        DeleteTree(T->Left);
    if(T->Right != NULL)
        DeleteTree(T->Right);
    free(T);
}

