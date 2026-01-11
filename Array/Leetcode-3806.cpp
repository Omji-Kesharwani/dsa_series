/*
You are given an integer array nums and two integers k and m.
You may perform at most k operations. In one operation, you may choose any index i and increase nums[i] by 1.
Return an integer denoting the maximum possible bitwise AND of any subset of size m after performing up to k operations optimally.
Example 1:
Input: nums = [3,1,2], k = 8, m = 2
Output: 6
Explanation:
We need a subset of size m = 2. Choose indices [0, 2].
Increase nums[0] = 3 to 6 using 3 operations, and increase nums[2] = 2 to 6 using 4 operations.
The total number of operations used is 7, which is not greater than k = 8.
The two chosen values become [6, 6], and their bitwise AND is 6, which is the maximum possible.
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int getOps(int x,int t)
    {
        if((x & t) == t) return 0;
        int cur =0;
        for(int i=30;i>=0;i--)
        {
            int t1= t & (1LL << i);
            int x1 = x & (1LL << i);
            if(t1 && !x1)
            {
                cur |= (1LL << i);
                cur |= (t & ((1LL <<i )-1));
                return  cur -x;
            }
            if(x1 )
            {
                cur |= (1LL << i);
            }
        }
        return cur-x;

    }

    int maximumAND(vector<int>& nums, int k, int m) {
        int cur = 0;
        // checking the bitwise and of all the numbers
        for(int i = 30 ; i>=0 ; i--)
        {
            int t = cur | (1<<i);
            vector<int>cost;
            for(int x: nums)
            {
                cost.push_back(getOps(x,t));
            } 
            sort(cost.begin(),cost.end());
            int need = 0;
            for(int i=0;i<m;i++)
            {
                need += cost[i];
                if(need > k) break ;
            }
            if(need <= k)
            cur = t ;
        }

        return (int)cur;
    }
};