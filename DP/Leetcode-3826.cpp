/*
3826. Minimum Partition Score
You are given an integer array nums and an integer k.

Your task is to partition nums into exactly k subarrays and return an integer denoting the minimum possible score among all valid partitions.

The score of a partition is the sum of the values of all its subarrays.

The value of a subarray is defined as sumArr * (sumArr + 1) / 2, where sumArr is the sum of its elements.

Example 1:
Input: nums = [5,1,2,1], k = 2
Output: 25
Explanation:
We must partition the array into k = 2 subarrays. One optimal partition is [5] and [1, 2, 1].
The first subarray has sumArr = 5 and value = 5 × 6 / 2 = 15.
The second subarray has sumArr = 1 + 2 + 1 = 4 and value = 4 × 5 / 2 = 10.
The score of this partition is 15 + 10 = 25, which is the minimum possible score.
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int n; // number of elements in the array 
    vector<vector<long long>>dp;// dp[i][j] = min cost to partition the array from index i to n-1 into j subarrays
    vector<long long >pref;// stores the prefix sum of the array
    long long INF = 1e18 ;
    long long dfs(int idx,int k)
    {
        if(idx == n && k==0) return 0; // if we have not to partition the whole array then the cost is 0
        if(idx == n || k==0) return INF; // if the partition is completed and the elements are remaining in the array , then it is impossible to partition the array into k subarrays

        if(dp[idx][k] !=-1) return dp[idx][k]; // if precalculated then the return the value
        long long ans = INF;
        for(int i = idx ;i <=n-k ; i++) // try for all the index from idx to n-k
        {
            long long curr = pref[i+1]-pref[idx];
            long long cost = curr * (curr+1)/2; // calculate the cost of the current partition
            if(cost >= ans) break ; // if the cost is greater than the previous minimum cost then break the loop
            ans = min(ans, cost+dfs(i+1,k-1));
        }
        return dp[idx][k]= ans;
    }
    long long minPartitionScore(vector<int>& nums, int k) {
       n = nums.size();
       pref.assign(n+1,0);
       for(int i=1;i<=n;i++)
       {
          pref[i] = pref[i-1] + nums[i-1];
       }     

       dp.assign(n,vector<long long>(k+1,-1));
       return dfs(0,k);
    }
};