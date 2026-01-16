#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

struct Item {
    string nm;
    int hrg, stk;
};

// Data Barang sesuai Screenshot
Item gds[] = {
    {"Aqua 600ml", 5000, 14}, {"Roti", 7000, 15}, {"Indomie", 3500, 40},
    {"Chitato", 12000, 50}, {"Teh Botol", 6000, 52}, {"Susu UHT", 8000, 52}
};
const int JM = 6;

// Fungsi Format Titik (Ribuan, Jutaan, dst)
string fmt(int n) {
    string s = to_string(n);
    int pos = s.length() - 3;
    while (pos > 0) {
        s.insert(pos, ".");
        pos -= 3;
    }
    return s;
}

string getT() {
    time_t n = time(0);
    tm* lt = localtime(&n);
    char buf[50];
    strftime(buf, sizeof(buf), "%A, %d %b %Y | %H:%M WIB", lt);
    return string(buf);
}

int main() {
    string pembeli = "chris";
    int sld = 603275; 
    
    while (true) {
        system("cls");
        cout << "========================================" << endl;
        cout << "              DAFTAR USER               " << endl;
        cout << "----------------------------------------" << endl;
        cout << "1    Admin" << endl;
        cout << "2    Member" << endl;
        cout << "========================================" << endl;
        cout << "[0] Keluar" << endl;
        cout << "========================================" << endl;
        
        string u, p;
        cout << "\n> Username : "; cin >> u;
        if (u == "0") break;

        if (u != "Admin" && u != "Member") {
            cout << "\n[Error] User tidak ditemukan!" << endl;
            system("pause"); continue; 
        }

        cout << "> Password : "; cin >> p;

        if (u == "Admin" && p == "admin123") {
            while (true) {
                system("cls");
                cout << "=== MANAGEMENT STOK (ADMIN) ===" << endl;
                cout << left << setw(4) << "No" << setw(18) << "Item" << "Stok" << endl;
                for (int i = 0; i < JM; i++) 
                    cout << left << setw(4) << i+1 << setw(18) << gds[i].nm << gds[i].stk << endl;
                cout << "----------------------------------------" << endl;
                cout << "[0] Log Out\n> Pilih No Barang: ";
                int pil, tmbh; cin >> pil;
                if (pil == 0) break;
                if (pil > 0 && pil <= JM) {
                    cout << "> Tambah Stok: "; cin >> tmbh;
                    gds[pil-1].stk += tmbh;
                }
            }
        } 
        else if (u == "Member" && p == "member123") {
            while (true) {
                system("cls");
                cout << "========================================" << endl;
                cout << "              MENU MEMBER               " << endl;
                cout << "----------------------------------------" << endl;
                cout << "Saldo Saat Ini: Rp " << fmt(sld) << endl;
                cout << "----------------------------------------" << endl;
                cout << "1. Belanja" << endl;
                cout << "2. Top Up Saldo" << endl;
                cout << "0. Log Out" << endl;
                cout << "========================================" << endl;
                cout << "> Pilih: "; int m_pil; cin >> m_pil;

                if (m_pil == 0) break;

                if (m_pil == 2) {
                    int isi;
                    cout << "\n> Masukkan Jumlah Top Up: Rp "; cin >> isi;
                    sld += isi;
                    cout << "[Sukses] Saldo berhasil ditambahkan!" << endl;
                    system("pause"); continue;
                }

                if (m_pil == 1) {
                    int kI[50], kQ[50], totI = 0, sub = 0;
                    while (true) {
                        system("cls");
                        cout << "========================================" << endl;
                        cout << "             DAFTAR BARANG              " << endl;
                        cout << "----------------------------------------" << endl;
                        cout << "Saldo      : Rp " << fmt(sld) << endl;
                        cout << "Keranjang  : Rp " << fmt(sub) << endl;
                        cout << "----------------------------------------" << endl;
                        cout << left << setw(4) << "No" << setw(18) << "Item" << setw(12) << "Harga" << "Stok" << endl;
                        cout << "----------------------------------------" << endl;
                        for (int i = 0; i < JM; i++) {
                            cout << left << setw(4) << i + 1 << setw(18) << gds[i].nm 
                                 << "Rp " << setw(9) << fmt(gds[i].hrg) << gds[i].stk << endl;
                        }
                        cout << "========================================" << endl;
                        cout << "[0] Selesai & Checkout" << endl;
                        cout << "\n> Pilih Barang : "; int pil; cin >> pil;
                        if (pil == 0) break;
                        cout << "> Jumlah       : "; int q; cin >> q;

                        int id = pil - 1;
                        if (id >= 0 && id < JM && gds[id].stk >= q) {
                            kI[totI] = id; kQ[totI] = q; totI++;
                            sub += (gds[id].hrg * q);
                            gds[id].stk -= q;
                        } else { cout << "\n[Error] Stok kurang!" << endl; system("pause"); }
                    }

                    if (totI > 0) {
                        system("cls");
                        cout << "========================================" << endl;
                        cout << "             TOTAL KERANJANG            " << endl;
                        cout << "----------------------------------------" << endl;
                        cout << "Saldo      : Rp " << fmt(sld) << endl;
                        cout << "----------------------------------------" << endl;
                        cout << left << setw(4) << "No" << setw(15) << "Item" << setw(10) << "Harga" << setw(6) << "Qty" << "Total" << endl;
                        for (int i = 0; i < totI; i++) {
                            int id = kI[i];
                            cout << left << setw(4) << i + 1 << setw(15) << gds[id].nm 
                                 << "Rp " << setw(7) << fmt(gds[id].hrg) << "x" << setw(5) << kQ[i] 
                                 << "Rp " << fmt(gds[id].hrg * kQ[i]) << endl;
                        }
                        cout << "========================================" << endl;
                        cout << left << setw(31) << "Subtotal" << "Rp " << fmt(sub) << endl;
                        cout << "========================================" << endl;
                        cout << "\nKetik \"-\" jika tidak tahu Kode Promo." << endl;
                        string promo; cout << "> Masukkan Kode Promo : "; cin >> promo;
                        int uang; cout << "> Masukkan Uang       : Rp "; cin >> uang;

                        int diskon = (promo == "HEMAT10") ? sub * 0.1 : 0;
                        int ppn = (sub - diskon) * 0.11;
                        int totTagihan = sub - diskon + ppn;
                        
                        // Perbaikan Logika Kembalian agar tidak minus
                        int kemb = (uang >= totTagihan) ? (uang - totTagihan) : 0;

                        if (sld >= totTagihan) {
                            sld -= totTagihan;
                            system("cls");
                            cout << "========================================" << endl;
                            cout << "              STRUK PESANAN             " << endl;
                            cout << "      " << getT() << endl;
                            cout << "\nNama       : " << pembeli << endl;
                            cout << "Sisa Saldo : Rp " << fmt(sld) << endl;
                            cout << "========================================" << endl;
                            cout << left << setw(15) << "Item" << setw(10) << "Harga" << setw(6) << "Qty" << "Total" << endl;
                            cout << "----------------------------------------" << endl;
                            for (int i = 0; i < totI; i++) {
                                int id = kI[i];
                                cout << left << setw(15) << gds[id].nm << "Rp " << setw(7) << fmt(gds[id].hrg) 
                                     << "x" << setw(5) << kQ[i] << "Rp " << fmt(gds[id].hrg * kQ[i]) << endl;
                            }
                            cout << "----------------------------------------" << endl;
                            cout << left << setw(31) << "Subtotal" << "Rp " << fmt(sub) << endl;
                            cout << left << setw(31) << "Diskon" << "Rp " << fmt(diskon) << endl;
                            cout << left << setw(31) << "PPN (11%)" << "Rp " << fmt(ppn) << endl;
                            cout << "========================================" << endl;
                            cout << left << setw(31) << "TOTAL TAGIHAN" << "Rp " << fmt(totTagihan) << endl;
                            cout << "----------------------------------------" << endl;
                            cout << left << setw(31) << "Uang diterima" << "Rp " << fmt(uang) << endl;
                            cout << "========================================" << endl;

                            // SISTEM DIVMOD KEMBALIAN (TETAP ADA)
                            int sisa = kemb;
                            int pec[] = {100000, 50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100};
                            if (kemb == 0) {
                                cout << right << setw(37) << "Rp 0" << endl;
                            } else {
                                for (int i = 0; i < 10; i++) {
                                    int jml = sisa / pec[i];
                                    sisa = sisa % pec[i];
                                    if (jml > 0) {
                                        cout << right << setw(34) << "Rp " << fmt(pec[i] * jml) << endl;
                                    }
                                }
                            }
                            cout << left << setw(31) << "Total Kembalian" << "Rp " << fmt(kemb) << endl;
                            cout << "========================================" << endl;
                        } else { cout << "\n[Gagal] Saldo Member tidak cukup!" << endl; }
                        system("pause");
                    }
                }
            }
        } else { cout << "\n[Error] Password Salah!" << endl; system("pause"); }
    }
    return 0;
}
