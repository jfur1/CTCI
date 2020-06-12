#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int data;
    Node *parent;
    Node *leftChild;
    Node *rightChild;
};

Node *newNode(int n){
    Node *new_node = new Node();
    new_node->data = n;
    new_node->leftChild = new_node->rightChild = NULL;
    return new_node;
}

Node *minimal_tree(vector<int> arr, int start, int end){
    if(start > end) return NULL; // terminating case for recursion

    int mid = start + (end - start) / 2 ;

    Node *root = newNode(arr[mid]);
    root->leftChild = minimal_tree(arr, start, mid-1);
    root->rightChild = minimal_tree(arr, mid+1, end);
    return root;
}

Node *minimal_tree(vector<int> arr){
    return minimal_tree(arr, 0, arr.size()-1);
}

void preOrderTraversal(Node *node){
    if(node != NULL){
        cout << node->data << ' ';
        preOrderTraversal(node->leftChild);
        preOrderTraversal(node->rightChild);
    }
}

int main(){
    // Given ascending list of unique integers, return a binary search tree of minimal height
    int A[] = {1, 3, 4, 6 , 7, 8, 9, 11, 13};
    // Map array [A] into vector [arr]
    vector<int> arr (A, A + sizeof(A) / sizeof(A[0]) );

    Node *root = minimal_tree(arr);
    preOrderTraversal(root);

    return 0;
}