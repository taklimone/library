#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A

#include "../DataStructure/binaryheap.cpp"

#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> &G, int source) {
    const T INF = numeric_limits<T>::max();
    using P = pair<T, int>;

    vector<T> dist(G.size(), INF);
    dist[source] = 0;

    binaryheap<P, greater<P>> que;
    que.insert(P(0, source));

    while(que.size() > 0) {
        P p = que.extract_max();
        int v = p.second;
        if(dist[v] < p.first) continue;

        for(auto edge : G[v]) {
            if(dist[edge.first] > dist[v] + edge.second) {
                dist[edge.first] = dist[v] + edge.second;
                que.insert(P(dist[edge.first], edge.first));
            }
        }
    }

    return dist;
}

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