#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <omp.h>

using namespace std;

class Graph {

    int V;
    map<string, vector<string> > adj;

public:

    Graph(int V) {
        this->V = V;
    }

    void addEdge(string u, string v) {

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void parallelBFS(string start) {

        map<string, bool> visited;
        queue<string> q;

        visited[start] = true;
        q.push(start);

        cout << "\nParallel BFS Traversal: ";

        while (!q.empty()) {

            string node = q.front();
            q.pop();

            cout << node << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++) {

                string neighbor = adj[node][i];

                #pragma omp critical
                {
                    if (!visited[neighbor]) {

                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }

        cout << endl;
    }
};

int main() {

    int V,E;

    cout<<"Enter number of vertices: ";
    cin>>V;

    Graph g(V);

    cout<<"Enter number of edges: ";
    cin>>E;

    cout<<"\nEnter edges (u v):\n";

    for(int i=0;i<E;i++) {

        string u,v;
        cin>>u>>v;

        g.addEdge(u,v);
    }

    string start;

    cout<<"\nEnter starting vertex: ";
    cin>>start;

    g.parallelBFS(start);

    return 0;
}

