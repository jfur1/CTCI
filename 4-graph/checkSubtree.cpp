#include <iostream>
using namespace std;

/* 4.10: Check Subtree: 
    T1 and T2 are two very large binary trees, with T1 much bigger than T2. Create an algorithm to
    determine if T2 is a subtree of T1. 
    
    A tree T2 is a subtree of T1 if there exists a node n in T1 such that the subtree of n is identical
    to T2. That is, if you cut off the tree at node n, the two trees would be identical. */

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

/* Solution: Traverse the tree T in preorder fashion. For every visited node in the traversal, see if the 
    subtree rooted with this node is identical to S. 
    
    Time Complexity: Worst case time complexity of the algorithm is )(mn) where m and n are the number
                     of nodes in the given two trees. */

// A utility function that checks whether trees with the roots, root1 and root2 are identical.
bool areIdentical(node *root1, node *root2){
    // Base cases:
    if(root1 == NULL && root2 == NULL) return true;

    if(root1 == NULL || root2 == NULL) return false;

    /* Check if the data of both roots are the same and the data of the left and right subtrees
        are also the same. */
    return (root1->key == root2->key && 
            areIdentical(root1->left, root2->left) &&
            areIdentical(root1->right, root2->right));
}

// Function returns true if S is a subtree of T, otherwise returns false
bool isSubtree(node *T, node *S){
    // Base Cases:
    if(S == NULL) return true;

    if(T == NULL) return false;

    // Check the tree with root as the current node
    if(areIdentical(T, S)) return true;

    // If the tree with the root as the current node doesn't match, then try the left and right
    // subtrees, one by one. 
    return isSubtree(T->left, S) ||
            isSubtree(T->right, S);
}

int main(){
    // TREE 1  
    /* Construct the following tree  
            26  
            / \  
           10  3  
          /  \  \  
          4   6   3  
           \  
            30  
    */
    node *T = newNode(26);  
    T->right         = newNode(3);  
    T->right->right = newNode(3);  
    T->left         = newNode(10);  
    T->left->left     = newNode(4);  
    T->left->left->right = newNode(30);  
    T->left->right     = newNode(6);  
  
    // TREE 2  
    /* Construct the following tree  
        10  
        / \  
       4   6  
        \  
        30  
    */
    node *S = newNode(10);  
    S->right     = newNode(6);  
    S->left     = newNode(4);  
    S->left->right = newNode(30);  
  
  
    if (isSubtree(T, S))  
        cout << "Tree 2 is subtree of Tree 1";  
    else
        cout << "Tree 2 is not a subtree of Tree 1"; 
    return 0;
}