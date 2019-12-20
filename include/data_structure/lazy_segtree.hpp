#ifndef TKLIB_LAZY_SEGTREE_HPP
#define TKLIB_LAZY_SEGTREE_HPP

#include <vector>
#include <functional>

namespace tklib {

template <typename T, typename E>
class LazySegtree {
private:
    using Op = std::function<T(T, T)>;
    using Compose = std::function<E(E, E)>;
    using Act = std::function<T(T, E)>;
    using Power = std::function<E(E, int)>;

    std::size_t N;
    std::vector<T> data;
    std::vector<E> lazy;
    const T idT;
    const E idE;
    const Op op;
    const Compose compose;
    const Act act;
    const Power power;

    void eval(std::size_t k, std::size_t len) {
        if(lazy[k] == idE) return;
        if(2 * k + 1 < 2 * N) {
            lazy[2 * k] = compose(lazy[2 * k], lazy[k]);
            lazy[2 * k + 1] = compose(lazy[2 * k + 1], lazy[k]);
        }
        data[k] = act(data[k], power(lazy[k], len));
        lazy[k] = idE;
    }

    void update(std::size_t left, std::size_t right, std::size_t k, std::size_t kl, std::size_t kr, E x) {
        eval(k, kr - kl);
        if(kr <= left || right <= kl) return;
        if(left <= kl && kr <= right) {
            lazy[k] = compose(lazy[k], x);
            eval(k, kr - kl);
            return;
        }
        update(left, right, 2 * k, kl, (kl + kr) / 2, x);
        update(left, right, 2 * k + 1, (kl + kr) / 2, kr, x);
        data[k] = op(data[2 * k], data[2 * k + 1]);
    }

    T get(std::size_t left, std::size_t right, std::size_t k, std::size_t kl, std::size_t kr) {
        eval(k, kr - kl);

        if(kr <= left || right <= kl) return idT;
        if(left <= kl && kr <= right) return data[k];
        
        T vl = get(left, right, 2 * k, kl, (kl + kr) / 2);
        T vr = get(left, right, 2 * k + 1, (kl + kr) / 2, kr);
        if(2 * k + 1 < 2 * N) data[k] = op(data[2 * k], data[2 * k + 1]);
        return op(vl, vr);
    }

public:
    LazySegtree(std::size_t n, T idT, E idE,
    const Op op, const Compose compose,
    const Act act, const Power power = [](E a, int){ return a; })
    : N(1), idT(idT), idE(idE), op(op), compose(compose), act(act), power(power) {
        while(N < n) N <<= 1;
        data.assign(2 * N, idT);
        lazy.assign(2 * N, idE);
    }
    
    template <typename InputIt>
    LazySegtree(InputIt first, InputIt last, T idT, E idE,
    const Op op, const Compose compose,
    const Act act, const Power power = [](E a, int){ return a; })
    : N(1), idT(idT), idE(idE), op(op), compose(compose), act(act), power(power) {
        std::vector<T> buffer(first, last);
        
        while(N < buffer.size()) N <<= 1;
        data.assign(2 * N, idT);
        lazy.assign(2 * N, idE);

        std::swap_ranges(buffer.begin(), buffer.end(), data.begin() + N);
        for(int i = N - 1; i >= 0; --i) data[i] = op(data[2 * i], data[2 * i + 1]);
    }

    void update(std::size_t left, std::size_t right, E x) {
        update(left, right, 1, 0, N, x);
    }

    T get(std::size_t left, std::size_t right) {
        return get(left, right, 1, 0, N);
    }

    T operator[](std::size_t k) {
        return get(k, k + 1);
    }
};

} // namespace tklib

#endif // TKLIB_LAZY_SEGTREE_HPP
