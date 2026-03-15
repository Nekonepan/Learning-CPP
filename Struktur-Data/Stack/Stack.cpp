#include <iostream>
using namespace std;

#define maks 5

struct Mahasiswa {
    int nim;
    string nama;
};

class Stack {
    friend ostream& operator<<(ostream&, const Stack&);

public:
    Stack();
    int penuh();
    int kosong();
    void cetak();
    void push(Mahasiswa*);
    Mahasiswa* pop();

private:
    Mahasiswa* A[maks];
    int banyak;
};

ostream& operator<<(ostream& out, const Stack& s) {
    out << "\nIsi stack : ";
    for (int i = 0; i < s.banyak; i++) {
        out << "[" << s.A[i]->nim << ", " << s.A[i]->nama << "] ";
    }
    return out;
}

Stack::Stack() {
    banyak = 0;
    for (int i = 0; i < maks; i++) {
        A[i] = nullptr;
    }
}

int Stack::penuh() {
    return banyak == maks;
}

int Stack::kosong() {
    return banyak == 0;
}

void Stack::cetak() {
    cout << "\nDATA MAHASISWA :" << endl;
    for (int i = 0; i < banyak; i++) {
        cout << i + 1 << ".\tNama : " << A[i]->nama << "\n\tNIM : " << A[i]->nim << endl;
    }
}

void Stack::push(Mahasiswa* x) {
    if (penuh()) {
        cout << "\nStack penuh!";
        return;
    }
    cout << "\nPush : [" << x->nim << ", " << x->nama << "]";

    A[banyak] = x;   // elemen baru berada di posisi paling atas
    banyak++;
}

Mahasiswa* Stack::pop() {
    if (kosong()) {
        cout << "\nStack kosong!";
        return nullptr;
    }

    Mahasiswa* temp = A[banyak - 1];
    cout << "\nPop : [" << temp->nim << ", " << temp->nama << "]";

    A[banyak - 1] = nullptr;
    banyak--;

    return temp;
}

int main() {
    int pilihan;
    Stack s;

    do {
        cout << "=======================================" << endl;
        cout << "|              STACK MENU             |" << endl;
        cout << "=======================================" << endl;
        cout << "| 1. Masukkan data mahasiswa (Push)   |" << endl;
        cout << "| 2. Hapus data mahasiswa (Pop)       |" << endl;
        cout << "| 3. Cetak data mahasiswa             |" << endl;
        cout << "| 4. Keluar                           |" << endl;
        cout << "=======================================" << endl;
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            int n;
            string m;
            cout << "Masukkan nim : ";
            cin >> n;
            cin.ignore();
            cout << "Masukkan nama : ";
            getline(cin, m);
            Mahasiswa* new_mahasiswa = new Mahasiswa();
            new_mahasiswa->nim = n;
            new_mahasiswa->nama = m;
            s.push(new_mahasiswa);
            cout << endl;
            break;
        }
        case 2: {
            Mahasiswa* popped = s.pop();
            if (popped != nullptr) {
                delete popped;
            }
            cout << endl;
            break;
        }
        case 3: {
            s.cetak();
            cout << endl;
            break;
        }
        case 4: {
            while (!s.kosong()) {
                Mahasiswa* popped = s.pop();
                if (popped != nullptr) {
                    delete popped;
                }
            }
            cout << "Keluar dari program." << endl;
            break;
        }
        default:
            cout << "Pilihan tidak valid. Silakan pilih menu dari 1-4." << endl;
        }
    } while (pilihan != 4);

    return 0;
}
