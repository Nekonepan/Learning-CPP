#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int A;
    int B;

    cout << "=====================================\n";
    cout << " PROGRAM PENUKARAN UANG (GREEDY)\n";
    cout << "=====================================\n\n";

    // Default pecahan Rupiah
    int C[100];
    int n = 6;

    cout << "Masukkan jumlah pecahan uang : ";
    cin >> B;
    
    for (int i = 0; i < B; i++) {
    	cout << "Masukkan coin ke-" << i + 1 << ": ";
    	cin >> C[i];
	}
	
	// SORTING
	for (int i = 0; i < B; i++) {
		for (int j = i + 1; j < B; j++ ) {
			if (C[i] < C[j]) {
				swap(C[i], C[j]);
			}
		}
	}
	
	cout << "Masukkan jumlah uang yang ingin ditukar (Rp): ";
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
