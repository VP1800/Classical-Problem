#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

#define GI ({int y; scanf("%d", &y); y;})
#define REP(i, N) for(int i = 0; i < N; i++)
#define REPV(i, ar) for(int i = 0; i < ar.size(); i++)
#define pb push_back
#define PDD pair<double, double>
#define LINF (1e18)
#define INF (1<<30)

using namespace std;

typedef pair<PDD, PDD> line;
vector<PDD> V;

#define X1 first.first
#define Y1 first.second 
#define X2 second.first
#define Y2 second.second

// Operator overloading for outputting lines
ostream& operator<<(ostream& o, line a) {
    o << a.X1 << " , " << a.Y1 << " to " << a.X2 << " " << a.Y2 << endl;
    return o;
}

// Function to find the intersection of two lines
PDD inter(const line A, const line B) {
    double a = A.X1, b = A.Y1, c = A.X2, d = A.Y2;
    double m = B.X1, n = B.Y1, p = B.X2, q = B.Y2;

    assert(fabs(a - c) > 1e-9);

    if (fabs(m - p) < 1e-9) {
        double x = m;
        double y = b + (x - a) * (b - d) * 1.0 / (a - c);
        return PDD(x, y);
    }

    double s1 = (b - d) * 1.0 / (a - c);
    double s2 = (n - q) * 1.0 / (m - p);

    assert(fabs(s1 - s2) > 1e-9);

    double x = (b - n + m * s2 - a * s1) * 1.0 / (s2 - s1);
    double y = b + (x - a) * (b - d) * 1.0 / (a - c);

    return PDD(x, y);
}

// Function to calculate the maximum based on intersections
double Max(line x) {
    REPV(i, V) {
        line t(V[i], PDD(V[i].first, V[i].second - 1.0));
        PDD pt = inter(x, t);
        assert(fabs(pt.first - V[i].first) < 1e-9);
        double y1 = V[i].second, y2 = V[i].second - 1;

        if (pt.second + 1e-6 < y2) {
            if (!i) return 0;
            PDD p1 = inter(x, line(PDD(V[i - 1].first, V[i - 1].second - 1.0), PDD(V[i].first, V[i].second - 1.0)));
            return p1.first;
        } else if (pt.second - 1e-6 > y1) {
            if (!i) return 0;
            PDD p1 = inter(x, line(V[i - 1], V[i]));
            return p1.first;
        }
    }
    return V.back().first;
}

int main() {
    int N;
    while (true) {
        N = GI;
        if (N == 0) break;

        V.clear();
        REP(i, N) {
            double a, b;
            cin >> a >> b;
            V.pb(PDD(a, b));
        }

        double ret = -1;
        REP(i, N) REP(j, N) if (j > i) {
            ret = max(ret, Max(line(V[i], V[j])));
            ret = max(ret, Max(line(V[i], PDD(V[j].first, V[j].second - 1.0))));
            ret = max(ret, Max(line(PDD(V[i].first, V[i].second - 1.0), V[j])));
            ret = max(ret, Max(line(PDD(V[i].first, V[i].second - 1.0), PDD(V[j].first, V[j].second - 1.0))));
        }

        printf("%.2lf\n", ret);
    }

    return 0;
}