#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B

#include "data_structure/segtree.hpp"

#include <iostream>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    tklib::Segtree<int> st(n, 0);

    while(q--) {
        int c, x, y; cin >> c >> x >> y;
        if(c == 0) {
            st.update(x, st[x] + y);
        } else {
            cout << st.query(x, y + 1) << endl;
        }
    }
}