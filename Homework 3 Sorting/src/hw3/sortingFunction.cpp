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
