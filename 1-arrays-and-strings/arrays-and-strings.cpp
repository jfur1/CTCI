//#include "arrays-and-strings.h"
#include <iostream>
#include <string>

namespace arrays_and_strings{
    class Arr{
        public:
            bool isUnique(std::string str);
            bool check_permutation(std::string str1, std::string str2);
            int URLify(char str[]);
            bool check_pp(std::string str);
            bool one_away(std::string str1, std::string str2);
            void str_compression(std::string str);
            void rotate_matrix(int (*matrix)[4]);
            void zero_matrix(int (*matrix)[4]);
    };
}

using namespace arrays_and_strings;
using namespace std;

/* 1.1: Implement an algorithm to determine if a string has all unique characters.
        What if you cannot use additional data structures?*/
bool Arr::isUnique(string str){
    bool char_set[128] = { 0 };
    for(int i = 0; i <str.length(); i++){
        int val = str[i];
        if(char_set[val]){
            cout << "The word <" << str << "> is NOT unique.\n";
            return false;
        }
        char_set[val] = true;
    }
    cout << "The word <" << str << "> IS unique!\n";
    return true;
}

/* 1.2: Given two strings, write a method to decide if one is a permutation of the other. */
bool Arr::check_permutation(string str1, string str2){
    if(str1.length() != str2.length()){
        cout << "The two words are NOT permutations of one another.\n";
        return false;   // Two words that are different lengths cannot be permutations of each other.
    }

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    for(int i = 0; i < str1.length(); i++){
        if(str1[i] != str2[i]){
            cout << "The two words are NOT permutations of one another.\n";
            return false;
        }
    }
    cout << "The two words ARE permutations of one another!\n";
    return true;
}

/* 1.3: URLify
    Write a method to replace all spaces in a string with '%20'. 
    You may assume that the string has sufficient space at the end to hold additional characters,
    and that you are given the "true" length of a string. (Note: If implementing in Java,
    please use a character array so that you can perform this operation in one place.) */
    
const int MAX = 1000;
// Maximum length of string after modifications. 

int Arr::URLify(char str[]){

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
    for(int i = 0; i < new_length; i++){
        printf("%c", str[i]);
    }
    return new_length;
}

/* 1.4: Check for Palindrome Permutation
    Given a string, write  a function to check if it is a permutation of a palindrome.
    A palindrome is a word or phase that is the same forwards and backwards. A permutation
    is a rearrangement of letters. The palindrome does not need to be limited to just 
    dictionary words. You can ignore character casing and non-letter characters. 
        EX: 
            Input: Tact Coa
            Output: True (permutations: "taco cat", "atco cta", etc.)*/
bool Arr::check_pp(string str){
    int count[256] = {0};

    for(int i = 0; i < str.length(); i++){
        if(str[i] == ' ')
            continue;
        count[str[i]]++;
    }

    int odd = 0;
    for(int i = 0; i < 256; i++){
        if(count[i] & 1)
            odd++;
        if(odd > 1){
            cout << '<' << str << '>' << " is NOT a permutation of a palindrome.\n";
            return false;
        }
    }
    cout << '<' << str << '>' << " IS a permutation of a palindrome!/n";
    return true;
}

/* 1.5: One Edit Away
    There are three types of edits that can be performed on strings: insert a character,
    remove a character, or replace a character. Given two strings, write a function to 
    check if they are one edit (or zero edits) away.
        Ex:
            pale, ple --> true
            pales, pale --> true
            pale, bale --> true
            pale, bake --> false    */
bool Arr::one_away(string str1, string str2){
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
        if(differences > 1){
            cout << '<' << str1 << ", " << str2 << '>' << " are NOT within one edit away.\n";
            return false;
        }
    }
    cout << '<' << str1 << ", " << str2 << '>' << " ARE within one edit away!\n";
    return true;
}
 
/* 1.6: String Compression
    Implement a method to perform basic string compression using the counts of repeated
    characters. For example, the string 'aabcccccaaa' would become 'a2b1c5a3'. If the 
    "compressed" string would not become smaller than the original string, your method
    should return the original string. You can assume the string has only uppercase and
    lowercase letters (a-z).*/
void Arr::str_compression(string str){
    char letter = str[0];
    int count = 0;
    string new_str = "";
    for(int i = 0; i < str.length(); i++){
        if(str[i] != letter){
            new_str += letter + to_string(count);
            letter = str[i];
            count = 1;
        }
        else{
            count++;
        }
    }
    new_str += letter + to_string(count);
    if(new_str.length() >= str.length()){
        cout << str << "\n";
    }
    else{
        cout << new_str << "\n";
    }
}

/* 1.7: Rotate Matrix:
    Given an image represented by an N x N matrix, where each pixel in the image is 
    represented by an integer, write a method to rotate the image by 90 degrees. Can you
    do this in place?   */
// void rorate_matrix(int matrix[R][C]){
    
// }

int main(){
    Arr arr;
    // TESTS: 

    // 1.1: isUnique()
    // arr.isUnique("computer");
    // arr.isUnique("mississippi");

    // 1.2: check_permutation()
    // arr.check_permutation("helicopter", "frozen");
    // arr.check_permutation("computer", "potercum");

    // 1.3: URLify()
    // char str[MAX] = "Mr John Smith   ";
    // arr.URLify(str);

    // 1.4: check_pp()
    // arr.check_pp("playstation");
    // arr.check_pp("taco cat");

    // 1.5: one_away()
    arr.one_away("pale", "ple");
    arr.one_away("pales", "pale");
    arr.one_away("pale", "bale");
    arr.one_away("pale", "bake");    

    // 1.6: String Compression
    // arr.str_compression("aaaaabbbccccddd");
    // arr.str_compression("aaabbc");
    
    // 1.7 Rotate Matrix 
    // int a[R][C] = { {1,  2,  3,  4}, 
    //     {5,  6,  7,  8}, 
    //     {9,  10, 11, 12}, 
    //     {13, 14, 15, 16}  }; 

}