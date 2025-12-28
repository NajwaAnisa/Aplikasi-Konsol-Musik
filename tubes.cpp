#include <iostream>
#include "TUBES.h"
using namespace std;

// IS: List User (LU) belum terdefinisi 
// FS: List User (LU) terbentuk sebagai list kosong (LU.first = nullptr)
void createListUser(listUser &LU){
    LU.first = nullptr;
}

// IS: List Song (LS) belum terdefinisi 
// FS: List Song (LS) terbentuk sebagai list kosong (LS.first dan LS.last = nullptr)
void createListSong(listSong &LS){
    LS.first = nullptr;
    LS.last = nullptr;
}

// IS: List Playlist (LP) belum terdefinisi 
// FS: List Playlist (LP) terbentuk sebagai list kosong (LP.first dan LP.last = nullptr)
void createListPlaylist(listPlaylist &LP){
    LP.first = nullptr;
    LP.last = nullptr;
}

// Input: Data detail lagu (id, judul, penyanyi, genre, album, menit, detik)
// Mengembalikan alamat (pointer) dari elemen lagu yang baru dibuat
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

// Input: Data kredensial (username, password, role)
// Mengembalikan alamat elemen User yang baru dibuat
adrUser createElmUser(string username, string password, string role){
    adrUser p = new elmUser;
    p->info.username = username;
    p->info.password = password;
    p->info.role = role;
    p->nextUser = nullptr;
    p->nextPlaylist = nullptr;
    return p;
}

// Input: Nama playlist dan jumlah lagu (countSong akan di-reset ke 0)
// Mengembalikan alamat elemen Playlist yang baru dibuat
adrPlaylist createElmPlaylist(string namaPlaylist, int countSong){
    adrPlaylist p = new elmPlaylist;
    p->info.namaPlaylist = namaPlaylist;
    p->info.countSong = 0;
    p->nextPlaylist = nullptr;
    p->firstSong = nullptr;
    return p;
}

// Input: Pointer (q) yang menunjuk ke elemen lagu yang sudah ada di List Song
// Mengembalikan alamat elemen Relasi (penghubung ke lagu)
adrRelasi createElmPointerSong(adrSong q){
    adrRelasi p = new elmRelasiPlaylistSong;
    p->next = nullptr;
    p->prev = nullptr;
    p->pointerSong = q;
    return p;
}

// IS: List User (LU) mungkin kosong, p adalah elemen user baru yang sudah teralokasi
// FS: p berhasil ditambahkan sebagai elemen pertama  di List User (LU)
void insertFirstUser(listUser &LU, adrUser p){
    if (LU.first == nullptr){
        LU.first = p;
    }else{
        p->nextUser = LU.first;
        LU.first = p;
    }

}

// IS: List Song (LS) mungkin kosong, p adalah elemen lagu baru yang sudah teralokasi
// FS: p berhasil ditambahkan di akhir List Song (LS). Menggunakan mekanisme Double Linked List
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

// IS: List User (LU) terdefinisi (mungkin kosong atau berisi elemen)
// FS: Menampilkan seluruh data user (username, password, role) ke layar.
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

// IS: List Song (LS) terdefinisi (mungkin kosong atau berisi elemen)
// FS: Menampilkan seluruh detail lagu (ID, Judul, Artist, Genre, Album, Durasi) ke layar.
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

// Input: List User (LU), string username, dan string password yang dicari
// Mengembalikan alamat User jika username dan password cocok
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

// Input: List Song (LS) dan string judul lagu (title)
// Mengembalikan alamat elemen lagu berdasarkan judul yang dicari
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

// IS: List Song (LS) terdefinisi, mungkin berisi lagu yang ingin dicari
// FS: Jika lagu ditemukan berdasarkan judul, data info (judul, artis, genre, dll) diupdate.
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

// IS: List Song (LS) terdefinisi dan tidak kosong
// FS: Elemen pertama list dikeluarkan dari list dan alamatnya disimpan dalam pointer p.
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

// IS: List Song (LS) terdefinisi dan tidak kosong
// FS: Elemen terakhir list dikeluarkan dari list dan alamatnya disimpan dalam pointer p.
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

// IS: List Song (LS) terdefinisi, prec adalah pointer yang menunjuk elemen sebelum elemen yang akan dihapus
// FS: Elemen setelah prec dihapus dari list, alamatnya disimpan di p, dan hubungan antar node (next/prev) diperbarui
void deleteAfterSong(listSong &LS, adrSong prec, adrSong &p){
    p = prec->next;

    prec->next = p->next;
    p->next->prev = prec;

    p->next = nullptr;
    p->prev = nullptr;
}

// IS: List Song (LS) dan List User (LU) terdefinisi
// FS: Lagu dengan judul tertentu dihapus dari List Utama (LS) DAN dihapus dari seluruh playlist
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

// IS: List User (LU) dan List Song (LS) terdefinisi
// FS: Menampilkan antarmuka menu untuk Admin dan menjalankan fungsi (Tambah, Lihat, Edit, Hapus)
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
            string title, artist, genre, album, minute, second;
            int song_id;

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

// IS: List User (LU), List Song (LS) terdefinisi, dan pointer user (user) menunjuk ke user yang sedang login
// FS: Menampilkan antarmuka interaktif untuk user yang meliputi navigasi library, playlist, pengurutan lagu, serta kontrol pemutaran lagu (play, next, prev, stop). 
// Status pemutaran (currentSong) diperbarui sesuai aksi pengguna.
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
            selectionSortByArtist(LS);
        }
    }
}

// IS: List Song (LS) terdefinisi 
// FS: Menampilkan daftar seluruh lagu yang ada di library dalam format tabel sederhana (No, Judul, Artis, Genre). Jika kosong, menampilkan pesan bahwa library kosong.
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

// IS: Pointer user (u) terdefinisi dan menunjuk ke elemen user tertentu
// FS: Menampilkan daftar nama playlist dan jumlah lagu di dalamnya yang dimiliki oleh user tersebut.
//     Jika user belum memiliki playlist, menampilkan pesan "Tidak ada playlist".
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

// IS: List Song (LS) dan user terdefinisi. selectedPlaylist dan selectedRelasi mungkin bernilai nullptr.
// FS: Menampilkan menu pengelolaan playlist (buat, lihat, hapus, tambah lagu, hapus lagu, putar).
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
            addPlaylist(user, createElmPlaylist(namaPlaylist, 0));
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

// IS: Pointer user (u) terdefinisi, p adalah elemen playlist baru yang sudah dibuat (createElmPlaylist).
// FS: p ditambahkan ke akhir daftar playlist milik user tersebut (Insert Last pada list playlist user).
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

// Input: Pointer user dan string nama playlist yang dicari
// Mengembalikan alamat playlist berdasarkan nama yang dicari pada user tertentu
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

// IS: Pointer user terdefinisi dan mungkin memiliki list playlist.
// FS: Elemen playlist pertama milik user dihapus dari list. Pointer head (nextPlaylist) user bergeser.
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

// IS: Pointer user terdefinisi dan mungkin memiliki list playlist (nextPlaylist).
// FS: Elemen playlist terakhir dalam list milik user dihapus.
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

// IS: Pointer prec (elemen sebelum target) terdefinisi
// FS: Elemen setelah prec dihapus dari list playlist user dan link disambungkan kembali.
// Memori elemen yang dihapus belum didealokasi (p->next diset nullptr).
void deleteAfterPlaylist(adrPlaylist prec) {

    if (prec == nullptr || prec->nextPlaylist == nullptr) {
        return; // tidak ada yang bisa dihapus
    }

    adrPlaylist p = prec->nextPlaylist;  // node yang akan dihapus
    prec->nextPlaylist = p->nextPlaylist;

    // putuskan link
    p->nextPlaylist = nullptr;
}

// IS: List playlist user terdefinisi, mungkin berisi playlist yang ingin dihapus
// FS: Playlist dengan nama tertentu dicari. Jika ditemukan, dihapus dari list baik di posisi pertama, terakhir, maupun tengah menggunakan prosedur penghapusan yang sesuai.
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
// IS: Pointer song terdefinisi 
// FS: Menampilkan pesan ke layar bahwa lagu tersebut sedang diputar.
void playSong(adrSong song) {
    if (song != nullptr) {
        cout << "\n SEDANG MEMUTAR: " << song->info.title << " - " << song->info.artist << endl;
    }
}

// IS: Pointer song terdefinisi 
// FS: Menampilkan pesan ke layar bahwa pemutaran lagu tersebut dihentikan.
void stopSong(adrSong song) {
    if (song != nullptr) {
        cout << "\n Pemutaran dihentikan: " << song->info.title << endl;
    }
}

// Mengembalikan alamat lagu berikutnya dalam Library berdasarkan logika Artist
// Input: List Lagu (LS) dan alamat lagu yang sedang diputar (current)
// Return: 1. Elemen next jika tersedia. 
//         2. Jika di akhir list, mencari lagu lain dengan Artist yang sama.
//         3. Jika tidak ada Artist yang sama, kembali ke elemen pertama (LS.first).
adrSong nextSongLibrary(listSong &LS, adrSong current) {

    if (current == nullptr || LS.first == nullptr) {
        cout << "Library kosong atau tidak ada lagu yang sedang diputar.\n";
        return nullptr;
    }
    string currentArtist = current->info.artist;
    adrSong P = current->next;
    while (P != current && P != nullptr) {
        if (P->info.artist == currentArtist) {
            cout << "Memutar lagu berikutnya oleh artis yang sama: " << currentArtist << endl;
            return P;
        }
        if (P == LS.last) {
            P = LS.first;
        } else {
            P = P->next; // Pindah ke elemen berikutnya
        }

    }

    cout << "Tidak ada lagi lagu oleh artis " << currentArtist << ". Kembali ke lagu pertama di Library.\n";
    return LS.first;

}

// Mengembalikan alamat lagu sebelumnya dalam Library dengan logika filter Artist
// Input: List Song (LS) dan alamat lagu yang sedang diputar (current)
// Return: Pointer lagu (adrSong) sebelumnya yang memiliki Artist yang sama. 
//         Jika tidak ditemukan hingga awal list, mengembalikan LS.last (looping).
adrSong prevSongLibrary(listSong &LS, adrSong current) {

    if (current == nullptr || LS.first == nullptr) {
        cout << "Library kosong atau tidak ada lagu yang sedang diputar.\n";
        return nullptr;
    }
    string currentArtist = current->info.artist;
    adrSong P = current->prev; // P mulai dari lagu sebelum current
    while (P != current) {
        // Cek apakah artisnya sama
        if (P->info.artist == currentArtist) {
            cout << "Memutar lagu sebelumnya oleh artis yang sama: " << currentArtist << endl;
            return P; // Lagu ditemukan, dikembalikan
        }
        if (P == LS.first) {
            P = LS.last;
        } else {
            P = P->prev; // Pindah ke elemen sebelumnya
        }
    }
    cout << "Tidak ada lagi lagu oleh artis " << currentArtist << " sebelumnya. Kembali ke lagu terakhir di Library.\n";
    return LS.last;

}

// Mengembalikan alamat relasi lagu berikutnya dalam Playlist
// Input: Pointer playlist aktif dan relasi lagu saat ini (p)
// Return: Pointer relasi (adrRelasi) berikutnya. Jika p adalah elemen terakhir, 
//         kembali ke elemen pertama.
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

// Mengembalikan alamat relasi lagu sebelumnya dalam Playlist
// Input: Pointer playlist aktif dan relasi lagu saat ini (p)
// Return: Pointer relasi (adrRelasi) sebelumnya. Jika p adalah elemen pertama, 
//         melakukan traversal untuk mengembalikan elemen terakhir.
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

// IS: List Song (LS) dan User terdefinisi. Nama playlist dan judul lagu diberikan oleh input.
// FS: Jika playlist dan lagu ditemukan, sebuah elemen relasi baru dibuat dan dihubungkan 
//     ke dalam list lagu milik playlist tersebut (Insert Last). countSong bertambah.
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

// IS: User terdefinisi, memiliki minimal satu playlist.
// FS: Relasi ke lagu dengan judul tertentu dihapus dari playlist yang dimaksud dan countSong berkurang.
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

// IS: Pointer user terdefinisi.
// FS: Menampilkan seluruh playlist yang dimiliki user beserta rincian lagu (judul & artis) yang ada di dalam setiap playlist tersebut ke layar.
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

// IS: List lagu (LS) terdefinisi, mungkin kosong atau berisi beberapa elemen yang belum terurut.
// FS: Seluruh elemen pada list terurut secara ascending (A-Z) berdasarkan JUDUL lagu.
// Prosedur ini menggunakan metode Selection Sort dengan menukar isi data (info), bukan alamat node.
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

// IS: List lagu (LS) terdefinisi, mungkin kosong atau berisi beberapa elemen yang belum terurut.
// FS: Seluruh elemen pada list terurut secara ascending (A-Z) berdasarkan nama ARTIS.
// Prosedur ini menggunakan metode Selection Sort dengan menukar isi data (info).
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



