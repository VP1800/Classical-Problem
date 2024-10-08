#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool a[20][20];
bool b[20][20];
vector<pair<int, int> > moves;
vector<pair<int, int> > bestmoves;

void flip(int x, int y) {
    moves.push_back(make_pair(x, y));
    b[x][y] = !b[x][y];
    if (x + 1 < 20) b[x + 1][y] = !b[x + 1][y];
    if (y + 1 < 20) b[x][y + 1] = !b[x][y + 1];
    if (x > 0) b[x - 1][y] = !b[x - 1][y];
    if (y > 0) b[x][y - 1] = !b[x][y - 1];
}

int main() {
    int X, Y, i, j, k;
    while (true) {
        scanf("%d %d", &X, &Y);
        getchar();
        if (X == 0 && Y == 0) return 0;
        
        char s[20];
        for (i = 0; i < Y; i++) {
            fgets(s, sizeof(s), stdin);
            for (j = 0; j < X; j++)
                a[j][i] = (s[j] == '0');
        }

        int minflips = 1000;
        for (i = 0; i < (1 << X); i++) {
            memcpy(b, a, sizeof(b));
            moves.clear();
            int flips = 0;
            for (j = 0; j < X; j++)
                if ((1 << j) & i) {
                    flips++;
                    flip(j, 0);
                }
            for (j = 1; j < Y; j++)
                for (k = 0; k < X; k++)
                    if (b[k][j - 1]) {
                        flip(k, j);
                        flips++;
                    }

            bool B = true;
            for (j = 0; j < X; j++)
                if (b[j][Y - 1]) {
                    B = false;
                    break;
                }

            if (B && flips < minflips) {
                minflips = flips;
                bestmoves = moves;
            }
        }

        if (minflips == 1000)
            printf("-1\n");
        else {
            printf("%d\n", (int)bestmoves.size());
            for (i = 0; i < (int)bestmoves.size(); i++)
                printf("%d %d\n", bestmoves[i].first + 1, bestmoves[i].second + 1);
        }
    }
    return 0;
}