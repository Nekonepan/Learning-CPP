#include <iostream>
#include <iomanip>
using namespace std;

void tukar(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void tampilData(int arr[], int n) {
    cout << "+------------------------------+" << endl;
    cout << "|      DATA NIM MAHASISWA      |" << endl;
    cout << "+------------------------------+" << endl;

    for (int i = 0; i < n; i++) {
        cout << "| NIM [ " << i << " ] : " << arr[i] << endl;
    }

    cout << "+------------------------------+" << endl;
}

void selectionSort(int arr[], int n) {

    cout << "\n================================================" << endl;
    cout << "           PROSES PENGURUTAN SELECTION SORT     " << endl;
    cout << "================================================" << endl;

    for (int i = 0; i < n - 1; i++) {

        int min_idx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        tukar(arr[i], arr[min_idx]);

        cout << "\nLangkah ke-" << i + 1 << endl;
        cout << "Hasil sorting : ";

        for (int k = 0; k < n; k++) {
            cout << arr[k] << " ";
        }

        cout << endl;
    }
}

int binarySearch(int arr[], int n, int target) {

    int kiri = 0;
    int kanan = n - 1;

    cout << "\n================================================" << endl;
    cout << "           PROSES PENCARIAN BINARY SEARCH       " << endl;
    cout << "================================================" << endl;

    while (kiri <= kanan) {

        int tengah = (kiri + kanan) / 2;

        cout << "\nKiri   : " << kiri << endl;
        cout << "Kanan  : " << kanan << endl;
        cout << "Tengah : " << tengah << endl;
        cout << "Data tengah = " << arr[tengah] << endl;

        if (arr[tengah] == target) {
            return tengah;
        }

        else if (target < arr[tengah]) {
            cout << "Pencarian pindah ke KIRI" << endl;
            kanan = tengah - 1;
        }

        else {
            cout << "Pencarian pindah ke KANAN" << endl;
            kiri = tengah + 1;
        }
    }

    return -1;
}

int main() {

    int n;

    cout << "Masukkan jumlah mahasiswa : ";
    cin >> n;

    int nim[n];

    for (int i = 0; i < n; i++) {
        cout << "Input NIM ke-" << i + 1 << " : ";
        cin >> nim[i];
    }

    cout << "\nDATA SEBELUM DIURUTKAN" << endl;
    tampilData(nim, n);

    selectionSort(nim, n);

    cout << "\nDATA SETELAH DIURUTKAN" << endl;
    tampilData(nim, n);

    int cari;

    cout << "\nMasukkan NIM yang ingin dicari : ";
    cin >> cari;

    int hasil = binarySearch(nim, n, cari);

    cout << "\n================================================" << endl;

    if (hasil != -1) {
        cout << ">>> NIM DITEMUKAN <<<" << endl;
        cout << "\nNIM " << cari
             << " ditemukan pada index ke-" << hasil << endl;
    }
    else {
        cout << ">>> NIM TIDAK DITEMUKAN <<<" << endl;
    }

    cout << "================================================" << endl;

    return 0;
}
