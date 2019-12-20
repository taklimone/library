#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E

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
        int c; cin >> c ;
        if(c == 0) {
            int s, t; long long x;
            cin >> s >> t >> x;
            st.update(s - 1, t, x);
        } else {
            int i; cin >> i;
            cout << st[i - 1] << '\n';
        }
    }
}