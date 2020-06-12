#include <iostream>
#include <string>
using namespace std;

struct Node{
    int data;
    Node* next;
    string key;
};

/* Function to create a new node with given data */
Node *newNode(int data)  
{  
    Node *new_node = new Node(); 
    new_node->data = data;  
    new_node->next = NULL;  
    return new_node;  
}  

Node *newNode(int data, string key)  
{  
    Node *new_node = new Node(); 
    new_node->data = data;  
    new_node->next = NULL;  
    new_node->key = key;
    return new_node;  
} 

class LinkedList{
    private:
        Node* head;

    public:

        LinkedList(Node* h){
            head = h;
        }

        void traverse(){
            Node* tmp = head;
            while(tmp != NULL){
                cout << tmp->data;
                if(tmp->next != NULL) cout << ", ";
                tmp = tmp->next;
            }
            cout << endl;
        }

        void insert(Node* leftValue, Node* newNode){
            if(leftValue == NULL){
                newNode->next = head;
                head = newNode;
            }else{
                Node* tmp = head;
                while(tmp != leftValue){
                    tmp = tmp->next;
                }
                newNode->next = tmp->next;
                tmp->next = newNode;
            }
        }

        void deleteNode(int value){
            Node* tmp = head;

            if(head->data == value){
                head = tmp->next;
                tmp->next = NULL;
            }else{
                while(tmp->next->data != value){
                    tmp = tmp->next;
                }
                Node* deleting = tmp->next;
                tmp->next = deleting->next;
                deleting->next = NULL;
            }
        }

        /* 2.1 Remove Dups: 
            Write code to remove duplicates from an unsorted linked list.
            Follow Up: How would you solve this problem if a temporary buffer is not allowed?*/
        void removeDups(){
            Node* tmp = head;
            Node* tmp2 = head;
            while(tmp->next != NULL){
                while(tmp2->next != NULL){
                    if(tmp->data == tmp2->next->data){
                        Node* deleting = tmp2->next;
                        //cout << "deleting " << tmp2->next->data << endl;
                        tmp2->next = tmp2->next->next;
                        deleting->next = NULL;
                    }
                    else{
                        tmp2 = tmp2->next;
                    }
                }
                tmp = tmp->next;
                tmp2 = tmp;
            }
        }

        /* 2.2 Return Kth to Last: 
            Implement an algorithm to find the Kth to last element of a singly linked list. */
        void k_to_l(int k){
            Node* tmp = head;
            int count = 0;
            while(tmp != NULL && tmp->next != NULL){
                count++;
                if(count > k){
                    cout << tmp->data << ", ";
                }
                tmp = tmp->next;
            }
            cout << tmp->data << endl;
        }

        /* 2.3 Delete Middle Node:
            Implement an algorithm to delete a node in the middle (i.e., any node but the first and
            last node, not necessarily the exact middle) of a singly linked list, given only access
            to that node.
            EX: 
                Input: the node 'c' from the linked list: a->b->c->d->e->f
                Output: nothing is returned, but the new linked list looks like: a->b->d->e->f */
        void deleteMiddle(int value){
            Node* tmp = head;
            while(tmp->next->data != value){
                tmp = tmp->next;
            }
            Node* deleting = tmp->next;
            tmp->next = tmp->next->next;
            deleting->next = NULL;
        }

        /* 2.4 Partition
            Write code to partition a linked list around a value x, such that all nodes less than x
            come before all nodes greater than or equal to x. (IMPORTANT: The partition element x can 
            appear anywhere in the "right partition"; it does not need to appear between the left and
            right partitions. The additional spacing in the example below indicates the partition.) 
            EX:
                Input: 3->5->8->5->10->2->1  [partition = 5]
                Output: 3->1->2  ->  10->5->5->8
        */
       void partition(int value){
           Node* tmp = head;
           string lower, upper = "";
           while(tmp != NULL){
               if(tmp->data < value){
                   lower += to_string(tmp->data) + "->";
               }else{
                   upper += to_string(tmp->data) + "->";
               }
               tmp = tmp->next;
           }
           cout << lower << " : " << upper << endl;
       }
};

/* 2.5 Sum Lists:
    You have two numbers represented by a linked list, where each node contains a single digit.
    The digits are stored in reverse order, such that the 1's digit is at the head of the list.
    Write a function that adds the two numbers and returns the sum as a linked list. (You are
    not allowed to "cheat" and just convert the linked list to an integer.)
    EX:
        Input: (7->1->6) + (5->9->2). That is, 617 + 295.
        Output: 2->1->9. That is, 912.
    Follow Up:
        Suppose the digits are stored in foward order. Repeat the above problem.
        EX:
            Input: (6->1->7) + (2->9->5). That is, 617 + 295.
            Output: 9->1->2. That is, 912. */
Node* sum_lists(Node* list1, Node* list2){
    Node* tmp1 = list1;
    Node* tmp2 = list2;
    Node *tmp3, *head3 = NULL;

    while(tmp1 != NULL && tmp2 != NULL){

        int sum = tmp1->data + tmp2->data;
        int carry = sum % 10;

        if(sum >= 10){
            if(head3 == NULL){
                head3 = newNode(1);
                Node* temp = newNode(carry);
                head3->next = temp;
                tmp3 = head3->next;
            }else{
                tmp3->data += 1;
                Node* temp = newNode(carry);
                tmp3->next = temp;
                tmp3 = tmp3->next;
            }
        }else{
            if(head3 == NULL){
                head3 = newNode(sum);
                tmp3 = head3;
            }else{
                tmp3->next = newNode(sum);
                tmp3 = tmp3->next;
            }
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return head3;
}
// A utility function to print a linked list  
void printList(Node *node)  
{  
    while(node != NULL)  
    {  
        cout << node->data << " ";  
        node = node->next;  
    }  
    cout<<endl;  
}  

/* 2.6: Palindrome:
    Implement a function to check if a linked list is a palindrome. */
Node* palindrome(Node* h){
    Node* tmp = h;
    string check = "";
    while(tmp != NULL){
        check += tmp->key;
        tmp = tmp->next;
    }
    cout << "Linked List spells: " << check << endl;
    if(check.length()%2 == 1 && check.length() > 1){ // 
        int pivotIdx = (check.length()+1)/2;
        for(int i = 0; i < pivotIdx; i++){
            int j = check.length()-1-i;
            if(check[i] != check[j]){
                cout << check << " is not a palindrome" << endl;
                return 0;
            }
            j--;
        }
        cout << check  << " is a palindrome" << endl;
    }
    else{
        int pivotIdx = (check.length())/2;
        for(int i = 0; i < pivotIdx; i++){
            int j = check.length()-1-i;
            if(check[i] != check[j]){
                cout << check << " is not a palindrome." << endl;
                return 0;
            }
            //j--;
        }
        cout << check << " is a palindrome." << endl;
    }
    return 0; 
}

/* 2.7: Intersection:
    Given two (singly) linked lists, determine if the two lists intersect. Return the intersection node. Note that the 
    intersection is defined based on reference, not value. That is, if the kth node of the first linked list is the exact
    same node (by referenece) as the jth node of the second linked list, then they are intersecting. */

Node* intersection(Node* head1, Node* head2){
    //Node* intersect;
    Node* tmp1 = head1;
    Node* tmp2 = head2;
    while(tmp1 != NULL){
        tmp2 = head2; // Reset head2 each time tmp1 is reset.
        while(tmp2 != NULL && tmp1 != NULL){
            //cout << "testing ";
            if(tmp1 == tmp2){
                cout << "The two lists intersect at node: " << tmp1->data << endl;
                return tmp1;
            }
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
    }
    cout << "The two lists do not intersect.";
    return 0;
}

/* 2.8: Loop Detection:
    Given a linked-list which might contain a loop, implement an algorithm that retirns the node at the beginning
    of the loop if one exists.
        EX:
            Input: A->B->C->D->E->C [the same C as earlier]
            Output: C */
bool loopDetection(Node* h){
    Node* temp;
    while(h != NULL){
        if(h->next == NULL){
            return false;
        }
        if(h->next == temp){
            return true;
        }
        Node* nex = h->next;
        h->next = temp;
        h = nex;
    }
    return false;
}

int main(){

    // 2.1 Testing
    Node head;
	head.data = 5;
	head.next = NULL;

    Node second;
    second.data = 8;
    second.next = NULL;

    Node third;
    third.data = 7;
    third.next = NULL;

    Node fourth;
    fourth.data = 9;
    fourth.next = NULL;

    Node fifth;
    fifth.data = 8;
    fifth.next = NULL;

    Node sixth; 
    sixth.data = 7;
    sixth.next = NULL;

    LinkedList unsortedList(&head);
    unsortedList.insert(&head, &second);
    unsortedList.insert(&second, &third);
    unsortedList.insert(&third, &fourth);
    unsortedList.insert(&fourth, &fifth);
    unsortedList.insert(&fifth, &sixth);
    cout << "Unsorted LinkedList list2 List w/ Ducplicates: " << endl;
    unsortedList.traverse();
    cout << "\nLinkedList list2 List after removing duplicates: " << endl ;
    unsortedList.removeDups();
    unsortedList.traverse();
    cout << endl;
    
    // 2.2 Testing
    unsortedList.k_to_l(2);

    // 2.3 Testing
    Node newN;
    newN.data = 11;
    newN.next = NULL;
    unsortedList.insert(NULL, &newN);
    cout << "List Before deleteMiddle(7): " << endl;
    unsortedList.traverse();
    cout << "List After deleteMiddle(7): " << endl;
    unsortedList.deleteMiddle(7);
    unsortedList.traverse();

    // 2.4 Testing
    cout << "Partition(8): " << endl;
    unsortedList.partition(8);

    // 2.5 Testing 

    Node* head1 = newNode(1);
    Node* second1 =  newNode(7);
    Node* third1 = newNode(5);
    
    Node* head2 = newNode(2);
    Node* second2 = newNode(4);
    Node* third2 = newNode(9);

    LinkedList list1(head1);
    list1.insert(head1, second1);
    list1.insert(second1, third1);

    LinkedList list2(head2);
    list2.insert(head2, second2);
    list2.insert(second2, third2);


    Node* res = sum_lists(head1, head2);

    cout << "List 1: "; printList(head1);
    cout << "List 2: "; printList(head2);
    cout << "Summing the two lists: "; printList(res);

    // 2.6 Testing
    Node* palindromeHead = newNode(0, "r");
    Node* pal2 = newNode(0, "a");
    Node* pal3 = newNode(0, "c");
    Node* pal4 = newNode(0, "e");
    Node* pal5 = newNode(0, "c");
    Node* pal6 = newNode(0, "s");
    Node* pal7 = newNode(0, "r");

    LinkedList pal(palindromeHead);
    pal.insert(palindromeHead, pal2);
    pal.insert(pal2, pal3);
    pal.insert(pal3, pal4);
    pal.insert(pal4, pal5);
    pal.insert(pal5, pal6);
    pal.insert(pal6, pal7);
    palindrome(palindromeHead);

    Node* palHead2 = newNode(0, "b");
    Node* pal22 = newNode(0, "o");
    Node* pal33 = newNode(0, "o");
    Node* pal44 = newNode(0, "b");
    
    LinkedList palindrome2(palHead2);
    palindrome2.insert(palHead2, pal22);
    palindrome2.insert(pal22, pal33);
    palindrome2.insert(pal33, pal44);
    palindrome(palHead2);
    
    // 2.7 Testing
    Node* ihead1 = newNode(10);
    Node* ihead2 = newNode(3); 
  
    Node* i2 = newNode(6);  
    ihead2->next = i2; 
  
    Node* i23 = newNode(9); 
    ihead2->next->next = i23; 
  
    Node* both = newNode(15); 
    ihead1->next = both; 
    ihead2->next->next->next = both; 
  
    Node* i234 = newNode(30); 
    ihead1->next->next = i234; 
  
    ihead1->next->next->next = NULL; 
    printList(ihead1);
    printList(ihead2);

    Node* res3 = intersection(ihead1, ihead2);

    // 2.8 Testing
    Node* loophead = newNode(1); 
    loophead->next = newNode(2); 
    loophead->next->next = newNode(3); 
    loophead->next->next->next = newNode(4); 
    loophead->next->next->next->next = newNode(5); 
  
    /* Create a loop for testing(5 is pointing to 3) */
    loophead->next->next->next->next->next = loophead->next->next; 
  
    bool found = loopDetection(loophead); 
    if (found) 
        cout << "Loop Found"; 
    else
        cout << "No Loop"; 

    return 0;
}