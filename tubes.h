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

// --- 2. Daftar User (Singly Linked List)

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

// --- 3. Playlist User

struct playlistInfo{
  string title;
  int countSong;
  int durasiTotal;
};

struct elmPlaylist{
    playlistInfo info;
    adrPlaylist nextPlaylist;
    adrSong firstSong;
};

struct listPlayist{
    adrPlaylist first;
    adrPlaylist last;
};
void createListSong(listSong &LS);
adrSong createElmSong(int song_id, string title, string artist, string genre, string album, int duration_seconds);
void createListUser(listUser &LU);
adrUser createElmUser(string username, string password, string role);
void menuUser();
void menuAdmin(listUser &LU, listSong &LS);
void insertFirstUser(listUser &LU, adrUser p);
void displayUser(listUser LU);
adrUser login(listUser LU, string username, string password);

void insertLastSong(listSong &LS, adrSong p); //menambah lagu
void displaySong(listSong LS); // melihat lagu
adrSong findSong(listSong LS, string title);
void editSong(listSong &LS); // mengubah data lagu
void deleteSong(SongInfo &LS); //mengahapus lagu



#endif // TUBES_H_INCLUDED