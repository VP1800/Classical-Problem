#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

int main() {
    int T, L, i, j, n;
    scanf("%d\n", &T); // Reading number of test cases
    char s[10010]; // Input string with a size limit

    while (T--) {
        fgets(s, 10010, stdin); // Use fgets instead of gets
        L = strlen(s);
        
        // Remove the newline character added by fgets
        if (s[L-1] == '\n') {
            s[L-1] = '\0';
            L--;
        }

        i = 0;
        j = 1;
        n = 0;
        while (i < L && j < L && n < L) {
            if (s[(i + n) % L] == s[(j + n) % L])
                n++;
            else {
                if (s[(i + n) % L] < s[(j + n) % L])
                    j += n + 1;
                else
                    i += n + 1;
                if (i == j)
                    j = i + 1;
                n = 0;
            }
        }
        printf("%d\n", (i < j ? i : j) + 1);
    }
    return 0;
}