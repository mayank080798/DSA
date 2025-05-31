/**
 * Question: 62. Unique Paths
 * Link: https://leetcode.com/problems/unique-paths/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    int numRows = 0;
    int numCols = 0;

    // TC: O(2^(N*M)) - where N is numRows and M is numCols
    int recursiveWorker(const int row, const int col)
    {
        /* Base Condition - Negative */
        if (row < 0 || col < 0) return 0;

        /* Base Condition - Positive */
        if (!row && !col) return 1;

        /* Robot could have come from upper cell or left cell */
        const int up = recursiveWorker(row-1, col);
        const int left = recursiveWorker(row, col-1);

        return (up + left);
    }

    // TC: O(N*M) - where N is numRows and M is numCols
    // SC: O(N*M) - where N is numRows and M is numCols
    int memoizationWorker(vector<vector<int>>& dp, const int row, const int col)
    {
        /* Base Condition - Negative */
        if (row < 0 || col < 0) return 0;

        /* Base Condition - Positive */
        if (!row && !col) return 1;

        /* Base Condition - Cell already memoized */
        if (dp[row][col] != -1) return dp[row][col];

        /* Robot could have come from upper cell or left cell */
        const int up = memoizationWorker(dp, row-1, col);
        const int left = memoizationWorker(dp, row, col-1);

        return dp[row][col] = (up + left);
    }

     // TC: O(M*N) - where M is number of rows and N is number of columns. Each cell is visited at most once
    // SC: O(M*N) - 2D vector
    int tabulationWorker(vector<vector<int>>& dp)
    {
        const int numRows = dp.size();
        const int numCols = dp[0].size();

        for (int row = 0; row < numRows; row += 1)
        {
            for (int col = 0; col < numCols; col += 1)
            {
                if (!row && !col)
                    continue;

                const int down = (row-1 >= 0) ? dp[row-1][col] : 0;
                const int right = (col-1 >= 0) ? dp[row][col-1] : 0;

                dp[row][col] = down + right;
            }
        }

        return dp[numRows-1][numCols-1];
    }

    // TC: O(M*N) - where M is number of rows and N is number of columns. Each cell is visited at most once
    // SC: O(N) - vector
    int optimizedTabulationWorker(const int numRows, const int numCols)
    {
        // Create a vector to represent the previous row of the grid.
        vector<int> prev(numCols, 0);

        for (int row = 0; row < numRows; row += 1)
        {
            vector<int> temp(numCols, 0);

            for (int col = 0; col < numCols; col += 1)
            {
                if (row == 0 && col == 0)
                {
                    temp[col] = 1;
                    continue;
                }

                const int right = (col-1 >= 0) ? temp[col-1] : 0;
                const int down = (row-1 >= 0) ? prev[col] : 0;

                temp[col] = right + down;
            }

            prev = temp;
        }

        return prev[numCols-1];
    }
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, -1));

        // return recursiveWorker(m-1, n-1);
        // return memoizationWorker(dp, m-1, n-1);
        return optimizedTabulationWorker(m, n);
    }
};