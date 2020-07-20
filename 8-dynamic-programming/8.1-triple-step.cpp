// A child is running up a staircase with N steps. They can either hop 1 step, 2 steps, or 3 steps.
//Implement a method to count how many possible ways the child can run up the steps.
#include <iostream>
#include <vector>
using namespace std;

// Brute Force: Recursive Implementation
// Solution comes from the fact that the stairs solution is similar to the fibonacci sequence.
// n_ways(i) = n_ways(i-3) + n_ways(i-2) + n_ways(i-1) ; where i = 3, 4, 5, ...
int n_ways(int n_steps){
    // Base Cases
    if(n_steps == 1) return 1;
    if(n_steps == 2) return 2;
    if(n_steps == 3) return 4;
    return n_ways(n_steps-3) + n_ways(n_steps-2) + n_ways(n_steps-1);
}
/*
    Recursive Implementation Runtime Analysis:
        - Branching Factor: 3
        - Depth: n
    Run Time: O(3^n)
    
    Spatial Complexity: O(3^n)  
        - No work is done outside the recursive calls to the stack. Therefore the space complexity is just the number of calls to the function.
*/


// Second Approach: Bottum-Up Dynamic Programming (Memoization)
// When we call nWays(n), there are only O(n) possible values that we can throw at the function. By using memoization and storing our results, 
// we can reduce the runtime of our function to be linear O(n).

int nWays_DP(int n){
    // Base Cases
    if(n == 1) return 1;
    if(n == 2) return 2;
    if(n == 3) return 4;

    // Memoization Array: 1 extra for i == 0
    int memo[n+2];
    memo[0] = 1;
    memo[1] = 2;
    memo[2] = 4;
    
    
    for(int i = 3; i <= n; i++){

        memo[i] = memo[i-3] + memo[i-2] + memo[i-1];
    }
    return memo[n-1];
}
/* Time Complexity: 
    - By caching results, the depth of our recursion tree is still n; however, for each level, only one child at most will have three of its own children.
    - This reduces our runtime to O(n)

    Space Complexity:
    - Caching results helped us improve our runtime; however, storing these results increased our space complexity: O(n)
    - Where n in the number of steps to traverse.
*/

/* Third Approach: Further Reduce Extra Space
    This approach takes advantage of the fact that memo[i] is only used to calculate memo[i-3] + memo[i-2] + memo[i-1], then we no longer need it.
    We can therefore reduce our extra space requirements by only keeping track of the past 3 values for the number of ways to go up N steps.
*/

int nWays_opt(int n){
    // if(n == 1) return 1;
    // if(n == 2) return 2;
    // if(n == 3) return 4;
    
    int a = 1;
    int b = 2;
    int c = 4;

    for(int i = 3; i < n; i++){
        int d = a + b + c;
        a = b;
        b = c;
        c = d;
    }
    return c;
}
/* Time Complexity: 
    - Time to complete is still O(N) where N is the number of steps 
    - Our iterative implementation is still an example of dynamic programming; however, we've gotten rid of the memoization array.

    Space Complexity:
    - Code is essentially storing the results from the previous 3 values, and at each iteration, it shifts the values.
    - O(1) : Only need to keep track of a few (constant) variables -- gets rid of memoization all together!    
*/

// Driver Code
int main(int argc, char* argv[]){

    int nSteps = 5;
    int nWays = n_ways(nSteps);
    cout << "Recursive Implementation:\n";
    cout << "Number of ways to climb up " << nSteps << " steps: " << nWays << endl;

    int nWaysDP = nWays_DP(nSteps);
    cout << "Memoization Implementation:\n";
    cout << "Number of ways to climb up " << nSteps << " steps: " << nWaysDP << endl;

    int nWaysOpt = nWays_opt(nSteps);
    cout << "Improved Memoization Implementation:\n";
    cout << "Number of ways to climb up " << nSteps << " steps: " << nWaysOpt << endl;
    
    return 0;
}
