#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node* prev;
};

Node* head = NULL;
Node* tail = NULL;

// Tambah node di depan
void tambahDepan(int value) {
	Node* newNode = new Node();
	newNode->data = value;
	newNode->prev = NULL;
	newNode->next = head;

	if (head != NULL)
		head->prev = newNode;
	else
		tail = newNode; // list kosong, tail ikut menunjuk newNode

	head = newNode;
}

// Tambah node di belakang
void tambahBelakang(int value) {
	Node* newNode = new Node();
	newNode->data = value;
	newNode->next = NULL;
	newNode->prev = tail;

	if (tail != NULL)
		tail->next = newNode;
	else
		head = newNode; // list kosong

	tail = newNode;
}

// Tambah node setelah nilai tertentu
void tambahTengah(int value, int afterValue) {
	if (head == NULL) {
		cout << "List kosong!\n";
		return;
	}

	Node* current = head;
	while (current != NULL && current->data != afterValue)
		current = current->next;

	if (current == NULL) {
		cout << "Data " << afterValue << " tidak ditemukan!\n";
		return;
	}

	Node* newNode = new Node();
	newNode->data = value;
	newNode->next = current->next;
	newNode->prev = current;

	if (current->next != NULL)
		current->next->prev = newNode;
	else
		tail = newNode; // jika disisipkan setelah tail

	current->next = newNode;
}

// Hapus node di depan
void hapusDepan() {
	if (head == NULL) {
		cout << "List kosong!\n";
		return;
	}

	Node* temp = head;
	head = head->next;

	if (head != NULL)
		head->prev = NULL;
	else
		tail = NULL; // list jadi kosong

	delete temp;
}

// Hapus node di belakang
void hapusBelakang() {
	if (tail == NULL) {
		cout << "List kosong!\n";
		return;
	}

	Node* temp = tail;
	tail = tail->prev;

	if (tail != NULL)
		tail->next = NULL;
	else
		head = NULL; // list kosong

	delete temp;
}

// Hapus node dengan nilai tertentu
void hapusTengah(int value) {
	if (head == NULL) {
		cout << "List kosong!\n";
		return;
	}

	Node* current = head;
	while (current != NULL && current->data != value)
		current = current->next;

	if (current == NULL) {
		cout << "Data " << value << " tidak ditemukan!\n";
		return;
	}

	if (current == head)
		hapusDepan();
	else if (current == tail)
		hapusBelakang();
	else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
	}
}

// Cetak dari depan ke belakang
void traversalMaju() {
	if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }
	
	Node* temp = head;
	cout << "List (maju): ";
	while (temp != NULL) {
		cout << temp->data << " <-> ";
		temp = temp->next;
	}
	cout << "NULL\n";
}

// Cetak dari belakang ke depan
void traversalMundur() {
	if (tail == NULL) {
        cout << "List kosong!\n";
        return;
    }
	
	Node* temp = tail;
	cout << "List (mundur): ";
	while (temp != NULL) {
		cout << temp->data << " <-> ";
		temp = temp->prev;
	}
	cout << "NULL\n";
}

int main() {
	tambahDepan(10);
	tambahDepan(5);
	tambahBelakang(20);
	tambahBelakang(30);
	traversalMaju();
	traversalMundur();

	tambahTengah(15, 10);
	traversalMaju();

	hapusDepan();
	traversalMaju();

	hapusTengah(20);
	traversalMaju();

	hapusBelakang();
	traversalMaju();

	return 0;
}