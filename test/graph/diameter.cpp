#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A

#include "graph/diameter.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;
    vector<vector<edge<int>>> G(n, vector<edge<int>>());
    for(int i = 1; i < n; ++i) {
        int s, t, w;
        cin >> s >> t >> w;
        G[s].push_back({t, w});
        G[t].push_back({s, w});
    }
    cout << diameter<int>(G) << endl;
}