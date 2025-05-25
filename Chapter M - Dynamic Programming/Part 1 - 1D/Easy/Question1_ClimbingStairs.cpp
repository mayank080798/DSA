/**
 * Question: 70. Climbing Stairs
 * Link: https://leetcode.com/problems/climbing-stairs/description/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    // TC: O(2^N) - where N is number of stairs
    // SC: O(N) - for recursion stack
    int recursiveWorker(const int stair)
    {
        /* Base Condition 1 */
        if (stair < 0) return 0;

        /* Base Condition 2 */
        if (stair == 0) return 1;

        /* Return total possible ways from current step */
        return recursiveWorker(stair-1) + recursiveWorker(stair-2);
    }

    // TC: O(N) - where N is number of stairs
    // SC: O(2N) - for recursion stack and vector
    int memoizationWorker(const int stair, vector<int>& dp)
    {
        /* Base Condition 1 */
        if (stair < 0) return 0;

        /* Base Condition 2 */
        if (stair == 0) return 1;

        /* Base Condition - Already memoized */
        if (dp[stair] != -1) return dp[stair];

        /* Return total possible ways from current step */
        return dp[stair] = (memoizationWorker(stair-1, dp) + memoizationWorker(stair-2, dp));
    } 

    // TC: O(N) - where N is number of stairs
    // SC: O(N) - for vector
    int tabulationWorker(const int stair, vector<int>& dp)
    {
        /* Base Condition */
        dp[0] = 1;
        dp[1] = 1;

        for (int step = 2; step <= stair; step += 1)
        {
            dp[step] = dp[step-1] + dp[step-2];
        }

        return dp[stair];
    } 

    // TC: O(N) - where N is number of stairs
    // SC: O(1)
    int optimizedTabulationWorker(const int stair)
    {
        /* Base Condition */
        if (stair <= 1)
            return stair;

        /* Update base cases */
        int prev1 = 1;
        int prev2 = 1;
        int result = -1;

        for (int step = 2; step <= stair; step += 1)
        {
            result = prev1 + prev2;

            prev1 = prev2;
            prev2 = result;
        }

        return result;
    } 
public:
    int climbStairs(int n)
    {
        vector<int> dp(n+1, -1);

        // return recursiveWorker(n);
        // return memoizationWorker(n, dp);
        // return tabulationWorker(n, dp);
        return optimizedTabulationWorker(n);
    }
};