#include <iostream>
#include "TUBES.h"
using namespace std;

int main()
{
    listUser LU;
    listSong LS;
    createListUser(LU);
    createListSong(LS);

    insertFirstUser(LU, createElmUser("admin", "123", "admin"));
    insertFirstUser(LU, createElmUser("aira", "000", "user"));
    displayUser(LU);

    int pilihan = -1;

    while (pilihan != 0) {
        cout << "\n=== MENU LOGIN ===\n";
        cout << "1. Login\n";
        cout << "0. Keluar Program\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string nama, pass;
            cout << "Username: ";
            cin >> nama;
            cout << "Password: ";
            cin >> pass;

            adrUser akun = login(LU, nama, pass);

            if (akun == nullptr) {
                cout << "Login gagal!\n";
            } else {
                cout << "\nLogin berhasil sebagai: " << akun->info.role << endl;

                if (akun->info.role == "admin") {
                    menuAdmin(LU,LS);     // admin bisa logout → balik ke login
                }
            }
        }
    }

    cout << "Program selesai.\n";

    return 0;


}

