#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int A;

    cout << "=====================================\n";
    cout << " PROGRAM PENUKARAN UANG (GREEDY)\n";
    cout << "=====================================\n\n";

    // Default pecahan Rupiah
    int n;
    
    cout << "Masukkan jumlah pecahan uang : ";
    cin >> n;
    int C[n];
    
    for (int i = 0; i < n; i++) {
        cout << "Masukkan pecahan uang ke-" << i + 1 << ": ";
        cin >> C[i];
	}
	
	// SORTING
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++ ) {
			if (C[i] < C[j]) {
				swap(C[i], C[j]);
			}
		}
	}
	
	cout << "Masukkan jumlah uang yang ingin ditukar (Rp): ";
    cin >> A;

    int total = 0;
    int jumlah_uang_pecahan = 0;

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
            jumlah_uang_pecahan++;
        }

        if (jumlah > 0) {
            cout << "Rp" << setw(22) << C[i] << " : " << jumlah << " lembar\n";
        }
    }

    cout << "-------------------------------------\n";
    cout << left << setw(25) << "Total Ditukar" << ": Rp " << total << endl;
    cout << left << setw(25) << "Jumlah uang pecahan" << ": " << jumlah_uang_pecahan << " Lembar" << endl;

    if (total != A) {
        cout << "Catatan: Tidak bisa ditukar secara tepat\n";
    }

    cout << "=====================================\n";

    return 0;
}
