#ifndef TKLIB_KRUSKAL_HPP
#define TKLIB_KRUSKAL_HPP

#include "data_structure/union_find.hpp"
#include <algorithm>
#include <vector>
#include <tuple>

namespace tklib {

template <typename T>
auto kruskal(std::size_t V, std::vector<std::tuple<int, int, T>> &G) {
    using edge_type = std::tuple<int, int, T>;

    std::sort(begin(G), end(G), 
    [](const edge_type &lhs, const edge_type &rhs)
    { return std::get<2>(lhs) < std::get<2>(rhs); });
    
    tklib::UnionFind uf(V);
    std::vector<edge_type> edgelist;

    for(edge_type &edge : G) {
        if(uf.unite(std::get<0>(edge), std::get<1>(edge))) {
            edgelist.push_back(edge);
        }
    }

    return edgelist;
}

} // namespace tklib

#endif // TKLIB_KRUSKAL_HPP
