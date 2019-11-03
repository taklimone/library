#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_8_C

#include "../DataStructure/binary_search_tree.cpp"

#include <iostream>
#include <string>

int main() {
    binary_search_tree<int> tree;
    int m; std::cin >> m;
    while(m--) {
        std::string query;
        std::cin >> query;
        if(query == "insert") {
            int key; std::cin >> key;
            auto z = new node<int>(key);
            tree.insert(z);
        } else if(query == "find") {
            int key; std::cin >> key;
            auto z = tree.find(key);
            std::cout << (z != nullptr ? "yes" : "no") << std::endl;
        } else if(query == "delete") {
            int key; std::cin >> key;
            auto z = tree.find(key);
            tree.remove(z);
        } else {
            tree.print_inorder(); std::cout << std::endl;
            tree.print_preorder(); std::cout << std::endl;
        }
    }
}
