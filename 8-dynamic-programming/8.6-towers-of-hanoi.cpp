/*
Towers of Hanoi: 
    In the classic problem of the Towers of Hanoi, you have 3 towers with N disks of different sizes which can slide onto any tower. The problem starts with 
    disks sorted in ascending order of sizes from top to bottom. (i.e., each disk sits on top of an even larger one). You have the following constraints:
        1) Only one disk can be moved at a time
        2) A disk is slid off the top of one tower onto another tower.
        3) A disk cannot be placed on top of a smaller disk

        Write a program to move the disks from the first tower to the last tower, using stacks.  

*/
#include <iostream>
using namespace std;

// Recursive Implementation of Tower of Hanoi Problem
void TOH(int N, char source, char aux, char dest){
    if(N == 1){
        cout << "Move disk " << N << " from " << source << " to " << dest << endl;
    }
    TOH(N-1, source, dest, aux);
    cout << "Move dist " << N << " from " << source << " to " << dest << endl;
    TOH(N-1, aux, source, dest);
}

int main(){
    int n;
    cout << "Enter the number of disks: \n";
    cin >> n;

    TOH(n, 'A', 'B', 'C');
    return 0;



}