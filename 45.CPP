#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
void do_testcase() {
    int M; cin >> M;
    int mdist;
    vector<int> config;
    vector<int> lookup(M * M * M);
    for (int z = 0 ; z < M; z++) {
        for (int y = 0; y < M; y++) {
            for (int x = 0; x < M; x++) {
                int value; cin >> value;
                if (value == 0) {
                    mdist = abs(x - (M-1)) + abs(y - (M-1)) + abs(z - (M-1));
                    value = M * M * M;
                }
                value--;
                lookup[value] = config.size();
                config.push_back(value);
            }
        }
    }
    int transpositions = 0;
    for (int i = 0; i < M * M * M; i++) {
        if (lookup[i] == i) continue;
        int i_val = config[i];
        swap(config[i], config[lookup[i]]);
        swap(lookup[i], lookup[i_val]);
        ++transpositions;
    }
    if ((transpositions + mdist) % 2 == 0) {
        cout << "Puzzle can be solved.\n";
    } else {
        cout << "Puzzle is unsolvable.\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    int N; cin >> N;
    while (N--) {
        do_testcase();
    }
}