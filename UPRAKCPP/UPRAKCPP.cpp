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



Item listItem[] = {
    {"Aqua 600ml", 5000, 14}, {"Roti", 7000, 15}, {"Indomie", 3500, 40},
    {"Chitato", 12000, 50}, {"Teh Botol", 6000, 52}, {"Susu UHT", 8000, 52}
};

const int jmlItem = 6;



string fmt(int n) {
    string s = to_string(n);
    int pos = s.length() - 3;
    while (pos > 0) {
        s.insert(pos, ".");
        pos -= 3;
    }
    return s;
}



string date() {
    time_t n = time(0);
    tm* lt = localtime(&n);
    char buf[50];
    strftime(buf, sizeof(buf), "%A, %d %b %Y | %H:%M WIB", lt);
    return string(buf);
}



int main() {
    string pembeli = "";
    int saldo = 0;
    


    while (true) {

        system("cls");
        cout << "========================================" << endl;
        cout << "              DAFTAR USER               " << endl;
        cout << "----------------------------------------" << endl;
        cout << " -  Admin" << endl;
        cout << " -  Member" << endl;
        cout << "========================================" << endl;
        cout << "[0] Keluar" << endl;
        cout << "========================================" << endl;
        
        string user, pass;

        cout << "\n> Username : "; cin >> user;

        if (user == "0") break;
        if (user != "Admin" && user != "Member") {

            cout << "\n[Error] User tidak ditemukan!" << endl;

            system("pause");
            continue; 
        }

        cout << "> Password : "; cin >> pass;

        if (user == "Admin" && pass == "admin123") {
            while (true) {
                system("cls");
                cout << "========================================" << endl;
                cout << "MENU ADMIN" << endl;
                cout << "\nMasukkan nomor barang untuk\nmenambahkan Stok atau Logout!" << endl;
                cout << "----------------------------------------" << endl;
                cout << left << setw(5) << "No" << setw(30) << "Item" << "Stok" << endl;
                cout << "----------------------------------------" << endl;
                for (int i = 0; i < jmlItem; i++) 
                cout << left << "[" << i + 1 << setw(3) << "]" << setw(30) << listItem[i].nm << listItem[i].stk << endl;
                cout << "========================================" << endl;
                cout << "[0]  Log Out\n\n";
                cout << "> Pilih       : ";
                int pilih, tmbh;

                if (!(cin >> pilih)) {
                    cout << "\n[Error] Input harus angka!" << endl;

                    cin.clear();
                    cin.ignore(1000, '\n');
                    system("pause");

                    continue;
                }

                if (pilih == 0) break;

                if (pilih > 0 && pilih <= jmlItem) {
                    cout << "> Tambah Stok : "; 
                    if (!(cin >> tmbh)) {
                        cout << "\n[Error] Input stok harus angka!" << endl;

                        cin.clear();
                        cin.ignore(1000, '\n'); 
                        system("pause");

                        continue;
                    }
                    listItem[pilih-1].stk += tmbh;
                }
            }
        }



        else if (user == "Member" && pass == "member123") {
            while (true) {
                system("cls");
                cout << "========================================" << endl;
                cout << "              MENU MEMBER               " << endl;
                cout << "----------------------------------------" << endl;
                cout << "Saldo Saat Ini: Rp " << fmt(saldo) << endl;
                cout << "----------------------------------------" << endl;
                cout << "[1]  Belanja" << endl;
                cout << "[2]  Top Up Saldo" << endl;
                cout << "========================================" << endl;
                cout << "[0]  Log Out\n" << endl;
                cout << "> Masukkan : "; int menuMem; cin >> menuMem;

                if (menuMem == 0) break;
                if (menuMem == 2) {
                    int isi;
                    cout << "> Masukkan Jumlah Top Up : Rp "; cin >> isi;
                    saldo += isi;
                    cout << "[Sukses] Saldo berhasil ditambahkan!" << endl;
                    system("pause");
                    continue;
                }

                if (menuMem == 1) {
                    // INPUT NAMA PEMBELI SECARA DINAMIS
                    cout << "> Masukkan Nama Pembeli : ";
                    cin >> pembeli;
                    
                    int kI[50], kQ[50], totI = 0, sub = 0;
                    while (true) {

                        system("cls");
                        cout << "==============================================" << endl;
                        cout << "                DAFTAR BARANG                 " << endl;
                        cout << "----------------------------------------------" << endl;
                        cout << "Nama       : " << pembeli << endl;
                        cout << "Saldo      : Rp " << fmt(saldo) << endl;
                        cout << "Keranjang  : Rp " << fmt(sub) << endl;
                        cout << "----------------------------------------------" << endl;
                        cout << left << setw(5) << "No" << setw(23) << "Item" << setw(14) << "Harga" << "Stok" << endl;
                        cout << "----------------------------------------------" << endl;

                        for (int i = 0; i < jmlItem; i++) {
                            cout << left << "[" << i + 1 << setw(3) << "]" << setw(23) << listItem[i].nm << "Rp " << setw(11) << fmt(listItem[i].hrg) << listItem[i].stk << endl;
                        }

                        cout << "==============================================" << endl;
                        cout << "[0]  Selesai & Checkout\n" << endl;
                        cout << "> Pilih Barang : "; int pilih; cin >> pilih;
                        if (pilih == 0) break;

                        cout << "> Jumlah       : "; int q; cin >> q;

                        int id = pilih - 1;
                        if (id >= 0 && id < jmlItem && listItem[id].stk >= q) {
                            kI[totI] = id; kQ[totI] = q; totI++;
                            sub += (listItem[id].hrg * q);
                            listItem[id].stk -= q;

                        } else {
                            
                            cout << "\n[Error] Stok kurang!" << endl; system("pause"); }
                    }

                    if (totI > 0) {
                        system("cls");
                        cout << "========================================" << endl;
                        cout << "             TOTAL KERANJANG            " << endl;
                        cout << "----------------------------------------" << endl;
                        cout << "Saldo      : Rp " << fmt(saldo) << endl;
                        cout << "----------------------------------------" << endl;
                        cout << left << setw(4) << "No" << setw(15) << "Item" << setw(10) << "Harga" << setw(6) << "Qty" << "Total" << endl;

                        for (int i = 0; i < totI; i++) {
                            int id = kI[i];
                            cout << left << setw(4) << i + 1 << setw(15) << listItem[id].nm << "Rp " << setw(7) << fmt(listItem[id].hrg) << "x" << setw(5) << kQ[i] << "Rp " << fmt(listItem[id].hrg * kQ[i]) << endl;
                        }

                        cout << "========================================" << endl;
                        cout << left << setw(31) << "Subtotal" << "Rp " << fmt(sub) << endl;
                        cout << "========================================" << endl;
                        
                        string promo; 
                        int uang, totTagihan, diskon = 0, ppn;

                        // TINDAKAN JIKA KODE PROMO SALAH
                        while (true) {
                            cout << "\nKetik \"-\" jika tidak tahu Kode Promo." << endl;
                            cout << "> Masukkan Kode Promo : "; cin >> promo;

                            if (promo == "HEMAT10") {
                                diskon = sub * 0.1; break;

                            } else if (promo == "-") {

                                diskon = 0; break;

                            } else {

                                cout << "[Error] Kode Promo \"" << promo << "\" salah atau tidak berlaku!" << endl;
                            }
                        }
                        
                        ppn = (sub - diskon) * 0.11;
                        totTagihan = sub - diskon + ppn;

                        // MENAMPILKAN TOTAL SEBENARNYA (PPN) SEBELUM BAYAR
                        cout << "----------------------------------------" << endl;
                        cout << left << setw(31) << "Diskon" << "Rp " << fmt(diskon) << endl;
                        cout << left << setw(31) << "PPN (11%)" << "Rp " << fmt(ppn) << endl;
                        cout << left << setw(31) << "TOTAL TAGIHAN" << "Rp " << fmt(totTagihan) << endl;
                        cout << "----------------------------------------" << endl;

                        while (true) {
                            cout << "> Masukkan Uang       : Rp "; 

                            if (!(cin >> uang)) {
                                cout << "\n[Error] Input harus angka!" << endl;
                                cin.clear(); cin.ignore(1000, '\n'); continue;
                            }

                            if (uang < totTagihan) {
                                cout << "\n[Error] Uang anda kurang Rp " << fmt(totTagihan - uang) << "!" << endl;

                            } else {

                                break; 
                            }
                        }

                        int kembali = uang - totTagihan;

                        if (saldo >= totTagihan) {
                            saldo -= totTagihan;
                            system("cls");
                            cout << "========================================" << endl;
                            cout << "              STRUK PESANAN             " << endl;
                            cout << "      " << date() << endl;
                            cout << "\nNama       : " << pembeli << endl; // Nama Dinamis
                            cout << "Sisa Saldo : Rp " << fmt(saldo) << endl;
                            cout << "========================================" << endl;
                            cout << left << setw(15) << "Item" << setw(10) << "Harga" << setw(6) << "Qty" << "Total" << endl;
                            cout << "----------------------------------------" << endl;

                            for (int i = 0; i < totI; i++) {
                                int id = kI[i];

                                cout << left << setw(15) << listItem[id].nm << "Rp " << setw(7) << fmt(listItem[id].hrg) << "x" << setw(5) << kQ[i] << "Rp " << fmt(listItem[id].hrg * kQ[i]) << endl;
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

                            int sisa = kembali;
                            int pec[] = {
                                100000,
                                50000,
                                20000,
                                10000,
                                5000,
                                2000,
                                1000,
                                500,
                                200,
                                100,
                                50,
                                20,
                                10};
                            int jmlPecahan = sizeof(pec) / sizeof(pec[0]);

                            if (kembali == 0) {
                                cout << right << setw(37) << "Rp 0" << endl;

                            } else {

                                for (int i = 0; i < jmlPecahan; i++) {
                                    int jml = sisa / pec[i];

                                    if (jml > 0) {
                                        sisa = sisa % pec[i];
                                        cout << right << setw(34) << "Rp " << fmt(pec[i] * jml) << endl;
                                    }
                                }
                            }
                            cout << left << setw(31) << "Total Kembalian" << "Rp " << fmt(kembali) << endl;
                            cout << "========================================" << endl;

                        } else { 

                            cout << "\n[Gagal] Saldo Member tidak cukup!" << endl; 
                            for(int i=0; i<totI; i++) listItem[kI[i]].stk += kQ[i];
                        }
                        system("pause");
                    }
                }
            }
        } else { cout << "\n[Error] Password Salah!" << endl;
            system("pause"); 
        }
    }
    return 0;
}