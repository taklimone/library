#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A

#include "data_structure/union_find.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    
    tklib::UnionFind uf(n);
    while(q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c) cout << (uf.find(x) == uf.find(y) ? 1 : 0) << '\n';
        else uf.unite(x, y);
    }
}