/*
Author: John Furlong
Date: June 12, 2020
Description: Circular Array
    Implement a circularArray class that supports an array-like data structure which can be efficiently rotated. If possible, the
    class should use a generic type (also called a template), and should support iteration via the standard (Obj o : circularArray) notation.
*/
#include <iostream>
const int size = 6;
using namespace std;

class circularArray{
    private:
        char data[size];
        
    public:
        circularArray(char arr[]){
            for(int i = 0; i < size; i++){
                data[i] = arr[i];
            }
        }

        // Function rotates the circular array, starting from a given index. Uses the mod operator to perform the rotation in-place.
        void rotate(int index){
            for(int i = index; i < size + index; i++){
                cout << data[(i % size)] << " ";
            }
        }
};

int main(){
    // This approach takes O(n) time and O(1) space.
    char values[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    circularArray circle(values);
    circle.rotate(3);
    return 0;
}