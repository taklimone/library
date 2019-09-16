#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

template <typename T>
struct edge{
    int from;
    int to;
    T weight;
};

template <typename T>
vector<T> bellman_ford(int V, const vector<edge<T>> &E, int source) {
    const T INF = numeric_limits<T>::max();
    vector<T> dist(V, INF);
    dist[source] = 0;

    // relax
    for(int i = 1; i < V; ++i) {
        for(edge<T> e : E) {
            if(dist[e.from] == INF) continue;
            dist[e.to] = min(dist[e.to], dist[e.from] + e.weight);
        }
    }

    // negative-weight cycle check
    for(edge<T> e : E) {
        if(dist[e.from] == INF) continue;
        if(dist[e.to] > dist[e.from] + e.weight) return vector<T>();
    }

    return dist;
}
