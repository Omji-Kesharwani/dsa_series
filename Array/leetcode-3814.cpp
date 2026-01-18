/*
You are given two integer arrays costs and capacity, both of length n, where costs[i] represents the purchase cost of the ith machine and capacity[i] represents its performance capacity.

You are also given an integer budget.

You may select at most two distinct machines such that the total cost of the selected machines is strictly less than budget.

Return the maximum achievable total capacity of the selected machines.

 

Example 1:

Input: costs = [4,8,5,3], capacity = [1,5,2,7], budget = 8

Output: 8

Explanation:

Choose two machines with costs[0] = 4 and costs[3] = 3.
The total cost is 4 + 3 = 7, which is strictly less than budget = 8.
The maximum total capacity is capacity[0] + capacity[3] = 1 + 7 = 8.

*/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        int n = costs.size();
        vector<pair<int,int>>vec(n); // pairs up the cost and the capacity in the same vector 
        for(int i = 0; i<n ; i++)
        {
            vec[i] = {costs[i],capacity[i]};
        }
     
        // sort the vector based on the cost in ascending order
        sort(vec.begin(),vec.end());
        // to calculate the prefix max of the capacity
        vector<int>premax(n);
        // to store the cost in the same order after the sorting the vec vector
        vector<int>capi(n);
        for(int i =0;i<n;i++)
        {
            capi[i] = vec[i].first ;
        }
        premax[0] = vec[0].second;
        for(int i = 1 ; i < n ; i++)
        {
            premax[i] = max(premax[i-1],vec[i].second);
        }
        int ans = 0;// stores the max capacity within the budget 
        // we check from every item in the vec vector
        for(int i = 0;i<n;i++)
        {
            int curr = vec[i].first;
            int rem = budget-curr;
            // if the item costs equals to the budget or more than the budget then we skip it
            if(rem <= 0 ) continue ;
            // firstly we take the item as single as it can give the max capacity 
            if(curr < budget)
            ans = max(ans, vec[i].second);
            // then search for the item with the cost less than the remaining budget in the capi vector 
            auto it = lower_bound(capi.begin(),capi.end(),rem);
            int idx = it - capi.begin()-1;
            // to check the same item is not counted twice
            int left = min(idx, i-1);
            if(left >=0)
            {
                ans = max(ans, vec[i].second + premax[left]);
            }
        }
        return ans;
    }
};