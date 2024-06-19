#ifndef __TREAP_HPP__
#define __TREAP_HPP__
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
        if (get_Size(cur->left) < k) {
            a = cur;
            split_By_Size(cur->right, a->right, b, k - get_Size(cur->left) - 1);
            push_Up(a);
        } else {
            b = cur;
            split_By_Size(cur->left, a, b->left, k);
            push_Up(b);
        }
    }
    void clear(node* &cur) {
        if (cur == nullptr) {
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

    void print_Small_K(int k){
        node *a,*b;
        split_By_Size(root,a,b,k);
        print(a);
        cout << endl;
        merge(root,a,b);
    }
    void print_Big_K(int k){
        node *a,*b;
        split_By_Size(root,a,b,n-k);
        print(b);
        cout << endl;
        merge(root,a,b);
    }
    void print(node* cur) const {
        if(cur == nullptr){
            return;
        }
        print(cur->left);
        cout << cur->value << " ";
        print(cur->right);
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

};

int main(){
    Treap<int> treap;
    for(int i = 0; i < 1000; i++){
        treap.insert(rand()%10000000);
    }
    cout << treap.size() << endl;
    cout << treap << endl;
    cout << "Small K" << endl;
    treap.print_Small_K(10);
    cout << endl;
    cout << "Big K" << endl;
    treap.print_Big_K(10);
    cout << endl;
    // int n = 7;
    // for(int i = 0; i < n; i++){
    //     treap.insert(i);
    // }
    // cout << treap << endl;
    // cout <<"Size: " << treap.size() << endl;
    // cout <<"middle: " << treap[n/2] << endl;
    // cout<<"Small K" << endl;
    // treap.print_Small_K(3);
    // cout << endl;
    // cout<<"Big K" << endl;
    // treap.print_Big_K(3);
    // cout << endl;
 
    return 0;
}


#endif