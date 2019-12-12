#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <vector>

namespace tklib {

class UnionFind {
private:
    std::vector<int> par;
    int components;

public:
    UnionFind(int n) : par(n, -1), components(n) {}

    bool unite(int x, int y) {
        if ((x = find(x)) == (y = find(y))) {
            return false;
        } else {
            if (par[x] < par[y]) std::swap(x, y);
            par[y] += par[x];
            par[x] = y;
            --components;
            return true;
        }
    }

    int find(int x) {
        if (par[x] < 0) return x;
        else return par[x] = find(par[x]);
    }

    int size(int x) {
        return -par[find(x)];
    }

    int count() {
        return components;
    }
};

} // namespace tklib

#endif // UNION_FIND_HPP
