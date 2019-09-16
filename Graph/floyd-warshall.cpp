#include <limits>
#include <vector>
using namespace std;

template <typename T>
void floyd_warshall(vector<vector<T>> &dist) {
    const T INF = numeric_limits<T>::max();
    size_t V = dist.size();
    for(size_t k = 0; k < V; ++k) {
        for(size_t i = 0; i < V; ++i) {
            for(size_t j = 0; j < V; ++j) {
                if(dist[i][k] == INF || dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}