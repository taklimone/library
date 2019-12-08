#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A

#include "graph/prim.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<pair<int, int>>> G(V);
    while(E--) {
        int s, t, w;
        cin >> s >> t >> w;
        G[s].emplace_back(t, w);
        G[t].emplace_back(s, w);
    }

    auto edgelist = prim<int>(G);
    int weight_sum = 0;
    for(auto e : edgelist) weight_sum += e.cost;
    cout << weight_sum << endl;
}
