#include <queue>
#include <vector>
using namespace std;

template <typename T>
struct edge{
    int from;
    int to;
    T cost;
};

template <typename T>
vector<edge<T>> prim(const vector<vector<pair<int, T>>> &G) {
    vector<bool> used(G.size(), false);
    auto compare = [](const edge<T> &lhs, const edge<T> &rhs){ return lhs.cost > rhs.cost; };
    priority_queue<edge<T>, vector<edge<T>>, decltype(compare)> que(compare);
    
    used[0] = true;
    for(auto neighbor : G[0]) que.push({0, neighbor.first, neighbor.second});

    vector<edge<T>> edgelist;
    while(!que.empty()) {
        edge<T> e = que.top(); que.pop();
        if(used[e.to]) continue;
        
        edgelist.push_back(e);
        used[e.to] = true;
        for(auto neighbor : G[e.to]) que.push({e.to, neighbor.first, neighbor.second});
    }

    return edgelist;
}
