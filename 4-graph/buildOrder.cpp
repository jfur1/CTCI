#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// class Stack{
//     private:
//         int top;
//         int maxSize;
//         int* data;
//     public:
//         Stack(int size){
//             top = -1;
//             maxSize = size;
//             data = new int[maxSize];
//         }
//         ~Stack(){
//             delete data;
//         }
//         bool isFull(){
//             return true ? (top == maxSize - 1) : false;
//         }
//         bool isEmpty(){
//             return true ? (top ==  -1) : false;
//         }
//         int push(int value){
//             if(isFull()) return -1;

//             top++;
//             data[top] = value;
//             return 0;
//         }
//         int* pop(){
//             if(isEmpty()){
//                 return NULL;
//             }
//             return &data[top--];
//         }
// };


/* 4.7: Build Order:
    You are given a list of projects and a list of dependencies (which is a list of pairs of projects,
    where the second project is dependent on the first project). All of a project's dependencies must be built before
    the project is. Find a build order that will allow the projects to be built. If there is no valid build order, then
    return an error. 
    EXAMPLE:
        Input: 
            Projects: a, b, c, d, e, f 
            Dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
        Output: 
            f, e, a, b, d, c
    */

class Graph{
    int V; // No. of vertices
    vector<int> *adj;

    public:
        Graph(int V){
            this->V = V;
            adj = new vector<int>[V];
        }
        void addEdge(int u, int v){
            adj[u].push_back(v); // Add vertex v to the adjacency list of vertex u.
        }
        void topologicalSortUtil(int u, vector<bool> &visited, stack<int> &Stack){
            // Mark the current node as visited
            visited[u] = true;

            // Recur for all the vertices adjacent to this vertex
            vector<int>::iterator i;
            for(i = adj[u].begin(); i != adj[u].end(); i++){
                if(!visited[*i])
                    topologicalSortUtil(*i, visited, Stack);
            }
            Stack.push(u);
        }

        void topologicalSort(){
            stack<int> Stack;

            // Mark all vertices as not visited
            vector<bool> visited(V, false);

            // Call the recursive helper function to store topological sort, starting from all vertices 1 by 1
            for(int i = 0; i < V; i++)
                if(visited[i] == false)
                    topologicalSortUtil(i, visited, Stack);
            
            // Print the contents of the stack:
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

    cout << "Following is a Topological Sorting\n";
    g.topologicalSort();

    return 0;
}