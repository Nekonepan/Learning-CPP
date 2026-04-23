#include <iostream>
#include <cmath>
using namespace std;

// Function untuk mengecek bilangan prima
bool prima(int x) {
    if (x < 2) {
        return false;
    } 
    if (x == 2) {
        return true;
    }

    int y = sqrt(x);

    for (int k = 2; k <= y; k++) {
        if (x % k == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int x;

    cout << "Masukkan bilangan: ";
    cin >> x;

    if (prima(x)) {
        cout << x << " adalah bilangan prima" << endl;
    } else {
        cout << x << " bukan bilangan prima" << endl;
    }

    return 0;
}