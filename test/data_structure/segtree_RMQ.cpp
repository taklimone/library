#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A

#include "data_structure/segtree.hpp"

#include <iostream>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    
    const int INF = (1LL << 31) - 1;
    std::vector<int> gen(n, INF);

    auto op = [](const int a, const int b){ return min(a, b); };
    tklib::Segtree<int, decltype(op)> st(gen.begin(), gen.end(), INF, op);

    while(q--) {
        int c, x, y; cin >> c >> x >> y;
        if(c == 0) {
            st.update(x, y);
        } else {
            cout << st.query(x, y + 1) << endl;
        }
    }
}