#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Struktur Item
struct Item {
    string name;
    int buyPrice;  // Harga dalam Diamond
    int sellPrice; // Harga jual kembali ke toko
    int stock;
};

// Struktur Inventory Player
struct InventoryItem {
    string name;
    int sellPrice;
    int qty;
};

// Fungsi helper format angka (tetap pakai titik agar rapi)
string formatNo(int num) {
    string s = to_string(num);
    int n = s.length();
    for (int i = n - 3; i > 0; i -= 3) s.insert(i, ".");
    return s;
}

class KasirGacha {
public:
    int diamonds = 0; // Currency utama
    vector<InventoryItem> myInv;
    vector<Item> shopItems = {
        {"Common Skin", 50, 25, 100},
        {"Epic Skin", 500, 200, 10},
        {"Legendary Wings", 2500, 1200, 2},
        {"Exp Scroll", 10, 5, 500}
    };

    void topUpMenu() {
        system("cls");
        cout << "========== TOP-UP DIAMOND ==========\n";
        cout << "Saldo Anda: " << formatNo(diamonds) << " Diamonds\n";
        cout << "------------------------------------\n";
        cout << "1. 100  Diamonds  - Rp 15.000\n";
        cout << "2. 500  Diamonds  - Rp 70.000 (Hemat!)\n";
        cout << "3. 1000 Diamonds  - Rp 130.000 (Best Value!)\n";
        cout << "4. 5000 Diamonds  - Rp 600.000 (Sultan Pack)\n";
        cout << "0. Batal\n";
        cout << "------------------------------------\n";
        cout << "Pilih Paket: ";
        int pil; cin >> pil;

        switch (pil) {
            case 1: diamonds += 100; cout << "[v] Berhasil menambah 100 Diamonds!\n"; break;
            case 2: diamonds += 500; cout << "[v] Berhasil menambah 500 Diamonds!\n"; break;
            case 3: diamonds += 1000; cout << "[v] Berhasil menambah 1000 Diamonds!\n"; break;
            case 4: diamonds += 5000; cout << "[v] Berhasil menambah 5000 Diamonds!\n"; break;
            case 0: return;
            default: cout << "[!] Pilihan tidak tersedia.\n"; break;
        }
        system("pause");
    }

    void buyMenu() {
        system("cls");
        cout << "========== DIAMOND SHOP ==========\n";
        cout << "Saldo: " << formatNo(diamonds) << " Diamonds\n\n";
        cout << left << setw(5) << "ID" << setw(18) << "Item" << setw(12) << "Harga" << "Stok" << endl;
        for (int i = 0; i < shopItems.size(); i++) {
            cout << left << setw(5) << i + 1 << setw(18) << shopItems[i].name
                 << setw(12) << shopItems[i].buyPrice << shopItems[i].stock << endl;
        }

        cout << "\nMasukkan ID (0 batal): "; int id; cin >> id;
        if (id <= 0 || id > shopItems.size()) return;
        cout << "Jumlah: "; int q; cin >> q;

        Item &t = shopItems[id-1];
        if (t.stock >= q && diamonds >= (t.buyPrice * q)) {
            diamonds -= (t.buyPrice * q);
            t.stock -= q;
            addToInv(t.name, t.sellPrice, q);
            cout << "[v] Pembelian Berhasil!\n";
        } else {
            cout << "[!] Diamonds atau Stok tidak cukup!\n";
        }
        system("pause");
    }

    void sellMenu() {
        system("cls");
        cout << "========== JUAL ITEM (INVENTORY) ==========\n";
        if (myInv.empty()) {
            cout << "Inventory kosong.\n"; system("pause"); return;
        }

        cout << left << setw(5) << "ID" << setw(18) << "Nama" << setw(8) << "Qty" << "Harga Jual" << endl;
        for (int i = 0; i < myInv.size(); i++) {
            cout << left << setw(5) << i + 1 << setw(18) << myInv[i].name
                 << setw(8) << myInv[i].qty << myInv[i].sellPrice << " Dia" << endl;
        }

        cout << "\nJual ID berapa? : "; int id; cin >> id;
        if (id <= 0 || id > myInv.size()) return;
        cout << "Jumlah: "; int q; cin >> q;

        InventoryItem &inv = myInv[id-1];
        if (q > 0 && q <= inv.qty) {
            int untung = inv.sellPrice * q;
            diamonds += untung;
            inv.qty -= q;
            cout << "[v] Berhasil menjual! + " << untung << " Diamonds\n";
            if (inv.qty == 0) myInv.erase(myInv.begin() + (id - 1));
        } else {
            cout << "[!] Jumlah salah!\n";
        }
        system("pause");
    }

    void gachaMenu() {
        int cost = 150; // Sekali gacha 150 Diamond
        system("cls");
        cout << "========== GACHA SYSTEM ==========\n";
        cout << "Biaya: " << cost << " Diamonds per Roll\n";
        cout << "Saldo: " << diamonds << " Diamonds\n";
        cout << "Gacha 1x? (y/n): "; char c; cin >> c;

        if (c == 'y' || c == 'Y') {
            if (diamonds >= cost) {
                diamonds -= cost;
                int r = rand() % shopItems.size();
                cout << "\nRolling... [ v ]\n";
                cout << "DAPAT: " << shopItems[r].name << "!\n";
                addToInv(shopItems[r].name, shopItems[r].sellPrice, 1);
            } else {
                cout << "[!] Diamond tidak cukup!\n";
            }
        }
        system("pause");
    }

    void showInv() {
        system("cls");
        cout << "========== MY INVENTORY ==========\n";
        for (auto &it : myInv) cout << "- " << it.name << " (x" << it.qty << ")\n";
        if (myInv.empty()) cout << "Kosong.\n";
        cout << "==================================\n";
        system("pause");
    }

private:
    void addToInv(string n, int s, int q) {
        for (auto &it : myInv) {
            if (it.name == n) { it.qty += q; return; }
        }
        myInv.push_back({n, s, q});
    }
};

int main() {
    srand(time(0));
    KasirGacha app;
    int menu;

    while (true) {
        system("cls");
        cout << "====================================\n";
        cout << "      GAME SHOP: DIAMOND STORE      \n";
        cout << "====================================\n";
        cout << " Diamonds: " << formatNo(app.diamonds) << endl;
        cout << "------------------------------------\n";
        cout << " 1. Top-up Diamond\n";
        cout << " 2. Buy Item (Store)\n";
        cout << " 3. Sell Item (Inventory)\n";
        cout << " 4. Gacha Item (150 Dia)\n";
        cout << " 5. Check Inventory\n";
        cout << " 0. Exit\n";
        cout << "------------------------------------\n";
        cout << " Pilih: "; cin >> menu;

        if (menu == 0) break;
        switch (menu) {
            case 1: app.topUpMenu(); break;
            case 2: app.buyMenu(); break;
            case 3: app.sellMenu(); break;
            case 4: app.gachaMenu(); break;
            case 5: app.showInv(); break;
        }
    }
    return 0;
}
