#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node* head = NULL;
Node* tail = NULL;

// Tambah di depan
void tambahDepan(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (head == NULL) {
        head = tail = newNode;
        head->next = head;
        head->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
}

// Tambah di belakang
void tambahBelakang(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (head == NULL) {
        head = tail = newNode;
        head->next = head;
        head->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        tail = newNode;
    }
}

// Tambah setelah nilai tertentu
void tambahTengah(int value, int afterValue) {
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }

    Node* current = head;
    do {
        if (current->data == afterValue) {
            Node* newNode = new Node();
            newNode->data = value;

            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;

            if (current == tail)
                tail = newNode;
            return;
        }
        current = current->next;
    } while (current != head);

    cout << "Data " << afterValue << " tidak ditemukan!\n";
}

// Hapus depan
void hapusDepan() {
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }

    if (head == tail) {
        delete head;
        head = tail = NULL;
    } else {
        Node* temp = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete temp;
    }
}

// Hapus belakang
void hapusBelakang() {
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }

    if (head == tail) {
        delete head;
        head = tail = NULL;
    } else {
        Node* temp = tail;
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete temp;
    }
}

// Hapus nilai tertentu
void hapusTengah(int value) {
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }

    if (head->data == value) {
        hapusDepan();
        return;
    }

    Node* current = head->next;
    while (current != head && current->data != value)
        current = current->next;

    if (current == head) {
        cout << "Data " << value << " tidak ditemukan!\n";
        return;
    }

    if (current == tail)
        hapusBelakang();
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
}

// Cetak maju
void traversalMaju() {
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }

    Node* temp = head;
    cout << "List (maju): ";
    do {
        cout << temp->data << " <-> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(head)\n";
}

// Cetak mundur
void traversalMundur() {
    if (tail == NULL) {
        cout << "List kosong!\n";
        return;
    }

    Node* temp = tail;
    cout << "List (mundur): ";
    do {
        cout << temp->data << " <-> ";
        temp = temp->prev;
    } while (temp != tail);
    cout << "(tail)\n";
}

int main() {
	int pilihan;
	
	do {
		cout << "=============================" << endl;
		cout << "   MENU LINKED LIST PRODUK   " << endl;
		cout << "=============================" << endl;
		cout << "1. Tambah Depan" << endl;
		cout << "2. Tambah Belakang" << endl;
		cout << "3. Tambah Tengah" << endl;
		cout << "4. Hapus Depan" << endl;
		cout << "5. Hapus Belakang" << endl;
		cout << "6. Hapus Tengah" << endl;
		cout << "7. Tampil Dari Depan" << endl;
		cout << "8. Tampil Dari Belakang" << endl;
		cout << "9. Keluar" << endl;
		cout << "Pilih menu : " << endl;
		cin >> pilihan;
		
		switch (pilihan) {
			case 1: {
				int nilai = 0;
				cout << "Masukkan nilai : ";
				cin >> nilai;
				tambahDepan(nilai);
				break;
			}
			case 2: {
				int nilai;
				cout << "Masukkan nilai : ";
				cin >> nilai;
				tambahBelakang(nilai);
				break;
			}
			case 3: {
				int nilai;
				int posisi;
				cout << "Masukkan nilai : ";
				cin >> nilai;
				cout << "Masukkan nilai setelah node : ";
				cin >> posisi;
				tambahTengah(nilai, posisi);
				break;
			}
			case 4: {
				hapusDepan();
				break;
			}
			case 5: {
				hapusBelakang();
				break;
			}
			case 6: {
				int nilai;
				cout << "Masukkan nilai yang akan dihapus : ";
				cin >> nilai;
				hapusTengah(nilai);
				break;
			}
			case 7: {
				traversalMaju();
				break;
			}
			case 8: {
				traversalMundur();
				break;
			}
			case 9: {
				return 0;
				break;
			}
		}
	} while (pilihan != 9);
}