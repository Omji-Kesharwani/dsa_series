/* Leetcode 975: Odd Even Jump */

/*
You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.

You may jump forward from index i to index j (with i < j) in the following way:

During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
It may be the case that for some index i, there are no legal jumps.
A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).

Return the number of good starting indices.

Example 1:

Input: arr = [10,13,12,14,15]
Output: 2
Explanation: 
From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
From starting index i = 4, we have reached the end already.
In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
jumps.
*/

/*Approach: Brute Force*/
/*Time complexity: O(n^3)*/

#include <bits/stdc++.h>
using namespace std;
class Solution {
  private:
   enum {ODD=0, EVEN=1};
   bool reachable(vector<int>& arr, int i,int parity)
   {
     if(i==arr.size()-1)
     {
        return true;
     }
     int closest =-1;
     if(parity==ODD)
     {
          for(int j=i+1;j<arr.size();j++)
          {
            if(arr[i] <= arr[j] && (closest==-1 || abs(arr[i]-arr[j]) < abs(arr[i]-arr[closest]) ))
            {
                closest=j;
            }
          }

          return closest==-1 ? false : reachable(arr,closest,EVEN);
     }
     else{
          for(int j=i+1;j<arr.size();j++)
          {
            if(arr[i] >= arr[j] && (closest==-1 || abs(arr[i]-arr[j]) < abs(arr[i]-arr[closest]) ))
            {
                closest=j;
            }
          }

          return closest==-1 ? false : reachable(arr,closest,ODD);
     }
    
   }
  public:
  int oddEvenJumps(vector<int>& arr) {

    int goodIndices = 0;
    for(int i=0;i<arr.size();i++)
    {
       if(reachable(arr,i,ODD))
       {
          goodIndices++;
       }
    }
    return goodIndices;
  }
};

// Optimizing using DP 
//Time complexity: O(n^2)


//Top Down Approach

class Solution {
  private:
   enum {ODD=0, EVEN=1};
   bool reachable(vector<int>& arr, int i,int parity,vector<vector<int>>& dp)
   {
     if(dp[i][parity]>-1)
     {
       return dp[i][parity];
     }

     if(i==arr.size()-1)
     {
        return dp[i][parity]= true;
     }

     int closestOddJump =-1;
     int closestEvenJump =-1;
     for(int j=i+1;j<arr.size();j++)
     {
       if(arr[i] <= arr[j] && (closestOddJump==-1 || abs(arr[i]-arr[j]) < abs(arr[i]-arr[closestOddJump]) ))
       {
           closestOddJump=j;
       }

        if(arr[i] >= arr[j] && (closestEvenJump==-1 || abs(arr[i]-arr[j]) < abs(arr[i]-arr[closestEvenJump]) ))
        {
            closestEvenJump=j;
        }
     }

     dp[i][ODD] = closestOddJump==-1 ? false : reachable(arr,closestOddJump,EVEN,dp);
     dp[i][EVEN] = closestEvenJump==-1 ? false : reachable(arr,closestEvenJump,ODD,dp);
     
     return (parity==ODD) ? dp[i][ODD] : dp[i][EVEN];

   }

  public:
  int oddEvenJumps(vector<int>& arr) {
    vector<vector<int>> dp(arr.size(),vector<int>(2,-1));
    int goodIndices = 0;
    for(int i=0;i<arr.size();i++)
    {
       if(reachable(arr,i,ODD,dp))
       {
          goodIndices++;
       }
    }
    return goodIndices;
  }
};

//Bottom Up Approach

class Solution {
  public:
  enum {ODD=0, EVEN=1};
  int oddEvenJumps(vector<int>& arr) {
    vector<vector<bool>>dp(arr.size(),vector<bool>(2,false));
    dp.back()[ODD]=true;
    dp.back()[EVEN]=true;

    int closestOddJump,closestEvenJump , goodIndices;
    goodIndices=1; //last index is always a good index

    for(int i=arr.size()-2;i>=0;i--)
    {
       closestOddJump =-1;
       closestEvenJump =-1;
       for(int j=i+1;j<arr.size();j++)
       {
         if(arr[i] <= arr[j] && (closestOddJump==-1 || abs(arr[i]-arr[j]) < abs(arr[i]-arr[closestOddJump]) ))
         {
             closestOddJump=j;
         }

          if(arr[i] >= arr[j] && (closestEvenJump==-1 || abs(arr[i]-arr[j]) < abs(arr[i]-arr[closestEvenJump]) ))
          {
              closestEvenJump=j;
          }
       }

       dp[i][ODD] = closestOddJump==-1 ? false : dp[closestOddJump][EVEN];
       dp[i][EVEN] = closestEvenJump==-1 ? false : dp[closestEvenJump][ODD];

       if(dp[i][ODD])
       {
          goodIndices++;
       }
    }

    return goodIndices;

  }
};

//Using the map/bst + dynamic Programming

//Time complexity: O(n log n)

class Solution {
  public:
  enum {ODD=0, EVEN=1};
  int oddEvenJumps(vector<int>& arr) {
    int goodIndices;
    vector<vector<bool>>dp(arr.size(),vector<bool>(2,false));
    dp.back()[ODD]=true;
    dp.back()[EVEN]=true;

    map<int,int>seen;// seen[value] = index of this value
    map<int,int>::iterator closest;
    goodIndices=1; //last index is always a good index
    seen[arr.back()]=arr.size()-1;

    for(int i=arr.size()-2;i>=0;i--)
    {
       //odd jump
       closest = seen.lower_bound(arr[i]);
       if(closest!=seen.end() && closest->first==arr[i])
       {
          dp[i][ODD] = dp[closest->second][EVEN];
          dp[i][EVEN] = dp[closest->second][ODD];
       }
      else
      {
        dp[i][ODD] = (closest != seen.end()) ? dp[closest->second][EVEN] : false;

        if(closest == seen.begin())
        {
          dp[i][EVEN] = false;
        }
        else
        {
          --closest;
          dp[i][EVEN] = dp[closest->second][ODD];
        }
      }


       if(dp[i][ODD])
        goodIndices++;


        seen[arr[i]]=i;
    }
    return goodIndices;
      
    }

  };

