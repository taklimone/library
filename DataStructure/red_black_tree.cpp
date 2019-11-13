#include <iostream>
#include <functional>
#include <stdexcept>

template <typename T>
struct node {
    T key;
    node* left;
    node* right;
    node* parent;
    bool red;
    std::size_t size;

    node(T key, node* left, node*right, node* parent, bool red, std::size_t size)
    :key(key), left(left), right(right), parent(parent), red(red), size(size) {}
};

template <typename T, typename Compare = std::less<T>>
class red_black_tree {
public:
    red_black_tree()
    : nil(new node<T>(T(), nullptr, nullptr, nullptr, false, 0)), root(nil), treesize(0)
    {}

    ~red_black_tree() {
        destroy(root);
        delete nil;
    }

    bool insert(T key) {
        if(find(key) != nil) return false;
        auto z = new node<T>(key, nil, nil, nil, true, 1);
        insert_node(z);
        return true;
    }

    bool remove(T key) {
        auto z = find(key);
        if(z == nil) {
            return false;
        } else {
            remove_node(z);
            return true;
        }
    }

    bool contains(T key) {
        return find(key) != nil;
    }

    std::size_t size() {
        return treesize;
    }

    bool empty() {
        return treesize == 0;
    }

    T find_by_rank(std::size_t rank) {
        if(rank >= treesize) {
            throw std::out_of_range("find_by_rank: out of range");
        }
        return find_by_rank(root, rank)->key;
    }

    std::size_t rank_of_key(T key) {
        auto x = find(key);
        if(x == nil) return treesize;

        std::size_t r = x->left->size;
        auto y = x;
        while(y != root) {
            if(y == y->parent->right) r += y->parent->left->size + 1;
            y = y->parent;
        }
        return r;
    }

    void print_inorder() {
        inorder_tree_walk(root);
    }

    void print_preorder() {
        preorder_tree_walk(root);
    }

private:
    node<T>* const nil;
    node<T>* root;
    std::size_t treesize;

    void destroy(node<T>* x) {
        if(x == nil) return;
        destroy(x->left);
        destroy(x->right);
        delete x;
    }

    void left_rotate(node<T>* x) {
        node<T>* y = x->right;
        
        x->right = y->left;
        if(y->left != nil) y->left->parent = x;
        
        y->parent = x->parent;
        if(x->parent == nil) root = y;
        else if(x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        
        y->left = x;
        x->parent = y;

        y->size = x->size;
        nil->size = 0;
        x->size = x->left->size + x->right->size + 1;
    }

    void right_rotate(node<T>* x) {
        node<T>* y = x->left;

        x->left = y->right;
        if(y->right != nil) y->right->parent = x;

        y->parent = x->parent;
        if(x->parent == nil) root = y;
        else if(x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;

        y->right = x;
        x->parent = y;

        y->size = x->size;
        nil->size = 0;
        x->size = x->left->size + x->right->size + 1;
    }

    void insert_node(node<T>* z) {
        node<T>* trailer = nil;
        node<T>* head = root;
        while(head != nil) {
            trailer = head;
            if(Compare()(z->key, head->key)) head = head->left;
            else head = head->right;
        }

        z->parent = trailer;
        if(trailer == nil) root = z;
        else if(Compare()(z->key, trailer->key)) trailer->left = z;
        else trailer->right = z;

        z->red = true;
        z->size = 1;

        auto y = z->parent;
        while(y != nil) {
            y->size += 1;
            y = y->parent;
        }

        ++treesize;
        insert_fixup(z);
    }

    void insert_fixup(node<T>* z) {
        while(z->parent->red) {
            if(z->parent == z->parent->parent->left) {
                node<T>* y = z->parent->parent->right;
                if(y->red) {
                    z->parent->red = false;
                    y->red = false;
                    z->parent->parent->red = true;
                    z = z->parent->parent;
                } else {
                    if(z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    right_rotate(z->parent->parent);
                }
            } else {
                node<T>* y = z->parent->parent->left;
                if(y->red) {
                    z->parent->red = false;
                    y->red = false;
                    z->parent->parent->red = true;
                    z = z->parent->parent;
                } else {
                    if(z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->red = false;
    }

    node<T>* minimum(node<T>* x) {
        while(x ->left != nil) x = x->left;
        return x;
    }

    void transplant(node<T>* u, node<T>* v) {
        if(u->parent == nil) root = v;
        else if(u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
        v->size = u->size;
    }

    void remove_node(node<T>* z) {
        // y will be removed or transplanted to the original position of z
        node<T>* y = z;
        bool y_original_red = y->red;
        
        // x will be transplanted to the original position of y after transplant
        // x might be nil
        node<T>* x;
        bool x_transplanted = true;

        if(z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if(z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_red = y->red;
            x = y->right;

            if(y->parent == z) {
                x->parent = y;
                x_transplanted = false;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                z->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->red = z->red;
        }

        auto w = (x_transplanted ? x : x->parent);
        while(w->size > 0 || w != nil) {
            w->size -= 1;
            w = w->parent;
        }

        --treesize;
        delete z;
        if(!y_original_red) remove_fixup(x);
    }

    void remove_fixup(node<T>* x) {
        while(x != root && !x->red) {
            if(x == x->parent->left) {
                node<T>* w = x->parent->right;
                if(w->red) {
                    w->red = false;
                    x->parent->red = true;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                
                if(!w->left->red && !w->right->red) {
                    w->red = true;
                    x = x->parent;
                } else {
                    if(!w->right->red) {
                        w->left->red = false;
                        w->red = true;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->right->red = false;
                    left_rotate(x->parent);
                    x = root;
                }
            } else {  // x == x->parent->right
                node<T>* w = x->parent->left;
                if(w->red) {
                    w->red = false;
                    x->parent->red = true;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                
                if(!w->right->red && !w->left->red) {
                    w->red = true;
                    x = x->parent;
                } else {
                    if(!w->left->red) {
                        w->right->red = false;
                        w->red = true;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->left->red = false;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->red = false;
    }

    node<T>* find(T key) {
        node<T>* x = root;
        while(x != nil) {
            if(Compare()(key, x->key)) x = x->left;
            else if(Compare()(x->key, key)) x = x->right;
            else break; 
        }
        return x;
    }

    node<T>* find_by_rank(node<T>* x, std::size_t rank) {
        std::size_t r = x->left->size;
        if(rank == r) return x;
        else if(rank < r) return find_by_rank(x->left, rank);
        else return find_by_rank(x->right, rank - r - 1);
    }

    void inorder_tree_walk(node<T>* x) {
        if(x == nil) return;
        inorder_tree_walk(x->left);
        std::cout << ' ' << x->key;
        inorder_tree_walk(x->right);
    }

    void preorder_tree_walk(node<T>* x) {
        if(x == nil) return;
        std::cout << ' ' << x->key;
        preorder_tree_walk(x->left);
        preorder_tree_walk(x->right);
    }
};