/**
 * Question: 322. Coin Change
 * Link: https://leetcode.com/problems/coin-change/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    // TC: O(exponential) because we can pick one coin, in worst case, amount number of times
    // SC: O(amount) - Recursion stack could go as deep as amount value
    int recursiveWorker(vector<int>& coins, const int index, const int amount)
    {
        /* Base Condition 1 */
        if (index < 0 || amount < 0) return INT_MAX-1;

        /* Base Condition 2 */
        if (index == 0)
        {
            if (!(amount % coins[index]))
                return (amount/coins[index]);
        }

        const int pick = 1 + recursiveWorker(coins, index, amount - coins[index]);
        const int notPick = recursiveWorker(coins, index-1, amount);

        return std::min(pick, notPick);
    }

    // TC: O(numCoins * amount)
    // SC: O(2 * numCoins * amount) - Recursion stack could go as deep as amount value
    int memoizationWorker(vector<vector<int>>& dp, vector<int>& coins, const int index, const int amount)
    {
        /* Base Condition 1 */
        if (index < 0 || amount < 0) return INT_MAX-1;

        /* Base Condition 2 */
        if (index == 0)
        {
            if (!(amount % coins[index]))
                return (amount/coins[index]);
        }

        /* Base Condition - Already memoized */
        if (dp[amount][index] != -1) return dp[amount][index];

        const int pick = 1 + memoizationWorker(dp, coins, index, amount - coins[index]);
        const int notPick = memoizationWorker(dp, coins, index-1, amount);

        return (dp[amount][index] = std::min(pick, notPick));
    }

    // TC: O(numCoins * amount)
    // SC: O(numCoins * amount) - Recursion stack could go as deep as amount value
    int tabulationWorker(vector<vector<int>>& dp, vector<int>& coins, const int index, const int totalAmount)
    {
        /* Fill dp table with base condition - when idx = 0, dp[amount][idx] = amount % idx */
        for (int amount = 0; amount <= totalAmount; amount += 1)
            if (!(amount % coins[0])) dp[amount][0] = amount/coins[0];

        /* Build tabulation using bottom-up approach */
        for (int idx = 1; idx <= index; idx += 1)
        {
            for (int amount = 0; amount <= totalAmount; amount += 1)
            {
                int pick = INT_MAX - 1;
                int notPick = dp[amount][idx-1];

                if ((amount - coins[idx]) >= 0)
                    pick = 1 + dp[amount - coins[idx]][idx];

                dp[amount][idx] = std::min(pick, notPick);
            }
        }

        return dp[totalAmount][index];
    }

    // TC: O(numCoins * amount)
    // SC: O(1)
    int optimizedTabulationWorker(vector<int>& coins, const int index, const int totalAmount)
    {
        vector<int> curr(totalAmount+1, INT_MAX-1);
        vector<int> prev(totalAmount+1, INT_MAX-1);

        /* Fill dp table with base condition - when idx = 0, dp[amount][idx] = amount % idx */
        for (int amount = 0; amount <= totalAmount; amount += 1)
            if (!(amount % coins[0])) prev[amount] = amount/coins[0];

        /* Build tabulation using bottom-up approach */
        for (int idx = 1; idx <= index; idx += 1)
        {
            for (int amount = 0; amount <= totalAmount; amount += 1)
            {
                int pick = INT_MAX - 1;
                int notPick = prev[amount];

                if ((amount - coins[idx]) >= 0)
                    pick = 1 + curr[amount - coins[idx]];

                curr[amount] = std::min(pick, notPick);
            }

            prev = curr;
        }

        return prev[totalAmount];
    }
public:
    int coinChange(vector<int>& coins, int amount)
    {
        // vector<vector<int>> dp(amount+1, vector<int>(coins.size(), -1));
        vector<vector<int>> dp(amount+1, vector<int>(coins.size(), INT_MAX-1));

        // const int numCoins = recursiveWorker(coins, coins.size()-1, amount);
        // const int numCoins = memoizationWorker(dp, coins, coins.size()-1, amount);
        // const int numCoins = tabulationWorker(dp, coins, coins.size()-1, amount);
        const int numCoins = optimizedTabulationWorker(coins, coins.size()-1, amount);

        return numCoins == INT_MAX-1 ? -1 : numCoins;
    }
};