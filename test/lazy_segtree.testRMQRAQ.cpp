#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H

#include "../DataStructure/lazy_segtree.cpp"

#include <iostream>

int main() {
    int n, q;
    cin >> n >> q;
    auto init = vector<int>(n, 0);
    lazy_segtree<int, int> st(init, (1LL << 31) - 1, 0,
    [](int a,  int b){ return min(a, b); },
    plus<int>(), plus<int>());

    while(q--) {
        int c, s, t; cin >> c >> s >> t;
        if(c == 0) {
            long long x; cin >> x;
            st.update(s, t + 1, x);
        } else {
            cout << st.get(s, t + 1) << endl;
        }
    }
}