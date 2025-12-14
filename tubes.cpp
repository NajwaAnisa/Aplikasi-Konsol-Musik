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
adrSong createElmSong(int song_id, string title, string artist, string genre, string album, string minute, string second){
    adrSong p = new elmSong;

    p->info.song_id = song_id;
    p->info.title = title;
    p->info.artist = artist;
    p->info.genre = genre;
    p->info.album = album;
    p->info.minute = minute;
    p->info.second = second;

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
adrPlaylist createElmPlaylist(string namaPlaylist, int countSong){
    adrPlaylist p = new elmPlaylist;
    p->info.namaPlaylist = namaPlaylist;
    p->info.countSong = 0;
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
        cout << "Song ID : " << P->info.song_id << endl;
        cout << "Judul   : " << P->info.title << endl;
        cout << "Artist  : " << P->info.artist << endl;
        cout << "Genre   : " << P->info.genre << endl;
        cout << "Album   : " << P->info.album << endl;
        cout << "Durasi  : " << P->info.minute << ":"
                         << P->info.second << endl;
        cout << "-----------------------------\n";
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

    cout << "Menit baru  : ";
    cin >> P->info.minute;

    cout << "Detik baru  : ";
    cin >> P->info.second;

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

void deleteSong(listSong &LS, listUser &LU){
    if (LS.first == nullptr) {
        cout << "Tidak ada lagu dalam list!\n";
        return;
    }

    string title;
    cout << "Masukkan judul lagu yang ingin dihapus: ";
    cin >> title;

    adrUser ptrUser = LU.first;
    while (ptrUser != nullptr){
        adrPlaylist ptrPlaylist = ptrUser->nextPlaylist;
        while (ptrPlaylist != nullptr){
            removeSongFromPlaylist(ptrUser, ptrPlaylist->info.namaPlaylist, title);
            ptrPlaylist = ptrPlaylist->nextPlaylist;
        }
        ptrUser = ptrUser->nextUser;
    }
    
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
            cout << "Minute: ";
            cin >> minute;
            cout << "Second: ";
            cin >> second;

            adrSong s = createElmSong(song_id, title, artist, genre, album, minute, second);
            insertLastSong(LS, s);

            cout << "Lagu berhasil ditambahkan!\n";
        } else if (pil == 2){
            displaySong(LS);
        } else if (pil == 3){
            editSong(LS);
        } else if (pil == 4){
            deleteSong(LS,LU);
        }

    } while (pil != 0);
}
void menuUser(listUser &LU, listSong &LS, adrUser user){
    int pilihan = -1;

    adrSong currentSong = nullptr;          // MODE LIBRARY
    adrPlaylist currentPlaylist = nullptr;  // MODE PLAYLIST
    adrRelasi currentRelasi = nullptr;       // MODE PLAYLIST
    bool isFromPlaylist = false;

    while (pilihan != 0) {
        cout << "\n=== MENU USER (" << user->info.username << ") ===\n";
        cout << "1. Lihat & Putar Lagu dari Library\n";
        cout << "2. Mengurutkan lagu berdasarkan Title\n";
        cout << "3. Mengurutkan lagu berdasarkan Genre\n";
        cout << "4. Atur Playlist\n";

        if (currentSong != nullptr) {
            cout << "5. Next Lagu\n";
            cout << "6. Prev Lagu\n";
            cout << "7. Stop Lagu\n";
            cout << "Sedang memutar: " << currentSong->info.title;
            if (isFromPlaylist) {
                cout << " (Playlist: " << currentPlaylist->info.namaPlaylist << ")";
            }
            cout << endl;
        }

        cout << "0. Logout\n";
        cout << "Pilih: ";
        cin >> pilihan;

        // ================= LIBRARY =================
        if (pilihan == 1) {
            displayAllSongs(LS);
            string title;
            cout << "Judul lagu: ";
            cin >> title;

            currentSong = findSong(LS, title);
            if (currentSong != nullptr) {
                isFromPlaylist = false;
                playSong(currentSong);
            } else {
                cout << "Lagu tidak ditemukan.\n";
            }
        }

        // ================= PLAYLIST =================
        else if (pilihan == 4) {
            menuPlaylist(LS, user, currentPlaylist, currentRelasi);

            if (currentPlaylist != nullptr && currentRelasi != nullptr) {
                currentSong = currentRelasi->pointerSong;
                isFromPlaylist = true;
                playSong(currentSong);
            }
        }

        // ================= NEXT =================
        else if (pilihan == 5 && currentSong != nullptr) {
            if (isFromPlaylist) {
                currentRelasi = nextSongPlaylist(currentPlaylist, currentRelasi);
                currentSong = currentRelasi->pointerSong;
            } else {
                currentSong = nextSongLibrary(LS, currentSong);
            }
            playSong(currentSong);
        }

        // ================= PREV =================
        else if (pilihan == 6 && currentSong != nullptr) {
            if (isFromPlaylist) {
                currentRelasi = prevSongPlaylist(currentPlaylist, currentRelasi);
                currentSong = currentRelasi->pointerSong;
            } else {
                currentSong = prevSongLibrary(LS, currentSong);
            }
            playSong(currentSong);
        }

        // ================= STOP =================
        else if (pilihan == 7 && currentSong != nullptr) {
            stopSong(currentSong);
            currentSong = nullptr;
            currentRelasi = nullptr;
            currentPlaylist = nullptr;
            isFromPlaylist = false;
        } else if (pilihan == 2){
            selectionSortTitleOnLibrary(LS);
        } else if (pilihan == 3){
            selectionSortByGenre(LS);
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
        cout << count << ".  | " << P->info.title << " | " << P->info.artist << " | " << P->info.genre << endl;
        P = P->next;
        count++;
    }

    cout << "------------------------------------------------------------\n";
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
             << " | Lagu: " << p->info.countSong;
        p = p->nextPlaylist;
        i++;
    }
}


void menuPlaylist(listSong &LS,adrUser user,adrPlaylist &selectedPlaylist,adrRelasi &selectedRelasi){ ////
    int pilihan = -1;
    string namaPlaylist, title;

    selectedPlaylist = nullptr;

    while (pilihan != 0) {
        cout << "\n=== ATUR PLAYLIST ===\n";
        cout << "1. Buat Playlist\n";
        cout << "2. Lihat Playlist & Lagu\n";
        cout << "3. Hapus Playlist\n";
        cout << "4. Tambah Lagu ke Playlist\n";
        cout << "5. Hapus Lagu dari Playlist\n";
        cout << "6. Putar Playlist\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "Nama playlist: ";
            cin >> namaPlaylist;
            addPlaylist(user, createElmPlayist(namaPlaylist, 0, 0));
        }

        else if (pilihan == 2) {
            displayAllUserPlaylistsAndSongs(user);
        }

        else if (pilihan == 3) {
            cout << "Nama playlist: ";
            cin >> namaPlaylist;
            deletePlaylist(user, namaPlaylist);
        }

        else if (pilihan == 4) {
            cout << "Nama playlist: ";
            cin >> namaPlaylist;
            cout << "Judul lagu: ";
            cin >> title;
            addSongToPlaylist(LS, user, namaPlaylist, title);
        }

        else if (pilihan == 5) {
            cout << "Nama playlist: ";
            cin >> namaPlaylist;
            cout << "Judul lagu: ";
            cin >> title;
            removeSongFromPlaylist(user, namaPlaylist, title);
        }

        else if (pilihan == 6) {
            displayAllUserPlaylistsAndSongs(user);

            cout << "Pilih Playlist: ";
            cin >> namaPlaylist;

            selectedPlaylist = searchPlaylistUser(user, namaPlaylist);
            if (selectedPlaylist == nullptr || selectedPlaylist->firstSong == nullptr) {
                cout << "Playlist kosong atau tidak ditemukan.\n";
                selectedPlaylist = nullptr;
                return;
            }

            // tampilkan lagu dalam playlist
            cout << "\nDaftar Lagu:\n";
            adrRelasi R = selectedPlaylist->firstSong;
            while (R != nullptr) {
                cout << "- " << R->pointerSong->info.title << endl;
                R = R->next;
            }

            cout << "Pilih judul lagu: ";
            cin >> title;

            // cari lagu dalam playlist
            R = selectedPlaylist->firstSong;
            while (R != nullptr && R->pointerSong->info.title != title) {
                R = R->next;
            }

            if (R == nullptr) {
                cout << "Lagu tidak ada di playlist.\n";
                selectedPlaylist = nullptr;
                return;
            }

            selectedRelasi = R;
            return; // kembali ke menuUser untuk PLAY
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
adrPlaylist searchPlaylistUser(adrUser user, string namaPlaylist) {
    adrPlaylist P = user->nextPlaylist;
    while (P != nullptr) {
        if (P->info.namaPlaylist == namaPlaylist) {
            return P;
        }
        P = P->nextPlaylist;
    }
    return nullptr;
}
void deleteFirstPlaylist(adrUser &user) {
    adrPlaylist p = user->nextPlaylist;

    if (p == nullptr) {
        cout << "Tidak ada playlist.\n";
        return;
    }

    // Geser head
    user->nextPlaylist = p->nextPlaylist;

    // Putuskan link
    p->nextPlaylist = nullptr;
}

void deleteLastPlaylist(adrUser &user) {

    if (user->nextPlaylist == nullptr) {
        cout << "Tidak ada playlist.\n";
        return;
    }

    adrPlaylist p = user->nextPlaylist;

    // Jika hanya 1 node → sama seperti delete first
    if (p->nextPlaylist == nullptr) {
        user->nextPlaylist = nullptr;
        return;
    }

    // Cari node sebelum terakhir
    adrPlaylist prec = nullptr;
    while (p->nextPlaylist != nullptr) {
        prec = p;
        p = p->nextPlaylist;
    }

    // Hapus node terakhir
    prec->nextPlaylist = nullptr;
}
void deleteAfterPlaylist(adrPlaylist prec) {

    if (prec == nullptr || prec->nextPlaylist == nullptr) {
        return; // tidak ada yang bisa dihapus
    }

    adrPlaylist p = prec->nextPlaylist;  // node yang akan dihapus
    prec->nextPlaylist = p->nextPlaylist;

    // putuskan link
    p->nextPlaylist = nullptr;
}
void deletePlaylist(adrUser &user, string namaPlaylist) {

    adrPlaylist p = searchPlaylistUser(user, namaPlaylist);
    if (p == nullptr) {
        cout << "Playlist tidak ditemukan.\n";
        return;
    }

    // CASE 1: playlist pertama
    if (p == user->nextPlaylist) {
        deleteFirstPlaylist(user);
    }
    // CASE 2: playlist terakhir
    else if (p->nextPlaylist == nullptr) {
        deleteLastPlaylist(user);
    }
    // CASE 3: playlist di tengah
    else {
        adrPlaylist prec = user->nextPlaylist;
        while (prec->nextPlaylist != p) {
            prec = prec->nextPlaylist;
        }
        deleteAfterPlaylist(prec);
    }

    cout << "Playlist '" << namaPlaylist << "' berhasil dihapus.\n";
}



void playSong(adrSong song) {
    if (song != nullptr) {
        cout << "\n SEDANG MEMUTAR: " << song->info.title << " - " << song->info.artist << endl;
    }
}

void stopSong(adrSong song) {
    if (song != nullptr) {
        cout << "\n Pemutaran dihentikan: " << song->info.title << endl;
    }
}

adrSong nextSongLibrary(listSong &LS, adrSong current) {
    if (current == nullptr || LS.first == nullptr) {
        cout << "Library kosong atau tidak ada lagu yang sedang diputar.\n";
        return nullptr;
    }

    // === 1. Jika masih ada lagu setelah current → lanjut normal ===
    if (current->next != nullptr) {
        return current->next;
    }

    // === 2. Jika current adalah lagu terakhir ===
    string currentArtist = current->info.artist;
    adrSong P = LS.first;

    // Cari lagu lain dengan artist yang sama (selain current)
    while (P != nullptr) {
        if (P != current && P->info.artist == currentArtist) {
            cout << "Memutar lagu lain oleh artis yang sama: "
                 << currentArtist << endl;
            return P;
        }
        P = P->next;
    }

    // === 3. Jika tidak ada lagu artist sama → kembali ke awal ===
    cout << "Tidak ada lagu lain oleh artis "
         << currentArtist
         << ". Kembali ke lagu pertama di Library.\n";

    return LS.first;
}
adrSong prevSongLibrary(listSong &LS, adrSong current) {
    if (current == nullptr || LS.first == nullptr) {
        cout << "Library kosong atau tidak ada lagu yang sedang diputar.\n";
        return nullptr;
    }
    string currentArtist = current->info.artist;
    adrSong P = current->prev; // P mulai dari lagu sebelum current

    while (P != nullptr) {

        // Cek apakah artisnya sama
        if (P->info.artist == currentArtist) {
            cout << "Memutar lagu sebelumnya oleh artis yang sama: " << currentArtist << endl;
            return P; // Lagu ditemukan, dikembalikan
        }

        P = P->prev; // Pindah ke elemen sebelumnya
    }

    cout << "Looping: Tidak ada lagi lagu oleh artis " << currentArtist << " sebelumnya. Kembali ke lagu terakhir di Library.\n";
    return LS.last;
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

        adrRelasi Q = currentPlaylist->firstSong;
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


void addSongToPlaylist(listSong &LS, adrUser user, string namaPlaylist, string title) {

    // 1. Cari playlist berdasarkan nama
    adrPlaylist PL = searchPlaylistUser(user, namaPlaylist);
    if (PL == nullptr) {
        cout << "Playlist tidak ditemukan!\n";
        return;
    }

    // 2. Cari lagu di library berdasarkan judul
    adrSong S = findSong(LS, title);
    if (S == nullptr) {
        cout << "Lagu tidak ditemukan di Library!\n";
        return;
    }

    // 3. Buat node relasi (menghubungkan playlist -> song)
    adrRelasi R = createElmPointerSong(S);

    // 4. Insert LAST ke dalam list relasi playlist
    if (PL->firstSong == nullptr) {
        // jika playlist masih kosong
        PL->firstSong = R;
    } else {
        // jika sudah ada lagu → cari LAST
        adrRelasi Q = PL->firstSong;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = R;
        R->prev = Q;
    }

    // 5. Update informasi playlist
    PL->info.countSong++;

    cout << "Lagu \"" << title << "\" berhasil ditambahkan ke playlist \""
         << namaPlaylist << "\".\n";
}

void removeSongFromPlaylist(adrUser user, string playlistName, string songTitle){

    // 1. cari playlist dulu
    adrPlaylist p = searchPlaylistUser(user, playlistName);
    if (p == nullptr){
        cout << "Playlist tidak ditemukan.\n";
        return;
    }

    // 2. cari relasi ke lagu
    adrRelasi r = p->firstSong;

    while (r != nullptr && r->pointerSong->info.title != songTitle){
        r = r->next;
    }

    if (r == nullptr){
        cout << "Lagu \"" << songTitle << "\" tidak ditemukan dalam playlist.\n";
        return;
    }

    // 3. Hapus node relasi
    if (r->prev == nullptr){            // delete FIRST
        p->firstSong = r->next;
        if (r->next != nullptr){
            r->next->prev = nullptr;
        }
    } else if (r->next == nullptr) {    // delete LAST
        r->prev->next = nullptr;
    } else {                             // delete MIDDLE
        r->prev->next = r->next;
        r->next->prev = r->prev;
    }

    // 4. UPDATE jumlah lagu dan durasi
    p->info.countSong--;

    delete r;

    cout << "Lagu \"" << songTitle << "\" berhasil dihapus dari playlist \"" << playlistName << "\".\n";
}
void displayAllUserPlaylistsAndSongs(adrUser user){
    adrPlaylist p = user->nextPlaylist;

    if (p == nullptr){
        cout << "User belum memiliki playlist.\n";
        return;
    }

    cout << "\n=== Semua Playlist User ===\n";

    while (p != nullptr){
        cout << "\nPlaylist: " << p->info.namaPlaylist << endl;
        cout << "Jumlah Lagu  : " << p->info.countSong << endl;

        adrRelasi r = p->firstSong;

        if (r == nullptr){
            cout << "(Kosong)\n";
        } else {
            while (r != nullptr){
                cout << "- "
                     << r->pointerSong->info.title
                     << " - "
                     << r->pointerSong->info.artist
                     << endl;   
                r = r->next;
            }
        }

        p = p->nextPlaylist;
    }
}
void selectionSortTitleOnLibrary(listSong &LS){
// I.S : List lagu (LS) mungkin kosong atau berisi beberapa elemen. Jika berisi, elemen-elemen belum terurut berdasarkan judul lagu.
// F.S : Seluruh elemen pada list akan terurut membesar (A-Z) berdasarkan judul lagu.

    if(LS.first == nullptr){
        cout << "Tidak ada lagu di library untuk diurutkan\n";
        return ;
    }
    adrSong p;
    p = LS.first;
    SongInfo temp;
    while(p != nullptr){
        adrSong mini = p;
        adrSong q = p->next;
        while(q != nullptr){
            if(q->info.title < mini->info.title){
                mini = q;
            }
            q = q->next;
        }
        temp = p->info;
        p->info = mini->info;
        mini->info = temp;

        p = p -> next;
    }
}
void selectionSortByArtist(listSong &LS){
// I.S : List lagu (LS) mungkin kosong atau berisi beberapa elemen.Jika berisi, elemen-elemen belum terurut berdasarkan nama artis.
// F.S : Seluruh elemen pada list akan terurut membesar (A-Z) berdasarkan nama artis.


    if(LS.first == nullptr){
        cout << "Tidak ada lagu di library untuk diurutkan\n";
        return ;
    }
    adrSong p;
    p = LS.first;
    SongInfo temp;
    while(p != nullptr){
        adrSong mini = p;
        adrSong q = p->next;
        while(q != nullptr){
            if(q->info.artist < mini->info.artist){
                mini = q;
            }
            q = q->next;
        }
        temp = p->info;
        p->info = mini->info;
        mini->info = temp;

        p = p -> next;
    }
}



