/**
 * Question: 64. Minimum Path Sum
 * Link: https://leetcode.com/problems/minimum-path-sum/description/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    // TC: O(2^(N*M)) - where N is numRows and M is numCols
    // SC: O(Path Length) ~ O(M+N) - for traversing one complete row and one complete column
    int recursiveWorker(vector<vector<int>>& grid, const int row, const int col)
    {
        /* Base Condition - Negative */
        if (row < 0 || col < 0) return 1000000;

        /* Base Condition - Positive */
        if (!row && !col) return grid[row][col];

        /* Move either down or right */
        const int down = recursiveWorker(grid, row-1, col);
        const int right = recursiveWorker(grid, row, col-1);

        return grid[row][col] + std::min(down, right);
    }

    // TC: O(2^(N*M)) - where N is numRows and M is numCols
    // SC: O(Path Length) ~ O(M+N) + O(M*N) - for traversing one complete row and one complete column
    int memoizationWorker(vector<vector<int>>& grid, vector<vector<int>>& dp, const int row, const int col)
    {
        /* Base Condition - Negative */
        if (row < 0 || col < 0) return 1000000;

        /* Base Condition - Positive */
        if (!row && !col) return grid[row][col];

        /* Base Condtion - Cell already memoized */
        if (dp[row][col] != -1) return dp[row][col];

        /* Move either down or right */
        const int down = memoizationWorker(grid, dp, row-1, col);
        const int right = memoizationWorker(grid, dp, row, col-1);

        return dp[row][col] = (grid[row][col] + std::min(down, right));
    }

    // TC: O(2^(N*M)) - where N is numRows and M is numCols
    // SC: O(M*N) - where N is numRows and M is numCols
    int tabulationWorker(vector<vector<int>>& grid, vector<vector<int>>& dp, const int numRows, const int numCols)
    {
        /* Populate base condition in dp table */
        dp[0][0] = grid[0][0];

        for (int row = 0; row < numRows; row += 1)
        {
            for (int col = 0; col < numCols; col += 1)
            {
                int down = 1000000;
                int right = 1000000;

                /* Base Condition */
                if (!row && !col) continue;

                /* Move right or down */
                if (row > 0) down = dp[row-1][col];
                if (col > 0) right = dp[row][col-1];

                dp[row][col] = (grid[row][col] + std::min(down, right));
            }
        }

        return dp[numRows-1][numCols-1];
    }

    // TC: O(M*N) - where M is number of rows and N is number of columns. Each cell is visited at most once
    // SC: O(N) - vector
    int optimizedTabulationWorker(vector<vector<int>>& grid, const int numRows, const int numCols)
    {
        // Create a vector to represent the previous row of the grid.
        vector<int> prev(numCols, 0);

        for (int row = 0; row < numRows; row += 1)
        {
            vector<int> temp(numCols, 0);

            for (int col = 0; col < numCols; col += 1)
            {
                /* Base Condition - starting point */
                if (row == 0 && col == 0)
                {
                    temp[col] = grid[row][col];
                    continue;
                }

                const int right = (col-1 >= 0) ? temp[col-1] : 1000000;
                const int down = (row-1 >= 0) ? prev[col] : 1000000;

                temp[col] = grid[row][col] + std::min(right, down);
            }

            prev = temp;
        }

        return prev[numCols-1];
    }
public:
    int minPathSum(vector<vector<int>>& grid)
    {
        const int numRows = grid.size();
        const int numCols = grid[0].size();
        // vector<vector<int>> dp(numRows, vector<int>(numCols, -1));
        vector<vector<int>> dp(numRows, vector<int>(numCols, 1000000));

        // return recursiveWorker(grid, numRows-1, numCols-1);
        // return memoizationWorker(grid, dp, numRows-1, numCols-1);
        // return tabulationWorker(grid, dp, numRows, numCols);
        return optimizedTabulationWorker(grid, numRows, numCols);
    }
};