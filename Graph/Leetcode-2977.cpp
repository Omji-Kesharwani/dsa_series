/*
2977. Minimum Cost to Convert String II

You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English characters. You are also given two 0-indexed string arrays original and changed, and an integer array cost, where cost[i] represents the cost of converting the string original[i] to the string changed[i].
You start with the string source. In one operation, you can pick a substring x from the string, and change it to y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y. You are allowed to do any number of operations, but any pair of operations must satisfy either of these two conditions:
The substrings picked in the operations are source[a..b] and source[c..d] with either b < c or d < a. In other words, the indices picked in both operations are disjoint.
The substrings picked in the operations are source[a..b] and source[c..d] with a == c and b == d. In other words, the indices picked in both operations are identical.
Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
Example 1:
Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
Output: 28
Explanation: To convert "abcd" to "acbe", do the following operations:
- Change substring source[1..1] from "b" to "c" at a cost of 5.
- Change substring source[2..2] from "c" to "e" at a cost of 1.
- Change substring source[2..2] from "e" to "b" at a cost of 2.
- Change substring source[3..3] from "d" to "e" at a cost of 20.
The total cost incurred is 5 + 1 + 2 + 20 = 28. 
It can be shown that this is the minimum possible cost.
*/

/*
APPROACH:
Key Observation 1
Think of each substring given in original and changed as a node. Each replacement rule is a directed edge from original to changed with the edge weight being cost

Example:
"ab" → "cd" (5)
"cd" → "ef" (2)
Even though "ab" → "ef" is not given, it is possible via:

"ab" → "cd" → "ef" (total cost = 7)

In above "ab", "cd" and "ef" are indivdual nodes.

ab -> cd connection with weight 5
cd -> ef connection with weight 2

Using above graph we can get ab->ef distance which will be 7
This is ALL PAIRS SHORTEST PATH PROBLEM - solvable by Flyod Warshall Algo.

After running Flyod Warshall this is what we get

dist[u][v] = minimum cost to convert substring u → substring v

Here each substring we are labelling it with a unique ID.
Unique ID is given with counter variable starting from 0 and incrementing each time once labelling is performed.

Example "ab" -> 1, "cd" -> 2, "ef" -> 3.

Now our earlier map of

"ab" -> "cd" with weight 5
"cd" -> "ef" with weight 2
Has changed to

1->2 with weight 5
2->3 with weight 2
So earlier dist["ab"]["ef"] is now dist[1][3] which is easier to store and calculate

Key Observation 2
Now when converting Source to Target, for each character we have 2 cases

If the character in source and target match, we should continue without any changes
source[i] == target[i] then continue to i+1

If source[i] is not equal to target[i], then we should try a substring replacement with starts from i.
So we should look at below 3 conditions satisfaction for different len
1. source[i..i+len-1] == original_substring
2. target[i..i+len-1] == changed_substring
3. A valid conversion cost exists (from Floyd–Warshall)
Among all the possibilities of substring which satisfy above condition, we should choose the one which gives us the minimum cost.

But we cannot know beforehand which one will give us the minimum cost.
So we need to perform each choice and get the answer and finally store the minimum of all such choices

Does this structure ring a bell ? Yes it's classic DP -> Perform all choices computation and get minimum/maximum of answer obtained from each choice

Recursive and DP state
Recursive State
solve(i) = minimum cost to convert source[i ... end] → target[i ... end]

Meaning:

We have already correctly converted everything before index i
Now we want the cheapest way to finish the rest
Base Case:

If i == n:
    return 0
Meaning

We’ve successfully converted the entire string
No more cost needed return 0
Recursive Transitions

At each index i, we have two choices

1. Characters already match
If source[i] == target[i] then solve(i) → solve(i + 1)

Why?

No replacement needed
Cheapest option is to just move forward
This handles cases where replacement is unnecessary.
2. Apply substring replacement
At index i, we try every substring replacement that:

Matches the source at position i
Matches the target at position i
Has a valid conversion cost
How to do that?

We iterate over all known substrings (mapped earlier):

Step 1: Match source substring
source[i ... i+len-1] == s1

Step 2: Match target substring
target[i ... i+len-1] == s2

Step 3: Ensure conversion exists
dist[s1][s2] != INF

If all are valid:
solve(i) → dist[s1][s2] + solve(i + len)

For each of the two steps, we always maintain a minmum answer which is returned at the end of the recursion.

Since the only state changing here is i which is the index, our DP state is i itself.

We can store dp[i]=ans before returning and checking if dp[i] exists below the base conditions to apply memoization

Complexity
Time complexity:
Flyod - O(K x K x K)
DP - O(N x N x K)

Space complexity:
O ( K x K)
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    const long long INF = 1e18;

    unordered_map<string, int> mp;
    vector<vector<long long>> dist;
    string src, tgt;
    int n;
    vector<long long> dp;

    long long solve(int i) {
        if (i == n) return 0;
        if (dp[i] != -1) return dp[i];

        long long ans = INF; //make ans INF so that when done min later it reduces

        // Option 1: characters already match
        if (src[i] == tgt[i]) {
            ans = min(ans, solve(i + 1));
        }

        // Option 2: try all substring replacements

        
        for (auto &p1 : mp) {

            //check for valid source substring s1
            const string &s1 = p1.first;
            int u = p1.second;
            int len = s1.size();

            if (i + len > n) continue;
            if (src.compare(i, len, s1) != 0) continue;

            for (auto &p2 : mp) {
                //find a valid target substring s2
                const string &s2 = p2.first;
                int v = p2.second;

                if (tgt.compare(i, len, s2) != 0) continue;
                if (dist[u][v] == INF) continue;

                ans = min(ans, dist[u][v]+solve(i + len));
            }
        }

        return dp[i] = ans;
    }

    long long minimumCost(string source,string target,vector<string>& original,vector<string>& changed,
        vector<int>& cost
    ) {
        src = source;
        tgt = target;
        n = source.size();

        //Map all unique strings and for each string -> Link it with a unique ID 
        int cnt = 0;
        for (int i = 0; i < original.size(); i++) {
            if (!mp.count(original[i])) mp[original[i]] = cnt++;
            if (!mp.count(changed[i]))  mp[changed[i]]  = cnt++;
        }

        // Build distance matrix cnt*cnt
        dist.assign(cnt, vector<long long>(cnt, INF));

        for (int i = 0; i < cnt; i++) dist[i][i] = 0;

        for (int i = 0; i < original.size(); i++) {
            int u = mp[original[i]];
            int v = mp[changed[i]];
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        // Floyd–Warshall
        for (int k = 0; k < cnt; k++)
            for (int i = 0; i < cnt; i++)
                for (int j = 0; j < cnt; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        // Memoized DFS
        dp.assign(n, -1);
        long long ans = solve(0);

        if(ans>=INF) return -1;

        return ans;
    }
};