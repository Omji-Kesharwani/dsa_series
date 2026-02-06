/*Minimum Cost Tree From Leaf Values

Given an array arr of positive integers, consider all binary trees such that:

Each node has either 0 or 2 children;
The values of arr correspond to the values of each leaf in an in-order traversal of the tree.
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree, respectively.
Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node. It is guaranteed this sum fits into a 32-bit integer.

A node is a leaf if and only if it has zero children.

 

Example 1:
Input: arr = [6,2,4]
Output: 32
Explanation: There are two possible trees shown.
The first has a non-leaf node sum 36, and the second has non-leaf node sum 32.
*/
/*

Approach : First use the small values as they will contribute only ones in the cost of making the internal node . Therefore first use the small values and then use the large values to make the internal nodes . This will give us the minimum cost of making the tree .
*/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int res = 0;
        stack<int> st;
        st.push(INT_MAX);

        for (int x : arr) {
            while (st.top() <= x) {
                int mid = st.top();
                st.pop();
                res += mid * min(st.top(), x);
            }
            st.push(x);
        }

        while (st.size() > 2) {
            int mid = st.top();
            st.pop();
            res += mid * st.top();
        }

        return res;
    }
};
