#include <iostream>
#include <cmath>
using namespace std;

// ==================== BANGUN DATAR ====================
class PersegiPanjang {
private:
    double panjang, lebar;
public:
    PersegiPanjang(double p, double l) : panjang(p), lebar(l) {}
    double hitungLuas() { return panjang * lebar; }
    double hitungKeliling() { return 2 * (panjang + lebar); }
};

class Lingkaran {
private:
    double r;
public:
    Lingkaran(double r) : r(r) {}
    double hitungLuas() { return M_PI * r * r; }
    double hitungKeliling() { return 2 * M_PI * r; }
};

class BujurSangkar {
private:
    double sisi;
public:
    BujurSangkar(double s) : sisi(s) {}
    double hitungLuas() { return sisi * sisi; }
    double hitungKeliling() { return 4 * sisi; }
};

class BelahKetupat {
private:
    double d1, d2, sisi;
public:
    BelahKetupat(double d1, double d2, double sisi)
        : d1(d1), d2(d2), sisi(sisi) {}
    double hitungLuas() { return (d1 * d2) / 2; }
    double hitungKeliling() { return 4 * sisi; }
};

class Segitiga {
private:
    double alas, tinggi, s1, s2, s3;
public:
    Segitiga(double a, double t, double s1, double s2, double s3)
        : alas(a), tinggi(t), s1(s1), s2(s2), s3(s3) {}
    double hitungLuas() { return 0.5 * alas * tinggi; }
    double hitungKeliling() { return s1 + s2 + s3; }
};

// ==================== BANGUN RUANG ====================
class Kubus {
private:
    double sisi;
public:
    Kubus(double s) : sisi(s) {}
    double hitungVolume() { return pow(sisi, 3); }
    double hitungLuasPermukaan() { return 6 * sisi * sisi; }
};

class Balok {
private:
    double p, l, t;
public:
    Balok(double p, double l, double t) : p(p), l(l), t(t) {}
    double hitungVolume() { return p * l * t; }
    double hitungLuasPermukaan() { return 2 * (p*l + p*t + l*t); }
};

class Kerucut {
private:
    double r, t, s;
public:
    Kerucut(double r, double t, double s) : r(r), t(t), s(s) {}
    double hitungVolume() { return (1.0/3) * M_PI * r * r * t; }
    double hitungLuasPermukaan() { return M_PI * r * (r + s); }
};

class Bola {
private:
    double r;
public:
    Bola(double r) : r(r) {}
    double hitungVolume() { return (4.0/3) * M_PI * pow(r, 3); }
    double hitungLuasPermukaan() { return 4 * M_PI * r * r; }
};

class Silinder {
private:
    double r, t;
public:
    Silinder(double r, double t) : r(r), t(t) {}
    double hitungVolume() { return M_PI * r * r * t; }
    double hitungLuasPermukaan() { return 2 * M_PI * r * (r + t); }
};

// ==================== MAIN ====================
int main() {
    PersegiPanjang pp[] = { {5,3}, {7,2}, {10,4} };
    Lingkaran ling[] = { {4}, {7}, {10} };
    BujurSangkar bs[] = { {5}, {8}, {12} };
    BelahKetupat bk[] = { {6,8,5}, {10,12,8}, {14,16,10} };
    Segitiga sg[] = { {4,6,3,4,5}, {5,8,6,5,7}, {10,12,7,9,11} };

    Kubus kb[] = { {3}, {5}, {7} };
    Balok bl[] = { {5,3,4}, {7,2,6}, {10,4,8} };
    Kerucut kr[] = { {3,5,6}, {5,7,8}, {7,10,12} };
    Bola bo[] = { {4}, {6}, {8} };
    Silinder si[] = { {3,7}, {5,10}, {7,12} };

    cout << "=== BANGUN DATAR ===\n";
    for (int i=0;i<3;i++)
        cout << "Persegi Panjang " << i+1 << " -> Luas: " << pp[i].hitungLuas()
             << ", Keliling: " << pp[i].hitungKeliling() << endl;

    for (int i=0;i<3;i++)
        cout << "Lingkaran " << i+1 << " -> Luas: " << ling[i].hitungLuas()
             << ", Keliling: " << ling[i].hitungKeliling() << endl;

    for (int i=0;i<3;i++)
        cout << "Bujur Sangkar " << i+1 << " -> Luas: " << bs[i].hitungLuas()
             << ", Keliling: " << bs[i].hitungKeliling() << endl;

    for (int i=0;i<3;i++)
        cout << "Belah Ketupat " << i+1 << " -> Luas: " << bk[i].hitungLuas()
             << ", Keliling: " << bk[i].hitungKeliling() << endl;

    for (int i=0;i<3;i++)
        cout << "Segitiga " << i+1 << " -> Luas: " << sg[i].hitungLuas()
             << ", Keliling: " << sg[i].hitungKeliling() << endl;

    cout << "\n=== BANGUN RUANG ===\n";
    for (int i=0;i<3;i++)
        cout << "Kubus " << i+1 << " -> Volume: " << kb[i].hitungVolume()
             << ", Luas Permukaan: " << kb[i].hitungLuasPermukaan() << endl;

    for (int i=0;i<3;i++)
        cout << "Balok " << i+1 << " -> Volume: " << bl[i].hitungVolume()
             << ", Luas Permukaan: " << bl[i].hitungLuasPermukaan() << endl;

    for (int i=0;i<3;i++)
        cout << "Kerucut " << i+1 << " -> Volume: " << kr[i].hitungVolume()
             << ", Luas Permukaan: " << kr[i].hitungLuasPermukaan() << endl;

    for (int i=0;i<3;i++)
        cout << "Bola " << i+1 << " -> Volume: " << bo[i].hitungVolume()
             << ", Luas Permukaan: " << bo[i].hitungLuasPermukaan() << endl;

    for (int i=0;i<3;i++)
        cout << "Silinder " << i+1 << " -> Volume: " << si[i].hitungVolume()
             << ", Luas Permukaan: " << si[i].hitungLuasPermukaan() << endl;
}
