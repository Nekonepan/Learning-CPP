#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAKS = 1000;
const int KOLOM = 4; // 0: ID, 1: Nama, 2: Jabatan, 3: Telp

void write_data(string data[][KOLOM], int jumlah) {
    ofstream file("data_karyawan.txt");
    if (file.is_open()) {
        file << jumlah << endl;
        for (int i = 0; i < jumlah; i++) {
            for (int j = 0; j < KOLOM; j++) {
                file << data[i][j] << endl;
            }
            file << "------------------------------" << endl;
        }
        file.close();
        cout << "Data berhasil disimpan" << endl;
    } else {
        cout << "Gagal membuka file" << endl;
    }
}

void read_data(string data[][KOLOM], int &jumlah) {
    ifstream file("data_karyawan.txt");
    if (file.is_open()) {
        file >> jumlah;
        file.ignore();
        for (int i = 0; i < jumlah; i++) {
            for (int j = 0; j < KOLOM; j++) {
                getline(file, data[i][j]);
            }
            string batas;
            getline(file, batas);
        }
        file.close();
    } else {
        jumlah = 0;
    }
}

void input_data(string data[][KOLOM], int &jumlah) {
    int input;
    string label[] = {"ID Karyawan", "Nama Karyawan", "Jabatan", "No. Telp"};

    cout << "Jumlah data yang ingin diinput : ";
    cin >> input;
    cin.ignore();

    for (int i = 0; i < input; i++) {
        cout << endl << "Data ke-" << i + 1 << endl;
        for (int j = 0; j < KOLOM; j++) {
            cout << label[j] << " : ";
            getline(cin, data[jumlah][j]);
        }
        cout << endl;
        jumlah++;
    }

    write_data(data, jumlah);
}

void tampil_data(const string data[][KOLOM], int jumlah) {
    string garis = "+---------------------+-------------------------------+---------------------+---------------------+";

    cout << garis << endl;
    cout << "| " << setw(20) << left << "ID Karyawan"
         << "| " << setw(30) << left << "Nama Karyawan"
         << "| " << setw(20) << left << "Jabatan"
         << "| " << setw(20) << left << "No. HP"
         << "|" << endl;
    cout << garis << endl;

    for (int i = 0; i < jumlah; i++) {
        cout << "| " << setw(20) << left << data[i][0]
             << "| " << setw(30) << left << data[i][1]
             << "| " << setw(20) << left << data[i][2]
             << "| " << setw(20) << left << data[i][3]
             << "|" << endl;
    }
    cout << garis << endl;
}

void swap_manual(string &a, string &b) {
    string temp = a;
    a = b;
    b = temp;
}

// SORT KECIL KE BESAR
void sort_ascending(string data[][KOLOM], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = i + 1; j < jumlah; j++) {
            if (data[i][0] > data[j][0]) {
                for (int k = 0; k < KOLOM; k++) {
                    swap_manual(data[i][k], data[j][k]);
                }
            }
        }
    }
}

// SORT BESAR KE KECIL
void sort_descending(string data[][KOLOM], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = i + 1; j < jumlah; j++) {
            if (data[i][0] < data[j][0]) {
                for (int k = 0; k < KOLOM; k++) {
                    swap_manual(data[i][k], data[j][k]);
                }
            }
        }
    }
}

void cari_karyawan(const string data[][KOLOM], int jumlah) {
    string cari_id;
    cout << "Masukkan ID karyawan yang ingin dicari: ";
    getline(cin >> ws, cari_id);
    bool find = false;

    for (int i = 0; i < jumlah; i++) {
        if (data[i][0] == cari_id) {
            cout << endl << "Karyawan ditemukan:" << endl;
            cout << "ID      : " << data[i][0] << endl;
            cout << "Nama    : " << data[i][1] << endl;
            cout << "Jabatan : " << data[i][2] << endl;
            cout << "No. Telp: " << data[i][3] << endl;
            find = true;
            break;
        }
    }

    if (!find) {
        cout << "Karyawan dengan ID " << cari_id << " tidak ditemukan." << endl;
    }
}

int main() {
    string data[MAKS][KOLOM];
    int jumlah = 0;
    int pilihan;

    read_data(data, jumlah);

    do {
        system("cls");
        cout << "+=============================================+" << endl;
        cout << "|          DATA KARYAWAN PT AMBATAGOR         |" << endl;
        cout << "+=============================================+" << endl;
        cout << "| 1. Input data karyawan                      |" << endl;
        cout << "| 2. Tampilkan data karyawan                  |" << endl;
        cout << "| 3. Sorting Data (Ascending / Descending)    |" << endl;
        cout << "| 4. Cari ID karyawan                         |" << endl;
        cout << "| 0. Keluar                                   |" << endl;
        cout << "+=============================================+" << endl;
        cout << "Pilihan : ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
            case 1: {  //INPUT DATA KARYAWAN ------------------------------------------------
                system("cls");
                input_data(data, jumlah);
                system("pause");
                break;
            }
            case 2: { //TAMPILKAN DATA KARYAWAN --------------------------------------------
                system("cls");
                tampil_data(data, jumlah);
                system("pause");
                break;
            }
            case 3: { //SORTING DATA ----------------------------------------------------------
                system("cls");
                cout << "+========================================+" << endl;
                cout << "|           PILIH MODE SORTING           |" << endl;
                cout << "+========================================+" << endl;
                cout << "| 1. Sort ASCENDING (ID kecil ke besar)  |" << endl;
                cout << "| 2. Sort DESCENDING (ID besar ke kecil) |" << endl;
                cout << "+========================================+" << endl;
                cout << "Pilihan : ";
                int mode;
                cin >> mode;

                switch (mode) {
                    case 1: {
                        sort_ascending(data, jumlah);
                        break;
                    }
                    case 2: {
                        sort_descending(data, jumlah);
                        break;
                    }
                    default: {
                        cout << "PILIHAN TIDAK VALID!" << endl;
                    }
                }

                cout << endl;
                tampil_data(data, jumlah);
                system("pause");
                break;
            }
            case 4: { //CARI KARYAWAN ------------------------------------------------------
                system("cls");
                cari_karyawan(data, jumlah);
                system("pause");
                break;
            }
            case 0: { // KELUAR ------------------------------------------------------------
                system("cls");
                cout << "+======================================+" << endl;
                cout << "|     PROGRAM SELESAI TERIMA KASIH     |" << endl;
                cout << "+======================================+" << endl;
                break;
            }
            default: {
                cout << "PILIHAN TIDAK VALID!" << endl;
            }
        }
        cout << endl;
    } while (pilihan != 0);

    return 0;
}
