#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Item {
    string nm;
    int hrg;
    int stk;
};

string format(int num) {
    string rb = to_string(num);
    int pos = rb.length() - 3;
    while (pos > 0) {
        rb.insert(pos, ".");
        pos -= 3;
    }
    return rb;
}

class mainMenu {
public:
    vector<Item> daftarMenu;
    int balance = 0;

    void detailMenu() {
        system("cls");
        cout << "=== DAFTAR MENU TERUPDATE ===" << endl;
        if (daftarMenu.empty()) {
            cout << "\nMenu masih kosong! Gunakan menu [2] untuk mengisi." << endl;
        } else {
            cout << "---------------------------------------------------" << endl;
            cout << left << setw(4) << "No" << setw(18) << "Nama" << setw(15) << "Harga" << "Stok" << endl;
            cout << "---------------------------------------------------" << endl;
            for (int i = 0; i < (int)daftarMenu.size(); i++) {
                cout << left << setw(4) << i + 1
                     << setw(18) << daftarMenu[i].nm
                     << "Rp " << setw(12) << format(daftarMenu[i].hrg)
                     << daftarMenu[i].stk << endl;
            }
        }
        cout << "\nKetik 0 untuk kembali: ";
        int back; cin >> back;
    }

    void updateMenu() {
        system("cls");
        cout << "--- UPDATE MENU BARU ---" << endl;
        cout << "[0] Batal / Kembali" << endl;
        cout << "Ketik nama menu (atau '0' untuk batal): ";
        string nama;
        cin.ignore();
        getline(cin, nama);

        if (nama == "0") return;

        Item baru;
        baru.nm = nama;
        cout << "Harga Satuan : "; cin >> baru.hrg;
        cout << "Jumlah Stok  : "; cin >> baru.stk;
        daftarMenu.push_back(baru);
        cout << "\n[Sukses] Menu " << baru.nm << " berhasil ditambahkan!" << endl;
        system("pause");
    }

    void hapusMenu() {
        system("cls");
        if (daftarMenu.empty()) {
            cout << "\n[Error] Tidak ada menu untuk dihapus." << endl;
            system("pause");
        } else {
            int id;
            cout << "=== HAPUS MENU ===" << endl;
            cout << "---------------------------------------------------" << endl;
            cout << left << setw(4) << "No" << setw(18) << "Nama" << setw(15) << "Harga" << "Stok" << endl;
            cout << "---------------------------------------------------" << endl;
            for (int i = 0; i < (int)daftarMenu.size(); i++) {
                cout << left << setw(4) << i + 1
                     << setw(18) << daftarMenu[i].nm
                     << "Rp " << setw(12) << format(daftarMenu[i].hrg)
                     << daftarMenu[i].stk << endl;
            }
            cout << "---------------------------------------------------" << endl;
            cout << "Masukkan Nomor Menu (0 untuk batal): "; cin >> id;

            if (id == 0) return;

            if (id > 0 && id <= (int)daftarMenu.size()) {
                cout << "[Sukses] Menu '" << daftarMenu[id - 1].nm << "' telah dihapus." << endl;
                daftarMenu.erase(daftarMenu.begin() + (id - 1));
                system("pause");
            } else {
                cout << "[Error] Nomor tidak valid!" << endl;
                system("pause");
            }
        }
    }

    void ambilMenu() {
        system("cls");
        if (daftarMenu.empty()) {
            cout << "\n[Error] Menu belum ada. Update menu dulu!" << endl;
            system("pause");
        } else {
            int id, jumlah;
            cout << "=== AMBIL PESANAN ===" << endl;
            cout << "---------------------------------------------------" << endl;
            cout << left << setw(4) << "No" << setw(18) << "Nama" << setw(15) << "Harga" << "Stok" << endl;
            cout << "---------------------------------------------------" << endl;
            for (int i = 0; i < (int)daftarMenu.size(); i++) {
                cout << left << setw(4) << i + 1
                     << setw(18) << daftarMenu[i].nm
                     << "Rp " << setw(12) << format(daftarMenu[i].hrg)
                     << daftarMenu[i].stk << endl;
            }
            cout << "---------------------------------------------------" << endl;
            cout << "Pilih Nomor Menu (0 untuk batal): "; cin >> id;

            if (id == 0) return;

            if (id > 0 && id <= (int)daftarMenu.size()) {
                cout << "Masukkan Jumlah Pesanan: "; cin >> jumlah;

                if (jumlah <= 0) return;

                int totalBiaya = daftarMenu[id - 1].hrg * jumlah;

                if (jumlah > daftarMenu[id - 1].stk) {
                    cout << "[Gagal] Stok tidak mencukupi!" << endl;
                } else if (balance < totalBiaya) {
                    cout << "[Gagal] Saldo kurang! Total: Rp " << format(totalBiaya) << endl;
                } else {
                    balance -= totalBiaya;
                    daftarMenu[id - 1].stk -= jumlah;
                    cout << "\n[Berhasil] Pesanan diambil!" << endl;
                    cout << "Total Bayar: Rp " << format(totalBiaya) << endl;
                }
                system("pause");
            } else {
                cout << "[Error] Menu tidak ditemukan!" << endl;
                system("pause");
            }
        }
    }

    void topupMenu() {
        while(true) {
            system("cls");
            cout << "========== TOP-UP DIAMOND ==========\n";
            cout << "Saldo Anda: " << format(balance) << " Diamonds\n";
            cout << "------------------------------------\n";
            cout << "1. Rp 10.000\n";
            cout << "2. Rp 100.000\n";
            cout << "3. Rp 500.000\n";
            cout << "4. Rp 1.000.000\n";
            cout << "0. Kembali ke Menu Utama\n";
            cout << "------------------------------------\n";
            cout << "Pilih Paket: ";
            int pil; cin >> pil;

            if (pil == 0) break;

            switch (pil) {
                case 1: balance += 10000; cout << "[v] Berhasil menambah Diamonds!\n"; break;
                case 2: balance += 100000; cout << "[v] Berhasil menambah Diamonds!\n"; break;
                case 3: balance += 500000; cout << "[v] Berhasil menambah Diamonds!\n"; break;
                case 4: balance += 1000000; cout << "[v] Berhasil menambah Diamonds!\n"; break;
                default: cout << "[!] Pilihan tidak tersedia.\n"; break;
            }
            system("pause");
        }
    }
};

int main() {
    mainMenu app;
    int menu;

    while (true) {
        string user, pass;
        bool verified = false;
        int attempt = 0;
        const int MAX_TRY = 4;

        while (attempt < MAX_TRY) {
            system("cls");
            cout << "===================================" << endl;
            cout << "               LOGIN" << endl;
            cout << "-----------------------------------" << endl;
            if (attempt > 0) {
                cout << " Attempt failed! (" << attempt << "/" << MAX_TRY << ")" << endl;
            } else {
                cout << " Please enter Username & Password" << endl;
            }
            cout << "===================================" << endl;
            cout << "[0] Exit program\n" << endl;
            cout << "> Username : "; cin >> user;

            if (user == "0") return 0;

            if (user != "Member") {
                attempt++;
                cout << "\n[Failed] Username is wrong!" << endl;
                system("pause");
                continue;
            }

            cout << "> Password : "; cin >> pass;

            if (user == "Member" && pass == "m123") {
                verified = true;
                break;
            } else {
                attempt++;
                cout << "\n[Failed] Wrong Password!" << endl;
                system("pause");
            }
        }

        if (!verified) {
            system("cls");
            cout << "========================================" << endl;
            cout << "            ACCESS DENIED!              " << endl;
            cout << "========================================" << endl;
            cout << " Too many wrong attempts. Goodbye!" << endl;
            system("pause");
            return 0;
        }

        while (true) {
            system("cls");
            cout << "===============================================" << endl;
            cout << "                JAWABAN UPRAK 2026               " << endl;
            cout << "===============================================" << endl;
            cout << "Nama  : Christopher Alexander Christian Lantang" << endl;
            cout << "Kelas : XII-2" << endl;
            cout << "Absen : 007" << endl;
            cout << "-----------------------------------------------" << endl;
            cout << " Saldo : Rp " << format(app.balance) << endl;
            cout << "-----------------------------------------------" << endl;
            cout << " 1. Lihat Detail Menu" << endl;
            cout << " 2. Update Menu" << endl;
            cout << " 3. Hapus Menu" << endl;
            cout << " 4. Ambil Pesanan" << endl;
            cout << " 5. Top-Up" << endl;
            cout << " 0. Logout" << endl;
            cout << "-----------------------------------------------" << endl;
            cout << " Pilih: "; cin >> menu;

            if (menu == 0) break;

            switch (menu) {
                case 1: app.detailMenu(); break;
                case 2: app.updateMenu(); break;
                case 3: app.hapusMenu(); break;
                case 4: app.ambilMenu(); break;
                case 5: app.topupMenu(); break;
                default:
                    cout << "\n[Error] Pilihan tidak tersedia." << endl;
                    system("pause");
                    break;
            }
        }
    }
    return 0;
}
