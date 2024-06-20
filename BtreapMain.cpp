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
        return Date != k.Date || Date != k.Date;
    }

    bool operator<(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(Date < k.Date) return true;
        else if(Date == k.Date) return Date < k.Date;
        else return false;
    }
    bool operator>(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(Date > k.Date) return true;
        else if(Date == k.Date) return Date > k.Date;
        else return false;
    }
    bool operator==(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        return Date == k.Date && Date == k.Date;
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
    int caseB_date = 0;
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
    freopen("P1out/b/158outputTreap.txt", "w", stdout);
    Treap<k_Bar> treapB;
    for (auto& it : k_line) {
        treapB.insert(it);
    }
    Treap<k_Bar> treap;
    int dat = 0;
    linklist<k_Bar> toListB = treapB.toList();
    for (auto& it : toListB) {
        if(dat%5==0){
            treap.insert(k_Bar(it.get_Date(), it.open, it.High, it.Low, it.close));
        }
        dat++;
    }
    cout <<"1: " << treap.size() << endl;
    cout << "8: " << endl;
    linklist<k_Bar> toList = treap.toList();
    float max5 =-1000000, min5 = 1000000;

    int i = 0;
        double previous_close = 0;
        for (auto& it : toList) {
            if (i != 0) {
                cout << it.get_Date() << " " << (it.get_close() - previous_close) / previous_close * 100 << endl;
                if((it.get_close() - previous_close) / previous_close * 100 > max5){
                    max5 = (it.get_close() - previous_close) / previous_close * 100;
                }
                if((it.get_close() - previous_close) / previous_close * 100 < min5){
                    min5 = (it.get_close() - previous_close) / previous_close * 100;
                }
            }
            previous_close = it.get_close();
            i++;
        }

    cout << "5Max: " << max5 << endl;
    cout << "5Min: " << min5 << endl;


    return 0;
}
