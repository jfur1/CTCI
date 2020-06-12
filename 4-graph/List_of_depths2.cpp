#include <iostream>
#include <vector>
using namespace std;

// Question: Given a binary tree, design an algorithm which creates a linked list of all the nodes at each depth 
// (e.g.: If you have a tree with depth D, you will have D linked-lists.)

struct Node{
	int key;
	Node* parent;
	Node* leftChild;
	Node* rightChild;
};

struct LLnode{
    int key;
    LLnode *next;
	LLnode(){
		key = -1;
		next = NULL;
	}
	LLnode(Node * node){
		key = node->key;
		next = NULL;
	}
};

class Queue{
	private:

	public:
        int head, tail;
		Node* data;
		int queueSize, maxQueue;
		
        Queue(int maxSize){
			head = 0;
			tail = 0;
			queueSize = 0;
			maxQueue = maxSize;
			data = new Node[maxQueue];	// Our queue keeps an updated inventory of BST nodes.
		}
		~Queue(){
			delete[] data;
		}

		int enqueue(Node *node){
			if (isFull()) return -1;

			data[tail++] = *node;	// Enqueue a BST node
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
				return &data[head++];	// Return BST node
			}
		}
        bool isEmpty(){
			return true ? (queueSize == 0) : false;
		}
		bool isFull(){
			return true? (queueSize == maxQueue) : false;
		}
};

class BST{
    private:
        Node *root;
		int nodeCount;

        void printNode(Node* n){
			if(n->leftChild != NULL){
				printNode(n->leftChild);
			}

			cout << n->key << " ";

			if(n->rightChild != NULL){
				printNode(n->rightChild);
			}
		}
		
    public:
        
        BST(int value){
            root = new Node;
            root->key = value;
            root->parent = NULL;
            root->leftChild = NULL;
            root->rightChild = NULL;
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
			newNode->parent = NULL; // In this function, the tmp is our parent
			newNode->leftChild = NULL;
			
			newNode->rightChild = NULL;

			// Figure out where new node goes
			Node* tmp = root;
			while(tmp != NULL){ // Run it off until the end of the tree
				if(value < tmp->key){ // Go left
					if(tmp->leftChild == NULL){
						tmp->leftChild = newNode;
						newNode->parent = tmp; // Reference to the parent
						nodeCount++;
						return 0;
					}
					tmp = tmp->leftChild;
				}
				else if(value > tmp->key){
					if(tmp->rightChild == NULL){
						tmp->rightChild = newNode;
						newNode->parent = tmp; // Reference to the parent
						nodeCount++;
						return 0;
					}
					tmp = tmp->rightChild;
				}
				// If we have duplicate values, each of the duplicate is just as good as the last
				// Adding duplicate values just makes our tree imbalanced and ugly with no benefit.
				// Therefore, we can just ignore duplicate values.
				else{
					delete newNode; // We delete newNode to avoid a memory leak
					return -1; // If it is a duplicate value, don't add
				}
			}
			return -1;
		}

		void inOrderPrint(){ // Helper function to call printNode and root, since they are private
			printNode(root);
		}


		void BST_to_list(){
			Node* tmp = root; // tmp will be our access to the root
			if(root == NULL) return;
			vector<LLnode> lists;	// Vector of ListNodes (1-Dim since each head uses pointers to connect a linked-list.)

			Queue *q = new Queue(nodeCount); // Initialize a queue for BFS (no visited vector)
			q->enqueue(root);	// enqueue the root

			while(!q->isEmpty()){
				int levelNodes = q->queueSize; // Keeps track of the number of nodes on a given level.
				LLnode *head = new LLnode; // head of new linked list
				LLnode *current = new LLnode; // tmp to insert if need be
				head = NULL;
				current = NULL;
				while(levelNodes > 0){ // While we still have nodes on a level that need to be added to the list
					Node *node = q->dequeue(); // dequeue the front
					LLnode *LN = new LLnode(node);
					if(head == NULL){ // New level => Start a new linked-list
						head = LN;
						current = LN;
					}else{		// Append to existing list
						current->next = LN;
						current = current->next;
					}
					if(node->leftChild != NULL)	// (Left-to-Right)
						q->enqueue(node->leftChild);
					if(node->rightChild != NULL)
						q->enqueue(node->rightChild);
					levelNodes--;	// Dequeue a node at the start of each loop => # of nodes on that level decreases by 1.
				}
				lists.push_back(*head); // After we finish creating the list, push the listHead into our vector (head points to rest of list)
			}
			for(int i = 0; i < lists.size(); i++){ // print lists!
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
	cout << "In Order Traversal: " << endl;
    bst.inOrderPrint();
	cout << endl;
	bst.BST_to_list();
}