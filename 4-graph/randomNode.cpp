#include <iostream>
#include <random>
using namespace std;

/* 4.11: Random Node:
    You are implementing a binary tree class from scratch which in addition to insert, find, and delete,
    has a method getRandomNode() which returns a random node from the tree. All nodes should be equally
    likely to be chosen. Design and implement an algorithm for getRandomNode, and explain how you would
    implement the rest of the methods.
    
    Solution: Include a private attribute "nodeCount" to use in the getRandomNode method. We will get an
            index: rand() % nodeCount that will be between 0 and n where n is the number of nodes. Then,
            we use the index as a termination point in a traversal. */

    class BST{

        struct node{
            int key;
            node *left, *right;
        };

        node *root;
        int nodeCount;

        node* DestroyRecursive(node *node){
            if(node){
                DestroyRecursive(node->left);
                DestroyRecursive(node->right);
                delete node;
            }
            return NULL;
        }

        node *newNode(int value){
            node *temp = (struct node *)malloc(sizeof(struct node));
            temp->key = value;
            temp->left = temp->right = NULL;
            return temp;
        }

        node *insert(node *node, int value){
            if(node == NULL){
                nodeCount++;
                return newNode(value);
            }

            else{
                struct node *temp;
                if(value < node->key){
                    temp = insert(node->left, value);
                    node->left = temp;
                }
                else{
                    temp = insert(node->right, value);
                    node->right = temp;
                }
                return node;
            }
        }

        node *findMin(node *node){
            if(node == NULL) return NULL;

            else if(node->left == NULL) return node;

            else return findMin(node->left);
        }

        node *remove(node *node, int data){
            struct node *temp;
 

            if(node == NULL) return NULL;

            else if(data < node->key)
                node->left = remove(node->left, data);

            else if(data > node->key)
                node->right = remove(node->right, data);
            
            else if(node->left && node->right){
                temp = findMin(node->right);
                node->key = temp->key;
                node->right = remove(node->right, node->key);
            }
            else{
                temp = node;
                if(node->left == NULL) node = node->right;
                
                else if(node->right == NULL) node = node->left;
                
                nodeCount--;
                delete temp;
            }
            return node;
        }

        void inorder(node *node){
            if(node == NULL) return;

            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }

        node *find(node *node, int data){
            if(node == NULL) return NULL;
            
            else if(data < node->key) return find(node->left, data);

            else if(data > node->key) return find(node->right, data);

            else return node;
        }

        void count(){
            cout << nodeCount;
        }

        // node *randomNode(node *node){

        // }


    public:
        BST(){
            root = NULL;
            nodeCount = 0;
        }

        ~BST(){
            root = DestroyRecursive(root);
        }

        void insert(int x){
            root = insert(root, x);
        }

        void remove(int x){
            root = remove(root, x);
        }

        void display(){
            inorder(root);
            cout << endl;
        }

        void search(int x){
            root = find(root, x);
        }

        void getNodeCount(){
            count();
            cout << endl;
        }

    };

    int main(){
        BST bst;
        bst.insert(20);
        bst.insert(25);
        bst.insert(15);
        bst.insert(10);
        bst.insert(30);
        bst.display();
        bst.remove(20);
        bst.display();
        bst.remove(25);
        bst.display();
        bst.remove(30);
        bst.insert(70);
        bst.display();
        bst.getNodeCount();
        bst.insert(55);
        bst.display();
        //cout << rand();

        return 0;
    }