#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph{
    int V;
    vector<int> *adj;

    public:
        Graph(int V){
            this->V = V;
            adj = new vector<int>[V];
        }
        void addEdge(int u, int v){
            adj[u].push_back(v);
        }
        void topologicalSortUtil(int u, vector<bool> &visited, stack<int> &Stack){
            visited[u] = true;

            vector<int>::iterator i;
            for(i = adj[u].begin(); i < adj[u].end(); i++){
                if(!visited[*i])
                    topologicalSortUtil(*i, visited, Stack);
            }
            Stack.push(u);
        }

        void topologicalSort(){
            stack<int> Stack;

            vector<bool> visited(V, false);

            for(int i = 0; i < V; i++){
                if(visited[i] == false){
                    topologicalSortUtil(i, visited, Stack);
                }
            }

            while(!Stack.empty()){
                cout << Stack.top() << " ";
                Stack.pop();
            }
        }

};

int main(){
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "The following is a topological sorting: \n";
    g.topologicalSort();
    return 0;
}