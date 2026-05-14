// Program Selection Sort menggunakan teknik Decrease and Conquer
#include <iostream>
using namespace std;

// Fungsi swap
void tukar(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Fungsi Selection Sort
void selectionSort(int arr[], int n) {

    // Mengurangi masalah sedikit demi sedikit
    for (int i = 0; i < n - 1; i++) {

        // Anggap elemen pertama adalah yang terkecil
        int min_idx = i;

        // Cari elemen terkecil pada bagian yang belum terurut
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Tukar elemen terkecil dengan posisi sekarang
        tukar(arr[i], arr[min_idx]);

        // Tampilkan proses
        cout << "Langkah " << i + 1 << " : ";
        for (int k = 0; k < n; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;
    }
}

// Fungsi menampilkan array
void tampilArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Program utama
int main() {

    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array sebelum diurutkan:\n";
    tampilArray(arr, n);

    cout << "\nProses Selection Sort:\n";
    selectionSort(arr, n);

    cout << "\nArray setelah diurutkan:\n";
    tampilArray(arr, n);

    return 0;
}