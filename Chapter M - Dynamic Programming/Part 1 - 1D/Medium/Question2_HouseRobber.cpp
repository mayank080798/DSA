/**
 * Question: 198. House Robber
 * Link: https://leetcode.com/problems/house-robber/description/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    // TC: O(2^N) - where N is number of houses
    // SC: O(N) - for recursin stack
    int recursiveWorker(vector<int>& nums, const int house)
    {
        int maxSummation = 0;

        /* Base Condition - 1 */
        if (house < 0) return 0;

        /* Base Condition - 2 */
        if (house == 0) return nums[house];

        const int pick = nums[house] + recursiveWorker(nums, house - 2);
        const int notPick = recursiveWorker(nums, house - 1);

        return std::max(pick, notPick);
    }

    // TC: O(N) - where N is number of houses
    // SC: O(2N) - for recursion stack and cache
    int memoizationWorker(vector<int>& nums, vector<int>& dp, const int house)
    {
        int maxSummation = 0;

        /* Base Condition - 1 */
        if (house < 0) return 0;

        /* Base Condition - 2 */
        if (dp[house] != 0) return dp[house];

        const int pick = nums[house] + memoizationWorker(nums, dp, house - 2);
        const int notPick = memoizationWorker(nums, dp, house - 1);

        dp[house] = std::max(pick, notPick);

        return dp[house];
    }

    // TC: O(N) - where N is number of houses
    // SC: O(N) - for cache
    int tabulationWorker(vector<int>& nums, vector<int>& dp, const int house)
    {
        if (nums.size() <= 1)
            return dp[0];

        for (int index = 1; index < nums.size(); index += 1)
        {
            const int pick = nums[index] + (index >= 2 ? dp[index-2] : 0);
            const int notPick = dp[index-1];

            dp[index] = std::max(pick, notPick);
        }

        return dp[house];
    }

    // TC: O(N) - where N is number of houses
    // SC: O(1)
    int optimalTabulationWorker(vector<int>& nums, vector<int>& dp, const int house)
    {
        int curr = 0;
        int prev2 = 0;
        int prev1 = dp[0];

        if (nums.size() <= 1)
            return dp[0];

        for (int index = 1; index < nums.size(); index += 1)
        {
            curr = std::max(prev1, (nums[index] + prev2));

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
public:
    int rob(vector<int>& nums)
    {
        vector<int> dp(nums.size());

        dp[0] = nums[0];

        return optimalTabulationWorker(nums, dp, nums.size()-1);
    }
};