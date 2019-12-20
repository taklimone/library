#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G

#include "data_structure/lazy_segtree.hpp"

#include <iostream>
#include <functional>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    tklib::LazySegtree<long long, long long> st(n, 0, 0,
    plus<long long>(), plus<long long>(), plus<long long>(), multiplies<long long>());

    while(q--) {
        int c, s, t; cin >> c >> s >> t;
        if(c == 0) {
            long long x; cin >> x;
            st.update(s - 1, t, x);
        } else {
            cout << st.get(s - 1, t) << '\n';
        }
    }
}