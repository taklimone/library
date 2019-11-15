#include <vector>
#include <functional>
using namespace std;

template <typename T, typename E>
class lazy_segtree {
private:
    using Op = function<T(T, T)>;
    using Compose = function<E(E, E)>;
    using Act = function<T(T, E)>;
    using Power = function<E(E, int)>;

    size_t N;
    vector<T> data;
    vector<E> lazy;
    const T idT;
    const E idE;
    const Op op;
    const Compose compose;
    const Act act;
    const Power power;

    void eval(size_t k, size_t len) {
        if(lazy[k] == idE) return;
        if(2 * k + 1 < 2 * N) {
            lazy[2 * k] = compose(lazy[2 * k], lazy[k]);
            lazy[2 * k + 1] = compose(lazy[2 * k + 1], lazy[k]);
        }
        data[k] = act(data[k], power(lazy[k], len));
        lazy[k] = idE;
    }

    void update(size_t a, size_t b, size_t k, size_t l, size_t r, E x) {
        eval(k, r - l);
        if(r <= a || b <= l) return;
        if(a <= l && r <= b) {
            lazy[k] = compose(lazy[k], x);
            eval(k, r - l);
            return;
        }
        update(a, b, 2 * k, l, (l + r) / 2, x);
        update(a, b, 2 * k + 1, (l + r) / 2, r, x);
        data[k] = op(data[2 * k], data[2 * k + 1]);
    }

    T get(size_t a, size_t b, size_t k, size_t l, size_t r) {
        eval(k, r - l);

        if(r <= a || b <= l) return idT;
        if(a <= l && r <= b) return data[k];
        
        T vl = get(a, b, 2 * k, l, (l + r) / 2);
        T vr = get(a, b, 2 * k + 1, (l + r) / 2, r);
        if(2 * k + 1 < 2 * N) data[k] = op(data[2 * k], data[2 * k + 1]);
        return op(vl, vr);
    }

public:
    lazy_segtree(size_t n, T idT, E idE,
    const Op op, const Compose compose,
    const Act act, const Power power = [](E a, int){ return a; })
    : idT(idT), idE(idE), op(op), compose(compose), act(act), power(power) {
        for(N = 1; N < n; N <<= 1);
        data = vector<T>(2 * N, idT);
        lazy = vector<E>(2 * N, idE);
    }
    
    lazy_segtree(const vector<T> &init, T idT, E idE,
    const Op op, const Compose compose,
    const Act act, const Power power = [](E a, int){ return a; })
    : idT(idT), idE(idE), op(op), compose(compose), act(act), power(power) {
        for(N = 1; N < init.size(); N <<= 1);
        data = vector<T>(2 * N, idT);
        lazy = vector<E>(2 * N, idE);
        for(size_t i = 0; i < init.size(); ++i) data[i + N] = init[i];
        for(size_t i = N - 1, last = -1; i != last; --i) data[i] = op(data[2 * i], data[2 * i + 1]);
    }

    void update(size_t left, size_t right, E x) {
        update(left, right, 1, 0, N, x);
    }

    T get(size_t left, size_t right) {
        return get(left, right, 1, 0, N);
    }

    T operator[](int k) {
        return get(k, k + 1);
    }
};
