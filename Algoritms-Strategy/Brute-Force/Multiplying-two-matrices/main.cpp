#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Masukkan ukuran matriks (n x n): ";
    cin >> n;

    int A[n][n], B[n][n], C[n][n];

    // Input matriks A
    cout << "Masukkan elemen matriks A:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    // Input matriks B
    cout << "Masukkan elemen matriks B:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }

    // Proses perkalian matriks
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0; // inisialisasi

            for (int k = 0; k < n; k++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }

    // Output hasil matriks C
    cout << "Hasil perkalian matriks C:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}