#include <iostream>
using namespace std;

struct Product {
	string nama_node, nama_penyanyi, judul_lagu;
	int jumlah_putar;
};

struct Node {
	Product data;
	Node* next;
};

Node* head = NULL;

void traversal () {
	Node* current = head;
	do {
		cout << "Node : " << current -> data.nama_node << endl;
		cout << "Nama Penyanyi : " << current -> data.nama_penyanyi << endl;
		cout << "Judul Lagu : " << current -> data.judul_lagu << endl;
		cout << "Jumlah Putar : " << current -> data.jumlah_putar << endl;
		cout << endl;

		current = current -> next;
	} while (current != head);
}

void print_node(Node* node) {
	if (node == NULL) {
		cout << "Node tidak ditemukan!" << endl;
		return;
	}
	cout << "Node : " << node -> data.nama_node << endl;
	cout << "Nama Penyanyi : " << node -> data.nama_penyanyi << endl;
	cout << "Judul Lagu : " << node -> data.judul_lagu << endl;
	cout << "Jumlah Putar : " << node -> data.jumlah_putar << endl;
}

void hitung_total_putar_penyanyi (string key) {
	int counter = 0;
	bool found = false;

	Node* current = head;
	do {
		if (current -> data.nama_penyanyi == key) {
			counter += current -> data.jumlah_putar;
			found = true;
		}
		current = current -> next;
	} while (current != head);

	if (!found) {
		cout << "Penyanyi '" << key << "' tidak ditemukan!" << endl;
		return;
	}

	cout << "Nama Penyanyi : " << key << endl;
	cout << "Jumlah Putar : " << counter << endl;
}

int main () {
	Node* A = new Node();
	A -> data.nama_node = "Node A";
	A -> data.nama_penyanyi = "Ed Sheeran";
	A -> data.judul_lagu = "Shape of You";
	A -> data.jumlah_putar = 1200;
	
	Node* B = new Node();
	B -> data.nama_node = "Node B";
	B -> data.nama_penyanyi = "Tenxi";
	B -> data.judul_lagu = "Bintang 5";
	B -> data.jumlah_putar = 1000;
	
	Node* C = new Node();
	C -> data.nama_node = "Node C";
	C -> data.nama_penyanyi = "RYO";
	C -> data.judul_lagu = "1/10";
	C -> data.jumlah_putar = 1100;
	
	Node* D = new Node();
	D -> data.nama_node = "Node D";
	D -> data.nama_penyanyi = "Ed Sheeran";
	D -> data.judul_lagu = "Perfect";
	D -> data.jumlah_putar = 1800;

	head = A;
	A -> next = B;
	B -> next = C;
	C -> next = D;
	D -> next = head;

	traversal();

	cout << endl;
	
	print_node(C);

	cout << endl;
	
	hitung_total_putar_penyanyi("Ed Sheeran");
}