#include <iostream>
using namespace std;

struct Node {
	int data;		// menyimpan nilai
	Node* next;		// pointer ke node berikutnya
};

// Pointer awal (head)
Node* head = NULL;

// Tambah node di depan
void tambah_depan(int value) {
	Node* new_node = new Node();	// Buat node baru
	new_node->data = value;
	new_node->next = head;			// Hubungkan ke head lama
	head = new_node;				// Jadikan node baru sebagai head
}

void tambah_tengah(int value, int posisi_setelah) {
	if (head == NULL) {
		cout << "List masih kosong! Tambahkan node terlebih dahulu:" << endl;
		return;
	}
	
	Node* new_node = new Node();
	Node* current = head;
	
//	Cari node dengan data yang di pilih
	while (current != NULL && current->data != posisi_setelah) {
		current = current->next;
	}
	
//	Jika yang data afterValue tidak ada
	if (current == NULL) {
		cout << "Data " << posisi_setelah << " tidak ditemukan dalam list!" << endl;
		return;
	}
	
	new_node->data = value;
	new_node->next = current->next;
	current->next = new_node;
}

void tambah_belakang(int value) {
	Node* new_node = new Node();
	new_node->data = value;		// Data diisi value
	new_node->next = NULL;		// Data next atau terakhir akan diisi NULL
	
	// Jika list kosong
	if (head == NULL) {
		head = new_node;
		return;
	}
	
	Node* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = new_node;	// Sambungkan di akhir
}

void hapus_depan() {
	if (head == NULL) {
		cout << "List kosong!" << endl;
		return;
	}
	
	Node* temp = head;
	head = head->next;	// Pindahkan head ke node berikut
	delete temp;		// Hapus node lama
}

void hapus_tengah(int target_value) {
	if (head == NULL) {
		cout << "List kosong!" << endl;
		return;
	}
	
	Node* prev = head;
	while (prev->next != NULL && prev->next->data != target_value) {
		prev = prev->next;
	}
	
	if (prev->next == NULL) {
		cout << "Data " << target_value << " tidak ditemukan!" << endl;
		return;
	}
	
	Node* del = prev->next;
	prev->next = del->next;
	delete del;
}

void hapus_belakang() {
	if (head == NULL) {
		cout << "List kosong" << endl;
		return;
	}
	
	if (head->next == NULL) {
		delete head;
		head = NULL;
		return;
	}
	
	Node* temp = head;
	while (temp->next->next != NULL) {
		temp = temp->next;
	}
	
	delete temp->next;
	temp->next = NULL;
}

void traversal() {
	if (head == NULL) {
		cout << "List kosong!" << endl;
		return;
	}
	
	Node* temp = head;
	cout << "Isi linked list : ";
	while (temp != NULL) {
		cout << temp->data << "->";
		temp = temp->next;
	}
	
	cout << "NULL" << endl;
}

int main() {
	
	int pilihan;
	
	do {
    cout << endl;
		cout << "=== MENU LINKED LIST ===" << endl;
		cout << "1. Tambah Depan" << endl;
		cout << "2. Tambah Tengah" << endl;
		cout << "3. Tambah Belakang" << endl;
		cout << "4. Hapus Depan" << endl;
		cout << "5. Hapus Tengah" << endl;
		cout << "6. Hapus Belakang" << endl;
		cout << "7. Tampilkan List" << endl;
		cout << "8. Keluar" << endl;
		cout << "Pilih menu : ";
		cin >> pilihan;
    cout << endl;
		
		int n;
		int posisi;
		
		switch (pilihan) {
			case 1: {
				cout << "Masukkan nilai baru : ";
				cin >> n;
				tambah_depan(n);
				break;
			}
			case 2: {
				cout << "Masukkan nilai baru : ";
				cin >> n;
				cout << "Masukkan data setelah nilai berapa? : ";
				cin >> posisi;
				tambah_tengah(n, posisi);
				break;
			}
			case 3: {
				cout << "Masukkan nilai baru : ";
				cin >> n;
				tambah_belakang(n);
				break;
			}
			case 4: {
				hapus_depan();
				cout << "Berhasil di hapus";
				break;
			}
			case 5: {
				cout << "Masukkan nilai yang akan di hapus : ";
				cin >> n;
				hapus_tengah(n);
				break;
			}
			case 6: {
				hapus_belakang();
				cout << "Berhasil di hapus";
				break;
			}
			case 7: {
				traversal();
				break;
			}
		}
	} while(pilihan != 8);
	return 0;
}