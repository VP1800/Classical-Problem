#include <algorithm>
#include <cstdio>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
void multi_dijkstra(const vector<int>& sources,
                    const vector<vector<pair<int, int>>>& adjlist,
                    vector<int>& dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>> Q;
    vector<int> vis(dist.size(), false);
    for (int i = 0; i < sources.size(); i++) {
        Q.emplace(0, sources[i]);
        dist[sources[i]] = 0;
    }
    while (!Q.empty()) {
        const auto top = Q.top();
        Q.pop();
        const int u = top.second;
        const int d = top.first;
        if (vis[u]) continue;
        vis[u] = true;
        for (const auto& edge : adjlist[u]) {
            const int v = edge.second;
            const int weight = edge.first;
            if (d + weight >= dist[v]) continue;
            dist[v] = d + weight;
            Q.emplace(d + weight, v);
        }

    }
}
void dijkstra(const int src, const vector<vector<pair<int, int>>>& adjlist,
              const vector<int>& prev_dist, unordered_map<int, int>& rank_dist,
              int& result) {
    unordered_map<int, int> local_dist;
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>> Q;
    local_dist[src] = 0;
    Q.emplace(0, src);
    ++result;
    while (!Q.empty()) {
        const auto top = Q.top();
        Q.pop();
        const int u = top.second;
        const int d = top.first;
        if (local_dist[u] < d) continue;
        local_dist[u] = d - 1;  // avoid revisiting
        const auto it = rank_dist.find(u);
        if (it == rank_dist.end()) {
            rank_dist[u] = d;
        } else {
            it->second = min(it->second, d);
        }
        for (const auto& edge : adjlist[u]) {
            const int v = edge.second;
            const int weight = edge.first;
            if (d + weight >= prev_dist[v]) continue;
            const auto it = local_dist.find(v);
            if (it == local_dist.end()) {
                local_dist[v] = d + weight;
                result++;
            } else if (it->second <= d + weight) {
                continue;
            } else {
                it->second = d + weight;
            }
            Q.emplace(d + weight, v);
        }
    }
}
void do_testcase() {
    int V, E; scanf("%d %d", &V, &E);
    vector<vector<pair<int, int>>> adjlist(V);
    vector<int> rank(V);
    vector<int> by_rank[11];
    int max_rank = 0;
    int max_rank_cnt = 0;
    for (int i = 0; i < V; i++) {
        scanf("%d", &rank[i]);
        if (rank[i] > max_rank) {
            max_rank = rank[i];
            max_rank_cnt = 0;
        }
        if (rank[i] == max_rank) {
            max_rank_cnt++;
        }
        by_rank[rank[i]].push_back(i);
    }
    for (int i = 0; i < E; i++) {
        int a, b, t; scanf("%d %d %d", &a, &b, &t); a--; b--;
        adjlist[a].emplace_back(t, b);
        adjlist[b].emplace_back(t, a);
    }
    int result = V * max_rank_cnt;
    vector<int> prev_dist(V, 1e9);
    multi_dijkstra(by_rank[max_rank], adjlist, prev_dist);
    for (int r = max_rank - 1; r >= 1; r--) {
        unordered_map<int, int> rank_dist;
        for (const int src : by_rank[r]) {
            dijkstra(src, adjlist, prev_dist, rank_dist, result);
        }
        for (const auto& p : rank_dist) {
            prev_dist[p.first] = min(prev_dist[p.first], p.second);
        }
    }
    printf("%d\n", result);
}
int main() {
    int z; scanf("%d", &z);
    while (z--) do_testcase();
}