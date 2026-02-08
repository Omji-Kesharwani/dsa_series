/*
You are given two integer arrays nums1 and nums2 of lengths n and m respectively, and an integer k.

You must choose exactly k pairs of indices (i1, j1), (i2, j2), ..., (ik, jk) such that:

0 <= i1 < i2 < ... < ik < n
0 <= j1 < j2 < ... < jk < m
For each chosen pair (i, j), you gain a score of nums1[i] * nums2[j].

The total score is the sum of the products of all selected pairs.

Return an integer representing the maximum achievable total score.

 

Example 1:

Input: nums1 = [1,3,2], nums2 = [4,5,1], k = 2

Output: 22

Explanation:

One optimal choice of index pairs is:

(i1, j1) = (1, 0) which scores 3 * 4 = 12
(i2, j2) = (2, 1) which scores 2 * 5 = 10
This gives a total score of 12 + 10 = 22.
*/

/*
Approach :
This is a classic DP with ordering constraints problem.
dp[i][j][t] = maximum score using first i elements of nums1, first j elements of nums2, choosing exactly t pairs.

dp[i][j][t] = max(
    dp[i-1][j][t],                        // skip nums1[i-1]
    dp[i][j-1][t],                        // skip nums2[j-1]
    dp[i-1][j-1][t-1] + nums1[i-1]*nums2[j-1]  // take pair
)


Why we DON’T implement dp[i][j][t] directly
Problem with direct 3D DP
Constraints can go up to n, m = 200
k up to min(n, m)
Memory would be:
200 × 200 × 200 = 8,000,000 states
Each state is long long → ~64 MB, borderline or TLE/MLE.


dp[t][j] =
maximum score using:
- current nums1 prefix (up to current i)
- first j elements of nums2
- exactly t pairs

This is equivalent to dp[i][j][t] .
Mapping :
Conceptual	               Code
dp[i][j][t]	           newdp[t][j]
dp[i-1][j][t]	           dp[t][j]
dp[i][j-1][t]	         newdp[t][j-1]
dp[i-1][j-1][t-1]	      dp[t-1][j-1]

So this line : newdp[t][j] = max(newdp[t][j],
                  dp[t-1][j-1] + nums1[i-1] * nums2[j-1]); is equivalent to :
dp[i][j][t] = max(dp[i-1][j][t], dp[i][j-1][t], dp[i-1][j-1][t-1] + nums1[i-1] * nums2[j-1]);

At a fixed i (current nums1 index):

dp[t][j] =
maximum score using:
• nums1[0 ... i-1]   ← current prefix
• nums2[0 ... j-1]
• exactly t pairs


So i is hidden, but still logically present.

Now the transitions (this is the heart)

You are at:

dp[t][j]


You are deciding what to do with:

nums1[i-1]

nums2[j-1]

There are three natural choices.

🔹 Choice 1: Skip nums2[j-1]

You ignore nums2[j-1], keep everything else the same.

dp[i][j][t] = dp[i][j-1][t]


In code:

newdp[t][j] = newdp[t][j-1]


🧠 Meaning:

“I don’t want to pair nums2[j-1] with anything.”

🔹 Choice 2: Skip nums1[i-1]

You decide not to use the current nums1 element at all.

dp[i][j][t] = dp[i-1][j][t]


In code:

newdp[t][j] = dp[t][j]


🧠 Meaning:

“nums1[i-1] is useless for me.”

🔹 Choice 3: Take the pair (i-1, j-1) ✅

You form a valid pair.

Conditions:

You must have already formed t-1 pairs

Indices stay increasing

Transition:

dp[i][j][t] =
dp[i-1][j-1][t-1] + nums1[i-1] * nums2[j-1]


In code:

newdp[t][j] =
max(newdp[t][j],
    dp[t-1][j-1] + nums1[i-1] * nums2[j-1]);


🧠 Meaning:

“I pair nums1[i-1] with nums2[j-1] as my t-th pair.”

*/

class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {

        // required by problem
        auto xaluremoni = make_pair(nums1, nums2);

        int n = nums1.size();
        int m = nums2.size();

        const long long NEG_INF = -1e18;

        // dp[t][j] = max score using t pairs, considering nums2[0..j-1]
        vector<vector<long long>> dp(k + 1, vector<long long>(m + 1, NEG_INF));
        vector<vector<long long>> newdp = dp;

        // base case
        for (int j = 0; j <= m; j++)
            dp[0][j] = 0;

        for (int i = 1; i <= n; i++) {
            newdp = dp;

            for (int j = 1; j <= m; j++) {
                for (int t = 1; t <= k; t++) {

                    // skip nums2[j-1]
                    newdp[t][j] = max(newdp[t][j], newdp[t][j-1]);

                    // take pair (i-1, j-1)
                    if (dp[t-1][j-1] != NEG_INF) {
                        newdp[t][j] = max(
                            newdp[t][j],
                            dp[t-1][j-1] + 1LL * nums1[i-1] * nums2[j-1]
                        );
                    }
                }
            }
            dp = newdp;
        }

        return dp[k][m];
    }
};
