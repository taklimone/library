#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I

#include "../DataStructure/lazy_segtree.cpp"

#include <iostream>

int main() {
    int n, q;
    cin >> n >> q;
    lazy_segtree<int, int> st(n, 0, -1001,
    plus<long long>(), [](int, int b){ return b; },
    [](int, int b){ return b; }, multiplies<int>());

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