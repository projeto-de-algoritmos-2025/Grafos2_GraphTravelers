#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        
        vector<vector<pair<int,int>>> adj(n+1);
        for(auto node : times){
            adj[node[0]].push_back({node[1], node[2]});
        }

        vector<int> delay(n+1, INT_MAX);

        int inner_sum;
        delay[k]=0;
        pq.push({0, k});
        while(!pq.empty()){

            pair<int,int> current=pq.top();
            pq.pop();

            if(current.first > delay[current.second]) continue;
            for(auto neighbour : adj[current.second]){
                inner_sum = delay[current.second] + neighbour.second;
                if(delay[neighbour.first] > inner_sum){
                    delay[neighbour.first] = inner_sum;
                    pq.push({delay[neighbour.first], neighbour.first});
                }

            }
        }

        int minimum_time =- 1;
        for(int i = 1; i <= n; i++){
            if(delay[i] == INT_MAX) return -1;
            minimum_time= max(minimum_time, delay[i]);
        }

        return minimum_time;
    }
};