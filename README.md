
# GAME_SEDERHANA

Game balap mobil sederhana berbasis terminal menggunakan C++ dan ncurses.

## Pembagian kode

- `include/auth.h`, `include/game.h`, `include/menu.h`: deklarasi antarmuka antarbagian.
- `src/auth.cpp`: login, reset password, dan input username/password.
- `src/game.cpp`: pemilihan level, gambar mobil, dan logika balapan.
- `src/menu.cpp`: menu utama dan navigasi ke fitur.
- `src/main.cpp`: inisialisasi ncurses dan titik masuk program.
- `Makefile`: instruksi kompilasi.

## Dependensi

Linux atau lingkungan Unix, `g++`, `make`, dan pustaka ncurses. Di Debian/Ubuntu, jalankan:

```bash
sudo apt install build-essential libncurses-dev
