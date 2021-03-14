/*
    8.7: Permutations without Duplicates:
    Write a method to compute all permutations of a string of unique characters.
*/
#include <iostream>
using namespace std;

void permutations(string str, int i, int n){
    if(i == n - 1){ 
        cout << str << endl;
        return;
    }
    // Process the remaining characters of the string
    for(int j = i; j < n; j++){
        swap(str[i], str[j]);

        permutations(str, i+1, n);

        swap(str[i], str[j]);
    }
}

int main(){
    string str = "ABC";

    permutations(str, 0, str.length());
    return 0;
}