#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <string>
using namespace std;


struct User {
    string nama;
    string password;
    string role;
};

typedef struct UserElm *adrUser;
typedef struct PlaylistElm *adrPlaylist;
typedef struct SongElm *adrSong;
typedef struct RelElm *adrRel;

struct UserElm {
    User info;
    adrUser next;
    adrUser prev;

    // Relasi user → playlist (1-to-N)
    adrPlaylist listPlaylist;

    // Relasi user → song (favorite/history) (N-to-M)
    adrRel listFavSong;
};

struct Playlist {
    string nama;
    int jumlahLagu;
    int durasiTotal;
};

struct PlaylistElm {
    Playlist info;
    adrPlaylist next;
    adrPlaylist prev;

    // Relasi playlist → song (N-to-M)
    adrRel listSong;
};

struct Song {
    string judul;
    string artist;
    string genre;
    string album;
    int durasi;
};

struct SongElm {
    Song info;
    adrSong next;
    adrSong prev;

    // Relasi balik (opsional): song → playlist (N-to-M)
    adrRel listPlaylist;
};

struct RelElm {
    adrRel next;

    // pointer parent (hanya salah satu yang dipakai)
    adrUser parentUser;         // jika relasi milik user → song
    adrPlaylist parentPlaylist; // jika relasi milik playlist → song

    // pointer child (song selalu child)
    adrSong child;
};

#endif // TUBES_H_INCLUDED
