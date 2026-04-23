#include <iostream>
using namespace std;

// Function mencari elemen terkecil
int cariElemenTerkecil(int a[], int n) {
    int min = a[0]; // inisialisasi dengan elemen pertama

    for (int k = 1; k < n; k++) {
        if (a[k] < min) {
            min = a[k];
        }
    }

    return min;
}

// Function untuk menghitung a^n
double pangkat(double a, int n) {
    int i;
    double hasil = 1;

    for (i = 1; i <= n; i++) {
        hasil = hasil * a;
    }

    return hasil;
}

int main () {
	int km, n;
	int a[n];
	
	cout << "===============================================" << endl;
	cout << "	SIMULASI PERJALANAN				" << endl;
	cout << "===============================================" << endl;
	
	cout << "Masukkan total jarak perjalanan (KM) : ";
	cin >> km;
	cout << "Masukkan jumlah SPBU : ";
	cin >> n;
	
	cout << endl;
	cout << "--- Input posisi SPBU (dalam KM dari awal) : " << endl;
    for (int i = 0; i < n; i++) {
		cout << "SPBU ke-" << i + 1 << " : ";
        cin >> a[i];
        cout << endl;
    }
    
    cout << "Daftar SPBU (KM): ";
    for (int i = 0; i < n; i++) {
		cout << a[i] << ", ";
    }
    
    int hasil = cariElemenTerkecil(a, n);
    
    cout << endl;
    cout << "Masukkan nilai pangkat k : ";
    cin >> n;
    
    
    
	cout << "===============================================" << endl;
	cout << "Total jarak perjalanan		: " << km << " KM" << endl;
	cout << "SPBU terdekat dari awal		: " << hasil << " KM" << endl;
	cout << "Simulasi konsumsi (jarak^" << n << ")	: " << pangkat(km, n) << endl;
	cout << "===============================================" << endl;
    
}