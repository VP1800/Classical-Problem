#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
struct Node {
    int segment_id;
    static const int EMPTY = 0;
    static const int RECURSIVE = -1;
};
struct NodeInterval {
    int begin;
    int end;
    NodeInterval left() const {
        return {begin, (begin + end) / 2};
    }
    NodeInterval right() const {
        return {(begin + end) / 2, end};
    }
};
struct Segtree {
    vector<Node> nodes;
    const NodeInterval root_interval;
    Segtree(int N) : nodes(4*N), root_interval{0, N} {}

    template <class Cb>
    void query(int y1, int y2, int node, NodeInterval node_interval, Cb cb) {
        if (nodes[node].segment_id == Node::EMPTY) return;
        if (nodes[node].segment_id > 0) {
            cb(nodes[node].segment_id);
            return;
        }
        const auto left_interval = node_interval.left();
        if (left_interval.begin < y2 && left_interval.end > y1) {
            query(y1, y2, 2*node, left_interval, cb);
        }
        const auto right_interval = node_interval.right();
        if (right_interval.begin < y2 && right_interval.end > y1) {
            query(y1, y2, 2*node + 1, right_interval, cb);
        }
    }

    void update(int y1, int y2, int node,
                NodeInterval node_interval, int segment_id) {
        if (node_interval.begin >= y1 && node_interval.end <= y2) {
            // base case: update the whole thing
            nodes[node].segment_id = segment_id;
            return;
        }
        const auto left_interval = node_interval.left();
        const auto right_interval = node_interval.right();
        if (nodes[node].segment_id > 0) {
            // propagate any lazy value that lives here
            nodes[2*node].segment_id = nodes[node].segment_id;
            nodes[2*node + 1].segment_id = nodes[node].segment_id;
        }
        nodes[node].segment_id = Node::RECURSIVE;
        if (left_interval.begin < y2 && left_interval.end > y1) {
            update(y1, y2, 2*node, left_interval, segment_id);
        }
        if (right_interval.begin < y2 && right_interval.end > y1) {
            update(y1, y2, 2*node + 1, right_interval, segment_id);
        }
    }
};
int main() {
    ios::sync_with_stdio(false);
    int d; cin >> d;
    while (d--) {
        int n; cin >> n;
        vector<tuple<int, int, int>> segments;
        int N = 0;
        for (int i = 0; i < n; i++) {
            int y1, y2, x; cin >> y1 >> y2 >> x;
            segments.emplace_back(x, 2 * y1, 2 * y2 + 1);
            N = max(N, 2 * y2 + 1);
        }
        sort(segments.begin(), segments.end());
        Segtree segtree(N);
        // hv[i][j] -> interval j is to the right of interval i, and they are
        // horizontally visible from each other. (Note that this is 0-based but
        // 1-based indices are stored inside the segment tree.)
        vector<vector<int>> hv(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            const auto& segment = segments[i];
            segtree.query(get<1>(segment), get<2>(segment),
                          1, segtree.root_interval,
                          [&hv, i](int prev) { hv[prev - 1][i] = 1; });
            segtree.update(get<1>(segment), get<2>(segment),
                           1, segtree.root_interval, i + 1);
        }
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!hv[i][j]) continue;
                for (int k = i + 1; k < j; k++) {
                    result += (hv[i][k] && hv[k][j]);
                }
            }
        }
        cout << result << '\n';
    }
}