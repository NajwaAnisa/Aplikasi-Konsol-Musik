#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
using namespace std;


struct User {
    string nama;
    string password;
    string role;
};
struct UserElm {
    User info;
    adrUser next;
    adrUser prev;

    // Relasi user → playlist (1-to-N)
    adrPlaylist listPlaylist;

    // Relasi user → song (favorite/history) (N-to-M)
    adrRel listFavSong;
};
#endif // TUBES_H_INCLUDED