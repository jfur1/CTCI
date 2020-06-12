#include <iostream>
using namespace std;
/* Implement a function to check if a binary tree is a binary search tree. */
#define MAX_SIZE 10 

struct node{
    int key;
    struct node *left, *right;
};

// Utility function to create a new BST
struct node* newNode(int value){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->key = value;
    temp->left = temp->right = NULL;
    return temp;
};

class stack{
    private:
        int top;
        int maxSize;
        node* data;

    public:
        stack(int size){
            top = -1;
            maxSize = size;
            data = new node[maxSize];
        }
        ~stack(){
            delete data;
        }
        bool isFull(){
            return true ? (top == maxSize -1) : false;
        }
        bool isEmpty(){
            return true ? (top == -1) : false;
        }
        node* push(node* node){
            if(isFull())
                return NULL;
            top++;
            data[top] = *node;
            return node;
        }
        node* pop(){
            if(isEmpty())
                return NULL;
            return &data[top--];
        }
};

// Utility function that performs an in-order traversal
void inorder(struct node *root){
    if(root != NULL){
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

bool validateBST(node* root){

    stack stack(10);
    double inorder = - 10000;

    while( !stack.isEmpty() || root != NULL){
        while(root != NULL){
            stack.push(root);
            root = root->left;
        }
        root = stack.pop();
        /* If the next element in inorder traversal is smaller than the previous one, then we have an invalid BST */
        if(root->key <= inorder) return false;
        inorder = root->key;
        root = root->right;
    }
    return true;
}

// Utility function to perform an insert on the BST
struct node* insert(struct node* node, int key){
    // If the tree is empty, retrun a new node
    if(node == NULL) return newNode(key);

    // Otherwise, recur down the tree
    if( key < node->key)
        node->left = insert(node->left, key);

    else if(key > node->key)
        node->right = insert(node->right, key);

    // Return the (unchanged) node pointer
    return node;
}

int main(){
    /* Let us create following BST 
              50 
           /     \ 
          30      70 
         /  \    /  \ 
       20   40  60   80 */

    struct node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // print an inorder traversal
    inorder(root);
    cout << endl;

    if(validateBST(root)){
        cout << "Valid BST\n";
    }
    else {
        cout << "Invalid BST\n";
    }
    return 0;
}