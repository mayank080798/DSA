/**
 * Question: 63. Unique Paths II
 * Link: https://leetcode.com/problems/unique-paths-ii/description/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
private:
    // TC: O(2^(N*M)) - where N is numRows and M is numCols
    // SC: O(Path Length) ~ O(M+N) - for traversing one complete row and one complete column
    int recursiveWorker(vector<vector<int>>& obstacleGrid, const int row, const int col)
    {
        /* Base Condition - Negative */
        if (row < 0 || col < 0 || obstacleGrid[row][col]) return 0;

        /* Base Condition - Positive */
        if (!row && !col) return 1;

        return recursiveWorker(obstacleGrid, row-1, col) + recursiveWorker(obstacleGrid, row, col-1);
    }

    // TC: O(N*M) - where N is numRows and M is numCols
    // SC: O(Path Length) ~ O(M+N) + O(M*N) - for traversing one complete row and one complete column
    int memoizationWorker(vector<vector<int>>& obstacleGrid, vector<vector<int>>& dp, const int row, const int col)
    {
        /* Base Condition - Negative */
        if (row < 0 || col < 0 || obstacleGrid[row][col]) return 0;

        /* Base Condition - Positive */
        if (!row && !col) return 1;

        /* Base Condition - Cell already memoized */
        if (dp[row][col] != - 1) return dp[row][col];

        return dp[row][col] = memoizationWorker(obstacleGrid, dp, row-1, col) + memoizationWorker(obstacleGrid, dp, row, col-1);
    }

    // TC: O(N*M) - where N is numRows and M is numCols
    // SC: O(M*N) - for dp vector
    int tabulationWorker(vector<vector<int>>& obstacleGrid, vector<vector<int>>& dp, const int numRows, const int numCols)
    {
        /* Fill base condition in dp table */
        if (!obstacleGrid[0][0]) dp[0][0] = 1;

        /* Construct dp table following bottom-up approach */
        for (int row = 0; row < numRows; row += 1)
        {
            for (int col = 0; col < numCols; col += 1)
            {
                int right = 0;
                int bottom = 0;

                /* Base Condition */
                if (!row && !col) continue;

                /* Base Condition - Obstacle */
                if (obstacleGrid[row][col]) continue;

                /* Robot moves either right or down */
                if (row > 0) bottom = dp[row-1][col];
                if (col > 0) right = dp[row][col-1];

                dp[row][col] = right + bottom;
            }
        }

        return dp[numRows-1][numCols-1];
    }

    // TC: O(N*M) - where N is numRows and M is numCols
    // SC: O(1) - constant space
    int optimizedTabulationWorker(vector<vector<int>>& obstacleGrid, const int numRows, const int numCols)
    {
        vector<int> prev(numCols, 0);

        /* Construct dp table following bottom-up approach */
        for (int row = 0; row < numRows; row += 1)
        {
            vector<int> curr(numCols, 0);

            for (int col = 0; col < numCols; col += 1)
            {
                int right = 0;
                int bottom = 0;

                /* Base Condition */
                if (!row && !col)
                {
                    curr[col] = 1;
                    continue;
                }

                /* Base Condition - Obstacle */
                if (obstacleGrid[row][col])
                {
                    curr[col] = 0;
                    continue;
                }

                /* Robot moves either right or down */
                if (row > 0) bottom = prev[col];
                if (col > 0) right = curr[col-1];

                curr[col] = right + bottom;
            }

            prev = curr;
        }

        return prev[numCols-1];
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
    {
        const int numRows = obstacleGrid.size();
        const int numCols = obstacleGrid[0].size();
        // vector<vector<int>> dp(numRows, vector<int>(numCols, -1));
        vector<vector<int>> dp(numRows, vector<int>(numCols, 0));

        /* Base Condition - Single cell */
        if (obstacleGrid[0][0])
            return 0;

        // return recursiveWorker(obstacleGrid, numRows-1, numCols-1);
        // return memoizationWorker(obstacleGrid, dp, numRows-1, numCols-1);
        // return tabulationWorker(obstacleGrid, dp, numRows, numCols);
        return optimizedTabulationWorker(obstacleGrid, numRows, numCols);
    }
};