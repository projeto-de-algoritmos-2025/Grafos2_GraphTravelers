#include <bits/stdc++.h>
using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {

    int tam = times.size();
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < tam; i++){
        adj[times[i][0]].push_back({times[i][1], times[i][2]});
    }

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    vector<int> delay(n, INT_MAX);

    pq.push({0, k});
    delay[k] = 0;

    int u, v, weight, inner_sum;
    while(!pq.empty()){

        u = pq.top()[1];
        pq.pop();

        for(auto x : adj[u]){
            v = x.first;
            weight = x.second;

            inner_sum = delay[u] + weight;
            if(delay[v] > inner_sum){
                delay[v] = inner_sum;
                pq.push({delay[v], v});

            }
        }
    }

    sort(delay.begin(), delay.end(), [](int a, int b){
        return a > b;
    });

    return delay[0];
}