#include <iostream>
#define MAX_SIZE 10 // Gives you a "private" global variable. Makes it so that it cannot be abused / modified 
using namespace std;

class Stack{
    private:
        int top;
        int max_size;
        int* data;

    public:
        Stack(int size){
            top = -1;
            max_size = size;
            data = new int[max_size];
        }
        ~Stack(){
            delete data;
        }
        // Is the Stack Full?
		bool isFull(){
			return true ? (top == max_size - 1) : false; // A quick way to write a conditional statement if there isn't a lot in the statement
		}		
        // Is the stack empty?
		bool isEmpty(){
			return true ? (top == -1) : false;
		}
        // Push
		int push(int value){
			if(isFull()){
				return -1;
			}

			top++; // Increment top before we pass the value (move it from -1)
			data[top] = value;

			return 0; // Return 0 if everything goes well
		}

		// Pop
		int* pop(){
			if(isEmpty()){
				return NULL; // Need to return NULL because this is a pointer to the stack
			}
			return &data[top--];
		}

};

class Queue{
	private:
		int head, tail;
		int* data;
		int queueSize, maxQueue;
		//Private Methods
		bool isEmpty(){
			return true ? (queueSize == 0) : false;
		}
		bool isFull(){
			return true? (queueSize == maxQueue) : false;
		}

	public:
		Queue(int maxSize){
			head = 0;
			tail = 0;
			queueSize = 0;
			maxQueue = maxSize;
			data = new int[maxQueue];
		}
		~Queue(){
			delete[] data;
		}

		int enqueue(int value){
			if (isFull()) return -1;
			data[tail++] = value;
			//cout << "Enqueued: " << value << endl;
			/*if(tail == maxQueue){
				tail = 0;
			}*/
			queueSize++;
			return 0;
		}

		int* dequeue(){
			if(isEmpty()) return NULL;
			//head = head + 1;
			//static int tmp = data[head]; //Create a temporary return variable to protect the privacy of data
			queueSize--;
			if(head == maxQueue-1){
				head = 0;
				return &data[maxQueue-1];
			}
			else{
				return &data[head++];
			}
		}
};

int main(){
	Stack myStack(MAX_SIZE);

	// Test Full/Empty
	cout << "--TEST FULL/EMPTY--" << endl;
	cout << "\tFull?: " << myStack.isFull() << endl;
	cout << "\tEmpty?: " << myStack.isEmpty() << endl;
	cout << endl;

	// Test push
	int returned;
	cout << "--PUSH--" << endl;
	for(int i = 0; i < 11; i++){	
		returned = myStack.push(i+1); //Push values 1-11 into the 10 slot array
		if(!returned){ //If the value is pushed print "Pushed: num"
			cout << "\tPushed: " << i+1 << endl;
		}
		else{ // If the stack is full, give error message
			cout << "\tStack is full! Failed to push " << i+1 << "." << endl;
		}
	}
	cout << "\tFull after push?: " << myStack.isFull() << endl;
	cout << "\tEmpty after push?: " << myStack.isEmpty() << endl;
	cout << endl;

	Queue myQueue(MAX_SIZE);
	myQueue.enqueue(1);
	myQueue.enqueue(2);
	myQueue.enqueue(3);
	myQueue.enqueue(4);
	
    return 0;
}