#include <bits/stdc++.h>

typedef struct Queue{
    int *arr;
    int head, tail;
    int maxVol;
} Queue;


Queue* init(unsigned size){
    Queue *que = (Queue*) malloc(sizeof(Queue));
    if(que){
        que->arr = (int*)calloc(size, sizeof(int));
        que->head = -1;
        que->tail = -1;
    }   return que;
}

void destroy(Queue *que){
    if(!que) return;
    free(que->arr);
    free(que);
}

bool isEmpty(Queue *que){
    return que->head == -1;
}

bool isFull(Queue *que){
    return que->maxVol == que->tail - que->head + 1;
}

void enqueue(Queue *que, int val){
    if(isFull(que)) return;
    if(isEmpty(que)) que->head++;
    que->tail++;
    que->arr[que->tail] = val;
}

int dequeue(Queue *que){
    int elem = -1;
    if(!isEmpty(que)){
        elem = que->arr[que->head];
        if(que->head == que->tail){
            que->head = -1;
            que->tail = -1;
        }   else {
            que->head++;
        }
    }   return elem;
}

void bfs(int **adjMatrix, int vCount, Queue* que, int startIdx){
    if(startIdx >= vCount) return;
    int node;
    int visited[vCount];
    for(int i = 0; i < vCount; i++){
        visited[i] = 0;
    }
    enqueue(que, startIdx);
    visited[startIdx] = 1;
    printf("BFS -> ");
    while(!isEmpty(que)){
        node = dequeue(que);
        printf(" V-%d", node);
        for(int i = 0; i < vCount; i++){
            if(adjMatrix[node][i] == 1 && visited[i] == 0){
                visited[i] = 1;
                enqueue(que, i);
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

void run(void){
    unsigned vCount ,eCount;
    printf("Enter number of vertices: ");
    scanf("%u", &vCount);
    printf("Enter number of edges: ");
    scanf("%u", &eCount);
    if(2*eCount > vCount*(vCount-1)) return;
    // Declare Adj. Matrix
    int **arr = NULL;
    arr = (int**)calloc(vCount, sizeof(int*));
    for(int i = 0 ; i < vCount; i++){
        arr[i] = (int*)calloc(vCount, sizeof(int));
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
    // Init Queue;
    Queue *que = init(2000);
    // Enter start idx
    int startIdx;
    printf("Enter startIdx: ");
    scanf("%d", &startIdx);
    // Start BFS
    bfs(arr, vCount, que, startIdx);
    // Delete Queue
    destroy(que);
    for(int i = 0; i < vCount; i++){
        free(arr[i]);
    }
    if(arr) free(arr);
}

int main(void){
    run();
    return 0;
}
