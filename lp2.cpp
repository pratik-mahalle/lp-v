#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <omp.h>

using namespace std;

class Graph {

    int V;

    // Adjacency list
    map<string, vector<string> > adj;

public:

    Graph(int V) {
        this->V = V;
    }

    // Add edge in undirected graph
    void addEdge(string u, string v) {

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Parallel DFS Function
    void parallelDFS(string start) {

        map<string, bool> visited;

        stack<string> st;

        st.push(start);

        cout << "\nParallel DFS Traversal: ";

        while (!st.empty()) {

            string node = st.top();
            st.pop();

            if (!visited[node]) {

                visited[node] = true;

                cout << node << " ";

                // Parallel processing of neighbors
                #pragma omp parallel for
                for (int i = 0; i < adj[node].size(); i++) {

                    string neighbor = adj[node][i];

                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {

                            st.push(neighbor);
                        }
                    }
                }
            }
        }

        cout << endl;
    }
};

int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "\nEnter edges :\n";

    for (int i = 0; i < E; i++) {

        string u, v;

        cin >> u >> v;

        g.addEdge(u, v);
    }

    string start;

    cout << "\nEnter starting vertex: ";
    cin >> start;

    g.parallelDFS(start);

    return 0;
}


