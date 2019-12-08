#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A

#include "graph/kruskal.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    vector<edge<int>> G;
    while(E--) {
        int s, t, w;
        cin >> s >> t >> w;
        G.push_back({s, t, w});
    }

    auto edgelist = kruskal<int>(V, G);
    int weight_sum = 0;
    for(auto e : edgelist) weight_sum += e.cost;
    cout << weight_sum << endl;
}
