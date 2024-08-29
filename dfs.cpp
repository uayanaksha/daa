#include <bits/stdc++.h>

typedef struct Stack{
    int *arr;
    int head;
    int maxVol;
} Stack;

Stack* init(unsigned size){
    Stack *ptr = (Stack*) malloc(sizeof(Stack));
    if(ptr){
        ptr->arr = (int*)calloc(size, sizeof(int));
        ptr->head = -1;
        ptr->maxVol = size;
    }   return ptr;
}

Stack* destroy(Stack *st){
    Stack *ptr = st;
    if(ptr){
        free(ptr->arr);
        free(ptr);
    }   return ptr;
}

bool isEmpty(Stack *st){
    return st->head == -1;
}

bool isFull(Stack *st){
    return st->maxVol == st->head + 1;
}

void push(Stack *st, int val){
    if(isFull(st)) return;
    st->head++;
    st->arr[st->head] = val;
}

int pop(Stack *st){
    int elem;
    elem = isEmpty(st) ? -1 : st->arr[st->head--];
    return elem;
}

void dfs(int **adjMatrix, int vCount, Stack* st, int startIdx){
    if(startIdx >= vCount) return;
    int node;
    int visited[vCount];
    for(int i = 0; i < vCount; i++){
        visited[i] = 0;
    }
    push(st, startIdx);
    visited[startIdx] = 1;
    printf("DFS -> ");
    while(!isEmpty(st)){
        node = pop(st);
        printf(" V-%d", node);
        for(int i = 0; i < vCount; i++){
            if(adjMatrix[node][i] == 1 && visited[i] == 0){
                visited[i] = 1;
                push(st, i);
            }
        }
    }   printf("\n");
}

void display(int **arr, unsigned size){
    printf("List[%d][%d]:\n", size, size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf(" %d", arr[i][j]);
        }   printf("\n");
    }   printf("\n");
}

int main(void){
    unsigned vCount ,eCount;
    printf("Enter number of vertices: ");
    scanf("%u", &vCount);
    printf("Enter number of edges: ");
    scanf("%u", &eCount);
    if(2*eCount > vCount*(vCount-1)) return 1;
    // Declare Adj. Matrix
    int **arr = NULL;
    arr = calloc(vCount, sizeof(int*));
    for(int i = 0 ; i < vCount; i++){
        arr[i] = calloc(vCount, sizeof(int));
    }
    // Initialize matrix
    for(int i =0, iidx, fidx; i < eCount;){
        printf("[Edge-%d]\n", i+1);
        printf("Initial idx: ");
        scanf("%d", &iidx);
        printf("Final idx: ");
        scanf("%d", &fidx);
        if(iidx == fidx){
            printf("*Self-Loop not allowed!\n");
        }   else if (iidx >= vCount || fidx >= vCount){
            printf("*Idx out of Range!\n");
        }   else if(arr[iidx][fidx]){
            printf("*Duplicate Entry!\n");
        }   else {
            arr[iidx][fidx] = 1;
            arr[fidx][iidx] = 1;
            i++;
        }   printf("---\n");
    }
    display(arr, vCount);
    // Init Stack;
    Stack *st = init(2000);
    // Enter start idx
    int startIdx;
    printf("Enter startIdx: ");
    scanf("%d", &startIdx);
    // Start DFS
    dfs(arr, vCount, st, startIdx);
    // Delete Stack
    st = destroy(st);
    for(int i = 0; i < vCount; i++){
        free(arr[i]);
    }
    if(arr) free(arr);
    return 0;
}

