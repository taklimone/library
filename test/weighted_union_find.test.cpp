#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B

#include "../DataStructure/weighted_union_find.cpp"

#include <iostream>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    weighted_union_find<int> uf(n);

    while(q--){
        int k; cin >> k;
        if(k == 0) {
            int x, y, z;
            cin >> x >> y >> z;
            uf.unite(x, y, z);
        } else {
            int x, y;
            cin >> x >> y;
            if(uf.find(x) != uf.find(y)) cout << '?' << endl;
            else cout << uf.diff(x, y) << endl;
        }
    }
}