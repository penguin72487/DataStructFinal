#include "Treap.hpp"
#include "linklist.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#define endl "\n"
#define FLT_MAX 3.402823466e+38F
class k_Bar : public treap_Value {
    int Date;
    string name;
    float exercisePrice;
    int expirationDate; // month
    char callPut; // C or P
    float transactionTime;
    float transactionPrice;
    float transactionVolume;
    float openingAuctionPrice;

public:
    k_Bar() : Date(0), name(""), exercisePrice(0), expirationDate(0), callPut('\0'), transactionTime(0), transactionPrice(0), transactionVolume(0), openingAuctionPrice(0) {}
    k_Bar(int _Date, string _name,  float _exercisePrice, int _expirationDate, char _callPut, float _transactionTime, float _transactionPrice, float _transactionVolume, float _openingAuctionPrice) : Date(_Date), name(_name), exercisePrice(_exercisePrice), expirationDate(_expirationDate), callPut(_callPut), transactionTime(_transactionTime), transactionPrice(_transactionPrice), transactionVolume(_transactionVolume), openingAuctionPrice(_openingAuctionPrice) {}
    treap_Value& operator=(const treap_Value& other) override {
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
    bool operator!=(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        return Date != k.Date || name != k.name || exercisePrice != k.exercisePrice || expirationDate != k.expirationDate || callPut != k.callPut || transactionTime != k.transactionTime || transactionPrice != k.transactionPrice || transactionVolume != k.transactionVolume || openingAuctionPrice != k.openingAuctionPrice;
    }
    bool operator<(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        // priorty name exercisePrice expirationDate callPut transactionPrice transactionTime transactionVolume openingAuctionPrice
        if(name < k.name) return true;
        else if(name == k.name) {
            if(exercisePrice < k.exercisePrice) return true;
            else if(exercisePrice == k.exercisePrice) {
                if(expirationDate < k.expirationDate) return true;
                else if(expirationDate == k.expirationDate) {
                    if(callPut < k.callPut) return true;
                    else if(callPut == k.callPut) {
                        if(transactionPrice < k.transactionPrice) return true;
                        else if(transactionPrice == k.transactionPrice) {
                            if(transactionTime < k.transactionTime) return true;
                            else if(transactionTime == k.transactionTime) {
                                if(transactionVolume < k.transactionVolume) return true;
                                else if(transactionVolume == k.transactionVolume) {
                                    if(openingAuctionPrice < k.openingAuctionPrice) return true;
                                    else return false;
                                } else return false;
                            } else return false;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    }
    bool operator>(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        // priorty name exercisePrice expirationDate callPut transactionPrice transactionTime transactionVolume openingAuctionPrice
        if(name > k.name) return true;
        else if(name == k.name) {
            if(exercisePrice > k.exercisePrice) return true;
            else if(exercisePrice == k.exercisePrice) {
                if(expirationDate > k.expirationDate) return true;
                else if(expirationDate == k.expirationDate) {
                    if(callPut > k.callPut) return true;
                    else if(callPut == k.callPut) {
                        if(transactionPrice > k.transactionPrice) return true;
                        else if(transactionPrice == k.transactionPrice) {
                            if(transactionTime > k.transactionTime) return true;
                            else if(transactionTime == k.transactionTime) {
                                if(transactionVolume > k.transactionVolume) return true;
                                else if(transactionVolume == k.transactionVolume) {
                                    if(openingAuctionPrice > k.openingAuctionPrice) return true;
                                    else return false;
                                } else return false;
                            } else return false;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    }
    bool operator==(const treap_Value& b) const override {
        const k_Bar& k = dynamic_cast<const k_Bar&>(b);
        return Date == k.Date && name == k.name && exercisePrice == k.exercisePrice && expirationDate == k.expirationDate && callPut == k.callPut && transactionTime == k.transactionTime && transactionPrice == k.transactionPrice && transactionVolume == k.transactionVolume && openingAuctionPrice == k.openingAuctionPrice;
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

void option_Input(ifstream &file, Treap<k_Bar> &treap, Treap<string> &uniProduct) {
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
        int expirationDate; // month
        char callPut; // C or P
        float transactionTime;
        float transactionPrice;
        float transactionVolume;
        float openingAuctionPrice;
        ss >> Date >> trash >> name >> trash >> exercisePrice >> trash >> expirationDate >> trash >> callPut >> trash >> transactionTime >> trash >> transactionPrice >> trash >> transactionVolume >> trash >> openingAuctionPrice;
        treap.insert(k_Bar(Date, name, exercisePrice, expirationDate, callPut, transactionTime, transactionPrice, transactionVolume, openingAuctionPrice));
        uniProduct.insert(name+" "+to_string(exercisePrice)+" "+to_string(expirationDate)+" "+callPut);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    Treap<k_Bar> treap;
    Treap<string> uniProduct;
    ////2017_05_15
    ifstream file("datasets\\problem2\\OptionsDaily_2017_05_15.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, treap, uniProduct);
    file.close();
    ////2017_05_16
    file.open("datasets\\problem2\\OptionsDaily_2017_05_16.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, treap, uniProduct);
    file.close();
    ////2017_05_17
    file.open("datasets\\problem2\\OptionsDaily_2017_05_17.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, treap, uniProduct);
    file.close();
    ////2017_05_18
    file.open("datasets\\problem2\\OptionsDaily_2017_05_18.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, treap, uniProduct);
    file.close();
    ////2017_05_19
    file.open("datasets\\problem2\\OptionsDaily_2017_05_19.csv");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    option_Input(file, treap, uniProduct);
    file.close();
    ////2017_05_22
    ////////////////////////////////////////////////////////////////////////////////////////////
    freopen("P2out/outputTreap.txt", "w", stdout);
    cout << "Treap" << endl;
    // cout<<treap<<endl;
    // cout<<uniProduct<<endl;
    cout<<"totle number of unique products: "<<uniProduct.size()<<endl;
    cout<<"totle number of transactions: "<<treap.size()<<endl;
    cout<<"TXO_1000_201706_P exists?: "<<endl;
    uniProduct.find("TXO 1000.000000 201706 P")? cout<<"Yes"<<endl: cout<<"No"<<endl;
    cout<<"TXO_9500_201706_C exists?: "<<endl;
    uniProduct.find("TXO 9500.000000 201706 C")? cout<<"Yes"<<endl: cout<<"No"<<endl;
    cout<<"TXO_5500_201706_C exists?: "<<endl;
    uniProduct.find("TXO 5500.000000 201706 C")? cout<<"Yes"<<endl: cout<<"No"<<endl;
    cout << "TXO_9900_201705_C exists?: " << endl;
    uniProduct.find("TXO 9900.000000 201705 C")? cout<<"Yes"<<endl: cout<<"No"<<endl;
    Treap<k_Bar> TXO_9900_201705_C;
    Treap<k_Bar> a, b;
    treap.slip_By_Value(a, TXO_9900_201705_C, k_Bar(0, "TXO", 9900, 201705, 'C', 0, 0, 0, 0));
    // cout<<TXO_9900_201705_C.size()<<endl;
    // cout<<TXO_9900_201705_C<<endl;
    TXO_9900_201705_C.slip_By_Value(TXO_9900_201705_C, b, k_Bar(0, "TXO", 9900, 201705, 'C', 0, FLT_MAX, 0, 0));
    cout<<TXO_9900_201705_C.size()<<endl;
    // cout<<TXO_9900_201705_C<<endl;
    Treap<k_Bar> e, f;
    TXO_9900_201705_C.slip_By_Size(e, f, 10);
    cout<<"Small 10"<<endl;
    cout<<e<<endl;
    // TXO_9900_201705_C.merge(e);
    cout<<"Big 10"<<endl;

    TXO_9900_201705_C.slip_By_Size(e, f, TXO_9900_201705_C.size()-10);
    // cout<<"E"<<endl; // "E" is the name of the variable
    // cout<<e<<endl;
    cout<<f<<endl;
    // TXO_9900_201705_C.merge(e, f);
    cout<<"Middle"<<endl;
    if(TXO_9900_201705_C.size()&1){
        cout<<TXO_9900_201705_C[TXO_9900_201705_C.size()/2]<<endl;
    }
    else{
        auto it = TXO_9900_201705_C[TXO_9900_201705_C.size()/2];
        auto it2 = TXO_9900_201705_C[TXO_9900_201705_C.size()/2-1];
        cout << it << endl<< it2<<endl;
        cout<<"Average: "<<(it.get_transactionPrice()+it2.get_transactionPrice())/2<<endl;
    }

    // cout<<treap<<endl;
    



    return 0;
}
