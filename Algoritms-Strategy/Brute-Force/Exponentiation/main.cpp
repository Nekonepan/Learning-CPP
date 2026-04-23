#include <iostream>
using namespace std;

// Function untuk menghitung a^n
double pangkat(double a, int n) {
    int i;
    double hasil = 1;

    for (i = 1; i <= n; i++) {
        hasil = hasil * a;
    }

    return hasil;
}

int main() {
    double a;
    int n;

    cout << "Masukkan nilai a: ";
    cin >> a;

    cout << "Masukkan nilai pangkat n: ";
    cin >> n;

    cout << a << "^" << n << " = " << pangkat(a, n) << endl;

    return 0;
}