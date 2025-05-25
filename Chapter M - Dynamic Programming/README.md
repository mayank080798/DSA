# Dynamic Programming

Dynamic programming amounts to breaking down an optimization problem into simpler sub-problems, and storing the solution to each sub-problem so that each sub-problem is only solved once.

## Reference

https://medium.com/basecs/less-repetition-more-dynamic-programming-43d29830a630

## Remember to remember

The trick to calculating all of the solutions to the various subproblems (and then choosing the best one) is remembering previous solutions.

![alt text](./Misc/image.png)
![alt text](./Misc/image-1.png)

## Identifying a Dynamic Programming Problem

1. Optimal substructure

    The solution to the problem can be constructed from solutions to subproblems.

    1. Can you divide the problem into smaller parts?
    2. Does solving the subparts help solve the whole?

2. Overlapping subproblems

    You solve the same subproblems multiple times.

    1. Naive recursion leads to repeated calls.
    2. You can build a recursion tree and notice repeated nodes.

3. Multiple Choices/Decisions at each step

    At each step, you are deciding between two or more options

    1. Include/exclude an item (Knapsack)
    2. Cut/do not cut a rod (Rod cutting)
    3. Buy/sell/hold a stock

4.  Need for All Possibilities / Count / Max / Min
    
    Problems ask you to:
    1. Count ways
    2. Minimize/Maximize something
    3. Return if possible or not

![alt text](./Misc/image3.png)

## Steps to solve a dynamic programming problem

1. Identify if the problem exhibits optimal substructure and overlapping subproblems.
2. Define the structure of the problem and the desired output.
3. Break down the problem into smaller, overlapping subproblems.
4. Create a memoization table to store the results of subproblems to avoid redundant calculations.
5. Write a recursive solution to the problem using the memoization table.
6. Convert the recursive solution to an iterative one, if possible, for better performance.

## Example: Fibonacci Sequence

#### Brute Force Approach

```
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

Time Complexity: O(2^N)
Space Complexity: O(N) due to call stack
```

#### Top-Down DP (Memoization)

```
int fib(int n, std::vector<int>& dp) {
    if (n <= 1) return n;
    if (dp[n] != -1) return dp[n];
    return dp[n] = fib(n - 1, dp) + fib(n - 2, dp);
}

Time Complexity: O(N)
Space Complexity: O(2N) for memoization vector and recursion stack
```

#### Bottom-Up DP (Tabulation)
```
int fibonacci(int n) {
    if (n <= 1) return n;
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

Time Complexity: O(N)
Space Complexity: O(N) for memoization vector
```

#### Space Optimized Iterative

```
int fibonacci(int n) {
    if (n <= 1) return n;
    int prev1 = 1, prev2 = 0, curr;
    for (int i = 2; i <= n; ++i) {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

Time Complexity: O(N)
Space Complexity: O(1)
```

#### Summary

| Approach                  | Time Complexity | Space Complexity |
| ------------------------- | --------------- | ---------------- |
| Brute Force Recursion     | `O(2^n)`        | `O(n)`           |
| Memoization (Top-Down)    | `O(n)`          | `O(n)`           |
| Tabulation (Bottom-Up)    | `O(n)`          | `O(n)`           |
| Space-Optimized Iterative | `O(n)`          | `O(1)`           |


# Dynamic Programming Patterns

1. Linear DP

    Problem Type: Compute value at position n based on previous values.

    State Transition: dp[i] = dp[i - 1] + dp[i - 2]
    
    Examples:
    1. Fibonacci numbers
    2. Climbing stairs
    3. Tiling problems
    4. Tribonacci sequence

2. Knapsack DP

    Problem Type: Maximize/minimize value under capacity constraint.

    State: dp[i][w] = best value with first i items and capacity w

    Examples:
    1. 0/1 Knapsack
    2. Unbounded Knapsack
    3. Subset sum
    4. Partition equal subset sum
    5. Target sum

3. Choice Dp
    
    Problem Type: Choose between multiple options at each step
    
    Examples:
    1. House Robber
    2. Paint House
    3. Coin Change
    4. Jump Game
    5. Buy & Sell Stocks

4. Longest Subsequence / Substring Pattern

    Problem Type: Find longest increasing, common, or palindromic subsequences.
    
    State: dp[i][j] = result considering substrings up to i and j
    
    Examples:
    1. Longest Common Subsequence (LCS)
    2. Longest Palindromic Subsequence
    3. Longest Increasing Subsequence
    4. Edit Distance
    5. Wildcard Matching

5. DP on Grids

    Problem Type: Count paths or find minimum cost path in a grid.
    
    State: dp[i][j] = answer at cell (i, j)
    
    Examples:
    1. Unique Paths
    2. Minimum Path Sum
    3. Maximal Square
    4. Dungeon Game
    5. Cherry Pickup