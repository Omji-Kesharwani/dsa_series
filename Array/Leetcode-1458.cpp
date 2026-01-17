/*
Given two arrays nums1 and nums2.

Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.

A subsequence of a array is a new array which is formed from the original array by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).

 

Example 1:

Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
Output: 18
Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
Their dot product is (2*3 + (-2)*(-6)) = 18.

*/

/*
PURE RECURSION (No DP)
Idea
At every index (i, j) you have three choices:

Take nums1[i] and nums2[j]
Skip nums1[i]
Skip nums2[j]
We try all possibilities and return the maximum dot product.

Recursive Definition
solve(i, j) = maximum dot product
              using nums1[i:] and nums2[j:]
Base Case
If either array ends:

return -infinity
Why?
Because subsequence must be non-empty.

Recursive Formula
take = nums1[i] * nums2[j] + max(0, solve(i+1, j+1))
skip1 = solve(i+1, j)
skip2 = solve(i, j+1)

return max(take, skip1, skip2)
*/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int n, m;
    vector<int> a, b;

    int solve(int i, int j) {
        if (i == n || j == m)
            return INT_MIN;

        int take = a[i] * b[j];
        int next = solve(i + 1, j + 1);
        if (next > 0)
            take += next;

        int skip1 = solve(i + 1, j);
        int skip2 = solve(i, j + 1);

        return max({take, skip1, skip2});
    }

    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        a = nums1;
        b = nums2;
        n = a.size();
        m = b.size();

        return solve(0, 0);
    }
};

/*
2️⃣ RECURSION + MEMOIZATION (Top-Down DP)
Now we optimize pure recursion by storing already computed results.

What changes?
We add a DP table
Before solving (i, j), we check if it is already solved
Each state (i, j) is computed only once
DP Meaning
dp[i][j] = maximum dot product
           using nums1[i:] and nums2[j:]
*/

class Solution {
public:
    int n, m;
    vector<int> a, b;
    vector<vector<int>> dp;
    vector<vector<bool>> vis;

    int solve(int i, int j) {
        if (i == n || j == m)
            return INT_MIN;

        if (vis[i][j])
            return dp[i][j];

        vis[i][j] = true;

        int take = a[i] * b[j];
        int next = solve(i + 1, j + 1);
        if (next > 0)
            take += next;

        int skip1 = solve(i + 1, j);
        int skip2 = solve(i, j + 1);

        return dp[i][j] = max({take, skip1, skip2});
    }

    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        a = nums1;
        b = nums2;
        n = a.size();
        m = b.size();

        dp.assign(n, vector<int>(m, 0));
        vis.assign(n, vector<bool>(m, false));

        return solve(0, 0);
    }
};

/*
3️⃣ TABULATION (Bottom-Up DP)
Now we remove recursion completely and build the solution iteratively.

Key Idea
Instead of solving from (0,0) using recursion, we compute answers for smaller suffixes first and build up to (0,0).

DP Definition (same meaning)
dp[i][j] = maximum dot product
           using nums1[i:] and nums2[j:]
Base Initialization
When either array is exhausted, answer must be invalid (non-empty subsequence required):

dp[n][*] = dp[*][m] = -infinity
So we create a (n+1) × (m+1) DP table.

Transition (same logic as recursion)
For every (i, j) from bottom-right to top-left:

take  = nums1[i] * nums2[j] + max(0, dp[i+1][j+1])
skip1 = dp[i+1][j]
skip2 = dp[i][j+1]

dp[i][j] = max(take, skip1, skip2)
*/

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MIN));

        // Fill table bottom-up
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int take = nums1[i] * nums2[j];
                if (dp[i + 1][j + 1] > 0)
                    take += dp[i + 1][j + 1];

                int skip1 = dp[i + 1][j];
                int skip2 = dp[i][j + 1];

                dp[i][j] = max({take, skip1, skip2});
            }
        }

        return dp[0][0];
    }
};

/*

4️⃣ SPACE OPTIMIZED DP
In tabulation we used a full n × m table.
But notice the transition:

dp[i][j] depends only on:
dp[i+1][j]
dp[i][j+1]
dp[i+1][j+1]
So we only need two rows at a time.

Idea
nextRow → represents dp[i+1][*]
currRow → represents dp[i][*]
We compute row by row from bottom to top.

Initialization
Both rows initialized with INT_MIN
This maintains the non-empty subsequence condition
Transition (same logic)
take  = nums1[i] * nums2[j] + max(0, nextRow[j+1])
skip1 = nextRow[j]
skip2 = currRow[j+1]

currRow[j] = max(take, skip1, skip2)
*/

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();

        vector<int> nextRow(m + 1, INT_MIN);
        vector<int> currRow(m + 1, INT_MIN);

        for (int i = n - 1; i >= 0; i--) {
            // reset current row
            fill(currRow.begin(), currRow.end(), INT_MIN);

            for (int j = m - 1; j >= 0; j--) {
                int take = nums1[i] * nums2[j];
                if (nextRow[j + 1] > 0)
                    take += nextRow[j + 1];

                int skip1 = nextRow[j];
                int skip2 = currRow[j + 1];

                currRow[j] = max({take, skip1, skip2});
            }

            nextRow = currRow;
        }

        return nextRow[0];
    }
};

/*
4 Single-Row DP
We want maximum dot product of two subsequences:

Let dp[j] store the maximum dot product using the first i elements of nums1 and first j elements of nums2.

Each cell depends on three possibilities:

Take both nums1[i-1] and nums2[j-1] → add to previous diagonal
Skip nums1[i-1] → take value from dp[j] (same column)
Skip nums2[j-1] → take value from dp[j-1] (left column)
We also consider taking the pair alone in case all previous products are negative (non-empty subsequence condition).

Transition
dp[j] = max(
    nums1[i-1] * nums2[j-1],            // take only this pair
    nums1[i-1] * nums2[j-1] + prev_diag,// take + extend previous diagonal subsequence
    dp[j],                               // skip nums1[i-1]
    dp[j-1]                              // skip nums2[j-1]
)
prev_diag remembers dp[i-1][j-1], the diagonal from the previous row.
We update dp[j] in-place, so we save space to O(m) instead of O(n×m).

*/

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        // Make nums2 the smaller array for efficiency
        if (m > n) return maxDotProduct(nums2, nums1);

        vector<int> dp(m + 1, -1e9); // 1D DP initialized to -infinity

        for (int i = 1; i <= n; ++i) {
            int prev_diag = -1e9; // Stores dp[j-1] from previous row
            for (int j = 1; j <= m; ++j) {
                int curr_product = nums1[i-1] * nums2[j-1];
                int temp = dp[j]; // Save current dp[j] before updating

                // Update dp[j] using the transition
                dp[j] = max({
                    curr_product,              // take this pair alone
                    curr_product + prev_diag,  // take pair + previous diagonal
                    dp[j],                     // skip nums1[i-1]
                    dp[j-1]                    // skip nums2[j-1]
                });

                prev_diag = temp; // Update diagonal for next iteration
            }
        }

        return dp[m];
    }
};