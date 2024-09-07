#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to mark non-prime numbers in the sieve array
void simpleSieve(int limit, vector<int> &prime) {
    // Create a boolean array "isPrime[0..limit]" and initialize all entries as true.
    // A value in isPrime[i] will be false if i is not a prime.
    vector<bool> isPrime(limit + 1, true);

    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            // Marking multiples of p as false
            for (int i = p * p; i <= limit; i += p)
                isPrime[i] = false;
        }
    }

    // Collecting all prime numbers till 'limit'
    for (int p = 2; p <= limit; p++) {
        if (isPrime[p]) {
            prime.push_back(p);
        }
    }
}

// Function to generate all primes in range [m, n] using segmented sieve
void segmentedSieve(int m, int n) {
    // Step 1: Find all primes up to the square root of n using the basic sieve
    int limit = floor(sqrt(n)) + 1;
    vector<int> prime;
    simpleSieve(limit, prime);

    // Step 2: Create a boolean array "isPrime" for the range [m, n]
    vector<bool> isPrime(n - m + 1, true);

    // Mark non-prime numbers in range [m, n]
    for (int i = 0; i < prime.size(); i++) {
        int currentPrime = prime[i];

        // Find the minimum number in the range [m, n] that is a multiple of currentPrime
        int base = (m / currentPrime) * currentPrime;
        if (base < m) base += currentPrime;

        // Mark multiples of currentPrime in range [m, n] as false
        for (int j = base; j <= n; j += currentPrime) {
            if (j != currentPrime)  // If it's the prime itself, don't mark it
                isPrime[j - m] = false;
        }
    }

    // Special case for when m is 1, since 1 is not a prime number
    if (m == 1) isPrime[0] = false;

    // Step 3: Print all primes in range [m, n]
    for (int i = 0; i <= n - m; i++) {
        if (isPrime[i]) {
            cout << (i + m) << endl;
        }
    }
}

int main() {
    int t;
    cin >> t;  // Number of test cases

    while (t--) {
        int m, n;
        cin >> m >> n;

        // Generating all prime numbers in the range [m, n]
        segmentedSieve(m, n);

        if (t) cout << endl;  // Separate test cases with an empty line
    }

    return 0;
}