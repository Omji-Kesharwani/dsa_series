/*
1928. Minimum Cost to Reach Destination in Time
There is a country of n cities numbered from 0 to n - 1 where all the cities are connected by bi-directional roads. The roads are represented as a 2D integer array edges where edges[i] = [xi, yi, timei] denotes a road between cities xi and yi that takes timei minutes to travel. There may be multiple roads of differing travel times connecting the same two cities, but no road connects a city to itself.

Each time you pass through a city, you must pay a passing fee. This is represented as a 0-indexed integer array passingFees of length n where passingFees[j] is the amount of dollars you must pay when you pass through city j.

In the beginning, you are at city 0 and want to reach city n - 1 in maxTime minutes or less. The cost of your journey is the summation of passing fees for each city that you passed through at some moment of your journey (including the source and destination cities).

Given maxTime, edges, and passingFees, return the minimum cost to complete your journey, or -1 if you cannot complete it within maxTime minutes.

Input: maxTime = 30, edges = [[0,1,10],[1,2,10],[2,5,10],[0,3,1],[3,4,10],[4,5,15]], passingFees = [5,1,2,20,20,3]
Output: 11
Explanation: The path to take is 0 -> 1 -> 2 -> 5, which takes 30 minutes and has $11 worth of passing fees.
*/

/*
APPROACH : Basically in this question we have to find the minimum cost to reach the destination in the given time. So, we can use Dijkstra's algorithm to find the minimum cost. But in this question, we have to consider the time as well. So, we have to modify the Dijkstra's algorithm to consider the time as well.

The adjacency matrix will store the node to which it traverse, the cost and the time .
The cost array will store the minimum cost to reach the node.
The time array will store the minimum time to reach the node.
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> adj[1001];
    int cost[1001], time[1001];
    
    int dijkstra(int src, int dest, int maxTime) {
        
        for (int i = 1; i <= dest; i++) {
            cost[i] = INT_MAX;
            time[i] = INT_MAX;
        }
        
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({cost[src], time[src], src});
        
        while (pq.empty() == 0) {
            vector<int> z = pq.top(); pq.pop();
            
            int c = z[0];     // cost
            int t = z[1];     // time
            int v = z[2];     // vertex
            
            for (int i=0;i<adj[v].size();i++) {
                
			    // if this edge does not cause the time to exceed maxTime 
             // adj[v][i][1] = time to reach this node from the given node 
                if (t + adj[v][i][1] <= maxTime) {
                    
				    // if cost will decrease
                    if (cost[adj[v][i][0]] > c + adj[v][i][2]) {
                        cost[adj[v][i][0]] = c + adj[v][i][2];
                        
                        time[adj[v][i][0]] = t + adj[v][i][1];
                        pq.push({cost[adj[v][i][0]], time[adj[v][i][0]], adj[v][i][0]});
                    }
                    
					// if time will decrease
                    else if (time[adj[v][i][0]] > t + adj[v][i][1]) {
                        time[adj[v][i][0]] = t + adj[v][i][1];
                        pq.push({c + adj[v][i][2], time[adj[v][i][0]], adj[v][i][0]});
                    }
                }
            }
        }
        
        return cost[dest];
    }
    
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& fee) {
        int i, x, y, t, e = edges.size(), n = fee.size();
        
        for (i=0;i<e;i++) {
            x = edges[i][0];
            y = edges[i][1];
            t = edges[i][2];
            
            adj[x].push_back({y, t, fee[y]});
            adj[y].push_back({x, t, fee[x]});
        }
        
        cost[0] = fee[0];
        time[0] = 0;
        
        int ans = dijkstra(0, n-1, maxTime);
        
        if(ans == INT_MAX)
            return -1;
        
        return ans;
    }
};