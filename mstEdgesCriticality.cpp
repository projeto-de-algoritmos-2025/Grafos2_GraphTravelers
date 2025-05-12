#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    class UnionFind{
    public:
        int V;
        vector<pair<int, int>> t; // first = root, second = tree size
        UnionFind(int V){
            this->V = V;
            t = vector<pair<int, int>>(V);
        }
        void init(){
            for (int i = 0; i < V; i++){
                t[i].first = i;
                t[i].second = 1;
            }
        }
        int find(int v){
            int root = v;
            while (root != t[root].first){
                root = t[root].first;
            }
            return root;
        }
        void _union(int va, int vb){
            if (t[va].second < t[vb].second){
                t[va].first = vb;
                t[vb].second = t[va].second;
            }
            else{
                t[vb].first = va;
                t[va].second = t[vb].second;
            }
        }
    };

    int evaluate_edge_kruskal(vector<vector<int>> &edges, int n, int subject, bool include){

        vector<vector<int>> mst(0);
        int total_sum = 0;

        UnionFind uf(n);
        uf.init();

        int mst_size = 0;
        int edges_size = edges.size();

        if (include == true){
            uf._union(uf.find(edges[subject][0]), uf.find(edges[subject][1]));
            mst.push_back(edges[subject]);
            total_sum += edges[subject][2];
            mst_size++;
        }

        for (int i = 0; i < edges_size && mst.size() < n; i++){

            if (i == subject)
                continue;
            int v = uf.find(edges[i][0]);
            int w = uf.find(edges[i][1]);
            if (v != w)
            {
                uf._union(v, w);
                mst.push_back(edges[i]);
                total_sum += edges[i][2];
                mst_size++;
            }
        }

        for (int i = 1; i < n; i++)
            if (uf.find(0) != uf.find(i)) return INT_MAX;

        return total_sum;
    }

    int kruskal_core(vector<vector<int>> &edges, int n){

        vector<vector<int>> mst(0);
        int total_sum = 0;

        UnionFind uf(n);
        uf.init();

        int mst_size = 0;
        int edges_size = edges.size();
        for (int i = 0; i < edges_size && mst.size() < n; i++){
            int v = uf.find(edges[i][0]);
            int w = uf.find(edges[i][1]);
            if (v != w){
                uf._union(v, w);
                mst.push_back(edges[i]);
                total_sum += edges[i][2];
                mst_size++;
            }
        }

        return total_sum;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges){

        vector<int> critical(0), pseudo_critical(0);

        int index = 0;
        for (auto &e : edges){
            e.push_back(index++);
        }

        sort(edges.begin(), edges.end(), [](vector<int> a, vector<int> b){ 
            return a[2] < b[2]; 
        });

        int current, 
            edges_size = edges.size(), 
            mst_length = kruskal_core(edges, n);

        for (int i = 0; i < edges.size(); i++){

            current = evaluate_edge_kruskal(edges, n, i, false);
            
            if (mst_length < current) critical.push_back(edges[i][3]);
            else{
                if (mst_length == evaluate_edge_kruskal(edges, n, i, true))
                    pseudo_critical.push_back(edges[i][3]);
            }
        }

        return {critical, pseudo_critical};
    }
};