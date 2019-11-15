#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E

#include "../DataStructure/lazy_segtree.cpp"

#include <iostream>

int main() {
    int n, q;
    cin >> n >> q;
    lazy_segtree<long long, long long> st(n, 0, 0,
    plus<long long>(), plus<long long>(), plus<long long>(), multiplies<long long>());

    while(q--) {
        int c; cin >> c ;
        if(c == 0) {
            int s, t; long long x;
            cin >> s >> t >> x;
            st.update(s - 1, t, x);
        } else {
            int i; cin >> i;
            cout << st[i - 1] << endl;
        }
    }
}