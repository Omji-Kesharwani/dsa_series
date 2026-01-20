/*
2035. Partition Array Into Two Arrays to Minimize Sum Difference

You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.

Return the minimum possible absolute difference.
*/

// Input: nums = [3,9,7,3]
// Output: 2
// Explanation: One optimal partition is: [3,9] and [7,3].
// The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.


/*
APPROACH : Meet in the middle
Step 1: What are we minimizing?
        We want to split the array into two equal-sized parts such that:
        difference = | sum1 - sum2 |

Step 2: Use total sum
        Let: totalSum = sum1 + sum2
        So: sum2 = totalSum - sum1
        Substitute:
        difference = | sum1 - (totalSum - sum1) |
                   = | 2 * sum1 - totalSum |
        The expression 2 * sum1 - totalSum = 0 when sum1 = totalSum / 2
        So we want to find sum1 as close to totalSum / 2 as possible.

Step 3 : Meet in the Middle (MITM) is an algorithmic technique where:
          Instead of solving a big exponential problem directly,
          you split the problem into two halves,
          solve each half independently,
          and then combine (meet) the results in the middle.

          You do this:
         Generate all subset sums of the left half
         Generate all subset sums of the right half
         Now combine one subset from left with one subset from right
        👉 The combination step is the “meeting in the middle”.

You never generate full 30-element subsets directly.
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
       int n = nums.size();
       int N = n/2;
       vector<vector<int>>left(N+1) , right(N+1);// store the subset sums based on the size of the subset in the each half where left for the first half and right for the second half
       int sum = accumulate(nums.begin(),nums.end(),0);
       // generate all subset sums for the left and right halves
       for(int mask = 0;mask < (1<<N) ; mask++)
       {
          int size =0;
          int sum1 = 0, sum2= 0;
          for(int j = 0; j < N ; j++)
          {
            // check if the jth bit is set in the mask then include nums[j] in the left subset and nums[j+N] in the right subset
            if(mask & (1<<j))
            {
                size++;
                sum1 += nums[j];
                sum2 += nums[j+N];
            }
          }
          // store the subset sums based on the size of the subset
          left[size].push_back(sum1);
          right[size].push_back(sum2);
       }
        // sort the subset sums of the right half for binary search to find the closest sum to the target
       for(int i =0;i<N;i++)
       {
         sort(right[i].begin(),right[i].end());
       }
       // find the minimum difference by combining the subset sums from left and right halves
       // initial difference when we take all the elements from the left half 
       int ans = abs(sum - 2* left[N][0]);
       for(int i = 1;i<N;i++)
       {
           for(auto it : left[i])
           {
            int b = (sum -2*it)/2;
            int right_idx = N-i;
            auto itr = lower_bound(right[right_idx].begin(),right[right_idx].end(),b);
            if(itr != right[right_idx].end())
            {
                ans = min(ans , abs(sum-2*(it+*itr)));
            }
           }
       }
       return ans ;
    }
};

