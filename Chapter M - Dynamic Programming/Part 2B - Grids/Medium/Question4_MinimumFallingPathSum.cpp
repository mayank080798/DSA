/**
 * Question: 931. Minimum Falling Path Sum
 * Link: https://leetcode.com/problems/minimum-falling-path-sum/description/
 */

#include <iostream>
#include <vector>

using namespace std;

#define ITERATIVE_APPROACH

class Solution
{
private:
    int numRows = 0;
    int numCols = 0;

    // TC: O(3^(M*N))  - where M is number of rows and N is number of columns
    // SC: O(M+N) - recursion stack space
    int recursiveWorker(vector<vector<int>>& matrix, const int row, const int col)
    {
        /* Base Condition - Invalid row or column */
        if (row >= numRows || col < 0 || col >= numCols)
            return INT_MAX;

        /* Base Condition - Reached last row */
        if (row == numRows-1)
            return matrix[row][col];

        const int path1 = recursiveWorker(matrix, row+1, col-1);
        const int path2 = recursiveWorker(matrix, row+1, col);
        const int path3 = recursiveWorker(matrix, row+1, col+1);

        return matrix[row][col] + std::min(path1, std::min(path2, path3));
    }

    // TC: O(M*N)  - where M is number of rows and N is number of columns. Each cell is visited at most once
    // SC: O(M+N) - recursion stack space
    int memoizationWorker(vector<vector<int>>& matrix, vector<vector<int>>& dp, const int row, const int col)
    {
        /* Base Condition - Invalid row or column */
        if (row >= numRows || col < 0 || col >= numCols)
            return INT_MAX;

        /* Base Condition - Reached last row */
        if (row == numRows-1)
            return matrix[row][col];

        /* Cell already memoized */
        if (dp[row][col] != -1)
            return dp[row][col];

        const int path1 = memoizationWorker(matrix, dp, row+1, col-1);
        const int path2 = memoizationWorker(matrix, dp, row+1, col);
        const int path3 = memoizationWorker(matrix, dp, row+1, col+1);

        return dp[row][col] = (matrix[row][col] + std::min(path1, std::min(path2, path3)));
    }

    // TC: O(M*N) - where M is number of rows and N is number of columns. Each cell is visited at most once
    // SC: O(M*N) - 2D vector
    void tabulationWorker(vector<vector<int>>& matrix, vector<vector<int>>& dp)
    {
        /* Copy last row of grid to dp 2D vector */
        for (int col = 0; col < numCols; col += 1)
        {
            dp[numRows-1][col] = matrix[numRows-1][col];
        }

        /* Check for minimum path moving to next row's col-1 or col or col+1 */
        for (int row = numRows-2; row >= 0; row -= 1)
        {
            for (int col = 0; col < numCols; col += 1)
            {
                const int path1 = dp[row+1][col];
                const int path2 = col - 1 >= 0 ? dp[row+1][col-1] : INT_MAX;
                const int path3 = col + 1 < numCols ? dp[row+1][col+1] : INT_MAX;

                dp[row][col] = (matrix[row][col] + std::min(path1, std::min(path2, path3)));
            }
        }
    }

    // TC: O(M*N) - where M is number of rows and N is number of columns. Each cell is visited at most once
    // SC: O(2N) - vector
    void optimizedTabulationWorker(vector<vector<int>>& matrix, vector<int>& curr, vector<int>& next)
    {
        /* Copy last row of grid to dp 2D vector */
        for (int col = 0; col < numCols; col += 1)
        {
            next[col] = matrix[numRows-1][col];
        }

        /* Check for minimum path moving to next row's col-1 or col or col+1 */
        for (int row = numRows-2; row >= 0; row -= 1)
        {
            for (int col = 0; col < numCols; col += 1)
            {
                const int path1 = next[col];
                const int path2 = col - 1 >= 0 ? next[col-1] : INT_MAX;
                const int path3 = col + 1 < numCols ? next[col+1] : INT_MAX;

                curr[col] = (matrix[row][col] + std::min(path1, std::min(path2, path3)));
            }

            next = curr;
        }
    }
public:
    int minFallingPathSum(vector<vector<int>>& matrix)
    {
        numRows = matrix.size();
        numCols = matrix.size();

        int minPathSum = INT_MAX;
        vector<int> next(numRows, 0);
        vector<int> curr(numRows, 0);
        vector<vector<int>> dp(numRows, vector<int>(numRows, -1));

#ifdef RECURSIVE_APPROACH
        /* Compute minimum path sum starting from each cell of first row */
        for (int col = 0; col < numCols; col += 1)
        {
            // minPathSum = std::min(minPathSum, recursiveWorker(matrix, 0, col));
            // minPathSum = std::min(minPathSum, memoizationWorker(matrix, dp, 0, col));
        }
#endif

#ifdef ITERATIVE_APPROACH
        // tabulationWorker(matrix, dp);
        optimizedTabulationWorker(matrix, curr, next);

        for (int col = 0; col < numCols; col += 1)
        {
            minPathSum = std::min(minPathSum, next[col]);
        }
#endif

        return minPathSum;
    }
};