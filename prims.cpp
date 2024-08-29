#include <bits/stdc++.h>

typedef int** Graph;

Graph INITGraph(unsigned vCount){
    Graph graph = (int**)calloc(vCount, sizeof(int*));
    for(int i = 0 ; i < vCount; i++){
        graph[i] = (int*)calloc(vCount, sizeof(int));
    }   return graph;
}

void DELETEGraph(Graph graph, unsigned vCount){
    for(int i = 0; i < vCount; i++){
        free(graph[i]);
    }
    if(graph) free(graph);
}

void display(Graph graph, unsigned vCount){
    printf("List[%d][%d]:\n", vCount, vCount);
    for(int i = 0; i < vCount; i++){
        for(int j = 0; j < vCount; j++){
            printf(" %d", graph[i][j]);
        }   printf("\n");
    }   printf("\n");
}

static int minKey(int key[], bool mstSet[], unsigned vCount){
    int min = INT_MAX, min_index;
    for (int v = 0; v < vCount; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

static void printMST(int parent[], Graph graph, unsigned vCount){
    printf("%2s|%2s\n", "Edge", "Weight");
    for (int i = 1; i < vCount; i++){
        printf(" %.2d-%.2d ", parent[i], i);
        printf(" %d\n", graph[i][parent[i]]);
    }
}

void primMST(Graph graph, unsigned vCount){
    int parent[vCount];
    int key[vCount];
    bool mstSet[vCount];
    for (int i = 0; i < vCount; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < vCount - 1; count++) {
        int u = minKey(key, mstSet, vCount);
        mstSet[u] = true;
        for (int v = 0; v < vCount; v++)
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    printMST(parent, graph, vCount);
}

int main(void){
    unsigned vCount, eCount;
    printf("Enter number of vertices: ");
    scanf("%u", &vCount);
    printf("Enter number of edges: ");
    scanf("%u", &eCount);
    if(2*eCount > vCount*(vCount-1)) return 1;
    Graph graph = INITGraph(vCount);
    for (int i = 0, i1, i2, weight; i < eCount; ) {
        printf("Enter initial idx: ");
        scanf("%d", &i1);
        printf("Enter final idx: ");
        scanf("%d", &i2);
        printf("Enter weight: ");
        scanf("%d", &weight);
        if(i1 == i2){
            printf("Self-loop not allowed!\n");
        } else if (i1 >= vCount || i1 < 0|| i2 >= vCount || i2 < 0) {
            printf("Index out of bound!\n");
        } else if (weight < 0) {
            printf("Negative weight not allowed!\n");
        } else {
            graph[i1][i2] = weight;
            graph[i2][i1] = weight;
            i++;
        }
    }
    display(graph, vCount);
    primMST(graph, vCount);
    DELETEGraph(graph, vCount);
    return 0;
}
