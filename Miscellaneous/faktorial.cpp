#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Masukkan bilangan bulat positif: ";
    cin >> n;

    if (n < 0) {
        cout << "Faktorial tidak terdefinisi untuk bilangan negatif." << endl;
        return 1;
    } if (n == 0 || n == 1) {
        cout << "Faktorial dari "<< n << " adalah 1" << endl;
        return 0;
    }

    long long faktorial = 1;
    for (int i = 1; i <= n; ++i) {
        faktorial *= i;
    }

    cout << "Faktorial dari " << n << " adalah " << faktorial << endl;

    return 0;
}