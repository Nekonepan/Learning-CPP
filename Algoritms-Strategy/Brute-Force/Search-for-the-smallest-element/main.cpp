#include <iostream>
using namespace std;

// Function mencari elemen terkecil
int cariElemenTerkecil(int a[], int n) {
    int min = a[0]; // inisialisasi dengan elemen pertama

    for (int k = 1; k < n; k++) {
        if (a[k] < min) {
            min = a[k];
        }
    }

    return min;
}

int main() {
    int n;

    cout << "Masukkan jumlah elemen: ";
    cin >> n;

    int a[n];

    cout << "Masukkan " << n << " bilangan:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int hasil = cariElemenTerkecil(a, n);

    cout << "Elemen terkecil adalah: " << hasil << endl;

    return 0;
}