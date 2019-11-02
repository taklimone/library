#include "../DataStructure/union-find.cpp"

#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
struct edge{
    int from;
    int to;
    T cost;
};

template <typename T>
vector<edge<T>> kruskal(size_t V, vector<edge<T>> &G) {
    sort(begin(G), end(G), 
    [](const edge<T> &lhs, const edge<T> &rhs){ return lhs.cost < rhs.cost; });
    union_find uf(V);

    vector<edge<T>> edgelist;
    for(auto e : G) {
        if(uf.unite(e.from, e.to)) {
            edgelist.push_back(e);
        }
    }

    return edgelist;
}
