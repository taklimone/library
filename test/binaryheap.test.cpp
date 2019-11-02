#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_2_C

#include "../DataStructure/binaryheap.cpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<binaryheap<int>> que(n, binaryheap<int>());
    while(q--) {
        int k, t; std::cin >> k >> t;
        if(k == 0) {
            int x; cin >> x;
            que[t].insert(x);
        } else if(k == 1) {
            if(que[t].size() > 0) cout << que[t].maximum() << endl;
        } else {
            if(que[t].size() > 0) que[t].extract_max();
        }
    }
}