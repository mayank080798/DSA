## How to Identify a DP on Grids Problem

Ask yourself these questions:

✅ 1. Is the problem based on a 2D grid or matrix?

Input is usually a 2D grid (m x n). Each cell may contain values like cost, number of paths, obstacles, letters, etc.

✅ 2. Are you required to move through the grid with constraints?

You can typically move in limited directions:
1. Right or Down
2. All 4 directions (up, down, left, right)
3. Sometimes diagonally

✅ 3. Does the problem ask for...

1. Count of paths?
2. Minimum or maximum value on a path?
3. Checking existence of a path or pattern?
4. Number of ways to reach a cell or configuration?

✅ 4. Do subproblems overlap?

If you can reuse solutions to smaller subproblems (e.g., the best path to a cell can use the best paths to its neighbors), it's a strong sign for DP.

## Common DP on Grid Patterns

| Pattern                         | Description                                         | Example Problem                          |
| ------------------------------- | --------------------------------------------------- | ---------------------------------------- |
| **Unique Paths**                | Count ways to reach bottom-right from top-left      | Leetcode 62                              |
| **Min/Max Path Sum**            | Find min/max total cost along a path                | Leetcode 64, 120                         |
| **Obstacle Grid**               | Grid has blocked cells; skip them in path counting  | Leetcode 63                              |
| **Word Search / DFS + DP**      | Check if a word exists in grid by forming sequences | Leetcode 79                              |
| **Longest Increasing Path**     | Move through increasing numbers in grid             | Leetcode 329                             |
| **Memoized Recursion in Grid**  | Often DFS with caching on a grid                    | Island problems, Word search variations  |
| **DP with States**              | Store extra state like direction, cost, or steps    | Robot movement with energy, knight paths |
| **Counting Islands / DFS + DP** | Count separate connected regions in a binary matrix | Leetcode 200                             |

## 🧰 General Template for DP on Grid

#### ✅ 1. Bottom-Up Tabulation (Iterative)

```
function solveDP(grid):
    m = number of rows in grid
    n = number of columns in grid

    # Initialize DP table
    dp = matrix of size (m x n) filled with 0 or INF depending on problem

    # Base case
    dp[0][0] = grid[0][0]  # or 1 if it's path counting

    # Fill first row
    for j from 1 to n-1:
        dp[0][j] = transition(dp[0][j-1], grid[0][j])

    # Fill first column
    for i from 1 to m-1:
        dp[i][0] = transition(dp[i-1][0], grid[i][0])

    # Fill the rest of the DP table
    for i from 1 to m-1:
        for j from 1 to n-1:
            dp[i][j] = transition(dp[i-1][j], dp[i][j-1], grid[i][j])
    
    return dp[m-1][n-1]  # or any target cell

```
**Replace transition() with your logic like min(...) + grid[i][j], dp[i-1][j] + dp[i][j-1], etc.**

#### ✅ 2. Top-Down DP with Memoization (Recursive)

```

function solve(i, j, grid, memo):
    # Base cases
    if i < 0 or j < 0:
        return INF or 0  # depending on problem (invalid path)
    
    if i == 0 and j == 0:
        return grid[0][0]  # or 1 if it's count of paths

    if memo[i][j] is not None:
        return memo[i][j]

    # Recurrence relation
    fromTop = solve(i-1, j, grid, memo)
    fromLeft = solve(i, j-1, grid, memo)

    # Transition
    memo[i][j] = transition(fromTop, fromLeft, grid[i][j])

    return memo[i][j]


function solveDP(grid):
    m = number of rows
    n = number of cols
    memo = matrix of size (m x n) filled with None

    return solve(m-1, n-1, grid, memo)

```

🧠 Replace transition() Based on Problem Type

| Problem Type              | Transition Function Example                        |
| ------------------------- | -------------------------------------------------- |
| Min Path Sum              | `min(top, left) + grid[i][j]`                      |
| Max Path Sum              | `max(top, left) + grid[i][j]`                      |
| Count Paths               | `top + left`                                       |
| Unique Paths w/ Obstacles | `if obstacle: 0 else: top + left`                  |
| DFS Grid w/ Conditions    | use `max()` over all 4 directions with memoization |
