/*
Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.

A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.

Return true if any cycle of the same value exists in grid, otherwise, return false.

Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
    struct Node{
        int r,c;
        int pr,pc;
    };
public:
    bool isCyclePresent(int i,int j , int m,int n , vector<vector<char>>& grid, vector<vector<int>>& vis)
    {
        vector<int>delRow= {-1,1,0,0};
        vector<int>delCol = {0,0,-1,1};
        queue<Node> q;
        q.push({i,j,-1,-1});
        vis[i][j]=1;
        while(!q.empty())
        {
            int r = q.front().r;
            int c = q.front().c;
            int pr = q.front().pr;
            int pc = q.front().pc ;
            q.pop();
            for(int i =0;i<4;i++)
            {
                int nRow = r+delRow[i];
                int nCol = c+delCol[i];

                if(nRow >= 0 && nRow < grid.size() && nCol >=0 && nCol < grid[0].size() && grid[nRow][nCol] == grid[r][c])
                {
                    if(vis[nRow][nCol])
                    {
                        if(!(nRow == pr && nCol == pc))
                        return true ;
                    }
                    else
                    {
                        vis[nRow][nCol] =1;
                        q.push({nRow,nCol,r,c});
                    }
                }
            }
        }
        return false ;
    }
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>>vis(m,vector<int>(n,0));

        for(int i = 0;i<m;i++)
        {
            for(int j = 0;j<n;j++)
            {
                if(!vis[i][j])
                {
                    if(isCyclePresent(i,j,m,n,grid,vis))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};