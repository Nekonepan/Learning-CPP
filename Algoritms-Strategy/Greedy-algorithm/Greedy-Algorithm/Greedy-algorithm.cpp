#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int A;

    cout << "=====================================\n";
    cout << " PROGRAM PENUKARAN UANG (GREEDY)\n";
    cout << "=====================================\n\n";

    // Default pecahan Rupiah
    int C[] = {50000, 20000, 10000, 5000, 2000, 1000};
    int n = 6;

    cout << "Masukkan jumlah uang (Rp): ";
    cin >> A;

    int total = 0;

    cout << "\n=====================================\n";
    cout << "        HASIL PENUKARAN UANG\n";
    cout << "=====================================\n";

    cout << left << setw(25) << "Jumlah Uang" << ": Rp " << A << endl;
    cout << "\nRincian Pecahan:\n";
    cout << "-------------------------------------\n";

    for (int i = 0; i < n; i++) {
        int jumlah = 0;

        while (total + C[i] <= A) {
            total += C[i];
            jumlah++;
        }

        if (jumlah > 0) {
            cout << "Rp" << setw(10) << C[i]
                 << " : " << jumlah << " lembar\n";
        }
    }

    cout << "-------------------------------------\n";
    cout << left << setw(25) << "Total Ditukar" << ": Rp " << total << endl;

    if (total != A) {
        cout << "Catatan: Tidak bisa ditukar secara tepat\n";
    }

    cout << "=====================================\n";

    return 0;
}
