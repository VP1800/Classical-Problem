#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
constexpr int V = 60;
constexpr int F = 32;
constexpr int E = V + F - 2;
int raw_data[F][6] = {
    { 0,  1,  2,  3,  4, -1},  // P0
    { 5,  6,  7,  8,  9, -1},  // P1
    {10, 11, 12, 13, 14, -1},  // P2
    {15, 16, 17, 18, 19, -1},  // P3
    {20, 21, 22, 23, 24, -1},  // P4
    {25, 26, 27, 28, 29, -1},  // P5
    {30, 31, 32, 33, 34, -1},  // P6
    {35, 36, 37, 38, 39, -1},  // P7
    {40, 41, 42, 43, 44, -1},  // P8
    {45, 46, 47, 48, 49, -1},  // P9
    {50, 51, 52, 53, 54, -1},  // P10
    {55, 56, 57, 58, 59, -1},  // P11
    { 2, 15, 19, 21, 20,  3},  // H12
    { 3, 20, 24, 26, 25,  4},  // H13
    { 0,  4, 25, 29,  6,  5},  // H14
    { 0,  5,  9, 11, 10,  1},  // H15
    { 1, 10, 14, 16, 15,  2},  // H16
    { 7, 42, 41, 49, 48,  8},  // H17
    {12, 47, 46, 54, 53, 13},  // H18
    {17, 52, 51, 34, 33, 18},  // H19
    {22, 32, 31, 39, 38, 23},  // H20
    {27, 37, 36, 44, 43, 28},  // H21
    {18, 33, 32, 22, 21, 19},  // H22
    {23, 38, 37, 27, 26, 24},  // H23
    { 6, 29, 28, 43, 42,  7},  // H24
    { 8, 48, 47, 12, 11,  9},  // H25
    {13, 53, 52, 17, 16, 14},  // H26
    {40, 58, 57, 45, 49, 41},  // H27
    {45, 57, 56, 50, 54, 46},  // H28
    {30, 34, 51, 50, 56, 55},  // H29
    {30, 55, 59, 35, 39, 31},  // H30
    {35, 59, 58, 40, 44, 36},  // H31
};
struct Edge {
    int v1;
    int v2;
    friend bool operator<(Edge e1, Edge e2) {
        return (e1.v1 < e2.v1) ||
               (e1.v1 == e2.v1 && e1.v2 < e2.v2);
    }
};
struct EdgeData {
    int left;  // polygon index
    int right;
};
vector<vector<EdgeData>> edges(V, vector<EdgeData>(V, EdgeData{-1, -1}));
vector<vector<int>> adj(V);  // the adjacent vertices are given in
                             // counterclockwise order
struct FaceAdj {
    Edge e;
    int index;  // face on the other side of this edge
};
vector<vector<FaceAdj>> face_adj(F);
void compile_graph() {
    for (int i = 0; i < F; i++) {
        const auto& f = raw_data[i];
        const int sides = (f[5] == -1 ? 5 : 6);
        for (int j = 0; j < sides; j++) {
            const auto v1 = f[j];
            const auto v2 = f[(j + 1) % sides];
            const auto v3 = f[(j + 2) % sides];
            edges[v1][v2].left = i;
            edges[v2][v1].right = i;
            if (adj[v2].empty()) {
                // v3 -> v1 is counterclockwise (relative to v2)
                adj[v2].push_back(v3);
                adj[v2].push_back(v1);
            } else if (adj[v2].size() == 2) {
                if (adj[v2][0] == v1) {
                    // (v1, w) -> (v1, w, v3)
                    adj[v2].push_back(v3);
                } else if (adj[v2][0] == v3) {
                    // (v3, w) -> (v3, v1, w)
                    adj[v2].insert(adj[v2].begin() + 1, v1);
                } else if (adj[v2][1] == v1) {
                    // (w, v1) -> (w, v3, v1)
                    adj[v2].insert(adj[v2].begin() + 1, v3);
                } else {
                    // (w, v3) -> (w, v3, v1)
                    adj[v2].push_back(v1);
                }
            }
        }
    }
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            const auto& e = edges[i][j];
            if (e.left == -1) continue;
            face_adj[e.left].push_back(FaceAdj{{i, j}, e.right});
        }
    }
}
enum Color {
    BLACK,
    WHITE,
    GREEN
};
void dfs(int face, vector<Color>& color, const set<Edge>& boundary_edges) {
    if (color[face] == GREEN) return;
    color[face] = GREEN;
    // look for adjacent faces but don't cross the boundary
    for (const auto& neighbour_info : face_adj[face]) {
        if (!boundary_edges.count(neighbour_info.e)) {
            dfs(neighbour_info.index, color, boundary_edges);
        }
    }
}
void do_testcase() {
    int n; cin >> n;
    // In our graph, the edge from 0 to 5 has a hexagon on both sides, and the
    // hexagon to its left is face number 15.
    Edge last_edge = {0, 5};  // edge between two hexagons
    set<Edge> boundary_edges;
    while (n--) {
        int a; cin >> a;
        // if a is 1, proceed to the "previous" vertex in adj[last_edge.v2].
        // if a is 2, proceed to the "next".
        const auto& neighbours = adj[last_edge.v2];
        int i = 0; while (neighbours[i] != last_edge.v1) ++i;
        const auto next = neighbours[(i + 3 - a) % 3];
        last_edge.v1 = last_edge.v2;
        last_edge.v2 = next;
        boundary_edges.insert(last_edge);
    }
    // hypothetically n could be 0? problem statement is not clear
    vector<Color> color(F);
    for (int i = 0; i < F; i++) {
        if (raw_data[i][5] == -1) {
            color[i] = BLACK;
        } else {
            color[i] = WHITE;
        }
    }
    if (!boundary_edges.empty()) {
        dfs(15, color, boundary_edges);
    }
    const int b = count(color.begin(), color.end(), BLACK);
    const int w = count(color.begin(), color.end(), WHITE);
    const int g = count(color.begin(), color.end(), GREEN);
    cout << b << ' ' << w << ' ' << g << '\n';
}
int main() {
    compile_graph();
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) do_testcase();
}