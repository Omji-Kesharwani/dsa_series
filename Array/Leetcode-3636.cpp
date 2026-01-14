/*
You are given an integer array nums of length n and an array queries, where queries[i] = [li, ri, thresholdi].
Return an array of integers ans where ans[i] is equal to the element in the subarray nums[li...ri] that appears at least thresholdi times, selecting the element with the highest frequency (choosing the smallest in case of a tie), or -1 if no such element exists.
Example 1:
Input: nums = [1,1,2,2,1,1], queries = [[0,5,4],[0,3,3],[2,3,2]]
Output: [1,-1,2]
*/
//Approach : Using Mo's algorithm 
//Time Complexity : O((n+q) * sqrt(n))
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:

    vector<int> subarrayMajority(vector<int>& a, vector<vector<int>>& queries) {
        //in (l, r) range just find the element with highest frequency
        const int n = a.size();
        const int q = queries.size();
        const int B = sqrt(n); // the size of the block 

        vector<int> order(q);
        iota(order.begin(), order.end(), 0); 
        // sort according to which query to be processed first 
        sort(order.begin(), order.end(), [&](int& i1, int& i2){
            if(queries[i1][0]/B == queries[i2][0]/B)
                return queries[i1][1] < queries[i2][1];

            return queries[i1][0]/B < queries[i2][0]/B;
        });

        //co-ordinate compression [optional can be skipped, if TC permits]
        vector<int> tmp = a;
        sort(tmp.begin(), tmp.end());
        map<int, int> mp;
        int cntr = 0;
        for(int i=0;i<n;i++)
        {
            if(mp.find(tmp[i])==mp.end())
            {
                mp[tmp[i]] = cntr;
                cntr++;
            }
        }
        vector<int> rev(cntr);
        //rev[compressed[i]] = original[i]
        for(int i=0;i<n;i++)
        {
            int t = a[i];
            a[i] = mp[a[i]];
            rev[a[i]] = t; 
        }

        vector<int> freq(cntr, 0);// stores the frequency of each element 
        vector<list<int>> bucket(n+1); //bucket[f] = stores numbers who have freq = f;
        vector<list<int>::iterator> itPos(cntr); //itPos[x]: tell where x is in bucket[f] (already know freq[x]);
        vector<int> minInBucket(n+1, cntr); // minInBucket[f] = minimum element in bucket[f].
        int maxFreq = 0; // stores the maximum frequency of any element in the current range

        //initial all the elements from 0 to cntr-1 in the bucket[0]
        for (int x = 0; x < cntr; x++) 
            itPos[x] = bucket[0].insert(bucket[0].end(), x);
        
            // insert and remove function
        auto insert = [&](int idx)
        {
            int x = a[idx];
            int f = freq[x];
            bucket[f].erase(itPos[x]);
            if(x == minInBucket[f])
            {
                int mini = cntr;
                for(int val: bucket[f])
                    mini = min(mini, val);
                minInBucket[f] = mini;
            }

            freq[x] = ++f;
            itPos[x] = bucket[f].insert(bucket[f].end(), x);
            
            if(x<minInBucket[f])
                minInBucket[f] = x;

            if(f > maxFreq)
                maxFreq = f;
        };

        auto remove = [&](int idx)
        {
            int x = a[idx];
            int f = freq[x];
            bucket[f].erase(itPos[x]);
            if(x == minInBucket[f])
            {
                int mini = cntr;
                for(int val: bucket[f])
                    mini = min(mini, val);
                minInBucket[f] = mini;
            }

            freq[x] = --f;
            itPos[x] = bucket[f].insert(bucket[f].end(), x);

            if(x<minInBucket[f])
                minInBucket[f] = x;

            while(maxFreq>0 && bucket[maxFreq].empty())
                maxFreq--;
        };

        auto getAns = [&]()
        {
            int x = minInBucket[maxFreq];
            return (pair<int,int>){maxFreq, rev[x]};
        };

        vector<int> ans(q, -1);
        int left = 0, right = -1;
        for(int i: order)
        {
            int l = queries[i][0], r = queries[i][1], th = queries[i][2];

            //after these left = l and right = r

            while(left > l)
            {
                left--;
                insert(left);
            }

            while(right < r)
            {
                right++;
                insert(right);
            }

            while(left < l)
            {
                remove(left);
                left++;
            }

            //This often only triggers when new block is seen(might be optimized)
            while(right > r)
            {
                remove(right);
                right--;
            }
            
            pair<int,int> p = getAns();
            //cout<<l<<' '<<r<<"-> "<<p.first<<' '<<p.second<<'\n';
            if(p.first >=th)
                ans[i] = p.second;
        }

        return ans;
    }
};