#ifndef SORTINGFUNCTION_H
#define SORTINGFUNCTION_H

#include <vector>
extern long long op_counter;

void ResetCounter();
void Insert(int temp, std::vector<int>& a, int i);
void InsertionSort(std::vector<int>& a, int n);
void QuickSort(std::vector<int>& a, int left, int right);
void Adjust(std::vector<int>& a, int root, int n);
void HeapSort(std::vector<int>& a, int n);
void Merge(const std::vector<int>& initList, std::vector<int>& mergedList, const int l, const int m, const int n);
void MergePass(const std::vector<int>& initList, std::vector<int>& resultList, const int n, const int s);
void MergeSort(std::vector<int>& a, int n);

#endif