#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAKS = 100;

void write_data(const string id[], const string nama[], const string jabatan[], const string telp[], int jumlah) {
    ofstream file("data_karyawan.txt");
    if (file.is_open()) {
        file << jumlah << endl;
        for (int i = 0; i < jumlah; i++) {
            file << id[i] << endl;
            file << nama[i] << endl;
            file << jabatan[i] << endl;
            file << telp[i] << endl;
            file << "------------------------------" << endl;
        }
        file.close();
        cout << "Data berhasil disimpan" << endl;
    } else {
        cout << "Gagal membuka file" << endl;
    }
}

void read_data(string id[], string nama[], string jabatan[], string telp[], int &jumlah) {
    ifstream file("data_karyawan.txt");
    if (file.is_open()) {
        file >> jumlah;
        file.ignore();
        for (int i = 0; i < jumlah; i++) {
            getline(file, id[i]);
            getline(file, nama[i]);
            getline(file, jabatan[i]);
            getline(file, telp[i]);
            string batas;
            getline(file, batas);
        }
        file.close();
    } else {
        jumlah = 0;
    }
}

void input_data(string id[], string nama[], string jabatan[], string telp[], int &jumlah) {
    int input;
    
    cout << "Jumlah data yang ingin diinput : ";
    cin >> input;
    cin.ignore();
    
    for (int i = 0; i < input; i++) {
        cout << endl;
        cout << "Data ke-" << i + 1 << endl;

        cout << "ID Karyawan : ";
        getline(cin, id[jumlah]);

        cout << "Nama Karyawan : ";
        getline(cin, nama[jumlah]);

        cout << "Jabatan : ";
        getline(cin, jabatan[jumlah]);

        cout << "No. Telp : ";
        getline(cin, telp[jumlah]);

        cout << endl;

        jumlah++;
    }

    write_data(id, nama, jabatan, telp, jumlah);
}

void tampil_data(const string id[], const string nama[], const string jabatan[], const string telp[], int jumlah) {
    string garis = "+---------------------+-------------------------------+---------------------+---------------------+";
    
    cout << garis << endl;
    cout << "| " << setw(20) << left << "ID Karyawan"
         << "| " << setw(30) << left << "Nama Karyawan" 
         << "| " << setw(20) << left << "Jabatan"
         << "| " << setw(20) << left << "No. HP"
         << "|" << endl;
    cout << garis << endl;

    for (int i = 0; i < jumlah; i++) {
        cout << "| " << setw(20) << left << id[i] 
             << "| " << setw(30) << left << nama[i] 
             << "| " << setw(20) << left << jabatan[i] 
             << "| " << setw(20) << left << telp[i] 
             << "|" << endl;
    }
    cout << garis << endl;
}

void swap_manual(string &a, string &b) {
    string temp;
    temp = a;
    a = b;
    b = temp;
}

// SORT KECIL KE BESAR
void sort_ascending(string id[], string nama[], string jabatan[], string telp[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = i + 1; j < jumlah; j++) {
            if (id[i] > id[j]) {
                swap_manual(id[i], id[j]);
                swap_manual(nama[i], nama[j]);
                swap_manual(jabatan[i], jabatan[j]);
                swap_manual(telp[i], telp[j]);
            }
        }
    }
}

// SORT BESAR KE KECIL
void sort_descending(string id[], string nama[], string jabatan[], string telp[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = i + 1; j < jumlah; j++) {
            if (id[i] < id[j]) {
                swap_manual(id[i], id[j]);
                swap_manual(nama[i], nama[j]);
                swap_manual(jabatan[i], jabatan[j]);
                swap_manual(telp[i], telp[j]);
            }
        }
    }
}

void cari_karyawan(const string id[], const string nama[], const string jabatan[], const string telp[], int jumlah) {
    string cari_id;

    cout << "Masukkan ID karyawan yang ingin dicari: ";
    getline(cin >> ws, cari_id);

    bool find = false;

    for (int i = 0; i < jumlah; i++) {
        if (id[i] == cari_id) {
            cout << endl;
            cout << "Karyawan ditemukan:" << endl;
            cout << "ID      : " << id[i] << endl;
            cout << "Nama    : " << nama[i] << endl;
            cout << "Jabatan : " << jabatan[i] << endl;
            cout << "No. Telp: " << telp[i] << endl;
            find = true;
            break;
        }
    }
    
    if (!find) {
        cout << "Karyawan dengan ID " << cari_id << " tidak ditemukan." << endl;
    }
}

int main() {
    string id[MAKS];
    string nama[MAKS];
    string jabatan[MAKS];
    string telp[MAKS];
    int jumlah = 0;
    int pilihan;

    read_data(id, nama, jabatan, telp, jumlah);

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
            case 1: { //INPUT DATA KARYAWAN ------------------------------------------------
                system("cls");
                input_data(id, nama, jabatan, telp, jumlah);
                system("pause");
                break;
            }
            case 2: { //TAMPILKAN DATA KARYAWAN --------------------------------------------
                system("cls");
                tampil_data(id, nama, jabatan, telp, jumlah);
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
                        sort_ascending(id, nama, jabatan, telp, jumlah);
                        break;
                    }
                    case 2: {
                        sort_descending(id, nama, jabatan, telp, jumlah);
                        break;
                    }
                    default: {
                        cout << "PILIHAN TIDAK VALID!" << endl;
                    }
                }

                cout << endl;
                tampil_data(id, nama, jabatan, telp, jumlah);

                system("pause");
                break;
            }
            case 4: { //CARI KARYAWAN ------------------------------------------------------
                system("cls");
                cari_karyawan(id, nama, jabatan, telp, jumlah);
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