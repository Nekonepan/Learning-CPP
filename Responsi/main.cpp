#include <iostream>
using namespace std;

class RentalPS {
private:
    string id[100];
    string nama[100];
    string jenisPS[100];
    string bonus[100];

    int lama[100];
    int harga[100];
    int total[100];
    int diskon[100];
    int bayar[100];

    int jumlah = 0;

public:

    void inputData() {
        cout << "\n=== INPUT DATA PENYEWA ===\n";

        cout << "ID Penyewa : ";
        cin >> id[jumlah];

        cin.ignore();

        cout << "Nama Penyewa : ";
        getline(cin, nama[jumlah]);

        cout << "Jenis PS (PS3/PS4/PS5) : ";
        cin >> jenisPS[jumlah];

        cout << "Lama Sewa (jam) : ";
        cin >> lama[jumlah];

        // Menentukan harga
        if (jenisPS[jumlah] == "PS3") {
            harga[jumlah] = 10000;
        }
        else if (jenisPS[jumlah] == "PS4") {
            harga[jumlah] = 15000;
        }
        else if (jenisPS[jumlah] == "PS5") {
            harga[jumlah] = 20000;
        }

        // Hitung total
        total[jumlah] = harga[jumlah] * lama[jumlah];

        // Hitung diskon
        if (total[jumlah] >= 200000) {
            diskon[jumlah] = total[jumlah] * 20 / 100;
        }
        else if (total[jumlah] >= 100000) {
            diskon[jumlah] = total[jumlah] * 10 / 100;
        }
        else {
            diskon[jumlah] = 0;
        }

        // Total bayar
        bayar[jumlah] = total[jumlah] - diskon[jumlah];

        // Bonus
        if (lama[jumlah] >= 8) {
            bonus[jumlah] = "Gratis Mie + Minuman";
        }
        else if (lama[jumlah] >= 5) {
            bonus[jumlah] = "Gratis Minuman";
        }
        else {
            bonus[jumlah] = "Tidak Ada";
        }

        jumlah++;

        cout << "\nData berhasil disimpan!\n";
    }

    void tampilData() {
        cout << "\n=== DATA PENYEWA ===\n";

        for (int i = 0; i < jumlah; i++) {
            cout << "\nData Ke-" << i + 1 << endl;

            cout << "ID : " << id[i] << endl;
            cout << "Nama : " << nama[i] << endl;
            cout << "Jenis PS : " << jenisPS[i] << endl;
            cout << "Lama Sewa : " << lama[i] << " jam" << endl;
            cout << "Harga : " << harga[i] << endl;
            cout << "Total : " << total[i] << endl;
            cout << "Diskon : " << diskon[i] << endl;
            cout << "Total Bayar : " << bayar[i] << endl;
            cout << "Bonus : " << bonus[i] << endl;
        }
    }

    void cariData() {
        string cari;
        bool ketemu = false;

        cout << "\nMasukkan ID Penyewa : ";
        cin >> cari;

        for (int i = 0; i < jumlah; i++) {
            if (cari == id[i]) {
                cout << "\nData Ditemukan\n";

                cout << "Nama : " << nama[i] << endl;
                cout << "Jenis PS : " << jenisPS[i] << endl;
                cout << "Total Bayar : " << bayar[i] << endl;

                ketemu = true;
            }
        }

        if (!ketemu) {
            cout << "Data tidak ditemukan!\n";
        }
    }

    void biayaTertinggi() {
        int max = 0;

        for (int i = 1; i < jumlah; i++) {
            if (bayar[i] > bayar[max]) {
                max = i;
            }
        }

        cout << "\n=== BIAYA TERTINGGI ===\n";

        cout << "Nama : " << nama[max] << endl;
        cout << "Total Bayar : " << bayar[max] << endl;
    }

    void biayaTerendah() {
        int min = 0;

        for (int i = 1; i < jumlah; i++) {
            if (bayar[i] < bayar[min]) {
                min = i;
            }
        }

        cout << "\n=== BIAYA TERENDAH ===\n";

        cout << "Nama : " << nama[min] << endl;
        cout << "Total Bayar : " << bayar[min] << endl;
    }

    int totalPendapatan(int n) {
        if (n == 0) {
            return bayar[0];
        }

        return bayar[n] + totalPendapatan(n - 1);
    }

    int jumlahPenyewaan(int n) {
        if (n == 0) {
            return 1;
        }

        return 1 + jumlahPenyewaan(n - 1);
    }

    void menu() {
        int pilih;

        do {
            cout << "\n===== RENTAL PLAYSTATION =====\n";

            cout << "1. Input Data\n";
            cout << "2. Tampilkan Data\n";
            cout << "3. Cari Data\n";
            cout << "4. Biaya Tertinggi\n";
            cout << "5. Biaya Terendah\n";
            cout << "6. Total Pendapatan\n";
            cout << "7. Jumlah Penyewaan\n";
            cout << "8. Keluar\n";

            cout << "Pilih Menu : ";
            cin >> pilih;

            switch (pilih) {
                case 1:
                    inputData();
                    break;

                case 2:
                    tampilData();
                    break;

                case 3:
                    cariData();
                    break;

                case 4:
                    biayaTertinggi();
                    break;

                case 5:
                    biayaTerendah();
                    break;

                case 6:
                    if (jumlah > 0) {
                        cout << "\nTotal Pendapatan : "
                             << totalPendapatan(jumlah - 1)
                             << endl;
                    }
                    break;

                case 7:
                    if (jumlah > 0) {
                        cout << "\nJumlah Penyewaan : "
                             << jumlahPenyewaan(jumlah - 1)
                             << endl;
                    }
                    break;

                case 8:
                    cout << "\nProgram selesai.\n";
                    break;

                default:
                    cout << "\nMenu tidak tersedia!\n";
            }

        } while (pilih != 8);
    }
};

int main() {
    RentalPS ps;

    ps.menu();

    return 0;
}