#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;
Node* tail = NULL;

// Tambah node di depan
void tambahDepan(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (head == NULL) { // jika list kosong
        head = tail = newNode;
        tail->next = head;
    } else {
        newNode->next = head;
        head = newNode;
        tail->next = head; // sambungkan ulang tail
    }
}

// Tambah node di belakang
void tambahBelakang(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (head == NULL) {
        head = tail = newNode;
        tail->next = head;
    } else {
        tail->next = newNode;
        tail = newNode;
        tail->next = head;
    }
}

// Tambah node setelah nilai tertentu
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
            current->next = newNode;

            if (current == tail)  // jika sisip setelah tail
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

    Node* temp = head;

    // jika hanya satu node
    if (head == tail) {
        head = tail = NULL;
    } else {
        head = head->next;
        tail->next = head;
    }

    delete temp;
}

// Hapus belakang
void hapusBelakang() {
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }

    // jika hanya satu node
    if (head == tail) {
        delete head;
        head = tail = NULL;
        return;
    }

    Node* current = head;
    while (current->next != tail)
        current = current->next;

    current->next = head;
    delete tail;
    tail = current;
}

// Hapus node berdasarkan nilai
void hapusTengah(int value) {
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }

    // jika yang dihapus head
    if (head->data == value) {
        hapusDepan();
        return;
    }

    Node* prev = head;
    Node* current = head->next;

    while (current != head && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == head) {
        cout << "Data " << value << " tidak ditemukan!\n";
        return;
    }

    prev->next = current->next;
    if (current == tail)
        tail = prev;

    delete current;
}

// Tampilkan linked list
void traversal() {
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }

    Node* temp = head;
    cout << "Circular List: ";
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);

    cout << "(kembali ke head)\n";
}

// MAIN PROGRAM
int main() {
    tambahBelakang(10);
    tambahDepan(5);
    tambahBelakang(20);
    traversal();

    tambahTengah(15, 10);
    traversal();

    hapusDepan();
    traversal();

    hapusTengah(20);
    traversal();

    hapusBelakang();
    traversal();

    return 0;
}