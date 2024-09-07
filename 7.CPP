#include <cstdlib>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

struct point { int x, y, z; };
using face = vector<point>;
// Face-edges are oriented.
struct face_edge { int f, v, d; /* d = +/- 1 */ };

struct ray {
    point pt;
    int u;  // unit vector code, defined above
    friend bool operator==(const ray& r1, const ray& r2) {
        return r1.pt.x == r2.pt.x && r1.pt.y == r2.pt.y &&
               r1.pt.z == r2.pt.z && r1.u == r2.u;

    }
};
namespace std {
template <> struct hash<ray> {
    size_t operator()(const ray& r) const {
        const long long w = r.pt.x + (r.pt.y << 10) + (r.pt.z << 20);
        return std::hash<long long>{}((w << 3) + r.u);
    }
};
}

using lookup_table = unordered_multimap<ray, face_edge>;

int get_uvec(point p1, point p2) {
    if (p1.x < p2.x) return 1;
    if (p1.x > p2.x) return -1;
    if (p1.y < p2.y) return 2;
    if (p1.y > p2.y) return -2;
    if (p1.z < p2.z) return 3;
    return -3;
}

long long volume(point p1, point p2, point p3) {
    long long r1 = p1.x * (p2.y * p3.z - p2.z * p3.y);
    long long r2 = p2.x * (p3.y * p1.z - p3.z * p1.y);
    long long r3 = p3.x * (p1.y * p2.z - p1.z * p2.y);
    return r1 + r2 + r3;
}

// the indicated face-edge is given positive orientation
long long dfs(const vector<face>& faces, vector<int>& orientation,
              face_edge fe, lookup_table& M, int& unvisited) {
    if (orientation[fe.f]) {
        if (orientation[fe.f] != fe.d) {
            cerr << "inconsistent orientations for face " << fe.f << '\n';
            abort();
        }
        return 0;
    }
    orientation[fe.f] = fe.d;
    while (unvisited < faces.size() && orientation[unvisited]) ++unvisited;
    const auto& face = faces[fe.f];
    long long result = 0;
    for (int i = 0; i < face.size(); i++) {
        for (int d = -1; d <= 1; d += 2) {
            const auto j = (i + d + face.size()) % face.size();
            const auto u = get_uvec(face[i], face[j]);
            const auto range = M.equal_range({face[i], u});
            if (range.first == range.second) {
                cerr << "current edge not found in lookup table\n";
                abort();
            }
            for (auto it = range.first; it != range.second; ++it) {
                const auto& new_fe = it->second;
                if (new_fe.f == fe.f) continue;
                result += dfs(faces, orientation,
                              {new_fe.f, new_fe.v, -new_fe.d * fe.d * d},
                              M, unvisited);
            }
        }
        if (i > 0 && i + 1 < face.size()) {
            // add a triangle to the result
            result += fe.d * volume(face[0], face[i], face[i+1]);
        }
    }
    return result;
}

void do_testcase() {
    int F; cin >> F;
    vector<face> faces;
    vector<int> orientation;  // 0 = unassigned, +1/-1 = assigned
    face_edge initial_fe = {-1, -1, 1};
    int least_z = 2000;
    for (int i = 0; i < F; i++) {
        face face;
        int P; cin >> P;
        while (P--) {
            int x, y, z; cin >> x >> y >> z;
            face.push_back(point{x, y, z});
            if (z < least_z) {
                least_z = z;
                initial_fe.f = i;
                initial_fe.v = face.size() - 1;
            }
        }
        faces.push_back(move(face));
        orientation.push_back(0);
    }
    // build lookup table
    lookup_table M;
    for (int i = 0; i < faces.size(); i++) {
        const auto& face = faces[i];
        for (int j = 0; j < face.size(); j++) {
            const int k = (j + 1) % face.size();
            const auto u = get_uvec(face[j], face[k]);
            M.emplace(ray{face[j], u}, face_edge{i, j, +1});
            M.emplace(ray{face[k], -u}, face_edge{i, k, -1});
        }
    }
    int unvisited = 0;
    auto vol = abs(dfs(faces, orientation, initial_fe, M, unvisited));
    while (unvisited < faces.size()) {
        const face_edge fe = {unvisited, 0, 1};
        vol -= abs(dfs(faces, orientation, fe, M, unvisited));
    }
    cout << "The bulk is composed of " << vol/6 << " units.\n";
}
int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        do_testcase();
    }
}