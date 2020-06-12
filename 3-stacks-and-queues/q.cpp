#include <iostream>
#include <vector>
using namespace std;

class Queue{

    private: 
        int head, tail;
        int* data;
        int queueSize, maxQueue;

    public:
        Queue(int maxSize){
            head = 0;
            tail = 0;
            queueSize = 0;
            maxQueue = maxSize;
            data = new int[maxQueue];
        }

        ~Queue(){
            delete[] data;
        }
        
        bool isEmpty(){
            return true ? (queueSize == 0) : false;
        }

        bool isFull(){
            return true ? (queueSize == maxQueue) : false;
        }

        int enqueue(int value){
            if(isFull()) return -1;
            data[tail++] = value;
            queueSize++;
            return 0;
        }

        int* dequeue(){
            if(isEmpty()) return NULL;
            queueSize--;
            if(head == maxQueue - 1){
                head = 0;
                return &data[maxQueue-1];
            }
            else{
                return &data[head++];

            }
        }
};

class Stack{

    private:

        int top;
        int maxSize = 10;
        int* data;

    public:
        Stack(int size){
            top = -1;
            maxSize = size;
            data = new int[maxSize];
        }

        ~Stack(){
            delete data;
        }

        bool isFull(){
            return true ? (top == maxSize -1) : false;
        }

        bool isEmpty(){
            return true ? (top == -1) : false;
        }

        int push(int value){
            if(isFull()) return -1;
            data[top] = value;
            return 0;
        }

        int* pop(){
            if(isEmpty()) return NULL;
            return &data[top--];
        }

};

class Graph{

    public:
    int V;
    vector<int> * adj;

    Graph(int V){
        this-> V =V;
        this->adj = new vector<int>[V];
    }

    void addEdge(int x, int y){
        adj[x].push_back(y);
    }

    bool isRoute(int x, int y){
        vector<bool> visited(V, false);
        visited[x] = true;
        Queue q(V);
        q.enqueue(x);

        while(!q.isEmpty()){
            int* v = q.dequeue();

            if(*v == y) return true;
            q.dequeue();
            visited[*v] = true;
            for(int i = 0; i < adj[*v].size(); i++){
                if(!visited[adj[*v][i]]){
                    q.enqueue(adj[*v][i]);
                }
            }
        }
        return false;
    }

};

int main(){

    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4,0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    
    printf("Route from 5 to 4?\n");
    g.isRoute(5, 4) ? printf("True\n") : printf("False\n");
    cout << endl;

    printf("Route from 5 to 1?\n");
    g.isRoute(5,1) ? printf("True\n") : printf("False\n");
    

    return 0;
}