#ifndef __TREAP_HPP__
#define __TREAP_HPP__
#include <iostream>
#include <random>
#include <ctime>
using namespace std;
#define endl "\n"
class treap_Value {
public:
    virtual treap_Value& operator=(const treap_Value&) { // Heap custom class should be inherited from heap_Value
        return *this;
    }
    virtual bool operator!=(const treap_Value &b) const = 0;
    virtual bool operator<(const treap_Value&) const = 0;// follow the logic of < to make max heap reverse the logic of < to make min heap
    virtual bool operator>(const treap_Value&) const = 0;// follow the logic of < to make max heap reverse the logic of < to make min heap
    virtual ~treap_Value() = default;
};

template<class T> // custom class should be inherited from heap_Value
class Treap{
    class node{
    public:
        T value;
        long long priority;
        long long index;
        long long size;
        int lazy_Tag;
        T max_Value;
        node *left;
        node *right;

        node(): left(nullptr),right(nullptr),size(1),lazy_Tag(0){}
        node(T __value,int __priority, long long __index):value(__value),priority(__priority),index(__index),size(1),lazy_Tag(0),max_Value(__value),left(nullptr),right(nullptr){}
        void swap(node* a,node* b){
            T tmp = a->value;
            a->value = b->value;
            b->value = tmp;
            int tmp2 = a->priority;
            a->priority = b->priority;
            b->priority = tmp2;
        }

    };
    node *root;
    int n;
    // void insert(T value,long long priority, int index){
        
    // }
    long long get_Size(node* cur){
        return cur? cur->size : 0;
    }
    T get_Max(node* cur){
        return cur? cur->max_Value : T();
    }
    void pull(node* cur){
        cur->max_Value = max(cur->value,max(get_Max(cur->left),get_Max(cur->right)));
        cur->lazy_Tag = 0;
    }
    void push(node* cur){
        if(cur->lazy_Tag){
            if(cur->left){
                cur->left->value += cur->lazy_Tag;
                cur->left->max_Value += cur->lazy_Tag;
                cur->left->lazy_Tag += cur->lazy_Tag;
            }
            if(cur->right){
                cur->right->value += cur->lazy_Tag;
                cur->right->max_Value += cur->lazy_Tag;
                cur->right->lazy_Tag += cur->lazy_Tag;
            }
            cur->lazy_Tag = 0;
        }
    }
    void merge(node* &cur,node* a,node* b){
        if(!a||!b){
            cur = a?a:b;
            return;
        }

        if(a->priority > b->priority){
            cur = a;
            push(cur);
            merge(cur->right,a->right,b);
            pull(cur);
        }
        else{
            cur = b;
            push(cur);
            merge(cur->left,a,b->left);
            pull(cur);
        }
    }
    void split_By_Index(node* cur,node* &a,node* &b,long long index){
        if(cur == nullptr){
            a = b = nullptr;
            return;
        }
        if(cur->index <= index){
            a = cur;
            push(a);
            split_By_Index(cur->right,a->right,b,index);
            pull(a);
        }
        else{
            b = cur;
            push(b);
            split_By_Index(cur->left,a,b->left,index);
            pull(b);
        }
    }
    

    void clear(node* &cur){
        if(cur == nullptr){
            return;
        }
        clear(cur->left);
        clear(cur->right);
        delete cur;
        cur = nullptr;
    }
    void insert(T value,long long priority, long long index){
        node *a,*b;
        split_By_Index(root,a,b,index);
        node *cur = new node(value,priority,index);
        merge(a,a,cur);
        merge(root,a,b);
    }
    public:
    Treap():root(nullptr),n(0){}
    ~Treap(){
        clear(root);
    }
    void insert(T value){
        insert(value,rand(),n++);
    }
    T get_Max(){
        return get_Max(root);
    }
    int size(){
        return n;
    }
    friend ostream& operator<<(ostream& os, const Treap& treap){
        treap.print(treap.root);
        return os;
    }
    void print(node* cur) const {
        if(cur == nullptr){
            return;
        }
        print(cur->left);
        cout << cur->value << " ";
        print(cur->right);
    }

};

int main(){
    srand(time(0));
    Treap<int> treap;
    for(int i = 0; i < 1000; i++){
        treap.insert(rand()%10000000);
    }
    cout << treap.size() << endl;
    cout << treap << endl;
    cout << treap.get_Max()<<endl;
    return 0;
}


#endif