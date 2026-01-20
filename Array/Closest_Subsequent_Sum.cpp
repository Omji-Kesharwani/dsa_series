/*
1755. Closest Subsequence Sum
You are given an integer array nums and an integer goal.

You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).

Return the minimum possible value of abs(sum - goal).

Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.

Example 1:
Input: nums = [5,-7,3,5], goal = 6
Output: 0
Explanation: Choose the whole array as a subsequence, with a sum of 6.
This is equal to the goal, so the absolute difference is 0.
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int n1 = n / 2;
        int n2 = n - n1;

        vector<int> left, right;

        // Subset sums of left half
        for (int mask = 0; mask < (1 << n1); mask++) {
            int sum = 0;
            for (int i = 0; i < n1; i++) {
                if (mask & (1 << i))
                    sum += nums[i];
            }
            left.push_back(sum);
        }

        // Subset sums of right half
        for (int mask = 0; mask < (1 << n2); mask++) {
            int sum = 0;
            for (int i = 0; i < n2; i++) {
                if (mask & (1 << i))
                    sum += nums[i + n1];
            }
            right.push_back(sum);
        }

        sort(right.begin(), right.end());

        int ans = INT_MAX;

        for (int x : left) {
            int need = goal - x;

            auto it = lower_bound(right.begin(), right.end(), need);

            if (it != right.end())
                ans = min(ans, abs(goal - (x + *it)));

            if (it != right.begin()) {
                --it;
                ans = min(ans, abs(goal - (x + *it)));
            }
        }

        return ans;
    }
};


