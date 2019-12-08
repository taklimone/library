#include <vector>
using namespace std;

class union_find {
public:
    union_find(int n): par(n, -1), components(n) {}

    bool unite(int x, int y) {
        if((x = find(x)) == (y = find(y))) {
            return false;
        } else {
            if(par[x] < par[y]) swap(x, y);
            par[y] += par[x];
            par[x] = y;
            --components;
            return true;
        }
    }

    int find(int x) {
        if(par[x] < 0) return x;
        else return par[x] = find(par[x]);
    }

    int size(int x) {
        return -par[find(x)];
    }

    int cnt() {
        return components;
    }

private:
    vector<int> par;
    int components;
};
