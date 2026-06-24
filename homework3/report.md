# 41143220
## 姓名：林辰恩
--

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
- **BEST Case：正序**
  - 其中 Quick Sort 的 Best Case 測資採用特別方式：
    先將區間切成對半進行處理，最後再將中間元素交換到最左端作為 pivot，以模擬最佳情況下的快速排序行為。
    ```
    EX:[0,1,2,3,4,5,6,7,8,9,10]
       [0,1,2,3,4]5[6,7,8,9,10] mid=5  
       [0,1]2[3,4]5[6,7]8[9,10] mid=2 和 mid=8  
       -------遞迴到底，開始swap left和mid-------
       [0,1]2[3,4]5[6,7]8[9,10] 
       [2,1,0,3,4]5[8,7,6,9,10]
       [5,1,0,3,4,2,8,7,6,9,10] //最佳化的排序

       -------Quick_sort 實作[5,1,0,3,4,2,8,7,6,9,10]最佳化的排序-------
                  [2,1,0,3,4]5[8,7,6,9,10]  <--pivot 選5 
    pivot 選2-->  [0,1]2[3,4]5[6,7]8[9,10]  <--pivot 選8 
                  [0,1,2,3,4,5,6,7,8,9,10]
    ```
- **WORST Case：倒序**
  - 資料由大到小排列，用於測試排序演算法在最差情況下的效能表現。

- **AVERAGE Case：隨機分布**
  - 使用 `mt19937` 產生隨機數據，以模擬一般實際應用中的資料分布情況。

```cpp
#include "SortingFunction.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm> 

using namespace std;
using namespace chrono;


void QuickSortBestCase(vector<int>& data, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    QuickSortBestCase(data, left, mid - 1);
    QuickSortBestCase(data, mid + 1, right);
    swap(data[left], data[mid]);
}

vector<int> getTestData(int n, string caseType, string algoName, mt19937& rng) {
    vector<int> data(n);
    for (int i = 0; i < n; i++)
        data[i] = i + 1; 

    if (caseType == "BEST") {
        if (algoName == "Quick Sort") {
            QuickSortBestCase(data, 0, n - 1);
        }     
        else {
            
        }
    }
    else if (caseType == "WORST") {
        if (algoName == "Insertion Sort" || algoName == "Quick Sort") {
            
            reverse(data.begin(), data.end());
        }
        else {
            reverse(data.begin(), data.end());
        }
    }
    else if (caseType == "AVERAGE") {
        
        shuffle(data.begin(), data.end(), rng);
    }
    return data;
}

int main() {
    int n = 2; // 陣列大小
    int numPermutations = 50; // 跑的次數

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

        vector<string> algoNames = { "Insertion Sort", "Quick Sort", "Merge Sort", "Heap Sort" };
        vector<string> cases = { "BEST", "AVERAGE", "WORST" };

        for (string name : algoNames) {
            cout << left << setw(18) << name;

            for (string c : cases) {
                double total_time = 0.0;
                long long total_ops = 0;

                for (int p = 0; p < numPermutations; p++) {
                    vector<int> testData = getTestData(n, c, name, rng);

                    // 清零計數器
                    ResetCounter();

                    // 開始計時
                    auto start = high_resolution_clock::now();

                   
                    if (name == "Insertion Sort") {
                        InsertionSort(testData, n);
                    }
                    else if (name == "Quick Sort") {
                        QuickSort(testData, 0, n - 1); 
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
                snprintf(buffer, sizeof(buffer),
                    "%.3f ms / %lld",
                    total_time / numPermutations,
                    total_ops / numPermutations);
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

針對四種排序演算法（Insertion Sort、Quick Sort、Merge Sort、Heap Sort）進行測試，並比較其理論時間複雜度（Big-O）與實際執行結果。

---

### 1. Insertion Sort（插入排序）

| 情況 | 理論複雜度 |
|------|-----------|
| Best Case | O(n) |
| Average Case | O(n²) |
| Worst Case | O(n²) |

Insertion Sort 在資料接近排序完成時表現最佳，只需少量比較與移動。

從實驗結果（n = 2000）可觀察：

- Best：0.025 ms / 1999 次
- Average：10.731 ms / 1,001,953 次
- Worst：20.208 ms / 1,999,000 次

可以明顯看出：

- Best Case 操作次數接近 O(n)
- Average 與 Worst Case 操作次數快速增加，呈現平方級成長

這驗證了 Insertion Sort 在資料量變大時效率會迅速下降，特別是反序排列時，效能最差。

---

### 2. Quick Sort（快速排序）

| 情況 | 理論複雜度 |
|------|-----------|
| Best Case | O(n log n) |
| Average Case | O(n log n) |
| Worst Case | O(n²) |

Quick Sort 在大多數情況下表現良好，但 Pivot 選擇會嚴重影響效能。

### 實驗結果（n = 2000）：

- Best：0.139 ms / 20,010 次
- Average：0.240 ms / 27,437 次
- Worst：5.503 ms / 2,002,998 次

### 分析：

- Best 與 Average 差異小，表示分割大致均勻
- Worst Case 操作次數大幅增加，接近 O(n²)
- 代表 Pivot 在 Worst Case 造成分割不均勻

---

### 3. Merge Sort（合併排序）

| 情況 | 理論複雜度 |
|------|-----------|
| Best Case | O(n log n) |
| Average Case | O(n log n) |
| Worst Case | O(n log n) |

Merge Sort 的特點是**穩定且不受資料排列影響**。

### 實驗結果（n = 2000）：

- Best：0.218 ms / 24,000 次
- Average：0.372 ms / 24,000 次
- Worst：0.234 ms / 24,000 次

### 分析：

- 三種情況操作次數幾乎完全一致
- stable排序法
- 完全符合 O(n log n) 穩定特性

---

### 4. Heap Sort（堆積排序）

| 情況 | 理論複雜度 |
|------|-----------|
| Best Case | O(n log n) |
| Average Case | O(n log n) |
| Worst Case | O(n log n) |

Heap Sort MAX-heap二元樹實作。

### 實驗結果（n = 2000）：

- Best：0.414 ms / 19,595 次
- Average：0.456 ms / 18,855 次
- Worst：0.386 ms / 17,993 次

### 分析：

- 三種情況差異極小
- 操作次數穩定維持在 O(n log n) 範圍
- 但整體執行時間略高於 Quick Sort

---

### 綜合比較分析

從實驗結果可歸納以下重點：


### 1. Insertion Sort

- 小資料量表現尚可
- n 增加後呈現 O(n²) 成長
- 不適合大規模資料

---

### 2. Quick Sort

- 平均效能最佳
- 適合大多數情境
- Worst Case 會退化為 O(n²)

---

### 3. Merge Sort

- 最穩定排序演算法
- 永遠維持 O(n log n)
- 但需要額外記憶體空間

---

### 4. Heap Sort

- 時間複雜度穩定
- 不需額外大記憶體
- 但常數時間成本較高

---

### 不同資料(N)選擇

| 資料規模 | 建議排序法 |
|----------|------------|
| n < 50 | Insertion Sort |
| 50 ~ 1000 | Quick Sort |
| n > 1000 | Quick / Merge Sort |
| 需要穩定排序 | Merge Sort |
| 記憶體受限 | Heap Sort |

---

### 總結

本次結果驗證以下結論：

- O(n²) 演算法（Insertion Sort）在大資料量下效率明顯下降
- O(n log n) 演算法（Quick / Merge / Heap）在大資料量仍保持良好效能
- Quick Sort 平均最快，但最壞情況不穩定
- Merge Sort 最穩定，但需要額外記憶體
- Heap Sort 在空間效率與穩定性間取得平衡

整體而言，本實驗結果與理論 Big-O 分析一致，驗證不同排序演算法在不同資料規模下的效能差異。


## 測試與驗證

以下為實驗程式碼編譯後的完整輸出結果：
```text
==================================================================================================================
  結果 (n = 2, 累積次數 = 50)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.000 ms / 1                    0.000 ms / 1                    0.000 ms / 1
Quick Sort        0.000 ms / 3                    0.000 ms / 3                    0.000 ms / 3
Merge Sort        0.001 ms / 4                    0.001 ms / 4                    0.001 ms / 4
Heap Sort         0.000 ms / 1                    0.000 ms / 1                    0.000 ms / 1
==================================================================================================================

==================================================================================================================
  結果 (n = 20, 累積次數 = 50)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.000 ms / 19                   0.002 ms / 109                  0.003 ms / 190
Quick Sort        0.001 ms / 78                   0.001 ms / 96                   0.001 ms / 228
Merge Sort        0.002 ms / 120                  0.003 ms / 120                  0.003 ms / 120
Heap Sort         0.003 ms / 63                   0.003 ms / 59                   0.002 ms / 54
==================================================================================================================

==================================================================================================================
  結果 (n = 200, 累積次數 = 50)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.003 ms / 199                  0.096 ms / 10066                0.208 ms / 19900
Quick Sort        0.007 ms / 1407                 0.017 ms / 1863                 0.057 ms / 20298
Merge Sort        0.017 ms / 1600                 0.026 ms / 1600                 0.028 ms / 1600
Heap Sort         0.030 ms / 1296                 0.035 ms / 1231                 0.027 ms / 1146
==================================================================================================================

==================================================================================================================
  結果 (n = 2000, 累積次數 = 50)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.025 ms / 1999                 10.731 ms / 1001953             20.208 ms / 1999000
Quick Sort        0.139 ms / 20010                0.240 ms / 27437                5.503 ms / 2002998
Merge Sort        0.218 ms / 24000                0.372 ms / 24000                0.234 ms / 24000
Heap Sort         0.414 ms / 19595                0.456 ms / 18855                0.386 ms / 17993
==================================================================================================================

```

## 申論及開發報告

在本次實作中，四種排序演算法皆在不同資料規模（n = 2, 20, 200, 2000）下進行測試，並觀察其時間與操作次數變化。

整體結果大致符合 Big-O 理論分析，但在實際執行過程中，也出現部分系統限制。

---

### Quick Sort 記憶體與遞迴深度問題

當資料規模增加至 n ≥ 3000 時，Quick Sort 出現遞迴深度過深的問題，導致系統記憶體壓力上升，甚至無法完成完整測試。

其原因如下：

- Quick Sort 為遞迴式分割演算法
- 在最壞情況下（Worst Case），遞迴深度會退化為 O(n)
- 若 pivot 選擇不佳且在資料量較大時，系統呼叫堆疊（stack）快速增加

因此在 n ≥ 3000 時，實際執行會出現：
- 遞迴呼叫過深
- 記憶體不足或執行終止的情況

---

### 其他演算法穩定性分析

相較之下：

- Merge Sort：遞迴深度固定為 O(log n)，記憶體穩定
- Heap Sort：非遞迴式結構，不受 stack 深度影響
- Insertion Sort：雖為 O(n²)，但不涉及遞迴，因此不會有記憶體問題

---

### 開發與實作觀察

在實作過程中，本實驗採用：

- `chrono` 進行時間測量
- 全域變數 `op_counter` 計算操作次數
- `mt19937` 產生隨機測資
- 重複執行 50 次取平均值以降低誤差

透過上述設計，可以較準確反映不同排序演算法在各種資料分布下的實際效能。

---

### 結論補充

雖然 Quick Sort 在平均情況下擁有最佳效能，但實驗結果顯示其對 pivot 選擇與資料分布非常敏感。

因此在實務應用中：

- 若資料規模較小或可控 → Quick Sort 最佳
- 若資料規模極大或要求穩定 → Merge Sort 或 Heap Sort 較適合
- 若資料接近排序完成 → Insertion Sort 仍具優勢


---
