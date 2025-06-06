#include "Treap.hpp"
#include "linklist.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#define endl "\n"

class k_Bar : public treap_Value {
    int Date;
    public:
        float open;
    float High;
    float Low;
    float close;
public:
    k_Bar() : Date(0), open(0), High(0), Low(0), close(0) {}
    k_Bar(int _Date, float _open, float _High, float _Low, float _close) : Date(_Date), open(_open), High(_High), Low(_Low), close(_close) {}
    treap_Value& operator=(const treap_Value& other) override {
        if (this != &other) {
            const k_Bar &k = dynamic_cast<const k_Bar &>(other);
            Date = k.Date;
            open = k.open;
            High = k.High;
            Low = k.Low;
            close = k.close;
        }
        return *this;
    }
    bool operator!=(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        return close != k.close || Date != k.Date;
    }

    bool operator<(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(close < k.close) return true;
        else if(close == k.close) return Date < k.Date;
        else return false;
    }
    bool operator>(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(close > k.close) return true;
        else if(close == k.close) return Date > k.Date;
        else return false;
    }
    bool operator==(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        return close == k.close && Date == k.Date;
    }
    float get_close() const {
        return close;
    }
    int get_Date() const {
        return Date;
    }

    float get_open() const {
        return open;
    }
    friend ostream& operator<<(ostream& os, const k_Bar& k) {
        os << k.Date << " " << k.open << " " << k.High << " " << k.Low << " " << k.close;
        return os;
    }
};

int main() {
    //////////////////////////////////////////////////////////////////////////////////////input
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    linklist<k_Bar> k_line;
    
    ifstream file("datasets/problem1/TWII_withRepeatedData.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    
    string header;
    getline(file, header); // 讀取並忽略表頭行
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        char trash;
        int Date;
        float open, High, Low, close;
        ss >> Date >> trash >> open >> trash >> High >> trash >> Low >> trash >> close;
        k_line.push_back(k_Bar(Date, open, High, Low, close));
    }

    file.close();


    // ////////////////////////////////////////////////////////////////////////////////////////////
    // freopen("P1out/b/outputTreap.txt", "w", stdout);
    Treap<k_Bar> treap;
    for (auto& it : k_line) {
        treap.insert(it);
    }
    cout<<treap<<endl;
    cout <<"1: " << treap.size() << endl;
    cout << "2: Small 10" << endl;
    Treap<k_Bar> a, b;
    treap.slip_By_Size(a, b, 10);
    cout << a << endl;

    cout << "3: Big 10" << endl;
    treap.slip_By_Size(a, b, treap.size()-10);
    cout << b << endl;

    cout << "4: Median" << endl;
    if(treap.size()&1){
        cout << treap[treap.size()/2] << endl;
    }
    else{
        auto it = treap[treap.size()/2];
        auto it2 = treap[treap.size()/2-1];
        cout<<it<<it2;
        cout << "Average: " << (it.get_close()+it2.get_close())/2 << endl;
    }

    return 0;
}
