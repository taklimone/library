#ifndef TKLIB_BELLMANN_FORD_HPP
#define TKLIB_BELLMANN_FORD_HPP

#include <vector>
#include <limits>
#include <algorithm>
#include <tuple>

namespace tklib {

template <typename T>
auto bellmanFord(int V, const std::vector<std::tuple<int, int, T>> &G, int source) {
    const T INF = std::numeric_limits<T>::max();
    std::vector<T> dist(V, INF);
    dist[source] = 0;

    auto relax = [&]() {
        bool updated = false;
        for(auto edge : G) {
            int from, to;
            T weight;
            std::tie(from, to, weight) = edge;
            if(dist[from] == INF) continue;
            if(dist[to] > dist[from] + weight) {
                updated = true;
                dist[to] = dist[from] + weight;
            }
        }
        return updated;
    };

    // relax
    for(int i = 1; i < V; ++i) relax();

    // negative-weight cycle check
    if(relax()) dist.clear();

    return dist;
}

} // namespace tklib

#endif // TKLIB_BELLMANN_FORD_HPP
