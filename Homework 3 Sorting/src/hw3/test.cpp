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