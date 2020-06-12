#include <iostream>
#include <vector>
using namespace std;

/* 4.9: BST sequences:
    A binary search tree was created by traversing through an array from left to right and inserting each element.
    Given a binary serach tree with unique elements, print all possible arrays that could have led to this tree. */

struct node{
    int key;
    node *left, *right;
};

struct node *newNode(int data){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = data;
    temp->left = temp->right = NULL;
    return temp;
};

struct node *insert(struct node *node, int data){
    if(node == NULL) return newNode(data);

    else{
        struct node *temp;

        if(data < node->key){
            temp = insert(node->left, data);
            node->left = temp;
        }
        else if(data > node->key){
            temp = insert(node->right, data);
            node->right = temp;
        }
        return node;
    }
}

// Solution help from Atul Vaibhav on StackOverflow.com
/* Uses a divide & conquer method via findAllSeq which takes a node pointer as input and returns 
    all the distinct sequences which will generate the subtree hanging from "node". Function 
    returns a vector of vector of ints containing all the sequences. Main idea here is that the
    root must come before all of its children.*/
vector<vector<int> > findAllSeq(node *node){
    // Base Case 1: If node is null, return a vector with an empty sequence
    if(node == NULL){
        vector<int> seq;
        vector<vector<int> > v;
        v.push_back(seq);
        return v;
    }
    // Base Case 2: If "node" is a leaf node, then return a vector with a single sequence.
    if(node->left == NULL && node->right == NULL){
        vector<int> seq;
        seq.push_back(node->key);
        vector<vector<int> > v;
        v.push_back(seq);
        return v;
    }

    vector<vector<int> > results, left, right;
    // Recursively generates all sequences for left sub-tree and right sub-tree.
    left = findAllSeq(node->left);
    right = findAllSeq(node->right);
    int size = left[0].size() + right[0].size() + 1;

    // Vector of boolean flags to distinguish left sequence elements from right sequence elements
    vector<bool> flags(left[0].size(), 0);
    for(int k = 0; k < right[0].size(); k++)
        flags.push_back(1);

    /* Finally, generate all permutations of the flags vector using "next_permutation()" 
        For each permutation of flags, we will have a distinct, merged sequence of L & R subtrees.*/
    for(int i = 0; i < left.size(); i++){
        for(int j = 0; j < right.size(); j++){
            do{
                vector<int> temp(size);
                temp[0] = node->key;
                int l = 0, r = 0;
                for(int k = 0; k < flags.size(); k++){
                    temp[k+1] = (flags[k]) ? right[j][r++] : left[i][l++];
                }
                results.push_back(temp);
            }
            while(next_permutation(flags.begin(), flags.end()));
        }
    }
    return results;
}

int main(){

    struct node* root = NULL;

    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 7);

    vector<vector<int> > ans = findAllSeq(root);
    for(int i = 0; i < ans.size(); i++){
        for(int j = 0; j < ans[i].size(); j++){
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "Total Number of Possible Input Arrays: " << ans.size() << endl;
    return 0;
}