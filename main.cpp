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
        return close != k.close || Date != k.Date;
    }

    bool operator<(const heap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(close < k.close) return true;
        else if(close == k.close) return Date < k.Date;
        else return false;
    }
    bool operator>(const heap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(close > k.close) return true;
        else if(close == k.close) return Date > k.Date;
        else return false;
    }
    float get_close() const {
        return close;
    }
    int get_Date() const {
        return Date;
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
        if (caseB_date %5 == 0){
            k_line.push_back(k_Bar(Date, open, High, Low, close));
            size++;
        }
        caseB_date++;
    }

    file.close();
    cout<< "1:" << endl;
    cout << size << endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    freopen("P1out/b/out.txt", "w", stdout);

    Heap<k_Bar> k_Heap(size);
    for(auto& it:k_line){
        k_Heap.push(it);
    }
    cout<< endl <<  "2:" << endl;
    // cout<<k_Heap.top()<<endl;
    k_Heap.sort();
    size=k_Heap.size();
    // int n=k_Heap.size();
    for(int i=0;i<10;i++){// small K
        cout<<k_Heap[i]<<endl;
    }
        cout << endl<< "3:" <<endl;
    for(int i=size-10;i<size;i++){// large K
        cout<<k_Heap[i]<<endl;
    }
    
    cout << endl << "4:" <<endl;
    // 找中位數
    if(size%2==0){
        cout<<k_Heap[size/2-1]<<endl;
        cout<<k_Heap[size/2]<<endl;
    }
    else{
        cout<<k_Heap[size/2]<<endl;
    }
    cout << endl<< "5:" <<endl;

    // cout<<k_Heap<<endl;
    //5
    float max_return=-1000000;
    float min_return=1000000;
    int max_index=0;
    int min_index=0;
    for(int i=1;i<size;i++){
        float daily_return=(k_Heap[i].get_close()-k_Heap[i-1].get_close())/k_Heap[i-1].get_close()*100;
        if(daily_return>max_return){
            max_return=daily_return;
            max_index=i;
        }
        if(daily_return<min_return){
            min_return=daily_return;
            min_index=i;
        }
    }
    cout<<"max_return: "<<max_return<<" on "<<k_Heap[max_index]<<endl;
    cout<<"min_return: "<<min_return<<" on "<<k_Heap[min_index]<<endl;
    cout << endl<< "6:" <<endl;
    //6
    //     Compute the intraday return for every day. Then determine what the maximum and 
    // minimum returns (return could be a negative value) are and on which day(s) they occur. 
    
    // Intraday returns is defined as: 
    
    // [(Close_price(t)-Open_price(t))/Open_price(t)]*100%, where t is date. 


    int max_index2=0;
    int min_index2=0;
    float max_return2=-1000000;
    float min_return2=1000000;
    for(int i=0;i<size;i++){
        float daily_return=(k_Heap[i].get_close()-k_Heap[i].open)/k_Heap[i].open*100;
        if(daily_return>max_return2){
            max_return2=daily_return;
            max_index2=i;
        }
        if(daily_return<min_return2){
            min_return2=daily_return;
            min_index2=i;
        }
    }
    cout<<"max_return2: "<<max_return2<<" on "<<k_Heap[max_index2]<<endl;
    cout<<"min_return2: "<<min_return2<<" on "<<k_Heap[min_index2]<<endl;
    cout << endl<< "7:" <<endl;
    
    //7 Make a plot of the closing price over time, in which the x-axis is the day index and y-axis is the price.

    for(int i=0;i<size;i++){
        cout<<i<<" "<<k_Heap[i].get_close()<<endl;
    }
    cout << endl<< "8:" <<endl;
    //8  Make a plot of the daily return over time, in which the x-axis is the day index and y-axis is the daily return.
    for(int i=0;i<size;i++){
        cout<<i<<" "<<(k_Heap[i].get_close()-k_Heap[i].open)/k_Heap[i].open*100<<endl;
    }
    //9  Make a plot of the intraday return over time, in which the x-axis is the day index and y-axis is the intraday return.
    cout << endl<< "9:" <<endl;
    for(int i=0;i<size;i++){
        cout<<i<<" "<<(k_Heap[i].get_close()-k_Heap[i].open)/k_Heap[i].open*100<<endl;
    }
    cout << endl<< "10:" <<endl;
    //10 Find the maximum, minimum and median prices using all the 4 columns of prices (i.e., Open_price, High_price, Low_price and Close_price) and determine on which date they occur.
    float max_price=-1000000;
    float min_price=1000000;
    float median_price;
    int max_index3=0;
    int min_index3=0;
    float max_high_price=-1000000;
    float min_high_price=1000000;
    float max_low_price=-1000000;
    float min_low_price=1000000;
    float max_close_price=-1000000;
    float min_close_price=1000000;
    int max_high_index=0;
    int min_high_index=0;
    int max_low_index=0;
    int min_low_index=0;
    int max_close_index=0;
    int min_close_index=0;

    for(int i=0;i<size;i++){
        float open_price=k_Heap[i].open;
        float high_price=k_Heap[i].High;
        float low_price=k_Heap[i].Low;
        float close_price=k_Heap[i].close;
        if(open_price>max_price){
            max_price=open_price;
            max_index3=i;
        }
        if(open_price<min_price){
            min_price=open_price;
            min_index3=i;
        }
        if(high_price>max_high_price){
            max_high_price=high_price;
            max_high_index=i;
        }
        if(high_price<min_high_price){
            min_high_price=high_price;
            min_high_index=i;
        }
        if(low_price>max_low_price){
            max_low_price=low_price;
            max_low_index=i;
        }
        if(low_price<min_low_price){
            min_low_price=low_price;
            min_low_index=i;
        }
        if(close_price>max_close_price){
            max_close_price=close_price;
            max_close_index=i;
        }
        if(close_price<min_close_price){
            min_close_price=close_price;
            min_close_index=i;
        }
    }

    // Print the results

    cout<<"max_open_price: "<<max_price<<" on "<<k_Heap[max_index3].get_Date()<<endl;
    cout<<"min_open_price: "<<min_price<<" on "<<k_Heap[min_index3].get_Date()<<endl;
    cout<<"max_high_price: "<<max_high_price<<" on "<<k_Heap[max_high_index].get_Date()<<endl;
    cout<<"min_high_price: "<<min_high_price<<" on "<<k_Heap[min_high_index].get_Date()<<endl;
    cout<<"max_low_price: "<<max_low_price<<" on "<<k_Heap[max_low_index].get_Date()<<endl;
    cout<<"min_low_price: "<<min_low_price<<" on "<<k_Heap[min_low_index].get_Date()<<endl;
    cout<<"max_close_price: "<<max_close_price<<" on "<<k_Heap[max_close_index].get_Date()<<endl;
    cout<<"min_close_price: "<<min_close_price<<" on "<<k_Heap[min_close_index].get_Date()<<endl;
    return 0;
}
