#include <iostream>
#include <vector>
using namespace std;

/* 4.12: Paths with Sum:
        You are given a binary tree in which each node contains an integer value (which might be positive
        or negative). Design an algorithm to count the number of paths that sum to a given value. The path
        does not need to start or end at the root or a leaf, but it must go downwards (traveling only from
        parent nodes to child nodes). */

struct node{
    int key;
    struct node *left, *right;
};

struct node* newNode(int data){
    node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = data;
    temp->left = temp->right = NULL;
    return temp;
};

struct node *insert(struct node *node, int data){
    if(node == NULL) return newNode(data);

    else{
        struct node* temp;
        if(data < node->key){
            temp = insert(node->left, data);
            node->left = temp;
        }
        else{
            temp = insert(node->right, data);
            node->right = temp;
        }
        return node;
    }
}

//utility function to print contents of 
//a vector from index i to it's end 
void printVector(const vector<int>& v, int i) 
{ 
    for (int j=i; j<v.size()-1; j++) 
        cout << v[j] << " -> ";
    cout << v[v.size()-1] << endl; 
} 

// This function prints all paths that have sum k. The idea here is to do a preorder traversal while 
// keeping track of the path that led to a node in a vector. At each node we check if there are ant paths
// that sum to k, and if there are we recursively print the path. 
void printPathUtil(node *root, vector<int>& path, int k){
    if(root == NULL) return;

    // add the current node to the path
    path.push_back(root->key);

    // Check if any k-sum paths exist in the left sub-tree
    printPathUtil(root->left, path, k);

    // Check if any k-sum paths exist in the right sub-tree
    printPathUtil(root->right, path, k);

    // Check if any k-sum paths terminate at this node. Traverse the entire path since there can be negatives.
    int f = 0;
    for(int i = path.size()-1; i >= 0; i--){
        f += path[i];

        // If path sums to k, then print the path
        if(f == k)
            printVector(path, i);
    }
    // Remove the current element from the path
    path.pop_back();
}

void printPath(node *root, int k){
    vector<int> path;
    printPathUtil(root, path, k);
}


int main(){
 /* 
 Constructing the following Binary Tree:
          1
        /     \
      3        -1
    /   \     /   \
   2     1   4     5                        
        /   / \     \                    
       1   1   2     6    */

    node *root = newNode(1); 
    root->left = newNode(3); 
    root->left->left = newNode(2); 
    root->left->right = newNode(1); 
    root->left->right->left = newNode(1); 
    root->right = newNode(-1); 
    root->right->left = newNode(4); 
    root->right->left->left = newNode(1); 
    root->right->left->right = newNode(2); 
    root->right->right = newNode(5); 
    root->right->right->right = newNode(2); 
  
    int k = 5; 
    printPath(root, k); 

    return 0;
}