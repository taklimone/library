#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D

#include "data_structure/lazy_segtree.hpp"

#include <iostream>

int main() {
    int n, q;
    cin >> n >> q;
    lazy_segtree<int, int> st(n, (1LL << 31) - 1, -1,
    [](int a, int b){ return min(a, b); },
    [](int a, int b){ return b; },
    [](int a, int b){ return b; }
    );

    while(q--) {
        int c; cin >> c;
        if(c == 0) {
            int s, t, x; cin >> s >> t >> x;
            st.update(s, t + 1, x);
        } else {
            int i; cin >> i;
            cout << st[i]<< endl;
        }
    }
}