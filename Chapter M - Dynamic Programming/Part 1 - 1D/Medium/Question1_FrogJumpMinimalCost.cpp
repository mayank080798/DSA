/**
 * Question: Geek Jump/Frog Jump
 * Link: https://www.geeksforgeeks.org/problems/minimal-cost/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=minimal-cost
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    // TC: O(Exponential) - where N is number of stairs
    // SC: O(N) - for recursion stack
    int recursiveWorker(const int step, vector<int>& stairs, const int maxSteps)
    {
        int cost = INT_MAX;
        int minimalCost = INT_MAX;

        /* Base Condition 1 */
        if (step <= 0) return 0;

        /* Compute minimum cost out all combinations from current step */
        for (int idx = 1; idx <= maxSteps; idx += 1)
        {
            if ((step - idx) >= 0)
            {
                cost = std::abs(stairs[step] - stairs[step-idx]);
            
                minimalCost = std::min(minimalCost, recursiveWorker(step-idx, stairs, maxSteps) + cost);
            }
        }
        
        // cout << "Step: " << step << " MinimalCost: " << minimalCost << endl;
        
        return minimalCost;
    }
    
    // TC: O(N*maxSteps) - where N is number of stairs
    // SC: O(2N) - for recursion stack and dp vector
    int memoizationWorker(const int step, vector<int>& stairs, vector<int>& dp, const int maxSteps)
    {
        int cost = INT_MAX;
        int minimalCost = INT_MAX;

        /* Base Condition 1 */
        if (step <= 0) return 0;
        
        /* Base Condition - Already memoized */
        if (dp[step] != -1) return dp[step];

        /* Compute minimum cost out all combinations from current step */
        for (int idx = 1; idx <= maxSteps; idx += 1)
        {
            if ((step - idx) >= 0)
            {
                cost = std::abs(stairs[step] - stairs[step-idx]);
            
                minimalCost = std::min(minimalCost, memoizationWorker(step-idx, stairs, dp, maxSteps) + cost);
            }
        }
        
        // cout << "Step: " << step << " MinimalCost: " << minimalCost << endl;
        
        return dp[step] = minimalCost;
    }
    
    // TC: O(N*maxSteps) - where N is number of stairs
    // SC: O(N) - for dp vector
    int tabulationWorker(vector<int>& stairs, vector<int>& dp, const int maxSteps)
    {
        int cost = INT_MAX;
        int minimalCost = INT_MAX;

        /* Base Case */
        dp[0] = 0;
        
        /* Build bottom up tabulation. Traverse maxSteps for each step */
        for (int step = 1; step < stairs.size(); step += 1)
        {
            minimalCost = INT_MAX;
            
            for (int idx = 1; idx <= maxSteps; idx += 1)
            {
                if ((step - idx) >= 0)
                {
                    cost = std::abs(stairs[step] - stairs[step-idx]);
                
                    minimalCost = std::min(minimalCost, dp[step-idx] + cost);
                }
            }
            
            dp[step] = minimalCost;
        }
        
        return dp[stairs.size()-1];
    }
public:
    int minimizeCost(int k, vector<int>& arr)
    {
        vector<int> dp(arr.size(), -1);
        
        // return recursiveWorker(arr.size()-1, arr, k);
        // return memoizationWorker(arr.size()-1, arr, dp, k);
        return tabulationWorker(arr, dp, k);
    }
};