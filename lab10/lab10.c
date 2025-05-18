#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
    int size;
    int *ptr_arr; // parent
} DisjointSets;

typedef struct _PrintDisjointSet{
    int size;
    int *ptr_arr; // wall, (if wall exists -> 1, otherwise 0)
} PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets *maze, int n);
int find(DisjointSets *sets, int x);
void union_(DisjointSets *sets, int i, int j);
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n);
void printMaze(PrintDisjointSets *maze, int n);
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze);

int main(int argc, char* argv[]){
    int num;
    FILE *fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &num);
    fclose(fi);

    DisjointSets *sets;
    PrintDisjointSets *maze;

    sets = (DisjointSets*)malloc(sizeof(DisjointSets));
    maze = (PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));

    init(sets, maze, num);
    createMaze(sets, maze, num);
    printMaze(maze, num);
    freeMaze(sets, maze);

    return 0;
}

void init(DisjointSets *sets, PrintDisjointSets *maze, int n){
    int s = n * n;
    sets->size = s;
    sets->ptr_arr = (int*)malloc(s * sizeof(int));
    for(int i = 0; i < s; i++) 
        sets->ptr_arr[i] = -1;
    maze->size = 2 * s;
    maze->ptr_arr = (int*)malloc(maze->size * sizeof(int));
    for(int j = 0; j < maze->size; j++){
        if(j == sets->size-1)
            maze->ptr_arr[j] = 0;
        else{
            maze->ptr_arr[j] = 1;
        }
    }
}

int find(DisjointSets *sets, int x){
    if(sets->ptr_arr[x] < 0)
        return x;
    else
        return find(sets, sets->ptr_arr[x]);
}

void union_(DisjointSets *sets, int i, int j){
    int root_i = find(sets, i);
    int root_j = find(sets, j);

    if(root_i == root_j)
        return;
    else
        if(sets->ptr_arr[root_i] < sets->ptr_arr[root_j])
            sets->ptr_arr[root_j] = root_i;
        else{
            if(sets->ptr_arr[root_i] == sets->ptr_arr[root_j])
                sets->ptr_arr[root_j]--;
            sets->ptr_arr[root_i] = root_j;
        }
}

void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n){
    srand(time(NULL));
    int s = maze->size;
    while(find(sets, 0) != find(sets, (sets->size-1))){
        int i = rand() % s;
        if((i % n) == n - 1)
            continue;
        int root1, root2;
        if(i < sets->size - 1){
            root1 = find(sets, i);
            root2 = find(sets, i+1);
        }
        else if(i < 2 * sets->size - 1){
            if(i + n > maze->size - 1)
                continue;
            root1 = find(sets, i % sets->size);
            root2 = find(sets, (i % sets->size) + n);
        }
        if(root1 != root2){
            union_(sets, root1, root2);
            maze->ptr_arr[i] = 0;
        }
    }
}

void printMaze(PrintDisjointSets *maze, int n){
    printf("*");
    for(int i = 0; i < n; i++){
        printf("-*");
    }
    printf("\n");
    int size = n * n;
    for(int i = 0; i < n; i++){
        for(int j = n * i; j < n * i + n; j++){
            if(j == n * i){
                if(i == 0)
                    printf(" ");
                else
                    printf("|");
            }
            if(maze->ptr_arr[j] == 1)
                printf(" |");
            else
                printf("  ");
        }
        printf("\n");
        for(int j = n * i; j < n * i + n; j++){
            printf("*");
            if(maze->ptr_arr[j + size] == 1)
                printf("-");
            else
                printf(" ");
        }
        printf("*");
        printf("\n");
    }
}

void freeMaze(DisjointSets *sets, PrintDisjointSets *maze){
    free(sets->ptr_arr);
    free(sets);
    free(maze->ptr_arr);
    free(maze);
}