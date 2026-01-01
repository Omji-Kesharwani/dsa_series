/*Leetcode
2472. Maximum Number of Non-overlapping Palindrome Substrings
You are given a string s and a positive integer k.

Select a set of non-overlapping substrings from the string s that satisfy the following conditions:

The length of each substring is at least k.
Each substring is a palindrome.
Return the maximum number of substrings in an optimal selection.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "abaccdbbd", k = 3
Output: 2
Explanation: We can select the substrings underlined in s = "abaccdbbd". Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
It can be shown that we cannot find a selection with more than two valid substrings.

*/
/*
APPROACH:
First find all the palindromic substrings of length at least k and store their intervals in a vector.
Then, we can use a greedy approach to select the maximum number of non-overlapping intervals. We iterate through the intervals and keep track of the last interval we selected. If the current interval starts after the last interval ends, we can select it and update the last interval. Otherwise, we skip the current interval.
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        int last = INT_MIN;//to keep track of the end of the last selected interval
        int ans = 0;
        vector<vector<int>> intervals ;
       //find all palindromic substrings of length at least k for odd and even length palindromes that whys we do center from 0 to 2*n
        for(int center =0 ; center<2*n ; center++ )
        {
            int left = center / 2;
            int right = left + center % 2;
            while(left >= 0 && right < n && s[left] == s[right])
            {
                if(right-left+1 >= k )
                {
                    intervals.push_back({left,right+1});
                    break;

                }
                left--;
                right++;
            }

          
        }

          for(auto v:intervals)
            {
                if(v[0]>= last)
                {
                    last=v[1];
                    ans++;
                }
                else if(v[1]<last)
                {
                    last = v[1]; 
                }
            }

            return ans;
    }
};