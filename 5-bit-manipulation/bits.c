#include "bits.h"
#include <stdio.h>

/* Helper Functions */
int getBit(int num, int i){
    return (num & (1 << i)) != 0;
}

int setBit(int num, int i){
    return num | (1 << i);
}

int clearBit(int num, int i){
    int mask = ~(1 << i);
    return num & mask;
}

void decToBin(int n){
    // Size of the integer is assumed to be 32 bits.
    for(int i = 31; i >= 0; i--){
        int k = n >> i;
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
    return;
}

/* CTCI Chapter 5 Questions */

/* 5.1: Bit Insertion 
    Given two, 32-bit numbers N & M, and 2 bit positions i & j, write a method to insert
    M into N such that M starts at position j and ends at bit i. You can assume
    that the bits j through i have enough space to fit all of M. That is, 
    if M = 10011, you can assume that there are ay least 5 bits between j and i. 
    You would not, for example, have j = 3, and i = 2, since M wouldn't fit.
*/
int bitInsertion(int N, int M, int i, int j){
    int x = 0;
    int new_N = N;
    for(int k = 0; k < 32; k++){
        if(k <= i && k >= j){
            new_N = getBit(M, x) ? setBit(new_N, k) : clearBit(new_N, k);
            x++;
        } else{
            new_N = getBit(N, k) ? setBit(new_N, k) : clearBit(new_N, k);
        }
    }
    printf("Original N Value: ");
    decToBin(N);

    printf("Value of M: ");
    decToBin(M);
        
    printf("New N Value: ");
    decToBin(new_N);
    return N;
}

/*5.2: Binary to string
    Given a real number between 0 and 1 (e.g., 0.72) that is passed in as a double,
    print the binary representation. If the number cannot be represented accurately
    in binary with at most 32 characters, print "ERROR".
*/
void binaryToString(double Num){
    double num = Num;
    char bitString[34];
    char prefix[] = {'0', ' ', '0', '1', '1', '1', '1', '1', '1', '1', ' '};
    double frac = 0.0;
    // Double precision value between 0 and 1 will always have a positive sign bit, as well as a biased exponent = 127
    for(int j = 0; j < 12; j++){
        bitString[j] = prefix[j];
    }
    // Now, we just need to find the normalized mantissa, and append 0's if needed.
    for(int i = 1; i < 27; i++){
        double pow = (1 << i); 
        frac = 1 / pow;

        if((num - frac) >= 0.0){
            num -= frac;
            bitString[10+i] = '1';
        }else{
            bitString[10+i] = '0';
        }
    }
    if(num != 0){
        printf("%s", "ERROR: Could not represent ");
        printf("%f", Num);
        printf("%s\n", " using 32 bits.");
        return;
    }
    printf("%f", Num);
    printf("%s", " represented in binary: ");
    printf("%s\n", bitString);
    return;
}



/* 5.3: Flip Bit to Win
    You have an integer and you can flip exactly one bit from a 0 to a 1. Write code to find the length
    of the longest sequence of 1s you could create.
 */
int flipBit(int num){
    if(~num == 0){
        return sizeof(int);
    }
    int currLen, prevLen, maxLen = 0;
    while(num != 0){

        // If the current bit is 1, then increment current length
        if((num & 1) == 1){
            currLen++;
        }

        // If the current bit is 0, then check the next bit of the number. 
        else if((num & 1) == 0){
            // Update the prevLen to 0 if the next bit is zero, or update currLen if the next bit is a 1.
            prevLen = ((num & 2) == 0) ? 0 : currLen;

            // If two consecutive bits are 0, then the currLen is also 0.
            currLen = 0;
        }
        // Update maxLen if required
        maxLen = (prevLen + currLen) > maxLen ? (prevLen + currLen) : maxLen;

        // Remove last bit (right shift)
        num >>= 1;
    }
    // We can always have a sequence of at least one bit (the flipped bit).
    return maxLen + 1;
}



/* 5.4: Next Number
    Given a positive integer, print the next smallest and the next largest number that have the same number of 1 bits 
    in their binary representation.
*/
int nextLargest(int num){
    // Let p = the position of the rightmost non-trailing zero.
    // c1 = the number of 1s to the right of p
    // c2 = the number of 0s to the right of p
    int c1 = 0;
    int c2 = 0;
    int c = num;
    while((c & 1) == 0 && c!= 0){
        c1++;
        c >>= 1;
    }
    while((c&1) == 1){
        c2++;
        c >>= 1;
    }
    if((c1 + c2) == 31 || (c1+c2) == 0){
        return -1;
    }
    int p = c1 + c2;
    // Flip the rightmost non-trailing zero:
    num |= (1 << p);
    // Clear all bits to the right of p:
    num &= ~((1 << p)-1);
    // Insert (c1 -1) ones to the right of p:
    num |= (1 << (c2 - 1)) - 1;

    return num;
}

int nextSmallest(int num){
    int c1 = 0;
    int c2 = 0;
    int tmp = num;
    while((tmp & 1) == 1){
        c2++;
        tmp >>= 1;
    }
    if(tmp == 0)
        return -1;
    while((tmp & 1) == 0 && tmp != 0){
        c1++;
        tmp >>= 1;
    }
    int p = c1 + c2;
    // Clear bits from p onwards:
    num &= ((~0) << (p+1));
    // Sequence of (c2+1) bits
    int mask = (1 << (c2+1)) -1;
    num |= (mask << (c1 -1));

    return num;
}

void nextNumber(int num){
    int nextSmall = nextSmallest(num);
    int nextLarge = nextLargest(num);
    printf("%s", "Next smallest number: ");
    printf("%d\n", nextSmall);
    printf("%s", "Next largest number: ");
    printf("%d\n", nextLarge);
    return;
}


/* 5.5: Debugger
    Explain what the following code does:
    ((n & (n-1) == 0)
*/
/*
   Ex 1: 
    Let n = 15          n - 1 = 14              n & (n-1)
          = 1111    =>        = 1110    =>      = (1111 & 1110)
                                                = 1110 != 0
    Ex 2:
     Let n = 8          n - 1 = 7               n & (n-1)
           = 1000   =>        = 0111    =>      = (1000 & 0111)
                                                = 0000 = 0
    So, this code checks to see whether subtracting 1 from a number n is 
    equivalent to bitswapping the number (i.e., n == ~n), or not.
*/


/* 5.6: Conversion
    Write a function to determine the number of bits you would need to flip
    in order to convert integer A into integer B.
    Ex: 
        Input: 29 (11101), 15 (01111)
        Output: 2
*/
int conversion(int A, int B){
    int C = A ^ B;
    int n = 0;
    while(C > 0){
        if((C & 1) == 1)
            n++;
        C >>= 1;
    }
    printf("Number of bitswaps required to convert %d into %d: ", A, B);
    printf("%d\n", n);
    return n;
}


/* 5.7: Pairwise Swap
    Write a program to swap odd and even bits in an integer with as few
    instructions as possible. (i.e., bit 0 and bit 1 are swapped,
    bit 2 and 3 are swapped, etc.)
*/
void pairwiseSwap(int num){
    int even_bits = num & 0xAAAAAAAAA;
    int odd_bits = num & 0x55555555;
    even_bits >>= 1;
    odd_bits <<= 1;
    int x = (even_bits | odd_bits);
    return decToBin(x);
}

/* 5.8: Draw Line
    A monochrome screen is stored as a single array of bytes, allowing eight consecutive pixels to be store in one byte.
    The screen has width w, where w is divisible by 8 (that is, no byte will be split across rows). The height of the 
    screen, of course, can be derived from the length of the array and the width. Implement a function that draws
    a horizontal line from (x1, y) to (x2, y). 
    The method should look something like: 
        drawLine(byte[] screen, int width, int x1, int x2, int y)
*/ 
void drawLine(int screen[], int width, int x1, int x2, int y){
    if(width % 8 != 0)
        printf("Width must be divisible by 8!\n");
    int point1 = (width * y) + x1;
    int point2 = (width * y) + x2;
    int size = sizeof(*screen) * 8;
    printf("%d\n", size);
    printf("%d\n", point1);
    printf("%d\n", point2);
    int height = (size/width) - 1;

    int i = 1;
    while(i < size){
        if(i >= point1 && i <= point2){
            printf(" X ");
        }else{
            printf(" O ");
        }
        i++;
        if(i % width == 0){
            i++;
            printf("\n");
        }
    }
    return;
}
