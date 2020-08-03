/*
    Write a recursive function to multiply two positive integers, without using the '*' operator.
    You can use addition, subtraction, and bit shifting, but you should minimize the number of 
    those operators.
*/
#include <iostream>
using namespace std;

int recursiveMultiply(int a, int b){
    if(a < b){
        return recursiveMultiply(b, a);
    }
    else if (b != 0){
        return (a + recursiveMultiply(a, b-1));
    }
    else{
        return 0;
    }
    
}

int main(int argc, char* argv[]){
    int a  = 5; 
    int b = 2;
    cout << recursiveMultiply(a, b);

    return 0;
}