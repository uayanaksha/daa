#include <cstdio>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

#define V 9

class Graph{
    private:
        vector<vector<int>> adj_matrix;
        unsigned vertices;

    public:
        Graph(const unsigned &vertices){
            this->vertices = vertices;
            adj_matrix = vector<vector<int>>(vertices, vector<int>(vertices, 0));
            srandom(time(0));
            int rand;
            for(int i = 0 ; i < vertices*vertices; i++){
                int iidx = random() % vertices;
                int fidx = random() % vertices;
                int weight = random() % 25;
                if(iidx != fidx) 
                    adj_matrix[iidx][fidx] = weight;
            }
        }

    private:
        int minDistance(int dist[], bool sptSet[]){
            int min = INT_MAX, min_index;
            for (int v = 0; v < V; v++)
                if (sptSet[v] == false && dist[v] <= min)
                    min = dist[v], min_index = v;
            return min_index;
        }

        void printSolution(int dist[]){
            printf("%10s | %20s\n", "Vertex", "Distance from Source");
            cout << std::string(40, '-') << endl;
            for (int i = 0; i < V; i++)
                printf("%10d | %20d\n", i, dist[i]);
        }

    public:
        void dijkstra(int src){
            int dist[V]; 
            bool sptSet[V]; 
            for (int i = 0; i < V; i++)
                dist[i] = INT_MAX, sptSet[i] = false;
            dist[src] = 0;
            for (int count = 0; count < V - 1; count++) {
                int u = minDistance(dist, sptSet);
                sptSet[u] = true;
                for (int v = 0; v < V; v++)
                    if (!sptSet[v] && adj_matrix[u][v]
                            && dist[u] != INT_MAX
                            && dist[u] + adj_matrix[u][v] < dist[v])
                        dist[v] = dist[u] + adj_matrix[u][v];
            }
            printSolution(dist);
        }

        void log(){
            cout << "Graph [" << vertices << "][" << vertices << "]: {" << endl;
            for(vector<int> rows : adj_matrix){
                cout << "    ";
                for (int node: rows) {
                    printf(" %.2d,", node);
                }   cout << endl;
            }   cout << "}" << endl;
        }
};

int main(){
    unsigned vertices, src;
    cout << "Enter the number of vertices: " && cin >> vertices;
    Graph graph(vertices);
    graph.log();
    cout << "Enter source index: " && cin >> src;
    graph.dijkstra(src);
    return 0;
}

