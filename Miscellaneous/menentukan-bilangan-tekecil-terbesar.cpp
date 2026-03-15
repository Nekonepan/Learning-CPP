#include <iostream>
using namespace std;

int main() {
    int arr[2][3] = {
        {12, 7, 28}, 
        {4, 10, 99}
    };

    // inisialisasi min dan max dengan elemen pertama
    int min = arr[0][0];
    int max = arr[0][0];

    // cek semua elemen
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] < min) {
                min = arr[i][j]; // update min jika ketemu lebih kecil
            }
            if (arr[i][j] > max) {
                max = arr[i][j]; // update max jika ketemu lebih besar
            }
        }
    }

    cout << "Nilai terkecil = " << min << endl;
    cout << "Nilai terbesar = " << max << endl;

    return 0;
}
