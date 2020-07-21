/* 
    A magic index in an array A[0, ..., n-1] is defined to be a magic index such that A[i] = i.
    Given a sorted array of distinct integers, write a method to find the magic index, if one exists.

    Follow Up: What if the values are not distinct?

    Author: John Furlong

    Solution:

    Time Complexity:

    Space Complexity:
*/
#include <iostream>
using namespace std;

// Brute Force: Check each element
int magicIndex(int arr[], int magic_index, int n){
    for(int i = 0; i < n; i++){
        if(arr[i] == magic_index)
            return magic_index;
    }
    return -1;
}

int main(int argc, char* argv[]){
    int arr[] = {2, 5, 3, 6, 9, 5};
    if(!magicIndex(arr, 5, 6))
        cout << "No Magic Index found.\n";
    else
        cout << "Magic Index found at position: " << magicIndex(arr, 5, 6) << endl;
    
    return 0;
}