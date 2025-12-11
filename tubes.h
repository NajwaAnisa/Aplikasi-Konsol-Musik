#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <string>
using namespace std;

// --- 1. Library Musik Global (Doubly Linked List) ---
typedef struct elmSong *adrSong;
struct SongInfo {
    int song_id;
    string title;
    string artist;
    string genre;
    string album;
    int duration_seconds;
};
struct elmSong{
    SongInfo info;
    adrSong next;
    adrSong prev;
};

struct listSong{
    adrSong first;
    adrSong last;
};
// --- 2. Relasi antara Playlist dengan Song
typedef struct elmRelasiPlaylistSong *adrRelasi;

struct elmRelasiPlaylistSong{
    adrRelasi next;
    adrRelasi prev;
    adrSong pointerSong;
};
// --- 3. Daftar User (Singly Linked List)

typedef struct  elmUser *adrUser;
typedef struct elmPlaylist *adrPlaylist;
struct UserInfo {
    string username;
    string password;
    string role;
};

struct elmUser{
    UserInfo info;
    adrUser nextUser;
    adrPlaylist nextPlaylist;
};

struct listUser {
    adrUser first;
};

// --- 4. Playlist User

struct playlistInfo{
  string namaPlaylist;
  int countSong;
  int durasiTotal;
};

struct elmPlaylist{
    playlistInfo info;
    adrPlaylist nextPlaylist;
    adrSong firstSong;
};

struct listPlaylist{
    adrPlaylist first;
    adrPlaylist last;
};

//menu //
void menuUser(listUser &LU, listSong &LS, adrUser user);
void menuAdmin(listUser &LU, listSong &LS);
void menuPlaylist(listSong &LS, adrUser user);

// user //
void createListUser(listUser &LU);
adrUser createElmUser(string username, string password, string role);
void insertFirstUser(listUser &LU, adrUser p);
void displayUser(listUser LU);
adrUser login(listUser LU, string username, string password);

// lagu //
void createListSong(listSong &LS);
adrSong createElmSong(int song_id, string title, string artist, string genre, string album, int duration_seconds);
void insertLastSong(listSong &LS, adrSong p); //menambah lagu
void displaySong(listSong LS); // melihat lagu
adrSong findSong(listSong LS, string title);
void editSong(listSong &LS); // mengubah data lagu
void deleteSong(listSong &LS); //mengahapus lagu general
void deleteFirstSong(listSong &LS, adrSong &p);
void deleteLastSong(listSong &LS, adrSong &p);
void deleteAfterSong(listSong &LS, adrSong prec, adrSong &p);

//Playlist//
void createListPlaylist(listPlaylist &LP);
adrPlaylist createElmPlaylist(string namaPlaylist, int countSong, int durasiTotal);
void addPlaylist(adrUser &u, adrPlaylist p);
void displayAllSongs(listSong LS);
void displayPlaylist(adrUser u);

// Untuk pemutaran//
void playSong(adrSong song);
void stopSong(adrSong song);
adrSong nextSongLibrary(listSong &LS, adrSong current);
adrSong prevSongLibrary(listSong &LS, adrSong current);

adrRelasi nextSongPlaylist(adrPlaylist currentPlaylist, adrRelasi p);
adrRelasi prevSongPlaylist(adrPlaylist currentPlaylist, adrRelasi p);


// Untuk Playlist (terhubung ke adrUser user)
void addSongToPlaylist(listSong &LS, adrUser user, string playlistName, string songTitle); //ini blm

void removeSongFromPlaylist(adrUser user, string playlistName, string songTitle); // ini blm
void displayPlaylistSongs(adrUser user, string playlistName); // ini blm
void playPlaylist(adrUser user, string playlistName); //ini blm tentu kepake

adrRelasi createElmPointerSong(adrSong q);



#endif // TUBES_H_INCLUDED