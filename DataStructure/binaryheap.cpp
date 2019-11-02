#include <vector>
#include <functional>
#include <utility>

template <typename T, typename Compare = std::less<T>>
class binaryheap {
public:
    binaryheap() {};

    binaryheap(std::vector<T> vec):data(vec) { build_heap(); }

    void insert(T val) {
        data.push_back(val);
        std::size_t pos = data.size() - 1;
        while(pos > root && Compare()(data[parent(pos)], data[pos])) {
            std::swap(data[parent(pos)], data[pos]);
            pos = parent(pos);
        }
    }

    T maximum() {
        return data.at(root);
    }

    T extract_max() {
        T max_elem = data.at(root);
        data[root] = data.back();
        data.pop_back();
        heapify(root);
        return max_elem;
    }

    std::size_t size() { return data.size(); }

private:
    std::vector<T> data;
    const std::size_t root = 0;
    std::size_t parent(std::size_t node) { return (node - 1) / 2; }
    std::size_t left_child(std::size_t node) { return (node << 1) + 1; }
    std::size_t right_child(std::size_t node) { return (node << 1) + 2; }

    void heapify(std::size_t pos) {
        while (pos < (data.size() >> 1)) {
            std::size_t l = left_child(pos);
            std::size_t r = right_child(pos);
            
            std::size_t largest = pos;
            if (l < data.size() && Compare()(data[largest], data[l])) largest = l;
            if (r < data.size() && Compare()(data[largest], data[r])) largest = r;

            if (largest == pos) break;
            std::swap(data[pos], data[largest]);
            pos = largest;
        }
    }

    void build_heap() {
        for (int pos = (data.size() >> 1) - 1; pos >= 0; --pos) {
            heapify(pos);
        }
    }
};