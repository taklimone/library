#include <iostream>
#include <functional>

template <typename T>
struct node {
    T key;
    node* left;
    node* right;
    node* parent;
    node(T key):key(key), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T, typename Compare = std::less<T>>
class binary_search_tree {
public:
    binary_search_tree(): root(nullptr) {}

    ~binary_search_tree() { destroy(root); }

    bool insert(node<T>* z) {
        node<T>* trailer = nullptr;
        node<T>* head = root;
        while(head != nullptr) {
            trailer = head;
            if(Compare()(z->key, head->key)) head = head->left;
            else if(Compare()(head->key, z->key)) head = head->right;
            else break;
        }

        z->parent = trailer;
        if(trailer == nullptr) root = z;
        else if(Compare()(z->key, trailer->key)) trailer->left = z;
        else if(Compare()(trailer->key, z->key)) trailer->right = z;
        else return false;

        return true;
    }

    void remove(node<T>* z) {
        if(z->left == nullptr) {
            transplant(z, z->right);
        } else if(z->right == nullptr) {
            transplant(z, z->left);
        } else {
            node<T>* y = minimum(z->right);
            if(y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }

    node<T>* find(T key) {
        node<T>* x = root;
        while(x != nullptr) {
            if(Compare()(key, x->key)) x = x->left;
            else if(Compare()(x->key, key)) x = x->right;
            else break; 
        }
        return x;
    }

    void print_inorder() {
        inorder_tree_walk(root);
    }

    void print_preorder() {
        preorder_tree_walk(root);
    }

private:
    node<T>* root;

    void destroy(node<T>* x) {
        if(x == nullptr) return;
        destroy(x->left);
        destroy(x->right);
        delete x;
    }

    node<T>* minimum(node<T>* x) {
        while(x ->left != nullptr) x = x->left;
        return x;
    }

    void transplant(node<T>* u, node<T>* v) {
        if(u->parent == nullptr) root = v;
        else if(u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if(v != nullptr) v->parent = u->parent;
    } 

    void inorder_tree_walk(node<T>* x) {
        if(x == nullptr) return;
        inorder_tree_walk(x->left);
        std::cout << ' ' << x->key;
        inorder_tree_walk(x->right);
    }

    void preorder_tree_walk(node<T>* x) {
        if(x == nullptr) return;
        std::cout << ' ' << x->key;
        preorder_tree_walk(x->left);
        preorder_tree_walk(x->right);
    }
};
