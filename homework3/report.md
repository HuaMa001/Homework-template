# 41143220
## 姓名：林辰恩




---

## 解題說明

使用四種排序演算法（**Insertion Sort 插入排序**、**Quick Sort 快速排序**、**Merge Sort 合併排序**、**Heap Sort 堆積排序**）在不同資料規模（$n = 2, 20, 200, 2000$）下，**Best Case 最佳情況**、**Average Case 平均情況**、**Worst Case 最壞情況**的實際表現。

計算：

1. **硬體開銷（時間，單位為 ms）**：利用 `<chrono>` 測量 CPU 執行的時間。
2. **步驟數量 (次數，單位為 count）**：在各演算法的程式碼中增加全域計數器 `op_counter`，計算操作次數。

實驗重複執行 50 次（`numPermutations = 50`）的方式計算。

---

## 程式實作

排序演算法於 `sortingFunction.cpp`，測資產生及結果輸出於 `test.cpp`。

### sortingFunction.cpp

```cpp
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
long long op_counter = 0;

void ResetCounter() {
    op_counter = 0;
}


void Insert(int temp, vector<int>& a, int i)
{
    while (i >= 0 && (op_counter++, temp < a[i]))
    {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = temp;
}

void InsertionSort(vector<int>& a, int n)
{
    for (int j = 1; j < n; j++) {
        int temp = a[j];
        Insert(temp, a, j - 1);
    }
}


void QuickSort(vector<int>& a, int left, int right)
{
    if (left < right)
    {
        int i = left,
            j = right + 1,
            pivot = a[left];
        do {
            do { i++; op_counter++; } while (i <= right && a[i] < pivot);
            do { j--; op_counter++; } while (j >= left && a[j] > pivot);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(a[left], a[j]);

        QuickSort(a, left, j - 1);
        QuickSort(a, j + 1, right);
    }
}


void Adjust(vector<int>& a, int root, int n)
{
    int j;
    int e = a[root];
  
    for (j = 2 * root + 1; j < n; j = 2 * j + 1)
    {
        op_counter++; 

        // 找出左右子節點中較大者
        if (j + 1 < n && a[j] < a[j + 1]) {
            j++;
        }

        // 比較父節點與較大子節點的值
        if (e >= a[j]) {
            break;
        }

        a[(j - 1) / 2] = a[j];
    }
    a[(j - 1) / 2] = e;
}

void HeapSort(vector<int>& a, int n)
{
    
    for (int i = n / 2 - 1; i >= 0; i--)
        Adjust(a, i, n);

    
    for (int i = n - 1; i >= 1; i--)
    {
        swap(a[0], a[i]);
        Adjust(a, 0, i);
    }
}


void Merge(const vector<int>& initList, vector<int>& mergedList, const int l, const int m, const int n) {
    int i1 = l, iResult = l, i2 = m + 1;
    while (i1 <= m && i2 <= n) {
        op_counter++; 
        if (initList[i1] <= initList[i2]) {
            mergedList[iResult++] = initList[i1++];
        }
        else {
            mergedList[iResult++] = initList[i2++];
        }
    }
    while (i1 <= m) { mergedList[iResult++] = initList[i1++]; op_counter++; }
    while (i2 <= n) { mergedList[iResult++] = initList[i2++]; op_counter++; }
}

void MergePass(const vector<int>& initList, vector<int>& resultList, const int n, const int s) {
    int i;
    for (i = 0; i <= n - 2 * s; i += 2 * s) {
        Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);
    }
    if ((i + s - 1) < n - 1) {
        Merge(initList, resultList, i, i + s - 1, n - 1);
    }
    else {
        for (int k = i; k < n; k++) {
            resultList[k] = initList[k];
            op_counter++;
        }
    }
}

void MergeSort(vector<int>& a, int n) {
    vector<int> tempList(n);
    for (int l = 1; l < n; l *= 2) {
        MergePass(a, tempList, n, l);
        l *= 2;
        MergePass(tempList, a, n, l);
    }
}

```

### test.cpp

```cpp
#include "SortingFunction.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using namespace chrono;


void QuickSortBestCase(vector<int>& data, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // 將這一區段的中位數，與最左邊（即 Pivot 位置）交換
    swap(data[left], data[mid]);

    // 遞迴處理左半邊與右半邊，確保下一層的第一個元素也是中位數
    QuickSortBestCase(data, left + 1, mid);
    QuickSortBestCase(data, mid + 1, right);
}

vector<int> getTestData(int n, string caseType, string algoName, mt19937& rng) {
    vector<int> data(n + 1);
    for (int i = 1; i <= n; i++) data[i] = i;

    if (caseType == "BEST") {
        if (algoName == "Quick Sort") {
            QuickSortBestCase(data, 1, n);
        }
        else {
            
        }
    }
    else if (caseType == "WORST") {
        reverse(data.begin() + 1, data.end()); 
    }
    else if (caseType == "AVERAGE") {
        shuffle(data.begin() + 1, data.end(), rng); 
    }
    return data;
}

int main() {
    int n = 2; // 陣列大小
    int numPermutations = 50; // 跑ㄉ次數

    while (n <= 3000)
    {
        random_device rd;
        mt19937 rng(rd());
  
        cout << "==================================================================================================================" << endl;
        cout << "  結果 (n = " << n << ", 累積次數 = " << numPermutations << ")" << endl;
        cout << "==================================================================================================================" << endl;
        cout << left << setw(18) << "演算法名稱"
            << setw(32) << "Best (ms / 次數)"
            << setw(32) << "Average (ms / 次數)"
            << setw(32) << "Worst (ms / 次數)" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------" << endl;

        // 四種演算法清單，迴圈跑
        vector<string> algoNames = { "Insertion Sort", "Quick Sort", "Merge Sort", "Heap Sort" };
        vector<string> cases = { "BEST", "AVERAGE", "WORST" };

        for (string name : algoNames) {
            cout << left << setw(18) << name;

            // 依序跑 Best, Average, Worst 三種情況
            for (string c : cases) {
                double total_time = 0.0;
                long long total_ops = 0;

                for (int p = 0; p < numPermutations; p++) {
                    vector<int> testData = getTestData(n, c, name, rng);

                    // 清零
                    ResetCounter();

                    // 開始計時
                    auto start = high_resolution_clock::now();

                    if (name == "Insertion Sort") {
                        InsertionSort(testData, n);
                    }
                    else if (name == "Quick Sort") {
                        QuickSort(testData, 1, n);
                    }
                    else if (name == "Merge Sort") {
                        MergeSort(testData, n);
                    }
                    else if (name == "Heap Sort") {
                        HeapSort(testData, n);
                    }

                    // 結束計時
                    auto end = high_resolution_clock::now();
                    duration<double, std::milli> elapsed = end - start;

                    total_time += elapsed.count();
                    total_ops += op_counter;
                }
   
                char buffer[100];
                snprintf(buffer, sizeof(buffer), "%.3f ms / %lld", total_time, total_ops);
                cout << left << setw(32) << buffer;
            }
            cout << endl;
        }
        cout << "==================================================================================================================" << endl << endl;
        n *= 10;
    }
    return 0;
}

```

---

## 效能分析



---

## 測試與驗證

以下為實驗程式碼編譯後的完整輸出結果：

```text
==================================================================================================================
  結果 (n = 2, 累積次數 = 50)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)               
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.005 ms / 50                   0.005 ms / 50                   0.005 ms / 50                   
Quick Sort        0.009 ms / 150                  0.007 ms / 150                  0.007 ms / 150                  
Merge Sort        0.042 ms / 200                  0.050 ms / 200                  0.068 ms / 200                  
Heap Sort         0.011 ms / 50                   0.014 ms / 50                   0.012 ms / 50                   
==================================================================================================================

==================================================================================================================
  結果 (n = 20, 累積次數 = 50)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)               
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.023 ms / 950                  0.170 ms / 5189                 0.181 ms / 9500                 
Quick Sort        0.039 ms / 4250                 0.067 ms / 4976                 0.073 ms / 11400                
Merge Sort        0.124 ms / 6000                 0.146 ms / 6000                 0.121 ms / 6000                 
Heap Sort         0.096 ms / 3150                 0.123 ms / 3007                 0.086 ms / 2750                 
==================================================================================================================

==================================================================================================================
  結果 (n = 200, 累積次數 = 50)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次訊)             Worst (ms / 次數)               
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.212 ms / 9950                 4.922 ms / 500900               9.703 ms / 995000               
Quick Sort        0.400 ms / 88300                1.122 ms / 90554                2.866 ms / 1014900              
Merge Sort        0.969 ms / 80000                1.810 ms / 80000                1.092 ms / 80000                
Heap Sort         1.589 ms / 64800                1.546 ms / 61604                1.388 ms / 57550                
==================================================================================================================

==================================================================================================================
  結果 (n = 2000, 累積次數 = 50)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)               
------------------------------------------------------------------------------------------------------------------
Insertion Sort    1.403 ms / 99950                577.880 ms / 50018552           1204.038 ms / 99950000          
Quick Sort        6.364 ms / 1390950              11.373 ms / 1361345             262.270 ms / 100149900          
Merge Sort        12.903 ms / 1200000             22.041 ms / 1200000             13.714 ms / 1200000             
Heap Sort         23.973 ms / 979750              21.387 ms / 943097              19.221 ms / 902550              
==================================================================================================================

```

## 申論及開發報告


---
