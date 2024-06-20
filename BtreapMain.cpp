#include "Treap.hpp"
#include "linklist.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#define endl "\n"
class k_Bar_Date : public treap_Value {
    int Date;
    public:
        float open;
    float High;
    float Low;
    float close;
public:
    k_Bar_Date() : Date(0), open(0), High(0), Low(0), close(0) {}
    k_Bar_Date(int _Date, float _open, float _High, float _Low, float _close) : Date(_Date), open(_open), High(_High), Low(_Low), close(_close) {}
    treap_Value& operator=(const treap_Value& other) override {
        if (this != &other) {
            const k_Bar_Date &k = dynamic_cast<const k_Bar_Date &>(other);
            Date = k.Date;
            open = k.open;
            High = k.High;
            Low = k.Low;
            close = k.close;
        }
        return *this;
    }
    bool operator!=(const treap_Value& b) const override {
        const k_Bar_Date& k = dynamic_cast<const k_Bar_Date&>(b);
        return Date != k.Date || Date != k.Date;
    }

    bool operator<(const treap_Value& b) const override {
        const k_Bar_Date& k = dynamic_cast<const k_Bar_Date&>(b);
        if(Date < k.Date) return true;
        else if(Date == k.Date) return Date < k.Date;
        else return false;
    }
    bool operator>(const treap_Value& b) const override {
        const k_Bar_Date& k = dynamic_cast<const k_Bar_Date&>(b);
        if(Date > k.Date) return true;
        else if(Date == k.Date) return Date > k.Date;
        else return false;
    }
    bool operator==(const treap_Value& b) const override {
        const k_Bar_Date& k = dynamic_cast<const k_Bar_Date&>(b);
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
    friend ostream& operator<<(ostream& os, const k_Bar_Date& k) {
        os << k.Date << " " << k.open << " " << k.High << " " << k.Low << " " << k.close;
        return os;
    }
};
class k_Bar_Close : public treap_Value {
    int Date;
    public:
        float open;
    float High;
    float Low;
    float close;
public:
    k_Bar_Close() : Date(0), open(0), High(0), Low(0), close(0) {}
    k_Bar_Close(int _Date, float _open, float _High, float _Low, float _close) : Date(_Date), open(_open), High(_High), Low(_Low), close(_close) {}
    treap_Value& operator=(const treap_Value& other) override {
        if (this != &other) {
            const k_Bar_Close &k = dynamic_cast<const k_Bar_Close &>(other);
            Date = k.Date;
            open = k.open;
            High = k.High;
            Low = k.Low;
            close = k.close;
        }
        return *this;
    }
    bool operator!=(const treap_Value& b) const override {
        const k_Bar_Close& k = dynamic_cast<const k_Bar_Close&>(b);
        return close != k.close || Date != k.Date;
    }

    bool operator<(const treap_Value& b) const override {
        const k_Bar_Close& k = dynamic_cast<const k_Bar_Close&>(b);
        if(close < k.close) return true;
        else if(close == k.close) return Date < k.Date;
        else return false;
    }
    bool operator>(const treap_Value& b) const override {
        const k_Bar_Close& k = dynamic_cast<const k_Bar_Close&>(b);
        if(close > k.close) return true;
        else if(close == k.close) return Date > k.Date;
        else return false;
    }
    bool operator==(const treap_Value& b) const override {
        const k_Bar_Close& k = dynamic_cast<const k_Bar_Close&>(b);
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
    friend ostream& operator<<(ostream& os, const k_Bar_Close& k) {
        os << k.Date << " " << k.open << " " << k.High << " " << k.Low << " " << k.close;
        return os;
    }
};

int main() {
    //////////////////////////////////////////////////////////////////////////////////////input
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    linklist<k_Bar_Date> k_line;
    
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
        k_line.push_back(k_Bar_Date(Date, open, High, Low, close));

        
    }

    file.close();


    // ////////////////////////////////////////////////////////////////////////////////////////////
    freopen("P1out/b/158outputTreap.txt", "w", stdout);
    Treap<k_Bar_Date> treapB;
    for (auto& it : k_line) {
        treapB.insert(it);
    }
    Treap<k_Bar_Close> treap_close;
    Treap<k_Bar_Date> treap_Date;
    int dat = 0;
    linklist<k_Bar_Date> toListB = treapB.toList();
    for (auto& it : toListB) {
        if(dat%5==0){
            treap_close.insert(k_Bar_Close(it.get_Date(), it.open, it.High, it.Low, it.close));
            treap_Date.insert(k_Bar_Date(it.get_Date(), it.open, it.High, it.Low, it.close));
        }
        dat++;
    }
    linklist<k_Bar_Close> toList_Close = treap_close.toList();
    cout <<"1: " << treap_Date.size() << endl;
    //(2) 找到10個最小價格及其對應的日期。
    cout << "2: Small 10" << endl;
    Treap<k_Bar_Close> a, b;
    treap_close.slip_By_Size(a, b, 10);

    cout << a << endl;


    //(3) 找到10個最大價格及其對應的日期。
    cout << "3: Big 10" << endl;
    Treap<k_Bar_Close> c, d;
    treap_close.slip_By_Size(c, d, treap_close.size()-10);

    cout << d << endl;


    //(4) 找到中位價格及其發生日期。
    cout << "4: Median" << endl;
    if(treap_close.size()&1){
        cout << treap_close[treap_close.size()/2].get_Date() << " " << treap_close[treap_close.size()/2].get_close() << endl;
    }
    else{
        auto it = treap_close[treap_close.size()/2];
        auto it2 = treap_close[treap_close.size()/2-1];
        cout << it.get_Date() << " " << it.get_close() << endl;
        cout << it2.get_Date() << " " << it2.get_close() << endl;
        cout << "Average: " << (it.get_close()+it2.get_close())/2 << endl;
    }

    //(7) 繪製收盤價隨時間變化的圖表，其中x軸為日期索引，y軸為價格。
    cout << "7: " << endl;
    for (auto& it : toList_Date) {
        cout << it.get_Date() << " " << it.get_close() << endl;
    }

    cout << "8: " << endl;
    
    float max5 =-1000000, min5 = 1000000;
    linklist<k_Bar_Date> toList_Date = treap_Date.toList();
    int i = 0;
        double previous_close = 0;
        for (auto& it : toListB) {
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

    //(9) 繪製日內收益率隨時間變化的圖表，其中x軸為日期索引，y軸為日內收益率。
    cout << "9: " << endl;
    float max6 =-1000000, min6 = 1000000;
    toList_Date = treap_Date.toList();
    i = 0;
        for (auto& it : toListB) {
            if (i != 0) {
                cout << it.get_Date() << " " << (it.get_close() - it.open) / it.open * 100 << endl;
                if((it.get_close() - it.open) / it.open * 100 > max5){
                    max6 = (it.get_close() - it.open) / it.open * 100;
                }
                if((it.get_close() - it.open) / it.open * 100 < min5){
                    min6 = (it.get_close() - it.open) / it.open * 100;
                }
            }
            i++;
        }
    cout << "6Max: " << max6 << endl;
    cout << "6Min: " << min6 << endl;
    return 0;
}
