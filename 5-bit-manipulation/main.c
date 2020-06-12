#include "bits.h"
#include <stdio.h>

int main(){
    /* Ch 5: Bit Manipulation Testing */

    // 5.1: Bit Insertion
    // int N = 1024;
    // int M = 15;
    // int j = 3;
    // int i = 6;
    // //int new_N = bitInsertion(N, M, i, j);

    // // 5.2: Binary To String
    // double num = 0.75;
    // double num2 = 0.33333;
    // //binaryToString(num);
    // //binaryToString(num2);

    // // 5.3: Flip Bit to Win
    // int tmp = 71;
    // int longestSeq = flipBit(tmp);
    // printf("%s\n", "Longest sequence of 1s created by flipping a single bit: ");
    // printf("%d\n", longestSeq);

    // 5.4: Next Number
    // int n = 6;
    // nextNumber(n);
    // n = 16;
    // nextNumber(n);
    // n = 15;
    // nextNumber(n);

    // 5.6: Conversion
    // int A = 29;
    // int B = 15;
    // int n = conversion(A, B);

    // 5.7: Pairwise Swap
    // int x = 23;
    // pairwiseSwap(x);

    // 5.8: Draw Line
    int screen[] = { 0, 0, 1, 1,  0, 0, 1, 1,
                     1, 1, 1, 1,  0, 1, 1, 0,
                     1, 0, 1, 1,  1, 0, 0, 1, 
                     0, 1, 1, 1,  0, 0, 1, 0};
    int width = 8;
    int x1 = 1;
    int x2 = 5;
    int y = 1;
    drawLine(screen, width, x1, x2, y);

    return 0;
}