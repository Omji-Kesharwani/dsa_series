/*
 Trionic Array II
 You are given an integer array nums of length n.

A trionic subarray is a contiguous subarray nums[l...r] (with 0 <= l < r < n) for which there exist indices l < p < q < r such that:
nums[l...p] is strictly increasing,
nums[p...q] is strictly decreasing,
nums[q...r] is strictly increasing.
Return the maximum sum of any trionic subarray in nums.
Example 1:
Input: nums = [0,-2,-1,-3,0,2,-1]
Output: -4
Explanation:
Pick l = 1, p = 2, q = 3, r = 5:
nums[l...p] = nums[1...2] = [-2, -1] is strictly increasing (-2 < -1).
nums[p...q] = nums[2...3] = [-1, -3] is strictly decreasing (-1 > -3)
nums[q...r] = nums[3...5] = [-3, 0, 2] is strictly increasing (-3 < 0 < 2).
Sum = (-2) + (-1) + (-3) + 0 + 2 = -4.
*/
/*
APPROACH :
Step 1 - Decomposition
We will first decompose our array nums into strictly decreasing subarrays.
More specifically, we need to end up with k pairs (p1,q1),(p2,q2),...(pk,qk) where for any i≤k the subarray [pi,qi] is strictly decreasing, and furtheremore p1=0, qk=n−1 and for any i<k it will hold that qi+1=pi+1.
If you think about it visually, we would cut the nums in k−1 places, so we would end up with k subarrays next to each other, and each subarray would be strictly decreasing.

Of all the ways we can cut, we would choose the one that produces the fewest subarrays.

Note that there is one unique cutting - decomposition - for any given array nums.


Why is the decomposition unique?
Because the cut positions are forced.
At every index i, if nums[i−1]≤nums[i], the array cannot be strictly decreasing across that boundary, so a cut must occur there.
If nums[i−1]>nums[i], the condition still holds, so making a cut there would be unnecessary and would increase the number of subarrays.

Thus:

some positions must be cuts,
all other positions must not be cuts.
Since the goal is the minimum number of subarrays, every valid cut is forced, and no optional cuts exist.
Therefore, the decomposition is unique.

Implementation Details
Scan the array once from left to right.

Maintain the start l of the current subarray.
Whenever the strict condition breaks (nums[i−1]≤nums[i]), close the current subarray at i−1 and start a new subarray at i.
After the scan, close the final subarray.
This yields a partition into maximal contiguous strictly decreasing subarrays in O(n).

Before P and after Q
Having all of the decreasing subarrays, we would choose one of them, i.e., (p,q), and we would try to find the best [l,r], where l<p<q<r, which is a Trionic Subarray.
More specifically, we are interested in finding:

l such that l<p and the subarray [l,p] is strictly increasing, while the sum of the elements in [l,p−1] is as large as possible.
r such that q<r and the subarray [q,r] is strictly increasing, while the sum of the elements in [q+1,r] is as large as possible.
Both tasks are symmetrical, so we would focus only on the first one.

Variation of Kadane's Algorithm
If you haven't learned Kadane's Algorithm, now is a good time to spend a little time learning it, since the algorithm we are going to use is very similar to it.
We would introduce an array maxEndingAt where maxEndingAt[i] is the largest possible sum of a strictly increasing subarray ending at position i.

Note that by default, one element on its own is classified as an increasing subarray, so initially maxEndingAt[i]=nums[i] for any i.

Furthermore, if nums[i−1]<nums[i] we can take the best subarray ending at i−1 and right next to it attach the element i making an increasing subarray ending at i with sum:
maxEndingAt[i−1]+nums[i].

Putting all of this together, we get the following O(N) algorithm for calculating maxEndingAt.

Symetrically we get the array maxStartingAt where maxStartingAt[i] is the largest sum of a strictly increasing subarray starting on position i.
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<tuple<int,int,long long>> decompose(vector<int>& nums)
    {
        int n = (int)nums.size();
        vector<tuple<int,int,long long>>subarrays;
        int l = 0;
        long long sum = nums[0];
        for(int i = 1; i<n;i++)
        {
            if(nums[i-1] <= nums[i])
            {
                subarrays.push_back({l,i-1,sum});
                l = i ;
                sum = 0 ;
            }
            sum += nums[i];
        }

        subarrays.push_back({l,n-1,sum});
        return subarrays ;
    }
    long long maxSumTrionic(vector<int>& nums) {
        int n = (int)nums.size();
        long long maxEndingAt[n];
        for(int i = 0;i<n;i++)
        {
            maxEndingAt[i] = nums[i];
            if(i > 0 && nums[i-1] < nums[i])
            {
                if(maxEndingAt[i-1] > 0 )
                {
                    maxEndingAt[i] += maxEndingAt[i-1] ;
                }
            }
        }

        long long maxStartingAt[n];
        for(int i = n-1 ;i >= 0 ;i--)
        {
            maxStartingAt[i] = nums[i] ;
            if(i < n-1 && nums[i] < nums[i+1])
            {
                if(maxStartingAt[i+1] > 0)
                {
                    maxStartingAt[i] += maxStartingAt[i+1];
                }
            }
        }

        vector<tuple<int,int,long long>> PQS = decompose(nums);
        long long ans = LLONG_MIN;
        for(auto [p,q,sum]:PQS)
        {
            if(p>0 && nums[p-1] < nums[p] && q<n-1 && nums[q] < nums[q+1] && p<q)
            {
                ans = max(ans , maxEndingAt[p-1] + sum + maxStartingAt[q+1]);
            }
        }

        return ans ;
    }
};