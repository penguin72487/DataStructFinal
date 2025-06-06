# 資料結構 2024期末專題
開發演算法 @企鵝72487   
使用演算法 @SiroKu_   
繪圖 @Jaxx   
寫報告 @提醒我打程式  
# 報告Canva連結
[DATA STRUCTURE FINAL PROJECT](https://www.canva.com/design/DAGIdrcn6Es/C-j-c14iJnXv4sfM9aSGpA/edit?utm_content=DAGIdrcn6Es&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)

# request

[原文](finalProject.pdf)  [原文附註釋](finalProject_with註釋.pdf)  
數據結構期末專案  
截止日期：2024年6月21日  

在這個期末專案中，你需要解決兩個主要問題。  

分數配分比例：  
問題 1：40%  
問題 2：32%  
編碼風格：18%  
報告：10%  
每個小組需要壓縮此專案相關的檔案並提交到Moodle上。每組的壓縮檔必須包含：  

所有源代碼  
最終報告（Word檔案，不超過20頁）。在報告中，你需要描述如何解決問題以及每個問題所獲得的結果（可用截圖呈現），並且確定描述每位學生在期末專案中的角色。  
在此專案中，當你需要找到最大值、最小值和中位數時，要求你必須實現Heapsort的C++類並使用這些類進行排序（你需要寫C++類，而不是僅使用C語言）。  
  
問題 1：單一金融產品問題 - 臺灣加權股價指數（TWII）的日常價格  
數據集：「TWII_withRepeatedData.xlsx」  
數據集包含以下5列數據：  
日期  
開盤價  
最高價  
最低價  
收盤價  
任務（A）：  
(1) 確定數據集中有多少獨特的日期。  
在移除重複日期的數據後，使用收盤價解決以下任務：  
(2) 找到10個最小價格及其對應的日期。  
(3) 找到10個最大價格及其對應的日期。  
(4) 找到中位價格及其發生日期。  
(5) 計算每天的日收益率（第一天除外），並確定最大和最小收益率及其發生日期。  
(6) 計算每天的日內收益率，並確定最大和最小收益率及其發生日期。  
(7) 繪製收盤價隨時間變化的圖表，其中x軸為日期索引，y軸為價格。  
(8) 繪製日收益率隨時間變化的圖表，其中x軸為日期索引，y軸為日收益率。  
(9) 繪製日內收益率隨時間變化的圖表，其中x軸為日期索引，y軸為日內收益率。  
(10) 使用所有四列價格數據（開盤價、最高價、最低價、收盤價）找到最大值、最小值和中位價格，並確定它們發生的日期。  
任務（B）：  
對於任務（A）中使用的相同數據集，移除重複日期的數據後，請每五天生成一組抽樣數據，然後對(1)-(10)進行相同的任務。  
問題 2：多金融產品問題 - 選擇權的逐筆價格數據  
數據集：  
「OptionsDaily_2017_05_15.csv」  
「OptionsDaily_2017_05_16.csv」  
「OptionsDaily_2017_05_17.csv」  
「OptionsDaily_2017_05_18.csv」  
「OptionsDaily_2017_05_19.csv」  
主要任務：  
(1) 確定這五個數據集中總共有多少獨特的產品。  
(2) 確定「TXO_1000_201706_P」產品是否存在於這些數據集中。  
(3) 確定「TXO_9500_201706_C」產品是否存在於這些數據集中。  
(4) 確定「GIO_5500_201706_C」產品是否存在於這些數據集中。  
(5) 對於「TXO_9900_201705_C」:  
a. 找到10個最小的價格和顯示這些最小價格的時間（由成交日期和成交時間的唯一組合決定）。  
b. 找到10個最大的價格和顯示這些最大價格的時間。  
c. 找到此產品的中位價格。  
d. 使用成交價格計算逐筆返回（除了第一筆），然後確定最大和最小返回是多少以及何時發生。  


# quickstar
  
請使用C++編譯執行mian.cpp，目前輸出在out.txt
# 資料結構
  
# Heap
  
要使用請  
`#include "Heap.hpp"`  
默認 max_Heap  
  
如果要自訂資料結構當數值，請繼承或是多型heap_Value   
使用`operator<`以及`operator>`去控制max_Heap與min_Heap，順著<或>的順序排序是max_Heap，反之是min_Heap    
    
push(T) 把數值推入堆積    
pop() 把數值移出推積  
top() 得到堆積最大值  
int size() 得到堆積大小  
bool empty() 判斷堆積是否為空  
sort() heap sort，做了之後就在也不是heap了，注意sort會把重複資料給去掉，size要重新獲取
T heap[] 用index取得堆積裡面root陣列的資料，用在heap sort之後  
cout<< 輸出堆積  


# linklist

要使用請  
`#include "linklist.hpp"`  
  

push_back(T) 加入數值  
insert(insex,T) 加入數值by index  
erase(index) 刪除數值by index  
iterator begin() 起始迭代器  
iterator end() 結束迭代器  
int size 返回數量  
bool empty() 判斷是否為空  
clear() 清空  
cout<< 輸出  


# Treap
如果要自訂資料結構當數值，請繼承或是多型treap_Value   
insert(T) 插入資料，而且不會重複資料。  
find(T)尋找某資料  
int size 回傳Treap大小  
slip_By_Value(Treap<T>& a, Treap<T>& b, T value)以小於某個數值切割當結尾切在左邊的a，剩下切在右邊的b  
slip_By_Size(Treap<T>& a, Treap<T>& b, int k)把K個數據切在左邊的a，剩下切在右邊的b  
 T operator[](int index) 輸出 index的數值  
linklist<T> toList()   
cout<< 中序輸出Treap  



