#include <iostream>
using namespace std;

// Fungsi Insertion Sort
void insertionSort(int arr[], int n) {

    // Mengurangi masalah sedikit demi sedikit
    for (int i = 1; i < n; i++) {

        // Elemen yang akan disisipkan
        int key = arr[i];

        // Indeks elemen sebelumnya
        int j = i - 1;

        // Geser elemen yang lebih besar ke kanan
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Sisipkan elemen pada posisi yang benar
        arr[j + 1] = key;

        // Tampilkan proses
        cout << "Langkah " << i << " : ";
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

    cout << "\nProses Insertion Sort:\n";
    insertionSort(arr, n);

    cout << "\nArray setelah diurutkan:\n";
    tampilArray(arr, n);

    return 0;
}