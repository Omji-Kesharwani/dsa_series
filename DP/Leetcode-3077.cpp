/*
You are given an array of integers nums with length n, and a positive odd integer k.

Select exactly k disjoint subarrays sub1, sub2, ..., subk from nums such that the last element of subi appears before the first element of sub{i+1} for all 1 <= i <= k-1. The goal is to maximize their combined strength.

The strength of the selected subarrays is defined as:

strength = k * sum(sub1)- (k - 1) * sum(sub2) + (k - 2) * sum(sub3) - ... - 2 * sum(sub{k-1}) + sum(subk)

where sum(subi) is the sum of the elements in the i-th subarray.

Return the maximum possible strength that can be obtained from selecting exactly k disjoint subarrays from nums.

Note that the chosen subarrays don't need to cover the entire array.

 

Example 1:

Input: nums = [1,2,3,-1,2], k = 3

Output: 22

Explanation:

The best possible way to select 3 subarrays is: nums[0..2], nums[3..3], and nums[4..4]. The strength is calculated as follows:

strength = 3 * (1 + 2 + 3) - 2 * (-1) + 2 = 22

 

Example 2:

Input: nums = [12,-2,-2,-2,-2], k = 5

Output: 64

Explanation:

The only possible way to select 5 disjoint subarrays is: nums[0..0], nums[1..1], nums[2..2], nums[3..3], and nums[4..4]. The strength is calculated as follows:

strength = 5 * 12 - 4 * (-2) + 3 * (-2) - 2 * (-2) + (-2) = 64

Example 3:

Input: nums = [-1,-2,-3], k = 1

Output: -1

Explanation:

The best possible way to select 1 subarray is: nums[0..0]. The strength is -1.
*/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
// dp[i][k][started] = max strength we can get from index i to n-1 with k subarrays and started = true if we have started a subarray and stored atleat one element 
    vector<vector<vector<long long>>> dp; 
    long long solve(int i , long long k , bool started , vector<int>& nums)
    {
        if(k==0) return 0; // checking if no more subarrays are required 
        if(i==nums.size()) // checking if we have reached the end of the array 
        {
          // if we have to count only one subarray and have counted atleast one element then return 0 else return -1e15
            if(k == 1 && started) return 0 ;
            return -1e15;
        }
        if(dp[i][k][started] != -1e16 ) return dp[i][k][started];
        long long ans = -1e15;
        // if we have atleast one element in the current subarray and then we can end this subarray 
        if(started)
        {
            ans = solve(i,k-1,false,nums);
        }
        // count this element in the current subarray and continue to the next element
        ans = max((k % 2 == 0 ? -1 : 1)*k*nums[i] + solve(i+1,k,true,nums),ans);
        // if we have not started the subarray and then we can skip this element and continue to the next element 
        if(!started )
        ans = max(solve(i+1,k,false,nums),ans);
        return dp[i][k][started] = ans; 
    }
    long long maximumStrength(vector<int>& nums, int k) {
        dp = vector<vector<vector<long long>>>(nums.size(),vector<vector<long long>>(k+1,vector<long long>(2,-1e16)));
        long long ans = -1e15 ;
        // initially start from the 0th index and started = false
        return solve(0,(long long)k,false,nums);
    }
};