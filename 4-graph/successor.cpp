#include <iostream>
using namespace std;

/* Write an alogorithm to find the "next" node (i.e. in-order successor) of a given node in a binary search tree. 
    You may assume that each node has a link to its parent. */

struct node{
    int data;
    struct node *left, *right, *parent;
};

struct node* newNode(int value){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = value;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

/* Given a non-empty binary search tree, return the minimum data value found in that tree.
    Note that the entire tree does not need to be searched. */

struct node* minValue(struct node* node){
    struct node* current = node;

    /* Loop down to find the left-most leaf node */
    while(current->left != NULL){
        current = current->left;
    }
    return current;
};

// void inorder(struct node *root){
//     if(root != NULL){
//         inorder(root->left);
//         printf("%d \n", root->data);
//         inorder(root->right);
//     }
// }

/* Given a binary serach tree and a number, inserts a new node with the given number in the correct place.
    Returns the new root pointer which the caller should then use (The standard trick to avoid using
    reference parameters). */
struct node* insert(struct node* node, int data){
    // If the tree is empty, return a new single node.
    if(node == NULL) return newNode(data);

    else{
        struct node* temp;
        // Otherwise, recur down the tree
        if(data <= node->data){
            temp = insert(node->left, data);
            node->left = temp;
            temp->parent = node;
        }
        else{
            temp = insert(node->right, data);
            node->right = temp;
            temp->parent = node;
        }
        return node;
    }
    
};

/* Implementation:
    The algorithm is divided into two cases on the basis of right subtree of the input node being empty or not. 
    
    1) If the right subtree of the node is not NULL, then the successor lies in the right subtree:
        Go to right subtree and return the node with minimum key value in the right subtree
    2) If the right subtree of the node is NULL, then the successor is one of the ancestors:
        Travel up using the parent pointer until you see a node which is the left child of its parent. The parent
        of such node is the successor. */
struct node* inOrderSuccessor(struct node* root, struct node* n){
    // Step 1 of the above algorithm:
    if(n->right != NULL){
        return minValue(n->right);
    }

    // Step 2 of the above algorithm
    struct node *temp = n->parent;
    while(temp != NULL && n == temp->right){
        n = temp;
        temp = temp->parent;
    }
    return temp;
};

int main(){

    /* Given BST:
                20
               /  \
              8    22
             / \ 
            4   12
                / \
               10  14   */

    struct node* root =  NULL, *temp, *succ, *min;

    root = insert(root, 20);
    root = insert(root, 8); 
    root = insert(root, 22); 
    root = insert(root, 4); 
    root = insert(root, 12); 
    root = insert(root, 10); 
    root = insert(root, 14);
    temp = root->left->right->right;

    succ = inOrderSuccessor(root, temp);

    if(succ != NULL)
        printf("\n Inorder successor of %d is %d", temp->data, succ->data);
    else
        printf("\n Inorder successor does not exist.");

    return 0;
}