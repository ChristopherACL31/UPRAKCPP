// UPRAKCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

/* ===== UI ===== */
void garis() {
    cout << "==============================\n";
}

/* ===== DATA BARANG ===== */
struct Barang {
    string nama;
    int harga;
};

Barang daftarBarang[] = {
    {"Aqua 600ml  :", 5000},
    {"Roti        :", 7000},
    {"Indomie     :", 3500},
    {"Chitato     :", 12000},
    {"Teh Botol   :", 6000},
    {"Susu UHT    :", 8000}
};

const int JUMLAH_BARANG = 6;
const double PPN = 0.11;

/* ===== STRUK ===== */
void cetakStruk(string nama, int idx[], int qty[], int totalItem,
    int subtotal, int diskon, int pajak, int total,
    int saldoAkhir) {

    time_t now = time(0);
    tm t;
    localtime_s(&t, &now);

    system("cls");
    garis();
    cout << "STRUK PEMBAYARAN\n";
    garis();
    cout << "Nama        : " << nama << endl;
    cout << "Tanggal     : " << t.tm_mday << "/" << t.tm_mon + 1
        << "/" << t.tm_year + 1900 << " " << t.tm_hour << ":" << t.tm_min << endl;

    garis();
    for (int i = 0; i < totalItem; i++) {
        cout << daftarBarang[idx[i]].nama
            << " x" << qty[i]
            << " = Rp " << daftarBarang[idx[i]].harga * qty[i] << endl;
    }

    garis();
    cout << "Subtotal    : Rp " << subtotal << endl;
    cout << "Diskon      : Rp " << diskon << endl;
    cout << "PPN 11%     : Rp " << pajak << endl;
    cout << "TOTAL       : Rp " << total << endl;
    cout << "Saldo Akhir : Rp " << saldoAkhir << endl;
    garis();
    cout << "TERIMA KASIH\n";
}

/* ===== MAIN ===== */
int main() {

    string namaPembeli = "Pembeli";
    int saldoPembeli = 200000;

    char ulangLogin;

    do {
        int menu;
        string password;

        system("cls");
        garis();
        cout << "LOGIN\n";
        garis();
        cout << "1. Admin\n";
        cout << "2. Pembeli\n";
        garis();
        cout << "\nPilih : ";
        cin >> menu;

        /* ===== LOGIN ===== */
        if (menu != 1 && password != "admin123") {
            cout << "Login admin gagal!\n";
            system("pause");
            continue;
        }
        if (menu != 2 && password != "pembeli123") {
            cout << "Login pembeli gagal!\n";
            system("pause");
            continue;
        }

        /* ===== ADMIN ===== */
        if (menu == 1) {
            int pilihAdmin;
            do {
                system("cls");
                garis();
                cout << "MENU ADMIN\n";
                garis();
                cout << "1. Lihat Saldo Pembeli\n";
                cout << "2. Top Up Saldo Pembeli\n";
                cout << "3. Logout\n";
                cout << "Pilih : ";
                cin >> pilihAdmin;

                if (pilihAdmin == 1) {
                    cout << "\nSaldo Pembeli : Rp " << saldoPembeli << endl;
                    system("pause");
                }
                else if (pilihAdmin == 2) {
                    int topup;
                    cout << "\nJumlah top up : ";
                    cin >> topup;
                    if (topup > 0) {
                        saldoPembeli += topup;
                        cout << "Top up berhasil!\n";
                    }
                    system("pause");
                }

            } while (pilihAdmin != 3);

            ulangLogin = 'y'; // 🔁 KEMBALI KE LOGIN
            continue;
        }

        /* ===== PEMBELI ===== */
        system("cls");
        cout << "Nama Pembeli : ";
        cin >> namaPembeli;
        cout << "Saldo Anda   : Rp " << saldoPembeli << endl;
        system("pause");

        int idx[50], qty[50];
        int totalItem = 0;
        int subtotal = 0;

        system("cls");
        garis();
        cout << "        DAFTAR BARANG\n";
        garis();

        for (int i = 0; i < JUMLAH_BARANG; i++) {
            cout << i + 1 << ". "
                << daftarBarang[i].nama
                << " Rp " << daftarBarang[i].harga << endl;
        }
        cout << "0. Checkout\n";
        garis();

        while (true) {
            int pilih;
            cout << "\nPilih Barang : ";
            cin >> pilih;

            if (pilih == 0) break;
            if (pilih < 1 || pilih > JUMLAH_BARANG) continue;

            int jumlah;
            cout << "Jumlah : ";
            cin >> jumlah;
            if (jumlah <= 0) continue;

            int index = pilih - 1;
            bool ada = false;

            for (int i = 0; i < totalItem; i++) {
                if (idx[i] == index) {
                    qty[i] += jumlah;
                    ada = true;
                    break;
                }
            }

            if (!ada) {
                idx[totalItem] = index;
                qty[totalItem] = jumlah;
                totalItem++;
            }

            subtotal += daftarBarang[index].harga * jumlah;
        }

        if (totalItem == 0) {
            cout << "Tidak ada transaksi.\n";
            break;
        }

        system("cls");
        garis();
        cout << "RINGKASAN BELANJA\n";
        garis();

        for (int i = 0; i < totalItem; i++) {
            cout << daftarBarang[idx[i]].nama
                << " x" << qty[i]
                << " = Rp " << daftarBarang[idx[i]].harga * qty[i] << endl;
        }

        int diskon = 0;
        string kode;
        cout << "\nKode Diskon (HEMAT10 / -) : ";
        cin >> kode;
        if (kode == "HEMAT10") diskon = subtotal * 0.1;

        int setelahDiskon = subtotal - diskon;
        int pajak = setelahDiskon * PPN;
        int total = setelahDiskon + pajak;

        garis();
        cout << "Subtotal : Rp " << subtotal << endl;
        cout << "Diskon   : Rp " << diskon << endl;
        cout << "PPN 11%  : Rp " << pajak << endl;
        cout << "TOTAL    : Rp " << total << endl;
        garis();

        if (saldoPembeli < total) {
            cout << "Saldo tidak cukup!\n";
            break;
        }

        saldoPembeli -= total;

        cetakStruk(namaPembeli, idx, qty, totalItem,
            subtotal, diskon, pajak, total, saldoPembeli);

        break; // selesai belanja → keluar program

    } while (true);

    return 0;
}


