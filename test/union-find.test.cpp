#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A
#include "../DataStructure/union-find.cpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    
    union_find uf(n);
    while(q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c) cout << (uf.find(x) == uf.find(y) ? 1 : 0) << endl;
        else uf.unite(x, y);
    }
}