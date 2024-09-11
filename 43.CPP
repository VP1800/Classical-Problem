#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>   // For scanf, printf
#include <cstring>  // For memset
#include <algorithm> // For std::max
using namespace std;

int N, M;
int pages[500]; // Array to store the number of pages per book

// Function to check if a certain maximum workload `x` can be distributed among M people
bool ok(long long x) {
    int next = 0; // The next book to assign
    for (int i = 0; i < M; i++) {
        long long sum = 0;
        do {
            sum += pages[next];
            if (sum <= x)
                next++;
        } while (next < N && sum <= x);
        if (next == N && sum <= x)
            return true; // Successfully assigned all books
    }
    return false; // Couldn't assign all books
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("books.in", "r", stdin);
    freopen("books.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t); // Read number of test cases
    int books[500];  // Array to store the number of books each person gets
    int work[500][500]; // Array to store the work assignments

    while (t--) {
        scanf("%d %d", &N, &M); // Read number of books (N) and number of people (M)
        memset(books, 0, sizeof(books)); // Initialize the books array

        long long total = 0;
        int _m = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d", pages + i); // Read number of pages in each book
            total += pages[i]; // Calculate total pages
            _m = max(_m, pages[i]); // Find the book with the most pages
        }

        // Calculate the initial bounds for binary search
        long long l = max((total + M - 1) / M, (long long)_m);
        long long u = total;

        // Perform binary search to find the minimum maximum workload
        while (u > l) {
            long long m = (l + u) / 2;
            if (ok(m))
                u = m;
            else
                l = m + 1;
        }

        // Distribute the books among M people with the minimum workload found
        int next = N - 1;
        for (int i = M - 1; i >= 0; i--) {
            long long sum = 0;
            for (;;) {
                sum += pages[next];
                if (sum <= l && next >= i)
                    work[i][books[i]++] = pages[next--]; // Assign books
                else
                    break;
            }
        }

        // Output the result
        for (int i = 0; i < M - 1; i++) {
            for (int j = books[i] - 1; j >= 0; j--)
                printf("%d ", work[i][j]);
            printf("/ ");
        }
        for (int i = books[M - 1] - 1; i > 0; i--)
            printf("%d ", work[M - 1][i]);
        printf("%d\n", work[M - 1][0]);
    }

    return 0;
}