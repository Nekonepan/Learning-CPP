#include <iostream>
using namespace std;

int binarySearch(int arr[], int n, int target) {

    int kiri = 0;
    int kanan = n - 1;

    while (kiri <= kanan) {

        // Cari index tengah
        int tengah = (kiri + kanan) / 2;

        cout << "Cek index " << tengah
             << " = " << arr[tengah] << endl;

        // Jika ditemukan
        if (arr[tengah] == target) {
            return tengah;
        }

        // Jika target lebih kecil
        else if (target < arr[tengah]) {
            kanan = tengah - 1;
        }

        // Jika target lebih besar
        else {
            kiri = tengah + 1;
        }
    }

    return -1;
}

int main() {

    int n;

    cout << "Masukkan jumlah data: ";
    cin >> n;

    int arr[n];

    cout << "Masukkan data secara urut:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int target;

    cout << "Masukkan angka yang dicari: ";
    cin >> target;

    int hasil = binarySearch(arr, n, target);

    if (hasil != -1)
        cout << "Data ditemukan di index ke-" << hasil << endl;
    else
        cout << "Data tidak ditemukan" << endl;

    return 0;
}