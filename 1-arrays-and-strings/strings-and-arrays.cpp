#include <iostream>

namespace arrays_and_strings{
    class Str{
        public:
            bool isUnique(std::string str);
            bool check_permutation(std::string str1, std::string str2);
            void URLify(char str[]);
            bool check_pp(std::string str);
            bool one_away(std::string str1, std::string str2);
            void str_compression(std::string str);
            void rotate_matrix(int matrix[3][4]);
            void zero_matrix(int matrix[3][4]);
    };
}

using namespace std;
using namespace arrays_and_strings;

/* 1.1: Implement an algorithm to determine if a string has all unique characters.
        What if you cannot use additional data structures? */
bool Str::isUnique(string str){
    bool chars[128] = { false }; // 128 values of the ASCII table
    for(int i = 0; i < str.length(); i++){
        int val = str[i]; // Get the decimal value for each character
        if(chars[val]){
            cout << "The word <" << str << "> is NOT unique.\n";
            return false;
        }
        chars[val] = true;
    }
    cout << "The word <" << str << "> IS unique\n";
    return true;
}

/* 1.2: Given two strings, write a method to decide if one is a permutation of the other. */
bool Str::check_permutation(string str1, string str2){
    if(str1.length() != str2.length()){
        cout << "The two words are NOT permuations of one another.\n";
        return false;
    }
    cout << '<' << str1 << "> and <" << str2 << "> ";
        sort(str1.begin(), str1.end());
        sort(str2.begin(), str2.end());
    /* If the two strings are not identical when sorted, then
        they cannot be permutations of each other */
    
    for(int i = 0; i < str1.length(); i++){
        if(str1[i] != str2[i]){
            cout << "are NOT permutations of one another.\n";
            return false;
        }
    }
    cout << "ARE permutations of one another.\n";
    return true;
}

/* 1.3: URLify
    Write a method to replace all spaces in a string with '%20'. 
    You may assume that the string has sufficient space at the end to hold additional characters,
    and that you are given the "true" length of a string. (Note: If implementing in Java,
    please use a character array so that you can perform this operation in one place.) */
const int MAX = 1000;
// Maximum length of string after modifications. 
void Str::URLify(char str[]){
    int space_count = 0 ,i;
    // Count spaces and find current length
    for(i =0; str[i]; i++){
        if(str[i] == ' '){
            space_count++;
        }
    }

    // Remove trailing spaces
    while(str[i-1] == ' '){
        space_count--;
        i--;
    }
    // Find new length
    int new_length = i + space_count * 2 + 1;

    int index = new_length - 1;

    if(new_length > MAX){
        cout << "Maximum modification length exceeded\n";
        return;
    }
    // Fill string termination
    str[index--] = '\0';
    // Fill the new string from the end
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
return;
}

/* 1.4: Check for Palindrome Permutation
    Given a string, write  a function to check if it is a permutation of a palindrome.
    A palindrome is a word or phase that is the same forwards and backwards. A permutation
    is a rearrangement of letters. The palindrome does not need to be limited to just 
    dictionary words. You can ignore character casing and non-letter characters. 
        EX: 
            Input: Tact Coa
            Output: True (permutations: "taco cat", "atco cta", etc.)*/
bool Str::check_pp(string str){
    int count[256] = { 0 };

    for(int i = 0; i < str.length(); i++){
        if(str[i] == ' ')
            continue;
        count[str[i]]++;
    }

    int odd = 0;
    for(int i = 0; i < 256; i++){
        // Only true if the count of a letter is 1.
        if(count[i] & 1)
            odd++;
        if(odd > 1){
            cout << '<' << str << '>' << " is NOT a permutation of a palindrome.\n";
            return false;           
        }
    }
    cout << '<' << str << '>' << " IS a permutation of a palindrome!\n";
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
bool Str::one_away(string str1, string str2){
    int count1[256] = {0};
    int count2[256] = {0};
    int index1[256] = {0};
    int index2[256] = {0};
    int differences = 0;

    // Keep a count for each letter of both strings
    for(int i = 0; i < str1.size(); i++){
        // Keep a count for each character
        count1[str1[i]]++;
        // Store what index each character occurs at
        index1[str1[i]] = i;
    }
    // Second for loop because words don't necessarily need to be same length
    for(int i = 0; i < str2.size(); i++){
         // Keep a count for each character
        count2[str2[i]]++;
        // Store what index each character occurs at
        index2[str2[i]] = i;       
    }

    // Check to see whether the two strings have more than one letter difference
    for(int i = 0; i < 256; i++){
        // Different characters not at the same index (pale, pale -- > true), but (pale, bake --> false)
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
void Str::str_compression(string str){
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


/* 1.8: Zero Matrix:
    Write an algorithm such that if an element in an M x N matrix is 0, its entire row and 
    column are set to zero. 
*/
#define R 3
#define C 4
void Str::zero_matrix(int matrix[R][C]){
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

/* 1.9: String Rotation:
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


int main(){
    // Testing

    Str str;

    // 1.1: isUnique()
    str.isUnique("computer");
    str.isUnique("mississippi");
    cout << endl;

    // 1.2: check_permutation()
    str.check_permutation("helicopter", "frozen");
    str.check_permutation("computer", "potercum");
    str.check_permutation("welcome", "goodbye");
    cout << endl;

    // 1.3: URLify()
    // char word[MAX] = "Mr John Smith   ";
    // str.URLify(word);
    // cout << endl;

    // 1.4: check_pp()
    str.check_pp("playstation");
    str.check_pp("taco cat");
    cout << endl;

    // 1.5: one_away()
    str.one_away("pale", "ple");
    str.one_away("pales", "pale");
    str.one_away("pale", "bale");
    str.one_away("pale", "bake"); 
    cout << endl;

    // 1.6: String Compression
    cout << "aaaaabbbccccddd --> ";
    str.str_compression("aaaaabbbccccddd");
    cout << "aaabbc --> ";
    str.str_compression("aaabbc");
    cout << endl;

    // 1.8 Testing:
    int mat[R][C] = {{0, 3, 2, 0}, 
                    {1, 3, 0, 9}, 
                    {2, 6, 7, 7}};
    cout << "Input Matrix \n"; 
    printMatrix(mat); 
  
    str.zero_matrix(mat);
  
    printf("Matrix after modification \n"); 
    printMatrix(mat);

    return 0;
}