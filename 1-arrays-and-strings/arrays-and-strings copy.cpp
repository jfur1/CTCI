#include <iostream>
using namespace std;

/* 1.1: Implement an algorithm to determine if a string has all unique characters.
        What if you cannot use additional data structures?*/
bool isUnique(string str){
    
    for(int i = 0; i < str.length()-1; i++){
        for(int j = 0; j < str.length()-1; j++){
            if(str[i] == str[j] && i != j){
                cout << "The word <" << str << "> is NOT unique!";
                return false;
            }
        }
    }
    cout << "The word <" << str << "> is unique!";
    return true;
}

/* 1.2: Given two strings, write a method to decide if one is a permutation of the other. */
bool check_permutation(string str1, string str2){

    int n1 = str1.length();
    int n2 = str2.length();

    if(n1 != n2){ // If two strings are not the same length, they cannot be permutations of each other.
        return false; 
    }

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    
    for(int i = 0; i < n1; i++){
        if(str1[i] != str2[i]){
            return false;
        }
    }
    return true;
}

/* 1.3: Write a method to replace all spaces in a string with '%20'. 
        You may assume that the string has sufficient space at the end to hold additional characters,
        and that you are given the "true" length of a string. (Note: If implementing in Java,
        please use a character array so that you can perform this operation in one place.) */

// Maximum length of string after modifications. 
const int MAX = 1000;

int URLify(char str[]){
    int space_count = 0 ,i;
    for(i =0; str[i]; i++){
        if(str[i] == ' '){
            space_count++;
        }
    }

    while(str[i-1] == ' '){
        space_count--;
        i--;
    }

    int new_length = i + space_count * 2 + 1;

    int index = new_length - 1;

    if(new_length > MAX){
        return -1;
    }

    str[index--] = '\0';

    for(int j = i-1; j >= 0; j--){
        if(str[j] == ' '){
            str[index] = '0';
            str[index - 1] = '2';
            str[index - 2] = '%';
            index = index - 3;
        }
        else{
            str[index] = str[j];
            index--;
        }
    }
    return new_length;
}

/* 1.4: Given a string, write  a function to check if it is a permutation of a palindrome.
        A palindrome is a word or phase that is the same forwards and backwards. A permutation
        is a rearrangement of letters. The palindrome does not need to be limited to just 
        dictionary words. You can ignore character casing and non-letter characters. 
        EX: 
            Input: Tact Coa
            Output: True (permutations: "taco cat", "atco cta", etc.)*/
#define NO_OF_CHARS 256
bool check_pp(string str){
    // Create a count array and initialize all values to 0
    int count[NO_OF_CHARS] = {0};

    // For each character in the input strings, increment count in the coorespding array.
    for(int i = 0; str[i]; i++){
        if(str[i] == ' ')
            continue;
        count[str[i]]++;
    }

    // Count odd reccurring characters
    int odd = 0;
    for(int i = 0; i < NO_OF_CHARS; i++){
        if(count[i] & 1)
            odd++;
        if(odd > 1)
            return false;
    }
    // Return true if odd count is 0 or 1
    return true;
}

/* 1.5: There are three types of edits that can be performed on strings: insert a character,
        remove a character, or replace a character. Given two strings, write a function to 
        check if they are one edit (or zero edits) away.
        Ex:
            pale, ple --> true
            pales, pale --> true
            pale, bale --> true
            pale, bake --> false
*/
bool one_away(string str1, string str2){
    // 256 = No. of possible characters (127 ASCII)
    int count1[256] = {0};
    int count2[256] = {0};
    int index1[256] = {0};
    int index2[256] = {0};

    int differences = 0;
    // Keep count for each letter of both strings
    for(int i = 0; i < str1.size(); i++){
        // Keep a count for each character
        count1[str1[i]]++;
        // Store what index each character occurs at
        index1[str1[i]] = i;
    }
    for(int i = 0; i < str2.size(); i++){
        // Keep a count for each character
        count2[str2[i]]++;
        // Store what index each character occurs at
        index2[str2[i]] = i;
    }

    // Check to see whether the two strings have more than one letter difference
    for(int i = 0; i < 256; i++){
        // Different Characters not at the same index (pale, pale -- > true), but (pale, bake --> false)
        if((count1[i] != count2[i]) && index1[i] != index2[i]){
            differences++;
        }
        if(differences > 1)
            return false;
    }
    return true;
}

/* 
    1.6: String Compression
    Implement a method to perform basic string compression using the counts of repeated
    characters. For example, the string 'aabcccccaaa' would become 'a2b1c5a3'. If the 
    "compressed" string would not become smaller than the original string, your method
    should return the original string. You can assume the string has only uppercase and
    lowercase letters (a-z).
*/
void str_compression(string str){
    char letter = str[0];
    int count = 0;
    for(int i = 0; i < str.length(); i++){
        if(str[i] != letter){
            cout << letter << count;
            letter = str[i];
            count = 1;
        }
        else{
            count++;
        }
    }
    cout << letter << count << endl;
}

/*
    1.7: Rotate Matrix:
    Given an image represented by an N x N matrix, where each pixel in the image is 
    represented by an integer, write a method to rotate the image by 90 degrees. Can you
    do this in place?
*/
#define R 3
#define C 4
void rorate_matrix(int matrix[R][C]){
    int row[R];
    int col[C];

    for(int i = 0; i < R; i++){
        row[i] = 0;
        col[i] = 0;
    }

}

/*
    1.8: Zero Matrix:
    Write an algorithm such that if an element in an M x N matrix is 0, its entire row and 
    column are set to zero. 
*/
void zero_matrix(int matrix[R][C]){
    int row[R];
    int col[C];

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(matrix[i][j] == 0){
                row[i] = 0;
                col[j] = 0;
            }
        }
    }

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(row[i] == 0 || col[j] == 0){
                matrix[i][j] = 0;
            }
        }
    }
}

void printMatrix(int mat[R][C]) 
{ 
    int i, j; 
    for (i = 0; i < R; i++) 
    { 
        for (j = 0; j < C; j++) 
        { 
            cout << mat[i][j]; 
        } 
        cout << endl; 
    } 
} 

/*
    1.9: String Rotation:
    Assume you have a method 'isSubstring' which checks if one word is a substring of 
    another. Given two strings, s1 and s2, write code to check if s2 is a rotation of 
    s1 using only one call to "isSubstring". 
    (e.g., "waterbottle" is a rotation of "erbottlewat").
*/
int isSubstring(string s1, string s2){
    int M = s1.length();
    int N = s2.length();

    for(int i = 0; i <= N - M; i++){
        int j;
        for(j = 0; j < M; j++){
            if(s2[i+j] != s1[j])
                break;
        }
        if(j == M)
            return i;
    }
    return -1;
}
// bool string_rot(string s1, string s2){

// }


int main(){
    // 1.1 Testing
    isUnique("hello");
    cout << endl;
    isUnique("halo");
    cout << endl;

    // 1.2 Testing
    if(check_permutation("abcdef", "bdface")){
        printf("Yes");
    }
    else{
        printf("No");
    }
    cout << endl;
    if(check_permutation("hello", "goodbye")){
        printf("Yes");
    }
    else{
        printf("No");
    }
    cout << endl;

    // 1.3 Testing
    char str[MAX] = "Mr John Smith   ";
    char str2[MAX] = "Hello Mr Furlong  ";
    int new_length = URLify(str);
    int new_length2 = URLify(str2);
    for(int i = 0; i < new_length; i++){
        printf("%c", str[i]);
    }
    for(int i = 0; i < new_length2; i++){
        printf("%c", str2[i]);
    }
    cout << endl;

    // 1.4 Testing
    if(check_pp("tact coa")){
        printf("Is a permutation of a palindrome.");
    }
    else{
        printf("Is NOT a permutation of a palindrome.");
    }
    cout << endl;
    if(check_pp("hello world")){
        printf("Is a permutation of a palindrome.");
    }
    else{
        printf("Is NOT a permutation of a palindrome.");
    }
    cout << endl;

    // 1.5 Testing
    if(one_away("pale", "bake")){
        printf("True");
    }
    else{
        printf("False");
    }
    cout << endl;

    // 1.6 Testing
    str_compression("aaabccccaaa");

    // 1.7 Testing

    // 1.8 Testing:
    int mat[R][C] = {{0, 3, 2, 0}, 
                    {1, 3, 0, 9}, 
                    {2, 6, 7, 7}}; 
  
    cout << "Input Matrix \n"; 
    printMatrix(mat); 
  
    zero_matrix(mat); 
  
    printf("Matrix after modification \n"); 
    printMatrix(mat); 

    // // 1.9 Testing 
    // if(string_rot("waterbottle", "erbottlewat")){
    //     cout << "True." << endl;
    // }
    // else{
    //     cout << "False." << endl;
    // }
    

    return 0;


    
}