// sudo apt install openmpi-bin libopenmpi-dev

#include <iostream>
#include <omp.h>
#include <queue>
#include <vector>

using namespace std;

class Graph {
  int V;
  vector<vector<int>> adj;

public:
  Graph(int vertices) {
    V = vertices;
    adj.resize(V);
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u); // Undirected graph
  }

  void parallelBFS(int start) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Parallel BFS Traversal: ";

    while (!q.empty()) {
      int size = q.size();

      vector<int> currentLevel;

      // Process all nodes at current level
      while (size--) {
        int node = q.front();
        q.pop();

        currentLevel.push_back(node);
        cout << node << " ";
      }

// Parallel processing of neighbors
#pragma omp parallel for
      for (int i = 0; i < currentLevel.size(); i++) {
        int node = currentLevel[i];

        for (int neighbor : adj[node]) {

#pragma omp critical
          {
            if (!visited[neighbor]) {
              visited[neighbor] = true;
              q.push(neighbor);
            }
          }
        }
      }
    }

    cout << endl;
  }
};

int main() {
  int V = 6;

  Graph g(V);

  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(2, 5);

  g.parallelBFS(0);

  return 0;
}
