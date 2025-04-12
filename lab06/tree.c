#include<stdio.h>
#include<stdlib.h>

struct TreeStruct{
    int size;
    int numOfNode;
    int* element;
};

typedef struct TreeStruct* Tree;

Tree CreateTree(int size);
void Insert(Tree tree, int value);
void PrintTree(Tree tree);
void PrintPreorder(Tree tree, int index);
void PrintInorder(Tree tree, int index);
void PrintPostorder(Tree tree, int index);
void DeleteTree(Tree tree);

int main(int argc, char* argv[]){
    FILE* fi;
    Tree tree;
    int treeSize;
    int tmpNum;

    fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &treeSize);

    tree = CreateTree(treeSize);

    while(fscanf(fi, "%d", &tmpNum) == 1){
        Insert(tree, tmpNum);
    }

    PrintTree(tree);
    DeleteTree(tree);

    return 0;
}

Tree CreateTree(int size){
    Tree tree = malloc(sizeof(Tree));
    tree->size = size;
    tree->numOfNode = 0;
    tree->element = malloc(sizeof(int) * size);
}

void Insert(Tree tree, int value){
    if(tree->size == tree->numOfNode)
        printf("Error with node %d! Tree is already full so we cannot insert any node in the tree!\n", value);
    else
        tree->element[tree->numOfNode++] = value;
}

void PrintTree(Tree tree){
    PrintPreorder(tree, 0);
    printf("\n");
    PrintInorder(tree, 0);
    printf("\n");
    PrintPostorder(tree, 0);
    printf("\n");
}

void PrintPreorder(Tree tree, int index){
    if(index >= tree->numOfNode)
        return;
    if(index == 0)
        printf("Preorder: ");
    printf("%d ", tree->element[index]);
    PrintPreorder(tree, 2 * index + 1);
    PrintPreorder(tree, 2 * index + 2);
    
}  

void PrintInorder(Tree tree, int index){
    if(index >= tree->numOfNode)
        return;
    if(index == 0)
        printf("Inorder: ");
    PrintInorder(tree, 2 * index + 1);
    printf("%d ", tree->element[index]);
    PrintInorder(tree, 2 * index + 2);
}

void PrintPostorder(Tree tree, int index){
    if(index >= tree->numOfNode)
        return;
    if(index == 0){
        printf("Postorder: ");
    }
    PrintPostorder(tree, 2 * index + 1); // 1 3 5 7
    PrintPostorder(tree, 2 * index + 2); // 2 4 6 
    printf("%d ", tree->element[index]);
}

void DeleteTree(Tree tree){
    free(tree->element);
    free(tree);
}