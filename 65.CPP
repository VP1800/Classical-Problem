#include <iostream>
using namespace std;
int gcd(int x, int y) {
    if (x == 0) return y;
    return gcd(y % x, x);
}
int calculate(int X, int Y, int x0) {
    const int G = gcd(X, Y);
    if (x0 % G == 0) return 2;
    return 2*X*Y/G - 4*(X/G)*(Y/G) + 2*X/G + 2*Y/G;
}
int main() {
    int d; cin >> d; while (d--) {
        int X, Y, a, b; cin >> X >> Y >> a >> b; X--; Y--; a--; b--;
        if (b != 0 && b != Y) {
            swap(X, Y);
            swap(a, b);
        }
        cout << calculate(X, Y, a) << '\n';
    }
}