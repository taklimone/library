#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

template <typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> &G, int source) {
    const T INF = numeric_limits<T>::max();
    using P = pair<T, int>;

    vector<T> dist(G.size(), INF);
    dist[source] = 0;

    priority_queue<P, vector<P>, greater<P>> que;
    que.emplace(0, source);

    while(!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;
        if(dist[v] < p.first) continue;

        for(auto edge : G[v]) {
            if(dist[edge.first] > dist[v] + edge.second) {
                dist[edge.first] = dist[v] + edge.second;
                que.emplace(dist[edge.first], edge.first);
            }
        }
    }

    return dist;
}