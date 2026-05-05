#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// ================= PIE SLICE =================
int hitungBagianLingkaran(int garis) {
    int total = 1;
    int tambahan = 0;

    for (int i = 1; i <= garis; i++) {
        tambahan += i;
    }

    total += tambahan;
    return total;
}

void menuPieSlice() {
    int garis;
    cout << "\n[ PIE SLICE PROBLEM ]" << endl;
    cout << "Jumlah garis pemotong: ";
    cin >> garis;

    int hasil = hitungBagianLingkaran(garis);
    cout << "Total potongan maksimum: " << hasil << endl;
}

// ================= SUDUT JAM =================
double cariSelisihSudut(int jam, int menit, int detik) {
    double sudutJam = (jam % 12) * 30 + menit * 0.5 + detik * (0.5 / 60);
    double sudutMenit = menit * 6 + detik * 0.1;

    double selisih = fabs(sudutJam - sudutMenit);
    return (selisih > 180) ? 360 - selisih : selisih;
}

void menuSudutJam() {
    int jam;
    double target;

    cout << "\n[ CLOCK ANGLE PROBLEM ]" << endl;
    cout << "Jam awal (1-12): ";
    cin >> jam;
    cout << "Target sudut (0-180): ";
    cin >> target;

    bool ketemu = false;

    for (int menit = 0; menit < 60 && !ketemu; menit++) {
        for (int detik = 0; detik < 60; detik++) {

            double sudut = cariSelisihSudut(jam, menit, detik);

            if (fabs(sudut - target) < 0.1) {
                cout << "Waktu ditemukan: "
                     << jam << ":"
                     << setw(2) << setfill('0') << menit << ":"
                     << setw(2) << setfill('0') << detik << endl;

                ketemu = true;
                break;
            }
        }
    }

    if (!ketemu) {
        cout << "Tidak ada waktu yang sesuai." << endl;
    }
}

// ================= MAIN MENU =================
int main() {
    int opsi;

    while (true) {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Hitung Pie Slice" << endl;
        cout << "2. Hitung Sudut Jam" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> opsi;

        if (opsi == 1) {
            menuPieSlice();
        } else if (opsi == 2) {
            menuSudutJam();
        } else if (opsi == 0) {
            cout << "Program selesai." << endl;
            break;
        } else {
            cout << "Input tidak valid!" << endl;
        }
    }

    return 0;
}
