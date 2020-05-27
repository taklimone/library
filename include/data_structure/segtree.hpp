#ifndef TKLIB_SEGTREE_HPP
#define TKLIB_SEGTREE_HPP

#include <vector>
#include <functional>

namespace tklib {

template <typename T, typename Op = std::plus<T>>
class Segtree {
private:
    std::size_t N;
    std::vector<T> data;
    T idelem;
    const Op &op;

public:
    Segtree(std::size_t n, T idelem, const Op &op = Op())
    : N(1), idelem(idelem), op(op) {
        while(N < n) N <<= 1;
        data.assign(2 * N, idelem);
    }

    template <typename InputIt>
    Segtree(InputIt first, InputIt last, T idelem, const Op &op = Op())
    : N(1), idelem(idelem), op(op) {
        std::vector<T> buffer(first, last);
        while(N < buffer.size()) N <<= 1;
        data.assign(2 * N, idelem);
        std::swap_ranges(buffer.begin(), buffer.end(), data.begin() + N);
        for(int i = N - 1; i > 0; --i) data[i] = op(data[2 * i], data[2 * i + 1]);
    }

    void update(std::size_t pos, T val) {
        for(data[pos += N] = val; pos >>= 1; ) {
            data[pos] = op(data[pos << 1], data[(pos << 1) + 1]);
        }
    }

    T query(std::size_t left, std::size_t right) {
        T vl = idelem, vr = idelem;
        for(left += N, right += N; left < right; left >>= 1, right >>= 1) {
            if(left & 1) vl = op(vl, data[left++]);
            if(right & 1) vr = op(data[--right], vr);
        }
        return op(vl, vr);
    }

    T operator[](std::size_t k) {
        return data[k + N];
    }
};

} // namespace tklib

#endif // TKLIB_SEGTREE_HPP
