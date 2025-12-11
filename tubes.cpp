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
void menuUser(listUser &LU, listSong &LS, adrUser user) {
    int pilihan = -1;
    adrSong currentlyPlaying = nullptr; // Lagu yang sedang diputar, bisa dari LS atau Playlist
    bool isFromPlaylist = false;

    while (pilihan != 0) {
        cout << "\n=== MENU USER (" << user->info.username << ") ===\n";
        cout << "1. Lihat Semua Lagu (Library)\n";
        cout << "2. Atur Playlist\n";

        if (currentlyPlaying != nullptr) {
            cout << "3. Next/Prev Lagu yang Sedang Diputar\n";
            cout << "4. Hentikan Lagu\n";
            cout << "   (Sedang memutar: " << currentlyPlaying->info.judul << ")";
            if (isFromPlaylist) {
                cout << " (dari Playlist: " << currentPlaylistName << ")";
            }
            cout << endl;
        }

        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "\n--- Library Lagu ---\n";
            displayAllSongs(LS);

            string judul;
            cout << "Masukkan Judul Lagu untuk Diputar: ";
            cin >> judul;

            adrSong songToPlay = findSong(LS, judul);

            if (songToPlay != nullptr) {
                currentlyPlaying = songToPlay;
                isFromPlaylist = false;
                playSong(currentlyPlaying);
            } else {
                cout << "Lagu tidak ditemukan di Library!\n";
            }

        } else if (pilihan == 2) {
            menuPlaylist(LS, user); // Memanggil sub-menu untuk mengatur playlist

        } else if (pilihan == 3 && currentlyPlaying != nullptr) {
            cout << "1. Lagu Selanjutnya\n";
            cout << "2. Lagu Sebelumnya\n";
            cout << "Pilih: ";
            int subPilihan;
            cin >> subPilihan;

            if (subPilihan == 1) {
                currentlyPlaying = nextSong(currentlyPlaylist, p);

            } else if (subPilihan == 2) {
                currentlyPlaying = prevSong(currentlyPlaylist, p);
                if (currentlyPlaying != nullptr){
                    playSong(currentlyPlaying);
                }
            }

        } else if (pilihan == 4 && currentlyPlaying != nullptr) {
            stopSong(currentlyPlaying);
            currentlyPlaying = nullptr;
            currentPlaylistName = "";
        } else if (pilihan == 0) {
            if (currentlyPlaying != nullptr) {
                stopSong(currentlyPlaying);
            }
            cout << "Logout berhasil.\n";
        } else {
            cout << "Pilihan tidak valid atau fitur tidak tersedia saat ini.\n";
        }
    }
}

void displayAllSongs(listSong LS) {
    if (LS.first == nullptr) {
        cout << "--- Library Lagu Kosong ---\n";
        return;
    }

    adrSong P = LS.first;
    int count = 1;

    cout << "\n========================================\n";
    cout << "           DAFTAR SEMUA LAGU          \n";
    cout << "========================================\n";

    // Header tabel
    cout << "No. | JUDUL LAGU             | ARTIS/PENYANYI      | GENRE\n";
    cout << "------------------------------------------------------------\n";

    // Looping untuk menampilkan setiap elemen
    while (P != nullptr) {
        cout << count << ".  | " << P->info.title << " | " << P->info.artis << " | " << P->info.genre << endl;
        P = P->next;
        count++;
    }

    cout << "------------------------------------------------------------\n";
}

void deleteFirst(listSong &LS, adrSong &p){
    p = LS.first;
    if (LS.first == nullptr){
        cout << "Library lagu kosong .\n";
    } else if (LS.first == LS.last){
        LS.first = nullptr;
        LS.last = nullptr;
    } else {
        LS.first = p -> next;
        LS.first -> prev = nullptr;
        p -> next = nullptr;
    }
}
void deleteLast(listSong &LS, adrSong &p){
    p = LS.last;
    if (LS.first == nullptr){
        cout << "Library lagu kosong .\n";
    } else if (LS.first == LS.last){
        LS.first = nullptr;
        LS.last = nullptr;
    } else {
        LS.last = p -> prev;
        LS.last -> next = nullptr;
        p -> prev = nullptr;
    }
}
void deleteAfter(listSong &LS, adrSong prec, adrSong &p){
    if (prec == nullptr || prec -> next == nullptr){
        return;
    }
    p = prec -> next;
    if(p == LS.last){
        deleteLast(LS, p);
    }
    prec -> next = p -> next;
    prec -> next -> prev = prec;
    p -> next = nullptr;
    p -> prev = nullptr;
}

void deleteSong(listSong &LS){
    string title;
    cout << "Masukkan judul lagu yang akan dihapus: ";
    cin >> title;

    adrSong p = findSong(LS, title);
    adrSong prec = nullptr;
    adrSong deleteNode = nullptr;

    if (p == nullptr){
        cout << "Lagu dengan judul " << title << " tidak ditemukan dalam library.\n";
        return;
    }

    if (p == LS.first){
        deleteFirst(LS, deleteNode);
    } else if (p == LS.last){
        deleteLast(LS, deleteNode);
    } else {
        prec = p -> prev;
        deleteAfter(LS, prec, deleteNode);
    }
    if (deleteNode != nullptr){
        delete deleteNode;
        cout << "Lagu dengan judul "<< title << " berhasil dihapus dari library.\n";
    }
}

void displayPlaylist(adrUser u){
    if (u == nullptr) {
        cout << "User tidak ditemukan.\n";
        return;
    }

    cout << "Playlist milik user: " << u->info.username << endl;

    if (u->nextPlaylist == nullptr) {
        cout << "Tidak ada playlist.\n";
        return;
    }

    adrPlaylist p = u->nextPlaylist;
    int i = 1;

    while (p != nullptr) {
        cout << i << ". " << p->info.namaPlaylist
             << " | Lagu: " << p->info.countSong
             << " | Durasi total: " << p->info.durasiTotal << " detik\n";
        p = p->nextPlaylist;
        i++;
    }
}


void menuPlaylist(listSong &LS, adrUser user) {
    int pilihan = -1;

    while (pilihan != 0) {
        cout << "\n=== ATUR PLAYLIST ===\n";
        cout << "1. Buat Playlist Baru\n";
        cout << "2. Hapus Playlist\n";
        cout << "3. Lihat Semua Playlist\n";
        cout << "4. Tambah Lagu ke Playlist\n";
        cout << "5. Hapus Lagu dari Playlist\n";
        cout << "6. Lihat Lagu dalam Playlist\n";
        cout << "7. Putar Lagu dari Playlist\n";
        cout << "0. Kembali ke Menu User\n";
        cout << "Pilih: ";
        cin >> pilihan;

        string playlistName, songTitle;

        if (pilihan == 1) {
            cout << "Nama Playlist Baru: ";
            createPlaylist(user, playlistName);
        } else if (pilihan == 2) {
            cout << "Nama Playlist yang akan Dihapus: ";
            cin >>  playlistName;
            removePlaylist(user, playlistName);
        } else if (pilihan == 3) {
            displayAllPlaylists(user);
        } else if (pilihan == 4) {
            cout << "Nama Playlist: ";
            cin >> playlistName;
            cout << "Judul Lagu (di Library): ";
            cin >>  songTitle;
            addSongToPlaylist(LS, user, playlistName, songTitle);
        } else if (pilihan == 5) {
            cout << "Nama Playlist: ";
            cin >> playlistName);
            cout << "Judul Lagu (di Playlist): ";
            cin >> songTitle;
            removeSongFromPlaylist(user, playlistName, songTitle);
        } else if (pilihan == 6) {
            cout << "Nama Playlist: ";
            cin >> playlistName;
            displayPlaylistSongs(user, playlistName);
        } else if (pilihan == 7) {
            cout << "Nama Playlist yang akan Diputar: ";
            cin >>  playlistName;

            adrSong firstSong = playFirstSongFromPlaylist(user, playlistName);
            if (firstSong != nullptr) {
                cout << "Memutar lagu pertama dari Playlist: " << playlistName << endl;
            }
        }
    }
}

void addPlaylist(adrUser &u, adrPlaylist p) {
    if (u->nextPlaylist == nullptr) {
        // playlist pertama user
        u->nextPlaylist = p;
    } else {
        // cari playlist terakhir user
        adrPlaylist q = u->nextPlaylist;
        while (q->nextPlaylist != nullptr) {
            q = q->nextPlaylist;
        }
        q->nextPlaylist = p;  // sambungkan playlist baru di akhir
    }
}



void playSong(adrSong song) {
    if (song != nullptr) {
        cout << "\n SEDANG MEMUTAR: " << song->info.judul << " - " << song->info.artis << endl;
    }
}

void stopSong(adrSong song) {
    if (song != nullptr) {
        cout << "\n Pemutaran dihentikan: " << song->info.judul << endl;
    }
}

adrSong nextSongLibrary(listSong &LS, adrSong current) {
    if (current == nullptr) {
        cout << " Tidak ada lagu yang sedang diputar untuk pindah ke selanjutnya.\n";
        return nullptr;
    } else{
        // === MODE 1: NAVIGASI DI GLOBAL LIBRARY (listSong) ==
            // Ada lagu selanjutnya.
            return current->next;
        }
    }
adrSong prevSongLibrary(listSong &LS, adrSong current) {
    if (current == nullptr) {
        cout << " Tidak ada lagu yang sedang diputar untuk pindah ke selanjutnya.\n";
        return nullptr;
    } else{
        // === MODE 1: NAVIGASI DI GLOBAL LIBRARY (listSong) ==
            // Ada lagu selanjutnya.
            return current->prev;
        }
    }

adrRelasi nextSongPlaylist(adrPlaylist currentPlaylist, adrRelasi p){
    if (p == nullptr) {
        cout << " Tidak ada lagu yang sedang diputar untuk pindah ke selanjutnya.\n";
        return nullptr;
    } else{
        if (p->next != nullptr) {
            // Ada lagu selanjutnya.
            return p->next;
        } else {
            // Mencapai akhir list, kembali ke awal (looping).
            return currentPlaylist -> firstSong;
        }
    }
}

adrRelasi prevSongPlaylist(adrPlaylist currentPlaylist, adrRelasi p) {
    if (p == nullptr) {
        cout << "Tidak ada lagu yang sedang diputar untuk pindah ke sebelumnya.\n";
        return nullptr;
    }

    // === 1. NAVIGASI MUNDUR  ===
    if (p->prev != nullptr) {
        return p->prev;
    }

    // === 2. MENCAPAI LAGU PERTAMA (Looping ke Belakang) ===
    else if (p == currentPlaylist->firstSong) {
        // Jika p adalah lagu pertama, kita harus looping ke lagu terakhir (LAST).

        adrRelasi Q = currentPlaylist->firstSong
        if (Q == nullptr){
            return nullptr;
        }
        // Traversal O(N) untuk mencari elemen terakhir (LAST) dalam List Relasi SLL/DLL non-circular
        while (Q->next != nullptr) {
            Q = Q->next;
        }

        cout << "Kembali ke lagu terakhir dalam Playlist.\n";
        return Q; // Q adalah elemen terakhir
    }
}

