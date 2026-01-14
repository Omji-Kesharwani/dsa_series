/*
There is a rooted tree consisting of n nodes numbered 0 to n - 1. Each node's number denotes its unique genetic value (i.e. the genetic value of node x is x). The genetic difference between two genetic values is defined as the bitwise-XOR of their values. You are given the integer array parents, where parents[i] is the parent for node i. If node x is the root of the tree, then parents[x] == -1.

You are also given the array queries where queries[i] = [nodei, vali]. For each query i, find the maximum genetic difference between vali and pi, where pi is the genetic value of any node that is on the path between nodei and the root (including nodei and the root). More formally, you want to maximize vali XOR pi.

Return an array ans where ans[i] is the answer to the ith query.

Input: parents = [-1,0,1,1], queries = [[0,2],[3,2],[2,5]]
Output: [2,3,7]
Explanation: The queries are processed as follows:
- [0,2]: The node with the maximum genetic difference is 0, with a difference of 2 XOR 0 = 2.
- [3,2]: The node with the maximum genetic difference is 1, with a difference of 2 XOR 1 = 3.
- [2,5]: The node with the maximum genetic difference is 2, with a difference of 5 XOR 2 = 7.
*/

// Approach : Using Trie
#include<bits/stdc++.h>
using namespace std;
// ===================== TRIE NODE =====================
struct Node{
    // child[0] -> next node if bit = 0
    // child[1] -> next node if bit = 1
    Node* child[2];

    // cnt = how many numbers pass through this node
    // used for safe removal (backtracking)
    int cnt;

    // wend stores numbers that end at this node
    vector<int> wend;

    Node(){
        // initially no children
        child[0] = NULL;
        child[1] = NULL;

        // initially no number passes through
        cnt = 0;
    }
};

// ===================== TRIE CLASS =====================
class Trie{
public:
    Node* root;

    Trie(){
        // create empty root
        root = new Node;
    }

    // -------- INSERT NUMBER INTO TRIE --------
    // n  = number to insert
    // ln = number of bits (31 bits for int)
    void insert(int n, int ln){
        Node* curr = root;

        // process bits from MSB to LSB
        for(int i = ln - 1; i >= 0; i--){
            // one more number passes through this node
            curr->cnt++;

            // extract i-th bit of n
            int x = (n & (1 << i)) ? 1 : 0;

            // create node if not present
            if(curr->child[x] == NULL){
                curr->child[x] = new Node;
            }

            // move to next node
            curr = curr->child[x];
        }

        // increase count at leaf node
        curr->cnt++;

        // store actual number at leaf
        curr->wend.push_back(n);
    }

    // -------- REMOVE NUMBER FROM TRIE --------
    // used during DFS backtracking
    void remove(int n, int ln){
        Node* curr = root;

        // go through same path as insert
        for(int i = ln - 1; i >= 0; i--){
            // decrease count (number is being removed)
            curr->cnt--;

            int x = (n & (1 << i)) ? 1 : 0;

            curr = curr->child[x];
        }

        // decrease count at leaf
        curr->cnt--;

        // remove the stored number
        curr->wend.pop_back();
    }

    // -------- FIND NUMBER THAT GIVES MAX XOR --------
    int getXorMax(int x, int ln){
        Node* curr = root;

        // traverse from MSB to LSB
        for(int i = ln - 1; i >= 0; i--){
            int bit = (x & (1 << i)) ? 1 : 0;

            // if one path is missing or empty, go to the other
            if(curr->child[0] == NULL || curr->child[0]->cnt == 0){
                curr = curr->child[1];
            }
            else if(curr->child[1] == NULL || curr->child[1]->cnt == 0){
                curr = curr->child[0];
            }
            else{
                // both paths exist
                // choose opposite bit to maximize XOR
                if(bit == 0){
                    curr = curr->child[1];
                }
                else{
                    curr = curr->child[0];
                }
            }
        }

        // return the number stored at leaf
        return curr->wend[0];
    }
};

// ===================== SOLUTION =====================
class Solution {
public:
    Trie trie;

    // -------- DFS ON TREE --------
    void dfs(
        int node,
        vector<vector<int>>& adj,
        map<int, vector<pair<int, int>>>& mp,
        vector<int>& result
    ){
        // if current node has queries
        if(mp.find(node) != mp.end()){
            // process all queries of this node
            for(auto it : mp[node]){
                int idx = it.first;  // query index
                int p   = it.second; // query value

                // find ancestor value giving max XOR
                result[idx] = p ^ trie.getXorMax(p, 31);
            }
        }

        // visit all children of current node
        for(auto adjNode : adj[node]){
            // add child to trie (becomes ancestor)
            trie.insert(adjNode, 31);

            // DFS call
            dfs(adjNode, adj, mp, result);

            // remove child after returning (backtracking)
            trie.remove(adjNode, 31);
        }
    }

    // -------- MAIN FUNCTION --------
    vector<int> maxGeneticDifference(
        vector<int>& parents,
        vector<vector<int>>& queries
    ){
        int n = parents.size();
        vector<vector<int>> adj(n);

        // build tree and find root
        int root = -1;
        for(int i = 0; i < n; i++){
            if(parents[i] == -1){
                root = i;
            }
            else{
                adj[parents[i]].push_back(i);
            }
        }

        // group queries by node
        map<int, vector<pair<int, int>>> mp;
        for(int i = 0; i < queries.size(); i++){
            int node = queries[i][0];
            int p    = queries[i][1];
            mp[node].push_back({i, p});
        }

        // insert root into trie
        trie.insert(root, 31);

        vector<int> result(queries.size(), 0);

        // start DFS
        dfs(root, adj, mp, result);

        return result;
    }
};
