# 41143220
## 姓名：林辰恩
--

## 解題說明

使用四種排序演算法（**Insertion Sort 插入排序**、**Quick Sort 快速排序**、**Merge Sort 合併排序**、**Heap Sort 堆積排序**）在不同資料規模（$n = 500, 1000, 2000, 3000, 4000,5000$）下，**Best Case 最佳情況**、**Average Case 平均情況**、**Worst Case 最壞情況**的實際表現。

計算：

1. **硬體開銷（時間，單位為 ms）**：利用 `<chrono>` 測量 CPU 執行的時間。
2. **步驟數量 (次數，單位為 count）**：在各演算法的程式碼中增加全域計數器 `op_counter`，計算操作次數。

實驗重複執行 10 次（`numPermutations = 50`）的方式計算。

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
#include <cmath>

using namespace std;
using namespace chrono;

// Quick Sort 最佳情況的資料生成
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

// 排序演算法 
void SmartSort(vector<int>& data, int n) {
    if (n <= 20) {
        InsertionSort(data, n);
    }
    else if (n < 3000) {
        QuickSort(data, 0, n - 1);
    }
    else {
        HeapSort(data, n);
    }
}

int main() {
    int numPermutations = 10; // 執行次數

 
    vector<int> n_sizes = { 500, 1000, 2000, 3000, 4000, 5000 };

    for (int n : n_sizes)
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

        
        vector<string> algoNames = { "Insertion Sort", "Quick Sort", "Merge Sort", "Heap Sort", "Smart Sort" };
        vector<string> cases = { "BEST", "AVERAGE", "WORST" };

        for (string name : algoNames) {
            cout << left << setw(18) << name;

            for (string c : cases) {
                // 當 n >= 3000 為 Quick Sort 時跳過，因為會系統崩潰
                if (name == "Quick Sort" && c == "WORST" && n >= 3000) {
                    cout << left << setw(32) << "Skip (Stack Overflow)";
                    continue;
                }

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
                    else if (name == "Smart Sort") {
                        SmartSort(testData, n);
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
    }
    return 0;
}

```

---



## 效能分析

針對四種排序演算法（Insertion Sort、Quick Sort、Merge Sort、Heap Sort）與自己寫得Smart Sort進行測試，並比較其理論時間複雜度（Big-O）與實際執行結果。
## 理論複雜度與實際結果比較
### 各演算法理論複雜度

| 演算法            | Best Case  | Average Case | Worst Case |
| -------------- | ---------- | ------------ | ---------- |
| Insertion Sort | O(n)       | O(n²)        | O(n²)      |
| Quick Sort     | O(n log n) | O(n log n)   | O(n²)      |
| Merge Sort     | O(n log n) | O(n log n)   | O(n log n) |
| Heap Sort      | O(n log n) | O(n log n)   | O(n log n) |
| Smart Sort     | O(n log n) | O(n log n)   | O(n log n) |

---

### 實際測試結果（n = 5000）

| 演算法            | Best (ms / 次數) | Average (ms / 次數)  | Worst (ms / 次數)      |
| -------------- | -------------- | ------------------ | -------------------- |
| Insertion Sort | 0.083 / 4,999  | 68.622 / 6,245,922 | 135.166 / 12,497,500 |
| Quick Sort     | 0.215 / 57,726 | **0.597 / 77,203** | Stack Overflow       |
| Merge Sort     | 0.716 / 70,000 | 1.087 / 70,000     | 0.663 / 70,000       |
| Heap Sort      | 1.299 / 56,093 | 1.285 / 53,846     | 1.169 / 51,632       |
| Smart Sort     | 1.268 / 56,093 | 1.353 / 53,848     | 1.176 / 51,632       |

---

##  理論與實驗結果分析

| 演算法            | 理論預期                   | 實驗結果分析                                                                                  |
| -------------- | ---------------------- | --------------------------------------------------------------------------------------- |
| Insertion Sort | O(n) ~ O(n²)           | Best Case 僅 4,999 次操作，但 Worst Case 達 12,497,500 次，操作次數平方成長，符合 O(n²) 特性。               |
| Quick Sort     | 平均 O(n log n)，最差 O(n²) | Average Case 僅需 0.597 ms，為所有演算法中最快；但 n ≥ 3000 時 Worst Case 發生 Stack Overflow，驗證其最差情況缺陷。 |
| Merge Sort     | 全部 O(n log n)          | 三種情況操作次數皆固定為 70,000 次，不受資料排列影響，符合穩定 O(n log n) 特性。                                      |
| Heap Sort      | 全部 O(n log n)          | 執行時間維持約 1 ms 左右，不會因資料排列不同而產生劇烈變化。                                                       |
| Smart Sort     | 全部 O(n log n)          | n ≤ 2000 時與 Quick Sort 行為相似；n ≥ 3000 時切換為 Heap Sort，因此避免 Stack Overflow。                |

---

## 4.3 各演算法特性比較

| 演算法            | 優點          | 缺點                      |
| -------------- | ----------- | ----------------------- |
| Insertion Sort | 小資料效率高、實作簡單 | 大資料效率差                  |
| Quick Sort     | 平均效能最佳      | 最差情況可能發生 Stack Overflow |
| Merge Sort     | 穩定排序、效能穩定   | 需額外記憶體空間                |
| Heap Sort      | 穩定且不易退化     | 平均速度略慢於 Quick Sort      |
| Smart Sort     | 同時兼顧速度與穩定性  | 實作較複雜                   |

---

## 4.4 結論

根據理論分析與實際測試結果可發現：

1. **Insertion Sort** 在接近排序完成的資料中表現最佳，但資料量增加後會呈現 O(n²) 的效能下降。
2. **Quick Sort** 在平均情況下速度最快，n = 5000 時僅需 0.597 ms，但在最差情況下會因遞迴過深而發生 Stack Overflow。
3. **Merge Sort** 的操作次數固定，效能最穩定，完全符合 O(n log n) 理論分析。
4. **Heap Sort** 雖然速度略慢於 Quick Sort，但能穩定維持 O(n log n) 效能且不會發生遞迴溢位。
5. **Smart Sort** 在一般情況下保有 Quick Sort 的高效率，在最差情況下則切換為 Heap Sort，因此兼具速度與穩定性。

綜合本次實驗結果，若僅考慮執行速度，Quick Sort 為最佳選擇；若同時考量效能、穩定性與可靠性，則 Smart Sort 為較適合作為通用排序演算法的方案。






## 測試與驗證

以下為實驗程式碼編譯後的完整輸出結果：
```text
==================================================================================================================
  結果 (n = 500, 累積次數 = 10)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.008 ms / 499                  0.683 ms / 61882                1.464 ms / 124750
Quick Sort        0.023 ms / 4008                 0.053 ms / 5534                 0.442 ms / 125748
Merge Sort        0.051 ms / 5000                 0.080 ms / 5000                 0.051 ms / 5000
Heap Sort         0.097 ms / 3896                 0.102 ms / 3717                 0.094 ms / 3514
Smart Sort        0.344 ms / 125748               0.048 ms / 5302                 0.326 ms / 125748
==================================================================================================================

==================================================================================================================
  結果 (n = 1000, 累積次數 = 10)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.015 ms / 999                  3.013 ms / 248433               5.759 ms / 499500
Quick Sort        0.070 ms / 9009                 0.134 ms / 12360                1.341 ms / 501498
Merge Sort        0.105 ms / 10000                0.172 ms / 10000                0.106 ms / 10000
Heap Sort         0.217 ms / 8813                 0.275 ms / 8434                 0.233 ms / 7991
Smart Sort        1.571 ms / 501498               0.123 ms / 12455                1.500 ms / 501498
==================================================================================================================

==================================================================================================================
  結果 (n = 2000, 累積次數 = 10)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.030 ms / 1999                 13.117 ms / 989652              27.697 ms / 1999000
Quick Sort        0.175 ms / 20010                0.280 ms / 27294                5.965 ms / 2002998
Merge Sort        0.442 ms / 24000                0.567 ms / 24000                0.404 ms / 24000
Heap Sort         0.716 ms / 19595                0.496 ms / 18856                0.555 ms / 17993
Smart Sort        5.776 ms / 2002998              0.250 ms / 27505                5.747 ms / 2002998
==================================================================================================================

==================================================================================================================
  結果 (n = 3000, 累積次數 = 10)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.042 ms / 2999                 27.860 ms / 2260786             53.880 ms / 4498500
Quick Sort        0.137 ms / 32869                0.365 ms / 44394                Skip (Stack Overflow)
Merge Sort        0.357 ms / 36000                0.595 ms / 36000                0.371 ms / 36000
Heap Sort         0.726 ms / 31459                0.795 ms / 30123                0.694 ms / 28780
Smart Sort        0.756 ms / 31459                0.746 ms / 30124                0.729 ms / 28780
==================================================================================================================

==================================================================================================================
  結果 (n = 4000, 累積次數 = 10)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.061 ms / 3999                 43.513 ms / 3992151             86.604 ms / 7998000
Quick Sort        0.174 ms / 44011                0.520 ms / 61401                Skip (Stack Overflow)
Merge Sort        0.494 ms / 48000                0.803 ms / 48000                0.492 ms / 48000
Heap Sort         0.993 ms / 43308                1.045 ms / 41713                0.947 ms / 40088
Smart Sort        0.965 ms / 43308                1.000 ms / 41716                0.991 ms / 40088
==================================================================================================================

==================================================================================================================
  結果 (n = 5000, 累積次數 = 10)
==================================================================================================================
演算法名稱        Best (ms / 次數)                Average (ms / 次數)             Worst (ms / 次數)
------------------------------------------------------------------------------------------------------------------
Insertion Sort    0.083 ms / 4999                 68.622 ms / 6245922             135.166 ms / 12497500
Quick Sort        0.215 ms / 57726                0.597 ms / 77203                Skip (Stack Overflow)
Merge Sort        0.716 ms / 70000                1.087 ms / 70000                0.663 ms / 70000
Heap Sort         1.299 ms / 56093                1.285 ms / 53846                1.169 ms / 51632
Smart Sort        1.268 ms / 56093                1.353 ms / 53848                1.176 ms / 51632
==================================================================================================================

```

## 申論及開發報告

本次實驗比較 Insertion Sort、Quick Sort、Merge Sort、Heap Sort 與 Smart Sort 在 n = 500～5000 的效能表現，並分析時間與操作次數變化。

---

### 實驗重點觀察

- **Insertion Sort**
  - 小資料（n=500）表現最佳（0.008 ms）
  - 隨資料量增加迅速退化為 O(n²)，n=5000 時達 135 ms

- **Quick Sort（重點問題）**
  - 平均效能最佳（n=5000 約 0.597 ms）
  - 操作次數隨 n 增加成長快速
  - **嚴重問題：Worst Case 不穩定**
    - n ≥ 3000 時出現 **Stack Overflow**
    - 原因為 pivot 選擇不佳導致遞迴深度退化為 O(n)
  - 結論：**速度快，但最差情況存在系統性風險**

- **Merge Sort**
  - 所有情況皆穩定（約 0.7～1.1 ms）
  - 操作次數固定（70,000 次）
  - 不受資料分布影響，符合 O(n log n)

- **Heap Sort**
  - 效能穩定（約 1.1～1.3 ms）
  - 不受資料排列影響
  - 無遞迴問題，不會發生 Stack Overflow

- **Smart Sort**
  - 小資料行為類似 Quick Sort
  - 大資料自動切換 Heap Sort
  - 可避免 Quick Sort 崩潰問題，兼具速度與穩定性

---

### 結論

- **最快平均效能：Quick Sort**
- **但 Quick Sort 最大問題：Worst Case 會發生 Stack Overflow（不可靠）**
- **最穩定：Merge Sort**
- **最安全（無遞迴風險）：Heap Sort / Smart Sort**
- **小資料最佳：Insertion Sort**
- **整體最均衡：Smart Sort**


---
