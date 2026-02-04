/*
3013. Divide an Array Into Subarrays With Minimum Cost II
You are given a 0-indexed array of integers nums of length n, and two positive integers k and dist.
The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.
You need to divide nums into k disjoint contiguous subarrays, such that the difference between the starting index of the second subarray and the starting index of the kth subarray should be less than or equal to dist. In other words, if you divide nums into the subarrays nums[0..(i1 - 1)], nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)], then ik-1 - i1 <= dist.
Return the minimum possible sum of the cost of these subarrays.
Example 1:
Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
Output: 5
Explanation: The best possible way to divide nums into 3 subarrays is: [1,3], [2,6,4], and [2]. This choice is valid because ik-1 - i1 is 5 - 2 = 3 which is equal to dist. The total cost is nums[0] + nums[2] + nums[5] which is 1 + 2 + 2 = 5.
It can be shown that there is no possible way to divide nums into 3 subarrays at a cost lower than 5.
*/

/*
APPROACH :
The key idea is to fix a position i>0 and assume that in the optimal solution the first subarray starts at position 0, the second subarray starts at position ≥i, while the last, k-th, subarray starts before position i+dist.

In other words, we have a range of positions [i,i+dist] from which we can choose the starts of the 2nd, 3rd, ... k-th subarray.
Obviously the most optimal choice is to choose the smallest k−1 elements in the range(subarray of nums) [i,i+dist]

Notice that if we do this for each i, the range is simply a window that is moving, and we are interested in the k−1th lowest elements in that window.

The rest of the solution is how to do this efficiently.

Lowest K elements in a sliding window
We need to be able to have a window of some fixed size, let's say w elements, and keep track of the sum of the smallest k elements in the window(we would assume k≤w).

To be able to do this efficiently, we would maintain two sets - more correctly, multisets.

In the first set - let's call it low - we would maintain the lowest k elements in the window.
In the second set - let's call it high - we would keep the other w−k elements.

Usually, when doing a sliding window, we need some data structure that would efficiently do two types of operations:

add() - when expanding the window to the right, we need to be able to insert an element x in the window.
remove() - at the same time, we need to shrink the window from the left, i.e., remove an element x from the window.
The key element in implementing this structure is how we balance the low and high sets; i.e., we want the low set to have exactly k elements when the window has size ≥k.

For this reason we are introducing the function rebalance():
Note that we keep sumLow, which is the sum of the elements in the low set. Every time we add an element to the set low, we increase the sum; every time we remove an element, we decrease the sum.

If the value x that we are trying to insert is smaller than or equal to the maximum element in the low set, x should definitely be inserted into the low set; otherwise, we insert it into the high set. This way, we guarantee that all of the elements in the low set are smaller than the elements in the high set.
After the insertion, we call the function rebalance to maintain the structure.

We need to check whether the element x we are trying to remove is in the low or high set, and then remove it from the set it is in. After that we call rebalance.
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    struct SmartWindow{ // for declaration of the custom window 
        int K; // number of elements in the window
        multiset<int> low, high; // to store the k  smallest elements in the low and next in the high set 
        long long sumLow = 0; // to store the sum of the k smallest elements in the low set

        SmartWindow(int k) : K(k) {}

        int windowSize() const{ // what is the size of the window
            return (int)low.size() + (int)high.size();
        }
        void rebalance() {  // to maintain the structure of the window
            int need = min(K, windowSize());

            while((int)low.size() > need){
                auto it = prev(low.end());
                int x = *it;
                low.erase(it);
                sumLow -= x;
                high.insert(x);
            }
            while((int)low.size() < need && !high.empty()){
                auto it = high.begin();
                int x = *it;
                high.erase(it);
                low.insert(x);
                sumLow += x;
            }
        }
        void add(int x){
            if(low.empty() || x <= *prev(low.end())){
                low.insert(x);
                sumLow += x;
            }
            else{
                high.insert(x);
            }
            rebalance();
        }
        void remove(int x){
            auto itLow = low.find(x);
            if(itLow != low.end()){
                low.erase(itLow);
                sumLow -= x;
            }
            else{
                auto itHigh = high.find(x);
                if(itHigh != high.end()){
                    high.erase(itHigh);
                }
            }
            rebalance();
        }
        long long query() const{
            return sumLow;
        }
    };
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = (int)nums.size();
        k -= 1;
        SmartWindow window(k);
        // first do for the single window from i .... i+dist
        for(int i = 1; i <= 1 + dist; i ++){
            window.add(nums[i]);
        }
        // then continue for the rest of the windows in the similar manner 
        long long ans = window.query();
        for(int i = 2; i + dist < n; i ++){
            window.remove(nums[i - 1]);
            window.add(nums[i + dist]);
            ans = min(ans, window.query());
        }
        return ans + nums[0];  // finally return the answer 
    }
};