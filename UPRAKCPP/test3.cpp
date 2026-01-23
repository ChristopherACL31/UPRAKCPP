#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

struct Item {
    string name;
    int buyPrice;
    int sellPrice;
    int stock;
};

struct InvItem {
    string name;
    int sellPrice;
    int qty;
};

string format(int num) {
    string rb = to_string(num);
    int pos = rb.length() - 3;
    for (int i = pos - 3; i > 0; i -= 3)
        rb.insert(i, ".");
    return rb;
}

class mainMenu {
    public:
    
    int balance = 0;
    vector <InvItem> mainInv;
    vector <Item> listItem = {
        {"Common Skin", 50, 25, 999},
        {"Epic Skin", 500, 200, 999},
        {"Legendary Wings", 2500, 1200, 999},
        {"Exp Scroll", 10, 5, 999}
    };

    void topupMenu() {
        system("cls");

    }

    void buyMenu() {
        system("cls");
    }

    void sellMenu() {
        system("cls");
    }

    void gachaMenu() {
        system("cls");
    }

    void showInv() {
        system("cls");
    }

    private:
    void addInv(string n, int s, int q) {
        for (auto &item : mainInv) {
            if (item.name == n) {
                item.qty += q;
                return;
            }
        }
        mainInv.push_back({n, s, q});
    }
};

int main() {
    srand(time(0));
    mainMenu app;
    string name;
    int menu;

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
            if (attempt > 0) {
                cout << " Not soo sigma.. Failed attempt (" << attempt << "/" << "3" << ")\n Failed after 3 attempt you're Done!" << endl;
            } else {
                cout << " Please enter the correct\n Username and Password!" << endl;
            }
            cout << "===================================" << endl;
            cout << "[0] Exit\n" << endl;
            cout << "> Username : "; cin >> user;

            if (user == "0") return 0;

            if (user != "Member") {
                attempt++;
                cout << "\n[Failed] Username is wrong!" << endl;
                cout << "Attempt left : " << (MAX_TRY - attempt) << endl;
                system("pause");
                continue;
            }

            cout << "> Password : "; cin >> pass;

            if (user == "Member" && pass == "m123") {
                verified = true;
                break;
            } else {
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
            continue;
        }

        if (user == "Member") {
            while (true) {
                system("cls");
                cout << "====================================" << endl;
                cout << "      GAME SHOP: DIAMOND STORE      " << endl;
                cout << "====================================" << endl;
                cout << " Diamonds: " << format(app.balance) << endl;
                cout << "------------------------------------" << endl;
                cout << " 1. Top-up Diamond" << endl;
                cout << " 2. Buy Item (Store)" << endl;
                cout << " 3. Sell Item (Inventory)" << endl;
                cout << " 4. Gacha Item (150 Dia)" << endl;
                cout << " 5. Check Inventory" << endl;
                cout << " 0. Exit" << endl;
                cout << "------------------------------------\n" << endl;
                cout << " Pilih: "; cin >> menu;

                if (menu == 0) break;
                switch (menu) {
                    case 1: app.topupMenu(); break;
                    case 2: app.buyMenu(); break;
                    case 3: app.sellMenu(); break;
                    case 4: app.gachaMenu(); break;
                    case 5: app.showInv(); break;
                }
            }
            return 0;
        }
    }
}