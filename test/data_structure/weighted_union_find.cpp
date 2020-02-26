#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B

#include "data_structure/weighted_union_find.hpp"

#include <iostream>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    tklib::WeightedUnionFind<int> uf(n);

    while(q--){
        int k; cin >> k;
        if(k == 0) {
            int x, y, z;
            cin >> x >> y >> z;
            uf.unite(x, y, z);
        } else {
            int x, y;
            cin >> x >> y;
            if(uf.find(x) != uf.find(y)) cout << "?\n";
            else cout << uf.diff(x, y) << '\n';
        }
    }
}