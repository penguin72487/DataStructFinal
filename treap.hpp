#ifndef __TREAP_HPP__
#define __TREAP_HPP__
#include "linklist.hpp"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

class treap_Value {
public:
    virtual treap_Value& operator=(const treap_Value&) {
        return *this;
    }
    virtual bool operator!=(const treap_Value &b) const = 0;
    virtual bool operator<(const treap_Value&) const = 0;
    virtual bool operator>(const treap_Value&) const = 0;
    virtual bool operator==(const treap_Value& b) const=0;
    virtual ~treap_Value() = default;
};

template<class T>
class Treap {
private:
    class node {
    public:
        T value;
        long long priority;
        long long size;
        node *left, *right;

        node(T __value, int __priority): value(__value), priority(__priority), size(1), left(nullptr), right(nullptr) {}
    };

    node *root;
    int n;
    mt19937 rng;  // 隨機數生成器
    uniform_int_distribution<int> dist;  // 均勻分布

    long long get_Size(node* cur) {
        return cur ? cur->size : 0;
    }

    void push_Up(node* cur) {
        if(cur != nullptr) {
            cur->size = get_Size(cur->left) + get_Size(cur->right) + 1;
        }
    }

    void merge(node* &cur, node* a, node* b) {
        if (!a || !b) {
            cur = a ? a : b;
            return;
        }
        if (a->priority > b->priority) {
            cur = a;
            merge(cur->right, a->right, b);
        } else {
            cur = b;
            merge(cur->left, a, b->left);
        }
        push_Up(cur);
    }

    void split_By_Value(node* cur, node* &a, node* &b, T value) {
        if (cur == nullptr) {
            a = b = nullptr;
            return;
        }
        if (cur->value < value) {
            a = cur;
            split_By_Value(cur->right, a->right, b, value);
            push_Up(a);
        } else {
            b = cur;
            split_By_Value(cur->left, a, b->left, value);
            push_Up(b);
        }
    }
    void split_By_Size(node* cur, node* &a, node* &b, int k) {
        if (cur == nullptr) {
            a = b = nullptr;
            return;
        }
        if(get_Size(cur)==k){
            a = cur;
            b = nullptr;
            push_Up(a);
            push_Up(b);
            return;
        }
        if(get_Size(cur->left)+1==k)
        {
            a = cur;
            b = cur->right;
            a->right = nullptr;
            push_Up(a);
            push_Up(b);
            return;
        }
        if(get_Size(cur->left)+1< k){
            a = cur;
            split_By_Size(cur->right, a->right, b, k-get_Size(cur->left)-1);
            push_Up(a);
        }
        else{
            b = cur;
            split_By_Size(cur->left, a, b->left, k);
            push_Up(b);
        }

    }
    void clear(node* &cur) {
        if (!cur) {
            return;
        }
        clear(cur->left);
        clear(cur->right);
        delete cur;
        cur = nullptr;
    }
    void insert(T value, int priority) {
        node *a, *b;
        split_By_Value(root, a, b, value);
        node *new_node = new node(value, priority);
        merge(a, a, new_node);
        merge(root, a, b);
    }
    node* copyRoot(node* &cur, node* other){
        if(other == nullptr){
            return nullptr;
        }
        cur = new node(other->value, other->priority);
        cur->size = other->size;
        cur->left = copyRoot(cur->left, other->left);
        cur->right = copyRoot(cur->right, other->right);
        return cur;
    }
    void toList(node* cur, linklist<T>& res){
        if(cur == nullptr){
            return;
        }
        toList(cur->left, res);
        res.push_back(cur->value);
        toList(cur->right, res);
    }
    void print(node* cur) const {
        if(cur == nullptr){
            return;
        }
        print(cur->left);
        cout << cur->value <<endl;
        print(cur->right);
    }

public:
    Treap(): root(nullptr), n(0), rng(random_device{}()), dist(1, 10000000) {}

    void insert(T value) {
        if (find(value)) {
            return;
        }
        insert(value, dist(rng));  // 使用更好的隨機數生成器
        n++;
    }

    ~Treap() {
        clear(root);
    }
    bool find(T value)
    {
        node* cur = root;
        while(cur){
            if(cur->value == value){
                return true;
            }
            if(cur->value < value){
                cur = cur->right;
            }
            else{
                cur = cur->left;
            }
        }
        return false;
        
    }
    int size(){
        return n;
    }
    friend ostream& operator<<(ostream& os, const Treap& treap){
        treap.print(treap.root);
        return os;
    }
    void slip_By_Value(Treap<T>& a, Treap<T>& b, T value){
        node *a_root = nullptr, *b_root = nullptr;
        node *tmp_root;
        copyRoot(tmp_root, root);
        split_By_Value(tmp_root, a_root, b_root, value);
        a.root = a_root;
        b.root = b_root;
        a.n = get_Size(a_root);
        b.n = get_Size(b_root);
    }
    void slip_By_Size(Treap<T>& a, Treap<T>& b, int k){
        node *a_root = nullptr, *b_root = nullptr;
        node *tmp_root;
        copyRoot(tmp_root, root);
        split_By_Size(tmp_root, a_root, b_root, k);
        a.root = a_root;
        b.root = b_root;
        a.n = get_Size(a_root);
        b.n = get_Size(b_root);

    }
    T operator[](int index){
        node *cur = root;
        while(cur){
            if(get_Size(cur->left) == index){
                return cur->value;
            }
            if(get_Size(cur->left) < index){
                index -= get_Size(cur->left) + 1;
                cur = cur->right;
            }
            else{
                cur = cur->left;
            }
        }
        return cur->value;
    }
    linklist<T> toList(){
        linklist<T> res;
        toList(root, res);
        return res;
    }


};

// int main(){
//     // Treap<int> treap;
//     // for(int i = 0; i < 1000; i++){
//     //     treap.insert(rand()%10000000);
//     // }
//     // cout << treap.size() << endl;
//     // cout << treap << endl;
//     // cout << "Small K" << endl;
//     // treap.print_Small_K(10);
//     // cout << endl;
//     // cout << "Big K" << endl;
//     // treap.print_Big_K(10);
//     // cout << endl;
//     // int n = 7;
//     // for(int i = 0; i < n; i++){
//     //     treap.insert(i);
//     // }
//     // cout << treap << endl;
//     // cout <<"Size: " << treap.size() << endl;
//     // cout <<"middle: " << treap[n/2] << endl;
//     // cout<<"Small K" << endl;
//     // Treap<int> a, b;
//     // treap.slip_By_Size(a, b, 3);
//     // cout << a << endl;
//     // // a.clear();
//     // // b.clear();
//     // cout << endl;
//     // cout<<"Big K" << endl;
//     // treap.slip_By_Size(a, b, n-3);
//     // cout << b << endl;
//     // a.clear();
//     // b.clear();
//     // cout << endl;
 
//     return 0;
// }


#endif