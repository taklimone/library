#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A

#include "graph/kruskal.hpp"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    vector<tuple<int, int, int>> G;
    while(E--) {
        int s, t, w;
        cin >> s >> t >> w;
        G.emplace_back(s, t, w);
    }

    auto edgelist = tklib::kruskal(V, G);
    int weight_sum = 0;
    for(auto e : edgelist) weight_sum += get<2>(e);
    cout << weight_sum << '\n';
}
