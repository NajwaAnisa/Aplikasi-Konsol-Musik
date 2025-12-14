# Aplikasi-Konsol-Musik
Aplikasi Konsol Manajemen Musik adalah aplikasi berbasis C++ (console) yang digunakan untuk mengelola library lagu yang dilakukan di menuAdmin dan mengatur playlist di menuUser oleh user.
Aplikasi ini menerapkan konsep Linked List, Multi Linked List, serta relasi Playlist–Song, sehingga cocok sebagai implementasi mata kuliah Struktur Data.

Anggota yang bersangkutan dalam pembuatan aplikasi:
1. Putri Ayu Nur Hakim – 103052400057 
2. Isabelle Rose Marie Rumondor – 103052430012 
3. Najwa Anisa Putri – 103052400054
   
Fitur utama aplikasi meliputi:
1.  Pengelolaan lagu dalam library (edit, delete, add, display)
2.  Pembuatan dan penghapusan playlist
3.	Menambahkan dan menghapus lagu dari playlist
4.	Memutar lagu dari library maupun playlist
5.	Navigasi lagu (Next / Previous) 
6.	Menampilkan jumlah lagu dan total durasi playlist

langkah-langkah menjalankan program:
1. saat masuk ke aplikasi akan menampilkan menu login, disini user bisa memilih 1 atau 0
   
         === MENU LOGIN ===
         1. Login
         0. Keluar Program
         Pilih:
pilihan 1 akan meminta input username dan password; 

      === MENU LOGIN ===
      3. Login
      0. Keluar Program
      Pilih: 1
      Username: admin
      Password: 123

      Login berhasil sebagai: admin

2. jika login sebagai admin maka akan menampilkan menu admin saja

         === MENU ADMIN ===
         1. Tambah Lagu
         2. Lihat semua Lagu
         3. Edit Lagu
         4. Hapus Lagu
         0. Logout
         Pilih:
admin akan memilih sesuai yang ingin dilakukan, ketika ingin ganti user tinggal pilih 0

3. jika login sebagai user maka akan menampilkan menu user

         === MENU USER (user..) ===
         1. Lihat & Putar Lagu dari Library
         2. Atur Playlist
         0. Logout
         Pilih:

4. ketika memilih pilihan 1 (menu user) akan menampilkan semua lagu library dan menginputkan judul lagu yang ingin diputar

         ========================================
                    DAFTAR SEMUA LAGU
         ========================================
         No. | JUDUL LAGU             | ARTIS/PENYANYI      | GENRE
         ------------------------------------------------------------
         1.  | .. | .. | ..
         ------------------------------------------------------------
         Judul lagu:
          SEDANG MEMUTAR: .. - ..
setelah itu akan menampilkan kembali menu user dengan tambahan ada navigasi lagu (next/prev/stop);
         
         === MENU USER (aira) ===
      1. Lihat & Putar Lagu dari Library
      2. Atur Playlist
      3. Next Lagu
      4. Prev Lagu
      5. Stop Lagu
      Sedang memutar: ..
      0. Logout
      Pilih:
