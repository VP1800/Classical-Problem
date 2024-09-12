#include <deque>
#include <iostream>
#include <string>
using namespace std;
void apply_move(deque<char>& state, char c) {
    state.push_back(c);
  top:
    const int l = state.size();
    if (l >= 2 && state[0] == 'R') {
        // cancel RR and RT at the beginning of the string
        state.erase(state.begin(), state.begin() + 2);
        goto top;
    }
    if (l >= 2 && state[0] == 'T' && state[1] == 'T') {
        // replace TT with R at the beginning of the string
        state.pop_front();
        state[0] = 'R';
        goto top;
    }
    if (l >= 2 && state[l - 1] == 'R' && state[l - 2] == 'R') {
        // cancel RR at the end of the string
        state.resize(l - 2);
        goto top;
    }
    if (l >= 3 && state[l - 1] == 'T' &&
        state[l - 2] == 'T' && state[l - 3] == 'T') {
        // cancel TTT at the end of the string
        state.resize(l - 3);
        goto top;
    }
}
void do_testcase() {
    string s;
    getline(cin, s);  // # of moves, which is redundant
    getline(cin, s);
    deque<char> state;
    for (const char c : s) {
        if (c == 'R') {
            apply_move(state, 'R');
        } else {
            apply_move(state, 'T');
            apply_move(state, 'R');
        }
    }
    int moves = 0;
    while (!state.empty()) {
        if (state.back() == 'R') {
            apply_move(state, 'R');
        } else {
            apply_move(state, 'T');
            apply_move(state, 'R');
        }
        ++moves;
    }
    cout << moves << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    for (int i = 0; i < 10; i++) {
        do_testcase();
    }
}