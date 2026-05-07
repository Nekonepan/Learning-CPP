#include <iostream>
#include <algorithm>
using namespace std;

// Prototype fungsi
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void merge(int arr[], int left, int mid, int right, int& step);
void mergeSort(int arr[], int left, int right, int& step);
void printArray(int arr[], int n);
void printSubArray(int arr[], int left, int right);

int main() {
    // Bubble Sort
    int arr1[] = {64, 25, 12, 22, 11};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Original array for Bubble Sort: ";
    printArray(arr1, n1);
    bubbleSort(arr1, n1);
    cout << "Final result of Bubble Sort: ";
    printArray(arr1, n1);
    cout << endl;

    // Selection Sort
    int arr2[] = {29, 10, 14, 37, 13};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Original array for Selection Sort: ";
    printArray(arr2, n2);
    selectionSort(arr2, n2);
    cout << "Final result of Selection Sort: ";
    printArray(arr2, n2);
    cout << endl;

    // Merge Sort
    int arr3[] = {38, 27, 43, 3, 9, 82, 10};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int step = 1;
    cout << "Original array for Merge Sort: ";
    printArray(arr3, n3);
    mergeSort(arr3, 0, n3 - 1, step);
    cout << "Final result of Merge Sort: ";
    printArray(arr3, n3);

    return 0;
}

// Bubble Sort (Ascending)
void bubbleSort(int arr[], int n) {
    int step = 1;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                cout << "Langkah " << step++ 
                     << ": Tukar " << arr[j] 
                     << " dan " << arr[j+1] << " -> ";
                swap(arr[j], arr[j+1]);
                printArray(arr, n);
            }
        }
    }
}

// Selection Sort (Ascending)
void selectionSort(int arr[], int n) {
    int step = 1;
    for(int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[min_idx])
                min_idx = j;
        }
        if(min_idx != i) {
            cout << "Langkah " << step++ 
                 << ": Tukar " << arr[i] 
                 << " dan " << arr[min_idx] << " -> ";
            swap(arr[i], arr[min_idx]);
            printArray(arr, n);
        }
    }
}

// Merge Sort
void mergeSort(int arr[], int left, int right, int& step) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, step);
        mergeSort(arr, mid + 1, right, step);
        merge(arr, left, mid, right, step);
    }
}

// Merge (Ascending)
void merge(int arr[], int left, int mid, int right, int& step) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];
    while(j < n2)
        arr[k++] = R[j++];

    cout << "Langkah " << step++ 
         << ": Merge index " << left 
         << " to " << right << " -> ";
    printSubArray(arr, left, right);

    delete[] L;
    delete[] R;
}

// Cetak seluruh array
void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Cetak sebagian array (untuk merge)
void printSubArray(int arr[], int left, int right) {
    for(int i = left; i <= right; i++)
        cout << arr[i] << " ";
    cout << endl;
}
