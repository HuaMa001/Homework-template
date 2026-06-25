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