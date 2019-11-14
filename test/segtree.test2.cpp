#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B

#include "../DataStructure/segtree.cpp"

#include <iostream>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    segtree<int> st(n, 0);

    while(q--) {
        int c, x, y; cin >> c >> x >> y;
        if(c == 0) {
            st.update(x, st[x] + y);
        } else {
            cout << st.query(x, y + 1) << endl;
        }
    }
}