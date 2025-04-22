#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode *PtrToNode;
typedef struct TreeNode *Tree;

struct TreeNode{
    int element;
    Tree left;
    Tree right;
};

Tree MakeEmpty(Tree tree);
Tree Insert(Tree tree, int value);
Tree Delete(Tree tree, int value);
PtrToNode Find(Tree tree, int value);
PtrToNode FindMin(Tree tree);
PtrToNode FindMax(Tree tree);
void Print(Tree tree);
void PrintInorder(Tree tree);

int main(int argc, char* argv[]){
    FILE *input;
    Tree tree = NULL;
    char command;
    int value, max, min;

    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("File %s open failed\n", argv[1]);
        return 0;
    }

    while(1){
        command = fgetc(input);
        if(feof(input)) break;

        switch(command){
            case 'i':
                fscanf(input, "%d", &value);
                tree = Insert(tree, value);
                break;
            case 'd':
                fscanf(input, "%d", &value);
                tree = Delete(tree, value);
                break;
            case 'f':
                fscanf(input, "%d", &value);
                PtrToNode result = Find(tree, value);
                if(result != NULL) printf("element %d exist.\n", result->element);
                else printf("Find failed : Element %d not found.\n", value);
                break;
            case 'm':
                if(tree == NULL){
                    printf("Min : NULL\n");
                    printf("Max : NULL\n");
                }
                else{
                    max = FindMax(tree)->element;
                    min = FindMin(tree)->element;
                    printf("Min : %d\n", min);
                    printf("Max : %d\n", max);
                }
                break;
            case 'p':
                printf("Inorder : ");
                if(tree != NULL)
                    PrintInorder(tree);
                printf("\n");
                break;
            default:
                break;
        }
    }
    MakeEmpty(tree);

    return 0;
}

Tree MakeEmpty(Tree tree){
    if(tree == NULL)
        return NULL;
    else if(tree->left != NULL)
        MakeEmpty(tree->left);
    else if(tree->right != NULL)
        MakeEmpty(tree->right);
    free(tree);
}

Tree Insert(Tree tree, int value){
    if(tree != NULL){
        if(Find(tree, value) != NULL){
            printf("Insert failed : Element %d is existed.\n", value);
            return tree;
        }
        if(tree->element < value)
            tree->right = Insert(tree->right, value);
        if(tree->element > value)
            tree->left = Insert(tree->left, value);
    }
    else{
        tree = malloc(sizeof(tree));
        tree->element = value;
        tree->left = NULL;
        tree->right = NULL;
    }
    return tree;
}
Tree Delete(Tree tree, int value){
    if(tree == NULL || Find(tree, value) == NULL){
        printf("Delete failed : Element %d not found\n", value);
        return tree;
    }
    if(value > tree->element)
        tree->right = Delete(tree->right, value);
    else if(value < tree->element)
        tree->left = Delete(tree->left, value);
    else{
        PtrToNode temp;
        if(tree->left != NULL && tree->right != NULL){
            temp = FindMin(tree->right);
            tree->element = temp->element;
            tree->right = Delete(tree->right, tree->element);
        }
        else if(tree->left == NULL){
            tree = tree-> right;
        }
        else if(tree->right == NULL){
            tree = tree->left;
        }
    }
    return tree;
}
PtrToNode Find(Tree tree, int value){
    if(tree->element == value)
        return tree;
    else if(tree->element > value){
        if(tree->left == NULL)
            return NULL;
        Find(tree->left, value);
    }
    else{
        if(tree->right == NULL){
            return NULL;
        }
        Find(tree->right, value);
    }
}
PtrToNode FindMin(Tree tree){
    if(tree == NULL)
        return NULL;
    else if(tree->left != NULL){
        tree = FindMin(tree->left);
    }
    return tree;
}
PtrToNode FindMax(Tree tree){
    if(tree == NULL)
        return NULL;
    else
        while(tree->right != NULL)
            tree = tree->right;
    return tree;
}
void Print(Tree tree){
    printf("%d ", tree->element);
}
void PrintInorder(Tree tree){
    if(tree == NULL)
        return;
    if(tree->left != NULL)
        PrintInorder(tree->left);
    Print(tree);
    if(tree->right != NULL)
        PrintInorder(tree->right);

}