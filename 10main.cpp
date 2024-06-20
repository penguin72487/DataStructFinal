#include "Heap.hpp"
#include "linklist.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#define endl "\n"
class k_Bar : public heap_Value {
    int Date;
    public:
        float open;
    float High;
    float Low;
    float close;
public:
    k_Bar() : Date(0), open(0), High(0), Low(0), close(0) {}
    k_Bar(int _Date, float _open, float _High, float _Low, float _close) : Date(_Date), open(_open), High(_High), Low(_Low), close(_close) {}
    heap_Value& operator=(const heap_Value& other) override {
        if (this != &other) {
            const k_Bar& k = dynamic_cast<const k_Bar&>(other);
            Date = k.Date;
            open = k.open;
            High = k.High;
            Low = k.Low;
            close = k.close;
        }
        return *this;
    }
    bool operator!=(const heap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        return Low != k.Low || Date != k.Date;
    }

    bool operator<(const heap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(Low < k.Low) return true;
        else if(Low == k.Low) return Date < k.Date;
        else return false;
    }
    bool operator>(const heap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(Low > k.Low) return true;
        else if(Low == k.Low) return Date > k.Date;
        else return false;
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
    int size = 0;
    int caseB_date = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        char trash;
        int Date;
        float open, High, Low, close;
        ss >> Date >> trash >> open >> trash >> High >> trash >> Low >> trash >> close;
        // if (caseB_date %5 == 0){
            k_line.push_back(k_Bar(Date, open, High, Low, close));
            size++;
        // }
        caseB_date++;
    }

    file.close();

    // ////////////////////////////////////////////////////////////////////////////////////////////
    freopen("P1out/a/10mid-low-out.txt", "w", stdout);

    Heap<k_Bar> k_Heap(size);
    for(auto& it:k_line){
        k_Heap.push(it);
    }
    k_Heap.sort();
    size=k_Heap.size();

    cout<<k_Heap[size/2].get_Date() << " " << k_Heap[size/2].get_close() << endl;
}
