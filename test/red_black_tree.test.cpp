#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B

#include "../DataStructure/red_black_tree.cpp"

#include <iostream>
using namespace std;

int main() {
    int q; cin >> q;
    red_black_tree<int> tree;
    while(q--) {
        int k, x; cin >> k >> x;
        if(k == 0) {
            tree.insert(x);
            cout << tree.size() << '\n';
        } else if(k == 1) {
            cout << (tree.contains(x) ? 1 : 0) << '\n';
        } else {
            tree.remove(x);
        }
    }
}