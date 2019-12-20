#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H

#include "data_structure/lazy_segtree.hpp"

#include <iostream>
#include <functional>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    auto init = vector<int>(n, 0);
    tklib::LazySegtree<int, int> st(init.begin(), init.end(), (1LL << 31) - 1, 0,
    [](int a,  int b){ return min(a, b); },
    plus<int>(), plus<int>());

    while(q--) {
        int c, s, t; cin >> c >> s >> t;
        if(c == 0) {
            int x; cin >> x;
            st.update(s, t + 1, x);
        } else {
            cout << st.get(s, t + 1) << '\n';
        }
    }
}