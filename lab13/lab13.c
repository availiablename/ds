#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue{
    int size;
    int *key;
    int front;
    int rear;
}Queue;

Queue *CreateQueue(int X);
void Enqueue(Queue *Q, int item);
int Dequeue(Queue *Q);

typedef struct _Graph{
    int size;
    int *vertex;
    int **edge;
}Graph;

Graph *CreateGraph(int X);
void InsertEdge(Graph *G, int u, int v);
void Topsort(Graph *G);

int main(int argc, char *argv[]){
    FILE *fi = fopen(argv[1], "r");
    int X, u, v;

    fscanf(fi, "%d", &X);

    Graph *G = CreateGraph(X);

    for(int i = 0; i < X; i++){
        fscanf(fi, "%d", &G->vertex[i]);
    }

    while(fscanf(fi, "%d %d", &u, &v) != EOF){
        InsertEdge(G, u, v);
    }

    Topsort(G);

    return 0;
}

Queue *CreateQueue(int X){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->size = 0;
    q->key = (int*)malloc(sizeof(int) * X);
    q->front = 0;
    q->rear = -1;
    return q;
}

void Enqueue(Queue *Q, int item){
    Q->key[++Q->rear] = item;
    Q->size++;
}

int Dequeue(Queue *Q){
    int pop_num;
    pop_num = Q->key[Q->front++];
    Q->size--;
    return pop_num;
}

Graph* CreateGraph(int X){
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->size = X;
    G->vertex = (int*)malloc(sizeof(int) * X);
    G->edge = (int**)malloc(sizeof(int*) * X);
    for(int i = 0; i < X; i++){
        G->vertex[i] = 0;
    }
    for(int i = 0; i < X; i++){
        G->edge[i] = (int*)malloc(sizeof(int) * X);
    }
    for(int i = 0; i < X; i++){
        for(int j = 0; j < X; j++){
            G->edge[i][j] = 0;
        }
    }
    return G;
}

void InsertEdge(Graph *G, int u, int v){
    int idx_u, idx_v;
    for(int i = 0; i < G->size; i++){
        if(G->vertex[i] == u)
            idx_u = i;
        if(G->vertex[i] == v)
            idx_v = i;
    }
    G->edge[idx_u][idx_v] += 1;
}

void Topsort(Graph *G){
    int indegree[(G->size)];
    for(int i = 0; i < G->size; i++)
        indegree[i] = 0;
    Queue* Q = CreateQueue(G->size);
    for(int i = 0; i < G->size; i++){
        for(int j = 0; j < G->size; j++){
            if(G->edge[i][j] != 0)
                indegree[j]++;
        }
    }
    for(int i = 0; i < G->size; i++){
        if(indegree[i] == 0){
            Enqueue(Q, i);
            indegree[i] = -1;
        }
    }
    int j = 0;
    while(Q->size){
        j = Dequeue(Q);
        for(int i = 0; i < G->size; i++){
            if(G->edge[j][i]){
                indegree[i] -= 1;
            }
            if(indegree[i] == 0){
                Enqueue(Q, i);
                indegree[i] = -1;
            }
        }
        printf("%d ", G->vertex[j]);
    }
    printf("\n");
}