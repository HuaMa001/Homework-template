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
    int n = 2; // 皚
    int numPermutations = 50; // 禲Ω计

    while (n <= 3000)
    {
        random_device rd;
        mt19937 rng(rd());

        cout << "==================================================================================================================" << endl;
        cout << "  挡狦 (n = " << n << ", 仓縩Ω计 = " << numPermutations << ")" << endl;
        cout << "==================================================================================================================" << endl;
        cout << left << setw(18) << "簍衡猭嘿"
            << setw(32) << "Best (ms / Ω计)"
            << setw(32) << "Average (ms / Ω计)"
            << setw(32) << "Worst (ms / Ω计)" << endl;
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

                    // 睲箂璸计竟
                    ResetCounter();

                    // 秨﹍璸
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

                    // 挡璸
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