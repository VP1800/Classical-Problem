#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;
struct Chain {
    int front;
    int back;
    int other(int front_or_back) const {
        return front_or_back == front ? back : front;
    }
};
void merge(vector<Chain*>& chains, int to_vertex, int from_vertex) {
    auto& to_chain = chains[to_vertex];
    auto& from_chain = chains[from_vertex];
    if (to_chain->back == to_vertex) {
        swap(to_chain->front, to_chain->back);
    }
    if (from_chain->front == from_vertex) {
        swap(from_chain->front, from_chain->back);
    }
    // to_vertex == to_chain->front && from_vertex == from_chain->back
    // link the two chains, from_vertex---to_vertex
    to_chain->front = from_chain->front;
    chains[to_chain->front] = to_chain;
}
void do_testcase() {
    int n, m; cin >> n >> m;
    // neighbour sets
    vector<unordered_set<int>> potential(n);
    vector<unordered_set<int>> actual(n);
    vector<Chain> chains(n);
    for (int i = 0; i < m + n; i++) {
        int a, b; cin >> a >> b; a--; b--;
        potential[a].insert(b);
        potential[b].insert(a);
    }
    vector<Chain*> chain_of(n);
    queue<int> q;  // can also be a stack or whatever
    for (int i = 0; i < n; i++) {
        chains[i].front = i;
        chains[i].back = i;
        chain_of[i] = &chains[i];
        if (potential[i].size() == 2) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        const int i = q.front();
        q.pop();
        if (actual[i].size() == 2) continue;
        if (actual[i].size() + potential[i].size() == 2) {
            const int nbr = *potential[i].begin();
            merge(chain_of, i, nbr);
            q.push(chain_of[i]->front);
            q.push(chain_of[i]->back);
            actual[i].insert(nbr);
            actual[nbr].insert(i);
            potential[nbr].erase(i);
            potential[i].erase(nbr);
            if (actual[nbr].size() == 2 && !potential[nbr].empty()) {
                for (const auto p : potential[nbr]) {
                    potential[p].erase(nbr);
                    q.push(p);
                }
                potential[nbr].clear();
            }
        } else if (actual[i].size() == 1) {
            const int other = chain_of[i]->other(i);
            if (actual[other].size() == 1 &&
                potential[other].size() > 1 &&
                potential[i].count(other)) {
                potential[i].erase(other);
                potential[other].erase(i);
                q.push(i);
                q.push(other);
            }
        }
    }
    vector<int> result = {0, *actual[0].begin()};
    for (int i = 2; i < n; i++) {
        const int last = result[i-1];
        const int secondlast = result[i-2];
        for (const auto nbr : actual[last]) {
            if (nbr != secondlast) {
                result.push_back(nbr);
                break;
            }
        }
    }
    if (result.back() < result[1]) {
        reverse(result.begin() + 1, result.end());
    }
    cout << result[0] + 1;
    for (int i = 1; i < n; i++) {
        cout << ' ' << result[i] + 1;
    }
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    int d; cin >> d;
    while (d--) do_testcase();
}