#include<stdio.h>
#include<stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct{
    int Capacity; //max heap capacity
    int Size; //current heap size
    int *Element;
};

Heap CreateHeap(int heapSize);
void Insert(Heap heap, int value);
int Find(Heap heap, int value);
void DeleteMax(Heap heap);
void PrintHeap(Heap heap);
void FreeHeap(Heap heap);

int main(int argc, char* argv[]){
    FILE *fi = fopen(argv[1], "r");
    char cv;
    Heap maxHeap;
    int value, MaxValue;

    while(!feof(fi)){
        fscanf(fi, "%c", &cv);
        switch(cv){
            case 'n':
                fscanf(fi, "%d", &value);
                maxHeap = CreateHeap(value);
                break;
            case 'i':
                fscanf(fi, "%d", &value);
                Insert(maxHeap, value);
                break;
            case 'd':
                DeleteMax(maxHeap);
                break;
            case 'f':
                fscanf(fi, "%d", &value);
                if(Find(maxHeap, value))
                    printf("%d is in the heap.\n", value);
                else
                    printf("%d is not in the heap.\n", value);
                break;
            case 'p':
                PrintHeap(maxHeap);
        }
    }
    FreeHeap(maxHeap);
    return 0;
}

Heap CreateHeap(int heapSize){
    Heap maxHeap = (Heap)malloc(sizeof(struct HeapStruct));
    maxHeap->Capacity = heapSize;
    maxHeap->Size = 0;
    maxHeap->Element = (int*)malloc(sizeof(int) * heapSize);
}

void Insert(Heap heap, int value){
    int i;
    if(heap->Size == heap->Capacity){
        printf("Insertion Error : Max Heap is full!\n");
        return;
    }
    if(heap->Size == 0){
        heap->Size++;
        heap->Element[0] = value;
        printf("Insert %d\n", value);
        return;
    }
    if(Find(heap, value)){
        printf("%d is already in the heap.\n", value);
        return;
    }
    for(i = heap->Size; i > 0;  i = (i - 1) / 2){
        if(value > heap->Element[(i-1)/2])
            heap->Element[i] = heap->Element[(i-1)/2];
        else
            break;
    }
    heap->Size++;
    heap->Element[i] = value;
    printf("Insert %d\n", value);
}

int Find(Heap heap, int value){
    for(int i = 0; i < heap->Size + 1; i++){
        if(value == heap->Element[i])
            return 1;
    }
    return 0;
}

void DeleteMax(Heap heap){
    int i, child;
    int max, last;
    if(heap->Size == 0){
        printf("Deletion Error : Max Heap is empty!\n");
        return;
    }
    max = heap->Element[0];
    heap->Element[0] = 0;
    last = heap->Element[heap->Size-1];
    for(i = 0; i*2 + 1 < heap->Size; i = child){
        child = 2 * i + 1;
        if(child != heap->Size && heap->Element[child + 1] > heap->Element[child]){
            child++;
        }
        if(last > heap->Element[child])
            heap->Element[i] = last;
        else{
            heap->Element[i] = heap->Element[child]; 
            heap->Element[child] = 0;
        }  
    }
    heap->Element[i] = last;
    heap->Size--;
    printf("Max Element %d is deleted.\n", max);
}

void PrintHeap(Heap heap){
    int child;
    if(heap->Size == 0){
        printf("Print Error : Max Heap is empty!\n");
        return;
    }
    for(int i = 0; i < heap->Size; i++)
        printf("%d ", heap->Element[i]);
    printf("\n");
}

void FreeHeap(Heap heap){
    free(heap->Element);
    free(heap);
}