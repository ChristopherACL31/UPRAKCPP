#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

struct Item {
    string nm;
    int hrg, stk;
};

Item listItem[] = {
    {"Barang 1", 1000, 1},
    {"Barang 2", 2000, 2},
    {"Barang 3", 3000, 3}
};

const int jmlItem = 3;

string rp(int rupiah) {
    string rb = to_string(rupiah);
    int pos = rb.length() - 3;
    while (pos > 0) {
        rb.insert(pos, ".");
        pos -= 3;
    }
    return rb;
}

string date() {
    time_t wib = time(0);
    tm* local = localtime(&wib);
    char dt[50];
    strftime(dt, sizeof(dt), "%A, %d %b %Y | %H:%M WIB", local);
    return string(dt);
}

int main() {
    string member = "";
    int balance = 0;

    while(true) {
        string user, pass;
        bool verified = false;
        int attempt = 0;
        const int MAX_TRY = 4;

        while(attempt < MAX_TRY) {
            system("cls");
            cout << "===================================" << endl;
            cout << "               LOGIN" << endl;
            cout << "-----------------------------------" << endl;
            cout << " - Admin" << endl;
            cout << " - Member" << endl;
            cout << "===================================" << endl;
            cout << "[0] Exit\n" << endl;
            if (attempt > 0) {
                cout << "[Info] Not soo sigma.. Failed attempt (" << attempt << "/" << "3" << ")\nFailed after 3 attempt you're Done!\n" << endl;
            } else {
                cout << "Please enter the correct Username and Password!\n" << endl;
            }
            cout << "> Username : "; cin >> user;
            if (user == "0") return 0;
            if (user != "Admin" && user != "Member") {
                attempt++;
                cout << "\n[Failed] Username is wrong!" << endl;
                cout << "Attempt left : " << (MAX_TRY - attempt) << endl;
                system("pause");
                continue;
            }

            cout << "> Password : "; cin >> pass;

            // Cek Kredensial (Gabungan)
            if (user == "Admin" && pass == "a123") {
                verified = true;
                break; // Login Berhasil, keluar dari loop percobaan
            }
            else if (user == "Member" && pass == "m123") {
                verified = true;
                break; // Login Berhasil
            }
            else {
                attempt++;
                cout << "\n[Failed] Password is wrong!" << endl;
                cout << "Attempt left : " << (MAX_TRY - attempt) << endl;
                system("pause");
            }
        }

        if (!verified) {
            system("cls");
            cout << "========================================" << endl;
            cout << "            ACCESS DENIED!              " << endl;
            cout << "----------------------------------------" << endl;
            cout << " YOU have been enter 3 WRONG ATTEMPT." << endl;
            cout << " GOODBYE Strangers..." << endl;
            cout << "========================================" << endl;
            system("pause");
            continue; // Kembali ke awal while(true) utama
        }

        if (user == "Admin") {
            while(true) {
                system("cls");
                cout << "===================================" << endl;
                cout << "            ADMIN MENU" << endl;
                cout << "-----------------------------------" << endl;
                cout << left << setw(5) << "No" << setw(25) << "Item" << "Stock" << endl;
                cout << "-----------------------------------" << endl;
                for (int no = 0; no < jmlItem; no++) {
                    cout << left << "[" << no+1 << setw(3) << "]" << setw(25) << listItem[no].nm << listItem[no].stk << endl;
                }
                cout << "===================================" << endl;
                cout << "[0] Logout\n" << endl;

                cout << "You can enter these item number\nto add an stock on it.\nOr enter \"0\" to Logout!\n" << endl;
                cout << "> Enter Selection : ";
                int enter, add;

                if (!(cin >> enter)) {
                    cout << "\n[Error] Input must be Number!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    system("pause");
                    continue;
                }
                if (enter == 0) break;

                if (enter > 0 && enter <= jmlItem) {
                    cout << "> Add Stock       : x";

                    if (!(cin >> add)) {
                        cout << "\n[Error] Input must be Number!" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        system("pause");
                        continue;
                    }
                    listItem[enter-1].stk += add;

                } else {
                    cout << "\n[Error] Item number isnt Available!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    system("pause");
                    continue;
                }
            }
        }

        else if (user == "Member") {
            while(true) {
                system("cls");
                cout << "===================================" << endl;
                cout << "            MEMBER MENU" << endl;
                cout << "-----------------------------------" << endl;
                cout << "Balance : Rp " << rp(balance) << endl;
                cout << "-----------------------------------" << endl;
                cout << "[1] Go to Store" << endl;
                cout << "[2] Add Balance" << endl;
                cout << "===================================" << endl;
                cout << "[0] Logout\n" << endl;
                cout << "> Enter Selection : ";
                int memMenu; cin >> memMenu;

                if (memMenu == 0) break;
                if (memMenu > 2) {
                    cout << "\n[Error] Menu number isnt Available!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    system("pause");
                    continue;
                }

                if (memMenu == 2) {
                    while(true) {
                        system("cls");
                        cout << "===================================" << endl;
                        cout << "                BANK" << endl;
                        cout << "-----------------------------------" << endl;
                        cout << "Balance : Rp " << rp(balance) << endl;
                        cout << "===================================" << endl;
                        cout << "[0] Back\n" << endl;
                        cout << "> Add Balance     : Rp ";
                        int adds;

                        if (!(cin >> adds)) {
                            cout << "\n[Error] Input must be Number!" << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            system("pause");
                            continue;
                        }
                        if (adds <= 0) break;
                        balance += adds;
                        cout << "\n[!] Balance is successfully Added!" << endl;
                        system("pause");
                        continue;
                    }
                }

                if (memMenu == 1) {
                    cin.ignore();
                    cout << "> Enter Name      : ";
                    string memName;
                    getline(cin, memName);

                    int Item[50], Qty[50], totalItem = 0, subTotal = 0;
                    while(true) {
                        system("cls");
                        cout << "==============================================" << endl;
                        cout << "                DAFTAR BARANG                 " << endl;
                        cout << "----------------------------------------------" << endl;
                        cout << "Name     : " << memName << endl;
                        cout << "Balance  : Rp " << rp(balance) << endl;
                        cout << "Cart     : Rp " << rp(subTotal) << endl;
                        cout << "----------------------------------------------" << endl;
                        cout << left << setw(5) << "No" << setw(23) << "Item" << setw(14) << "Harga" << "Stok" << endl;
                        cout << "----------------------------------------------" << endl;
                        for (int no = 0; no < jmlItem; no++) {
                            cout << left << "[" << no + 1 << setw(3) << "]" << setw(23) << listItem[no].nm << "Rp " << setw(11) << rp(listItem[no].hrg) << listItem[no].stk << endl;
                        }
                        cout << "==============================================" << endl;
                        cout << "[0]  Selesai & Checkout\n" << endl;
                        cout << "> Enter item : ";
                        int enter; cin >> enter;
                        if (enter == 0) break;

                        cout << "> Enter Qty  : "; int qty; cin >> qty;

                        int id = enter - 1;
                        if (id >= 0 && id < jmlItem && listItem[id].stk >= qty) {
                            Item[totalItem] = id;
                            Qty[totalItem] = qty;
                            totalItem++;

                            subTotal += (listItem[id].hrg * qty);
                            listItem[id].stk -= qty;

                        } else {

                            cout << "\n[Error] The stock isn't enough!!" << endl;
                            system("pause");
                        }
                    }
                    if (totalItem > 0) {
                        system("cls");
                        cout << "==============================================" << endl;
                        cout << "                  TOTAL CART                " << endl;
                        cout << "----------------------------------------------" << endl;
                        cout << "Name     : " << memName << endl;
                        cout << "Balance  : Rp " << rp(balance) << endl;
                        cout << "----------------------------------------------" << endl;
                        cout << left << setw(5) << "No" << setw(23) << "Item" << setw(14) << "Price" << setw(6) << "Qty" << "Total" << endl;
                        cout << "----------------------------------------------" << endl;
                        for (int i = 0; i < totalItem; i++) {
                            int id = Item[i];
                            cout << left << setw(4) << i + 1 << setw(23) << listItem[id].nm << "Rp " << setw(11) << rp(listItem[id].hrg) << "x" << setw(6) << Qty[i] << "Rp " << rp(listItem[id].hrg * Qty[i]) << endl;
                        }
                        cout << "==============================================" << endl;
                        cout << left << setw(31) << "Subtotal" << "Rp " << rp(subTotal) << endl;
                        cout << "==============================================" << endl;

                        string promo;
                        int money, total, disc = 0, ppn;

                        // TINDAKAN JIKA KODE PROMO SALAH
                        while (true) {
                            cout << "Type \"-\" if you didnt know the Promo code." << endl;
                            cout << "> Enter promo code : "; cin >> promo;

                            if (promo == "HEMAT10") {
                                disc = subTotal * 0.1; break;

                            } else if (promo == "-") {

                                disc = 0; break;

                            } else {

                                cout << "[Error] Kode Promo \"" << promo << "\" salah atau tidak berlaku!" << endl;
                            }
                        }

                        ppn = (subTotal - disc) * 0.11;
                        total = subTotal - disc + ppn;

                        // MENAMPILKAN TOTAL SEBENARNYA (PPN) SEBELUM BAYAR
                        cout << "----------------------------------------------" << endl;
                        cout << left << setw(31) << "DISCOUNT" << "Rp " << rp(disc) << endl;
                        cout << left << setw(31) << "PPN (11%)" << "Rp " << rp(ppn) << endl;
                        cout << left << setw(31) << "TOTAL" << "Rp " << rp(total) << endl;
                        cout << "----------------------------------------------" << endl;

                        while (true) {
                            cout << "> Enter your money  : Rp ";

                            if (!(cin >> money)) {
                                cout << "\n[Error] Input must be Number!" << endl;
                                cin.clear();
                                cin.ignore(1000, '\n');
                                system("pause");
                                continue;
                            }

                            if (money < total) {
                                cout << "\n[Error] Uang anda kurang Rp " << rp(total - money) << "!" << endl;

                            } else {

                                break;
                            }
                        }

                        int change = money - total;

                        if (balance >= total) {
                            balance -= total;
                            system("cls");
                            cout << "========================================" << endl;
                            cout << "              STRUK PESANAN             " << endl;
                            cout << "      " << date() << endl;
                            cout << "\nNama       : " << memName << endl; // Nama Dinamis
                            cout << "Sisa Saldo : Rp " << rp(balance) << endl;
                            cout << "========================================" << endl;
                            cout << left << setw(15) << "Item" << setw(10) << "Harga" << setw(6) << "Qty" << "Total" << endl;
                            cout << "----------------------------------------" << endl;

                            for (int no = 0; no < totalItem; no++) {
                                int id = Item[no];

                                cout << left << setw(15) << listItem[id].nm << "Rp " << setw(7) << rp(listItem[id].hrg) << "x" << setw(5) << Qty[no] << "Rp " << rp(listItem[id].hrg * Qty[no]) << endl;
                            }

                            cout << "----------------------------------------" << endl;
                            cout << left << setw(31) << "Subtotal" << "Rp " << rp(subTotal) << endl;
                            cout << left << setw(31) << "Diskon" << "Rp " << rp(disc) << endl;
                            cout << left << setw(31) << "PPN (11%)" << "Rp " << rp(ppn) << endl;
                            cout << "========================================" << endl;
                            cout << left << setw(31) << "TOTAL TAGIHAN" << "Rp " << rp(total) << endl;
                            cout << "----------------------------------------" << endl;
                            cout << left << setw(31) << "Uang diterima" << "Rp " << rp(money) << endl;
                            cout << "========================================" << endl;
                            cout << left << setw(31) << "Total Kembalian" << "Rp " << rp(change) << endl;
                            cout << "========================================" << endl;

                        } else {

                            cout << "\n[Gagal] Saldo Member tidak cukup!" << endl;
                            for (int no = 0; no < totalItem; no++)
                            listItem[Item[no]].stk += Qty[no];
                        }
                        system("pause");
                    }
                }
            }
        }
    }
}
