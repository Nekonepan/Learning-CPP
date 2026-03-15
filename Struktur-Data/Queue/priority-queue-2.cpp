#include <iostream>
#include <string>

using namespace std;

struct Node {
    string NIK;
    string nama;
    string alamat;
    int priority;
    Node* prev;
    Node* next;
};

Node* head = NULL;
int current_size = 0;

bool queue_is_empty() {
    return head == NULL;
}

void Enqueue(const string& nik, const string& nama, const string& alamat, int priority) {
    Node* new_node = new Node;
    new_node->NIK = nik;
    new_node->nama = nama;
    new_node->alamat = alamat;
    new_node->priority = priority;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (queue_is_empty() || new_node->priority < head->priority) {
        // Kasus 1: Antrian kosong atau prioritas lebih tinggi dari head
        new_node->next = head;
        if (head != NULL) {
            head->prev = new_node;
        }
        head = new_node;
    } else {
        // Kasus 2: Cari posisi penyisipan (Prioritas Terkecil -> Terbesar)
        Node* current = head;
        while (current->next != NULL && current->next->priority <= new_node->priority) {
            current = current->next;
        }

        new_node->next = current->next;
        new_node->prev = current;

        if (current->next != NULL) {
            current->next->prev = new_node;
        }
        current->next = new_node;
    }

    current_size++;
    cout << "Ditambahkan: | NIK : " << nik << " | Nama : " << nama << " | Alamat : " << alamat <<" |" << " (Prioritas: " << priority << ")" << endl;
}

string Dequeue() {
    if (queue_is_empty()) {
        cout << "Antrian kosong. Tidak bisa Dequeue." << endl;
        return "";
    }

    Node* min_node = head;
    string data = min_node->NIK + ", " + min_node->nama + ", " + min_node->alamat;
    int priority = min_node->priority;

    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }

    delete min_node;
    current_size--;

    cout << "Diekstrak: " << data << " (Prioritas: " << priority << ")" << endl;
    return data;
}

void display() {
    if (queue_is_empty()) {
        cout << "Antrian kosong" << endl;
        return;
    }

    cout << "\n=== Status Priority Queue (Prio Tertinggi -> Terendah) ===" << endl;
    Node* current = head;
    while (current != NULL) {
        cout << "[" << current->NIK << ", " << current->nama << ", " << current->alamat << ", P:" << current->priority << "]";
        if (current->next != NULL) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << "\nJumlah elemen: " << current_size << "\n" << endl;
}

int main() {
    int pilihan;

    do {
        cout << "=== MENU QUEUE KTP ===" << endl;
        cout << "1. Enqueue / Tambah layanan KTP" << endl;
        cout << "2. Deque / Layani KTP" << endl;
        cout << "3. Tampilkan queue" << endl;
        cout << "4. Keluar" << endl;
        cout << "-------------------------------" << endl;
        cout << "Masukkan pilihan : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
            int prioritas;
            string nik, nama, alamat;
            
            cin.ignore();
            cout << "Masukkan NIK : ";
            getline(cin, nik);
            cout << "Masukkan Nama : ";
            getline(cin, nama);
            cout << "Masukkan Alamat : ";
            getline(cin, alamat);
            cout << "Masukkan prioritas (Semakin kecil lebih tinggi prioritasnya) : ";
            cin >> prioritas;
            cin.ignore();

            Enqueue(nik, nama, alamat, prioritas);
            break;
            } case 2: {
            Dequeue();
            break;
            } case 3: {
            display();
            break;
            }
            default: {
            cout << "Pilihan tidak valid" << endl;
            }
        }
        } while (pilihan != 4);
    return 0;
}
