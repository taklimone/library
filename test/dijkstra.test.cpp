#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A

#include "../Graph/dijkstra.cpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int V, E, r;
    cin >> V >> E >> r;
    vector<vector<pair<int, int>>> G(V);
    while(E--) {
        int s, t, d;
        cin >> s >> t >> d;
        G[s].emplace_back(t, d);
    }

    auto dist = dijkstra<int>(G, r);
    for(int i=0; i<V; ++i) {
        if(dist[i] == numeric_limits<int>::max()) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }
}