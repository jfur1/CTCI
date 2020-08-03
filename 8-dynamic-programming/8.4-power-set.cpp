/*
    Power Set:
        Write a method to return all subsets of a set.
    
    Solution: Help from Geekforgeeks
        
        Example:
            Set = [a, b, c]
            power_set_size = pow(2, 3) = 8
            Run binary counter: 000 to 111

            Value of Counter        Subset
                000                 -> Empty Set
                001                 -> a
                010                 -> b
                011                 -> ab
                100                 -> c
                101                 -> ac
                110                 -> bc
                111                 -> abc
*/
#include <iostream>
#include <math.h>
using namespace std;

class gtg{
    public:
        void printPowerSet(char *set, int set_size){
            unsigned int pow_set_size = pow(2, set_size);
            int counter, j;

            for(counter = 0; counter < pow_set_size; counter++){
                for(j = 0; j < pow_set_size; j++){
                    if(counter & (1 << j))
                        cout << set[j];
                }
                cout << endl;
            }
        }
};


int main(int argc, char* argv[]){
    gtg g;
    char set[] = {'a', 'b', 'c'};
    g.printPowerSet(set, 3);
    return 0;
}