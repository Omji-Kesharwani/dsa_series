/*
You are given a string array grid of size n, where each string grid[i] has length m. The character grid[i][j] is one of the following symbols:
'.': The cell is available.
'#': The cell is blocked.
You want to count the number of different routes to climb grid. Each route must start from any cell in the bottom row (row n - 1) and end in the top row (row 0).
However, there are some constraints on the route.
You can only move from one available cell to another available cell.
The Euclidean distance of each move is at most d, where d is an integer parameter given to you. The Euclidean distance between two cells (r1, c1), (r2, c2) is sqrt((r1 - r2)^2 + (c1 - c2)^2).
Each move either stays on the same row or moves to the row directly above (from row r to r - 1).
You cannot stay on the same row for two consecutive turns. If you stay on the same row in a move (and this move is not the last move), your next move must go to the row above.
Return an integer denoting the number of such routes. Since the answer may be very large, return it modulo 109 + 7.

 

Example 1:

Input: grid = ["..","#."], d = 1

Output: 2

Explanation:

We label the cells we visit in the routes sequentially, starting from 1. The two routes are:

.2
#1
32
#1
We can move from the cell (1, 1) to the cell (0, 1) because the Euclidean distance is sqrt((1 - 0)2 + (1 - 1)2) = sqrt(1) <= d.

However, we cannot move from the cell (1, 1) to the cell (0, 0) because the Euclidean distance is sqrt((1 - 0)2 + (1 - 0)2) = sqrt(2) > d.
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    const int M = 1e9+7;// modulo
    int numberOfRoutes(vector<string>& grid, int d) {
        int n = grid.size(); // number of rows
        int m = grid[0].size(); // number of columns
        vector<vector<long long>>dp(n,vector<long long>(m,0)); // dp[i][j] = number of ways to reach cell (i,j)
        vector<long long>prefix(m,0); // prefix sum array
        // Base case : for the last row, if the cell is available, then dp[n-1][i] = 1
        for(int i=0;i<m;i++)
        {
            if(grid[n-1][i] == '.') // only if the cell is available 
            dp[n-1][i] =1;
        }

        for(int i=0;i<m;i++)
        {
            if(i==0)
            {
                prefix[i] = dp[n-1][i];
            }
            else
            {
                prefix[i] = dp[n-1][i]+prefix[i-1];
            }

            prefix[i] %= M;
        }
      // for storing the number of ways to reach the cell (i,j) from the same row but different column the distance between them is less than or equal to d
        for(int i=0;i<m;i++)
        {
            if(grid[n-1][i] != '.')
            {
                continue;
            }

            int j1 = max(-1,i-d-1);
            int j2 = min(m-1,i+d);
            int extra = dp[n-1][i];
            if(j1 >= 0) dp[n-1][i] += (prefix[j2]-prefix[j1]+M)%M;
            else
            dp[n-1][i] += prefix[j2] ;
            dp[n-1][i] %= M;
            dp[n-1][i] -= extra ;
            dp[n-1][i] += M;
            dp[n-1][i] %= M ;     
        }
      
         // again calculating the prefix sum array
       for(int i=0;i<m;i++)
        {
            if(i==0)
            {
                prefix[i] = dp[n-1][i];
            }
            else
            {
                prefix[i] = dp[n-1][i]+prefix[i-1];
            }

            prefix[i] %= M;
        }
       /*
       Now since we can move to the row above only the we must see this equation carefully
       sqrt(sqr(1) + sqr(j-i)) <= d
       => lim = sqrt(d*d-1)
       again doing for the other rows with the below calcualted prefix
       */
        int lim = 0;
        if(d != 0) 
        lim = (int)sqrt(d*d-1);

        for(int i = n-2 ; i>=0 ; i--)
        {
            for(int j=0;j<m;j++)
            {
                if(grid[i][j] != '.') continue;
                int j1 = max(-1,j-lim-1),j2 = min(m-1,j+lim);
                if(j1>=0) dp[i][j] += (prefix[j2]-prefix[j1] + M) % M ;
                else dp[i][j] += prefix[j2];
                dp[i][j] %= M;
            }

            for(int j=0;j<m;j++)
            {
                if(j==0) prefix[j] = dp[i][j];
                else prefix[j] = dp[i][j] + prefix[j-1];
                prefix[j] %= M;
            }

            for(int j=0;j<m;j++)
            {
                if(grid[i][j]!='.') continue ;
                int j1 = max(-1,j-d-1) , j2 = min(m-1,j+d);
                int extra = dp[i][j];
                if(j1 >=0 )
                dp[i][j] += (prefix[j2]-prefix[j1] +M) %M;
                else dp[i][j] += prefix[j2];
                dp[i][j] %= M;

                dp[i][j] -= extra ;
                dp[i][j] += M;
                dp[i][j] %= M;
            }

             for(int j=0;j<m;j++)
            {
                if(j==0) prefix[j] = dp[i][j];
                else prefix[j] = dp[i][j] + prefix[j-1];
                prefix[j] %= M;
            }


        
        }



    return prefix[m-1];




    }
};