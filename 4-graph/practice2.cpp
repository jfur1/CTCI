#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int key;
    Node* parent;
    Node *leftChild;
    Node* rightChild;
};

struct LLnode{
    int key;
    LLnode* next;
    LLnode(){
        key = -1;
        next  = NULL;
    }
    LLnode(Node *node){
        key = node->key;
        next = NULL;
    }
};

class Queue{
    public:
        int head, tail;
        Node* data;
        int queueSize, maxQueue;

        Queue(int maxSize){
            head = tail = queueSize = 0;
            maxQueue = maxSize;
            data = new Node[maxQueue];
        }
        ~Queue(){
            delete[] data;
        }

        bool isFull(){
            return true ? (queueSize == maxQueue) : false;
        }
        bool isEmpty(){
            return true ? (queueSize == 0) : false;
        }

        int enqueue(Node *node){
            if(isFull()) return -1;

            data[tail++] = *node;
            queueSize++;
            return 0;
        }

        Node* dequeue(){
            if(isEmpty()) return NULL;

            queueSize--;
            if(head == maxQueue-1){
                head = 0;
                return &data[maxQueue-1];
            }
            else{
                return &data[head++];
            }

        }
};

class BST{

    private:
        Node *root;
        int nodeCount;

        void printNode(Node *n){
            if(n->leftChild != NULL) printNode(n->leftChild);
            cout << n->key << " ";
            if(n->rightChild != NULL) printNode(n->rightChild);
        }

    public:

        BST(int value){
            root = new Node;
            root->key = value;
            root->leftChild = NULL;
            root->rightChild = NULL;
            root->parent = NULL;
            nodeCount = 1;
        }

        void recursiveDestructor(Node *node){
            if(node){
                recursiveDestructor(node->leftChild);
                recursiveDestructor(node->rightChild);
                delete node;
            }
        }
        ~BST(){
            recursiveDestructor(root);
        }

        int insert(int value){
            Node *newNode = new Node;
            newNode->key = value;
            newNode->parent = NULL;
            newNode->leftChild = NULL;
            newNode->rightChild = NULL;

            Node *tmp = root;
            while(tmp != NULL){
                if(value < tmp->key){ // Go left
                    if(tmp->leftChild == NULL){ // Make sure that the spot is open
                        tmp->leftChild = newNode;
                        newNode->parent = tmp; // Add a bidirectional edge
                        nodeCount++;
                        return 0;
                    }
                } 
                else if(value > tmp->key){
                    if(tmp->rightChild == NULL){
                        tmp->rightChild = newNode;
                        newNode->parent = tmp;
                        nodeCount++;
                        return 0;
                    }
                }
                // If we have duplicate values, then each of the duplicates is just as good as the last
                // Add the duplicate just makes our tree imbalanced and ugly with no benefit
                // Therefore, we will ignore duplicate values 
                else{
                    delete newNode; // delete to avoid memory leak
                    return -1;
                }
            }
            return -1;
        }

        void inOrderPrint(){ // Need a helper function because the root of the BST is a private class member
            printNode(root);
        }
        
        void BST_to_list(){
            Node *tmp = root;
            if(root == NULL) return;
            vector<LLnode> lists; // 1-D vector of list heads (1-D since each head is linked by pointers)

            Queue *q = new Queue(nodeCount); // PRACTICE: what if we did not have a node count??
            q->enqueue(root);

            while (!q->isEmpty()){
                int levelNodes = q->queueSize;
                LLnode *head = new LLnode; // head of the new linked list
                LLnode *current = new LLnode; // tmp to be inserted if need be
                head = current = NULL;

                while(levelNodes > 0){ // Stil have nodes on a given level to be added
                    Node *node = q->dequeue();
                    LLnode *LN = new LLnode(node);
                    if(head == NULL) head = current = LN; // New level => start a new linked list

                    else{
                        current->next = LN;
                        current = current->next;
                    }

                    if(node->leftChild != NULL) q->enqueue(node->leftChild);
                    if(node->rightChild != NULL) q->enqueue(node->rightChild);

                    levelNodes--;
                }
                lists.push_back(*head);
            }
            for(int i = 0; i < lists.size() - 1; i++){
                cout << endl;
                LLnode tmp = lists[i];
                LLnode *temp = &tmp;

                while(temp != NULL){
                    if(temp->next == NULL){
                        cout << temp->key;
                        break;
                    }
                    cout << temp->key << "->";
                    temp = temp->next;
                }
            }
            return;
        }
};

int main(){

    BST bst(4);
    bst.insert(2);
    bst.insert(6);
    bst.insert(3);
    bst.insert(9);
    bst.insert(1);
    
    cout << "In Order Traversal: \n";
    bst.inOrderPrint();
    cout << endl;
    
    
    bst.BST_to_list();

}