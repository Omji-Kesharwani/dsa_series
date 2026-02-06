/*K-Concatenation Maximum Sum*/
/*
Given an integer array arr and an integer k, modify the array by repeating it k times.
For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].
Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.
As the answer can be very large, return the answer modulo 109 + 7.

Example 1:
Input: arr = [1,2], k = 3
Output: 9
*/

/*
🚀 Key Observations
Directly concatenating the array k times is inefficient for large k
The solution depends heavily on the total sum of the array
Kadane’s Algorithm is the backbone of the solution
🧩 Strategy Breakdown
We split the problem into cases based on the value of k and the total sum of the array.
✅ Case 1: k == 1
Simply compute the maximum subarray sum using Kadane’s Algorithm
✅ Case 2: k ≥ 2 and totalSum ≥ 0
Important Insight:
If the total sum of the array is non-negative, repeating the array increases the possible subarray sum.
Optimal Subarray Structure
[ suffix of A ] + [ full A ] × (k - 2) + [ prefix of A ]
Why only 2 concatenations are enough?
First array → best suffix
Last array → best prefix
Middle (k - 2) arrays → fully included
So we:
Compute the maximum subarray sum in two concatenated arrays
Add (k - 2) × totalSum
❌ Case 3: k ≥ 2 and totalSum < 0
Key Idea:
Repeating a negatively summed array reduces the total sum.
So:
The optimal subarray never includes full middle arrays
The best possible subarray:
Lies fully inside one array, or
Wraps once around (suffix + prefix)
➡ This becomes a maximum circular subarray problem
🛠 Function-Wise Explanation
🔹 maxSubarraySumCircular(nums)
Purpose:
Find the maximum subarray sum in a circular array
Approach
Uses Kadane’s Algorithm twice:
For maximum subarray (normal case)
For minimum subarray (to handle wrap-around)
Formula
max(
    maxSubarraySum,
    totalSum - minSubarraySum
)
Edge Case
If all elements are negative → return the largest element
🔹 maxSubarraySumCircularDouble(nums)
Purpose:
Compute the maximum subarray sum in two concatenated arrays
Why?
This captures:
Best suffix of first array
Best prefix of second array
Which together represent the best cross-boundary subarray
Method
Duplicate the array
Run Kadane’s Algorithm once
🔹 kConcatenationMaxSum(arr, k)
Main Driver Function
Steps
Compute totalSum of the array
Handle cases:
k == 1 → simple Kadane
k ≥ 2 and totalSum ≥ 0
result =
  maxSubarraySumInTwoArrays
  + (k - 2) × totalSum
k ≥ 2 and totalSum < 0
→ Use circular subarray logic
Return result modulo 10^9 + 7
⏱ Complexity Analysis
Metric	Value
Time Complexity	O(n)
Space Complexity	O(n)
Extra Array Used	Only for 2× concatenation
🧠 Final Intuition
Positive total sum → repeat helps → use prefix + suffix + middle arrays
Negative total sum → repeat hurts → use at most one wrap
Kadane’s Algorithm is the key tool in all cases
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
    private:
     const int MOD = 1e9+7;
     int maxSubarraySumCircular(const vector<int>& nums)
     {
        int n = nums.size();
        int maxSum = INT_MIN ;
        int minSum = INT_MAX ;
        int totalSum = 0 ,currentMax = 0 , currentMin = 0 ;
        for(const int& num : nums)
        {
            currentMax = max(currentMax+num ,num);
            maxSum = max(maxSum,currentMax);
            currentMin = min(currentMin + num , num);
            minSum = min(minSum ,currentMin) ;
            totalSum += num ;
        }

        if(maxSum <= 0) return *max_element(nums.begin(),nums.end());
        return max(maxSum , totalSum-minSum );
     }

     int maxSubarraySumCircularDouble(const vector<int>& nums)
     {
        vector<int>doubleArray(nums.begin(),nums.end());
        doubleArray.insert(doubleArray.end(),nums.begin(),nums.end());
        long long maxSum =0,currentSum =0;
        for(const int& num : doubleArray)
        {
            currentSum = max(currentSum + num ,(long long)num);
            maxSum = max(maxSum , currentSum);
            if(currentSum < 0) currentSum = 0;
        }
        return maxSum % MOD;
     }
public:

    int kConcatenationMaxSum(vector<int>& arr, int k) {
       int totalSum = accumulate(arr.begin(),arr.end(),0LL) ;
       if(k==1)
       {
        int maxSingle =0;
        int currentSum = 0;
        for(const int& num :arr)
        {
            currentSum = max(currentSum+num , num);
            maxSingle = max(maxSingle,currentSum);
        }
        return maxSingle ;
       }  
       else {
        if(totalSum >=0)
        {
            int maxSubSum = maxSubarraySumCircularDouble(arr);
            long long result = maxSubSum ;
            result = (result + 1LL * (totalSum % MOD) *((k-2) % MOD )) % MOD;
            return (int)result ;
        }
        else
        {
            int maxSubSum = maxSubarraySumCircular(arr);
            return max(maxSubSum,0);
        }
       }
    }
};