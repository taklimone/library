#include <vector>
#include <utility>
using namespace std;

template <typename T>
struct edge {
    int to;
    T weight;
};

template <typename T>
pair<T, int> dfs(const vector<vector<edge<T>>> &G, int v, int par) {
    pair<T, int> farthest(0, v);
    for(edge<T> e : G[v]) {
        if(e.to == par) continue;
        auto far = dfs(G, e.to, v);
        far.first += e.weight;
        if(farthest.first < far.first) farthest = far;
    }
    return farthest;
}

template <typename T>
T diameter(const vector<vector<edge<T>>> &G) {
    auto far1 = dfs<T>(G, 0, -1);
    auto far2 = dfs<T>(G, far1.second, -1);
    return far2.first;
}