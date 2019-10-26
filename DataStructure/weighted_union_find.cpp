#include <vector>
using namespace std;

template <typename T>
class weighted_union_find {
public:
    weighted_union_find(size_t n)
    :par(n, -1), weight_diff(n, 0) {}

    // weight(y) - weight(x) = w
    bool unite(int x, int y, T w) {
        w += weight(x);
        w -= weight(y);

        if((x = find(x)) == (y = find(y))) {
            return false;
        } else {
            if(par[y] < par[x]) {
                swap(x, y);
                w = -w;
            }
            par[x] += par[y];
            par[y] = x;
            weight_diff[y] = w;
            return true;
        }
    }

    int find(int x) {
        if(par[x] < 0) {
            return x;
        } else {
            int root = find(par[x]);
            weight_diff[x] += weight_diff[par[x]];
            return par[x] = root;
        }
    }

    T weight(int x) {
        find(x);
        return weight_diff[x];
    }

    T diff(int x, int y) {
        return weight_diff[y] - weight_diff[x];
    }

    int size(int x) {
        return -par[find(x)];
    }

private:
    vector<int> par;
    vector<T> weight_diff;
};
