#include <vector>
#include <functional>
using namespace std;

template <typename T, typename Op = plus<T>>
class segtree {
private:
    size_t N;
    vector<T> data;
    T idelem;
    const Op &op;

public:
    segtree(size_t n, T idelem, const Op &op = Op())
    : idelem(idelem), op(op) {
        for(N = 1; N < n; N <<= 1);
        data = vector<T>(2 * N, idelem);
    }

    segtree(const vector<T> &init, T idelem, const Op &op = Op())
    : idelem(idelem), op(op) {
        for(N = 1; N < init.size(); N <<= 1);
        data = vector<T>(2 * N, idelem);
        for(int i = 0; i < init.size(); ++i) data[i + N] = init[i];
        for(int i = N - 1; i >= 0; --i) data[i] = op(data[2 * i], data[2 * i + 1]);
    }

    void update(size_t pos, T val) {
        data[pos + N] = val;
        for(pos = (pos + N) / 2; pos > 0; pos >>= 1) {
            data[pos] = op(data[2 * pos], data[2 * pos + 1]);
        }
    }

    T query(size_t left, size_t right) {
        left += N;
        right += N;

        T vl = idelem, vr = idelem;
        while(left < right) {
            if(left & 1) vl = op(vl, data[left++]);
            if(right & 1) vr = op(data[right - 1], vr);
            left >>= 1;
            right >>= 1;
        }
        return op(vl, vr);
    }

    T operator[](size_t k) {
        return data[k + N];
    }
};
