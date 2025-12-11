#include <iostream>
#include "TUBES.h"
using namespace std;

void createListUser(listUser &LU){
    LU.first = nullptr;
}
void createListSong(listSong &LS){
    LS.first = nullptr;
    LS.last = nullptr;
}
void createListPlaylist(listPlaylist &LP){
    LP.first = nullptr;
    LP.last = nullptr;
}
adrSong createElmSong(int song_id, string title, string artist, string genre, string album, int duration_seconds){
    adrSong p = new elmSong;
    p->info.song_id = song_id;
    p->info.title = title;
    p->info.artist = artist;
    p->info.genre = genre;
    p->info.album = album;
    p->info.duration_seconds = duration_seconds;

    p->next = nullptr;
    p->prev = nullptr;
    return p;
}
adrUser createElmUser(string username, string password, string role){
    adrUser p = new elmUser;
    p->info.username = username;
    p->info.password = password;
    p->info.role = role;
    p->nextUser = nullptr;
    p->nextPlaylist = nullptr;
    return p;
}
adrPlaylist createElmPlayist(string namaPlaylist, int countSong, int durasiTotal){
    adrPlaylist p = new elmPlaylist;
    p->info.namaPlaylist = namaPlaylist;
    p->info.countSong = 0;
    p->info.durasiTotal = 0;
    p->nextPlaylist = nullptr;
    p->firstSong = nullptr;
    return p;
}
adrRelasi createElmPointerSong(adrSong q){
    adrRelasi p = new elmRelasiPlaylistSong;
    p->next = nullptr;
    p->prev = nullptr;
    p->pointerSong = q;
    return p;
}
void insertFirstUser(listUser &LU, adrUser p){
    if (LU.first == nullptr){
        LU.first = p;
    }else{
        p->nextUser = LU.first;
        LU.first = p;
    }

}
void insertLastSong(listSong &LS, adrSong p){
    if (LS.first == nullptr) {
        LS.first = p;
        LS.last = p;
    } else {
        LS.last->next = p;
        p->prev = LS.last;
        LS.last = p;
    }
}
void displayUser(listUser LU){
    adrUser P = LU.first;
    while (P != nullptr) {
        cout << "Nama: " << P->info.username << endl;
        cout << "Password: " << P->info.password << endl;
        cout << "Role: " << P->info.role << endl;
        cout << "-----------------------------" << endl;
        P = P->nextUser;
    }
}
void displaySong(listSong LS){
    adrSong P = LS.first;
    while (P != nullptr) {
        cout << "Song_id: " << P->info.song_id << endl;
        cout << "Title: " << P->info.title << endl;
        cout << "Artist: " << P->info.artist << endl;
        cout << "Genre: " << P->info.genre << endl;
        cout << "Album: " << P->info.album << endl;
        cout << "Durasi: " << P->info.duration_seconds << endl;
        cout << "-----------------------------" << endl;
        P = P->next;
    }

}
adrUser login(listUser LU, string username, string password){
    adrUser P = LU.first;
    while (P != nullptr) {
        if (P->info.username == username && P->info.password == password) {
            return P;
        }
        P = P->nextUser;
    }
    return nullptr;
}
adrSong findSong(listSong LS, string title){
    adrSong P = LS.first;
    while (P != nullptr) {
        if (P->info.title == title) {
            return P;  // ditemukan
        }
        P = P->next;
    }
    return nullptr; // tidak ditemukan
}
void editSong(listSong &LS){
    string title;
    cout << "Masukkan judul lagu yang ingin diedit: ";
    cin >> title;

    adrSong P = findSong(LS, title);

    if (P == nullptr) {
        cout << "Lagu tidak ditemukan!\n";
        return;
    }

    cout << "\n=== EDIT LAGU ===\n";
    cout << "\nMasukkan data baru:\n";
    cout << "Judul baru: ";
    cin >> P->info.title;

    cout << "Artist baru: ";
    cin >> P->info.artist;

    cout << "Genre baru: ";
    cin >> P->info.genre;

    cout << "Album baru: ";
    cin >> P->info.album;

    cout << "Durasi baru: ";
    cin >> P->info.duration_seconds;

    cout << "\nLagu berhasil diedit!\n";

}
void deleteFirstSong(listSong &LS, adrSong &p){
    p = LS.first;

    // hanya 1 elemen
    if (LS.first == LS.last) {
        LS.first = nullptr;
        LS.last = nullptr;
    } else {
        LS.first = p->next;
        LS.first->prev = nullptr;
        p->next = nullptr;
    }
}
void deleteLastSong(listSong &LS, adrSong &p){
    p = LS.last;

    // hanya 1 elemen
    if (LS.first == LS.last) {
        LS.first = nullptr;
        LS.last = nullptr;
    } else {
        LS.last = p->prev;
        LS.last->next = nullptr;
        p->prev = nullptr;
    }
}

void deleteAfterSong(listSong &LS, adrSong prec, adrSong &p){
    p = prec->next;

    prec->next = p->next;
    p->next->prev = prec;

    p->next = nullptr;
    p->prev = nullptr;
}

void deleteSong(listSong &LS){
    if (LS.first == nullptr) {
        cout << "Tidak ada lagu dalam list!\n";
        return;
    }

    string title;
    cout << "Masukkan judul lagu yang ingin dihapus: ";
    cin >> title;

    adrSong P = findSong(LS, title);

    if (P == nullptr) {
        cout << "Lagu tidak ditemukan!\n";
        return;
    }

    adrSong prec = nullptr;
    adrSong temp = LS.first;

    // cari prec
    while (temp != nullptr && temp->next != P) {
        temp = temp->next;
    }
    prec = temp;

    adrSong deletedNode = nullptr;

    // --- Hapus node ---
    if (P == LS.first) {
        deleteFirstSong(LS, deletedNode);
    }else if (P == LS.last) {
        deleteLastSong(LS, deletedNode);
    }else {
        deleteAfterSong(LS, prec, deletedNode);
    }

    // hapus memori node yang diambil
    delete deletedNode;

    cout << "Lagu berhasil dihapus!\n";
}

void menuAdmin(listUser &LU, listSong &LS){
    int pil;
    do {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Lihat semua Lagu\n";
        cout << "3. Edit Lagu\n";
        cout << "4. Hapus Lagu\n";
        cout << "0. Logout\n";
        cout << "Pilih: ";
        cin >> pil;

        if (pil == 1) {
            string title, artist, genre, album;
            int song_id, duration_seconds;

            cout << "Song_id: ";
            cin >> song_id;
            cout << "Judul lagu: ";
            cin >> title;
            cout << "Artist: ";
            cin >> artist;
            cout << "Genre: ";
            cin >> genre;
            cout << "Album: ";
            cin >> album;
            cout << "Durasi: ";
            cin >> duration_seconds;

            adrSong s = createElmSong(song_id, title, artist, genre, album, duration_seconds);
            insertLastSong(LS, s);

            cout << "Lagu berhasil ditambahkan!\n";
        } else if (pil == 2){
            displaySong(LS);
        } else if (pil == 3){
            editSong(LS);
        } else if (pil == 4){
            deleteSong(LS);
        }

    } while (pil != 0);
}


