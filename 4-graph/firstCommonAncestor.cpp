#include <iostream>
#include <vector>
using namespace std;

/* 4.8: First Common Ancestor:
    Design an algorithm and write code to find the first common ancestor of two nodes in a binary tree.
     Avoid storing additional nodes in a data structure. NOTE: This is not necessarily a binary tree.
    */

struct node{
    int key;
    struct node *left, *right;
};

node* newNode(int data){
    node *temp = new node;
    temp->key = data;
    temp->left = temp->right = NULL;
    return temp;
}
// boolean to determine whether or not a LCA exists (wrote the wrong algorithm -- still works properly)
bool FCA(node *current, int p, int q){
    // If we reach the end of a branch, then return false
    if(current == NULL) return false;

    // Left branch recursion. If the left recursion returns true, set left = 1 else 0
    int left = FCA(current->left, p, q) ? 1 : 0;

    // Right recursion
    int right = FCA(current->right, p, q) ? 1 : 0;

    // If the current node is one of p or q
    int mid = (current->key == p || current->key == q) ? 1 : 0;

    // If any two of the flags (left, right, or mid) become True:
    if(mid + left + right >= 2){
        node* ans = current;
    }

    // Return true if any one of the three bool values are True:
     return (left + mid + right > 0);
}

// Algorithm to determine THE VALUE of the lowest common ancestor:
bool findPath(node *root, vector<int> &path, int k){
    // base case
    if(root == NULL) return false;

    // Store this node in path vector. The node will be removed if not in the path from root to k
    path.push_back(root->key);

    // See if the k is the same as the root
    if(root->key == k) return true;

    // Check if k is found in the left or right sub-tree
    if( (root->left && findPath(root->left, path, k)) ||
        (root->right && findPath(root->right, path, k)) )
        return true;

    // If k is not present in the subtree rooted with root, then remove the root from path[] and return false
    path.pop_back();
    return false;
}

// Algorithm that returns LCA if node n1 and node n2 are present in the given binary tree, otherwise returns -1
int findLCA(node *root, int n1, int n2){
    // vector to store paths to n1 and n2 from the root:
    vector<int> path1, path2;

    // Find paths from root to n1 and root to n2. If either n1 or n2 is not present, then return -1
    if( !findPath(root, path1, n1) || !findPath(root, path2, n2))
        return -1;

    int i;
    for(i = 0; i < path1.size() && i < path2.size(); i++)
        if(path1[i] != path2[i])
            break;
    return path1[i-1];
}


int main(){
    node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    // NOTE: the lowest common ancestor of two given nodes n1 and n2, 
    // can be one of the two nodes themselves, by definition
    cout << "FCA(4, 5) == " << findLCA(root, 4, 5);
    cout << endl;
    cout << "FCA(4, 6) == " << findLCA(root, 4, 6);   
    cout << endl;
    cout << "FCA(3, 4) == " << findLCA(root, 3, 4);
    cout << endl;
    cout << "FCA(2, 4) == " << findLCA(root, 2, 4);
    cout << endl;

    return 0;
}