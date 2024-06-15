#include "Heap.hpp"
#include "linklist.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#define endl "\n"

linklist<string> all_products;
class k_Bar : public heap_Value {
    int Date;
    string name;
    float exercisePrice;
    int expirationDate;// month
    char callPut;// C or P
    float transactionTime;
    float transactionPrice;
    float transactionVolume;
    float openingAuctionPrice;

public:
    k_Bar() : Date(0), name(""), exercisePrice(0), expirationDate(0), callPut(' '), transactionTime(0), transactionPrice(0), transactionVolume(0), openingAuctionPrice(0) {}
    k_Bar(int _Date, string _name,  float _exercisePrice, int _expirationDate, char _callPut, float _transactionTime, float _transactionPrice, float _transactionVolume, float _openingAuctionPrice) : Date(_Date), name(_name), exercisePrice(_exercisePrice), expirationDate(_expirationDate), callPut(_callPut), transactionTime(_transactionTime), transactionPrice(_transactionPrice), transactionVolume(_transactionVolume), openingAuctionPrice(_openingAuctionPrice) {}
    heap_Value& operator=(const heap_Value& other) override {
        if (this != &other) {
            const k_Bar& k = dynamic_cast<const k_Bar&>(other);
            Date = k.Date;
            name = k.name;
            exercisePrice = k.exercisePrice;
            expirationDate = k.expirationDate;
            callPut = k.callPut;
            transactionTime = k.transactionTime;
            transactionPrice = k.transactionPrice;
            transactionVolume = k.transactionVolume;
            openingAuctionPrice = k.openingAuctionPrice;
        }
        return *this;
    }
    bool operator!=(const heap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        return Date != k.Date || name != k.name || exercisePrice != k.exercisePrice || expirationDate != k.expirationDate || callPut != k.callPut || transactionTime != k.transactionTime || transactionPrice != k.transactionPrice || transactionVolume != k.transactionVolume || openingAuctionPrice != k.openingAuctionPrice;
    }
    bool operator<(const heap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(transactionPrice < k.transactionPrice) return true;
        else if(transactionPrice == k.transactionPrice) return Date < k.Date;
        else return false;
    }
    bool operator>(const heap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        if(transactionPrice > k.transactionPrice) return true;
        else if(transactionPrice == k.transactionPrice) return Date > k.Date;
        else return false;
    }
    float get_transactionPrice() const {
        return transactionPrice;
    }
    friend ostream& operator<<(ostream& os, const k_Bar& k) {
        os << k.Date << " " << k.name << " " << k.exercisePrice << " " << k.expirationDate << " " << k.callPut << " " << k.transactionTime << " " << k.transactionPrice << " " << k.transactionVolume << " " << k.openingAuctionPrice;
        return os;
    }

    int getNameCount() const {
        return name.size();
    }
    int getDate() const {
        return Date;
    }
    string getName() const {
        return name;
    }

};
void option_Input(ifstream &file,linklist<k_Bar> &TXO_1000_201706_P,
    linklist<k_Bar> &TXO_9500_201706_C,
    linklist<k_Bar> &GIO_5500_201706_C,
    linklist<k_Bar> &TXO_9900_201705_C, int &size)
    {
        string header;
        getline(file, header); // 讀取並忽略表頭行
        getline(file, header); // 讀取並忽略表頭行
        string line;
        while(getline(file, line)){
            stringstream ss(line);
            string item;
            char trash;
            int Date;
            string name;
            float exercisePrice;
            int expirationDate;// month
            char callPut;// C or P
            float transactionTime;
            float transactionPrice;
            float transactionVolume;
            float openingAuctionPrice;
            ss >> Date >> trash >> name >> trash >> exercisePrice >> trash >> expirationDate >> trash >> callPut >> trash >> transactionTime >> trash >> transactionPrice >> trash >> transactionVolume >> trash >> openingAuctionPrice;
            if(!all_products.exist(name)){
                all_products.push_back(name);
            }
            if(name== "TXO" && exercisePrice==1000 && expirationDate==201706 && callPut=='P'){
                TXO_1000_201706_P.push_back(k_Bar(Date, name, exercisePrice, expirationDate, callPut, transactionTime, transactionPrice, transactionVolume, openingAuctionPrice));
            }
            else if(name=="TXO" && exercisePrice==9500 && expirationDate==201706 && callPut=='C'){
                TXO_9500_201706_C.push_back(k_Bar(Date, name, exercisePrice, expirationDate, callPut, transactionTime, transactionPrice, transactionVolume, openingAuctionPrice));
            }
            else if(name=="GIO" && exercisePrice==5500 && expirationDate==201706 && callPut=='C'){
                GIO_5500_201706_C.push_back(k_Bar(Date, name, exercisePrice, expirationDate, callPut, transactionTime, transactionPrice, transactionVolume, openingAuctionPrice));
            }
            else if(name=="TXO" && exercisePrice==9900 && expirationDate==201705 && callPut=='C'){
                TXO_9900_201705_C.push_back(k_Bar(Date, name, exercisePrice, expirationDate, callPut, transactionTime, transactionPrice, transactionVolume, openingAuctionPrice));
            }
            size++;
        }
    }

int main() {
    //////////////////////////////////////////////////////////////////////////////////////input
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    linklist<k_Bar> TXO_1000_201706_P;
    linklist<k_Bar> TXO_9500_201706_C;
    linklist<k_Bar> GIO_5500_201706_C;
    linklist<k_Bar> TXO_9900_201705_C;

    ////2017_05_15
    ifstream file("datasets\\problem2\\OptionsDaily_2017_05_15.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    int size=0;
    option_Input(file, TXO_1000_201706_P, TXO_9500_201706_C, GIO_5500_201706_C, TXO_9900_201705_C, size);
    file.close();
    ////2017_05_16
    file.open("datasets\\problem2\\OptionsDaily_2017_05_16.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, TXO_1000_201706_P, TXO_9500_201706_C, GIO_5500_201706_C, TXO_9900_201705_C, size);
    file.close();
    ////2017_05_17
    file.open("datasets\\problem2\\OptionsDaily_2017_05_17.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, TXO_1000_201706_P, TXO_9500_201706_C, GIO_5500_201706_C, TXO_9900_201705_C, size);
    file.close();
    ////2017_05_18
    file.open("datasets\\problem2\\OptionsDaily_2017_05_18.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, TXO_1000_201706_P, TXO_9500_201706_C, GIO_5500_201706_C, TXO_9900_201705_C, size);
    file.close();
    ////2017_05_19
    file.open("datasets\\problem2\\OptionsDaily_2017_05_19.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, TXO_1000_201706_P, TXO_9500_201706_C, GIO_5500_201706_C, TXO_9900_201705_C, size);
    file.close();

    ////////////////////////////////////////////////////////////////////////////////////////////
    freopen("P2out/output.txt", "w", stdout);
    //(1) 確定這五個數據集中總共有多少獨特的產品。
    cout << "Total number of unique products: " << all_products.size() << endl;
    // 確定特定產品是否存在
    bool TXO_1000_201706_P_exists = !TXO_1000_201706_P.empty();
    bool TXO_9500_201706_C_exists = !TXO_9500_201706_C.empty();
    bool GIO_5500_201706_C_exists = !GIO_5500_201706_C.empty();
    
    cout << "TXO_1000_201706_P exists: " << (TXO_1000_201706_P_exists ? "Yes" : "No") << endl;
    cout << "TXO_9500_201706_C exists: " << (TXO_9500_201706_C_exists ? "Yes" : "No") << endl;
    cout << "GIO_5500_201706_C exists: " << (GIO_5500_201706_C_exists ? "Yes" : "No") << endl;

    // 針對 TXO_9900_201705_C 的操作
    // 找到10個最小價格和最大價格及其時間
    Heap<k_Bar> k_Heap(TXO_9900_201705_C.size());
    for(auto& it: TXO_9900_201705_C) {
        k_Heap.push(it);
    }

    cout << "Top 10 smallest prices with times:" << endl;
    k_Heap.sort();
    for(int i = 0; i < 10 && i < k_Heap.size(); i++) {
        cout << k_Heap[i] << endl;
    }
    cout << endl;

    cout << "Top 10 largest prices with times:" << endl;
    for(int i = k_Heap.size() - 10; i < k_Heap.size(); i++) {
        cout << k_Heap[i] << endl;
    }
    cout << endl;

    // 中位價格
    float median_price;
    int mid_index = k_Heap.size() / 2;
    if (k_Heap.size() % 2 == 0) {
        median_price = (k_Heap[mid_index - 1].get_transactionPrice() + k_Heap[mid_index].get_transactionPrice()) / 2;
    } else {
        median_price = k_Heap[mid_index].get_transactionPrice();
    }
    cout << "Median price: " << median_price << endl;

    // 計算逐筆返回並找到最大和最小返回
    float max_return = -1e9, min_return = 1e9;
    int max_return_index = -1, min_return_index = -1;
    for (int i = 1; i < k_Heap.size(); i++) {
        float return_value = (k_Heap[i].get_transactionPrice() - k_Heap[i - 1].get_transactionPrice()) / k_Heap[i - 1].get_transactionPrice();
        if (return_value > max_return) {
            max_return = return_value;
            max_return_index = i;
        }
        if (return_value < min_return) {
            min_return = return_value;
            min_return_index = i;
        }
    }

    cout << "Max return: " << max_return << " at " << k_Heap[max_return_index].getDate() << endl;
    cout << "Min return: " << min_return << " at " << k_Heap[min_return_index].getDate() << endl;

    return 0;
}
