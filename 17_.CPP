#include <ctime>
#include <iostream>
using namespace std;
constexpr unsigned MODULUS = 4000000007;
unsigned pmod(unsigned base, int exponent) {
    int mask = 1;
    unsigned long long result = 1;
    unsigned long long p = base;
    while (exponent) {
        if (exponent & mask) {
            result = (result * p) % MODULUS;
            exponent &= ~mask;
        }
        p = (p * p) % MODULUS;
        mask <<= 1;
    }
    return result;
}
int main() {
    unsigned a;
    cin >> a;
    auto x = pmod(a, (MODULUS + 1) / 4);
    time_t t = x > MODULUS / 2 ? MODULUS - x : x;
    char result[27] = {};
    strftime(result, 27, "%c", gmtime(&t));
    cout << result << endl;
}