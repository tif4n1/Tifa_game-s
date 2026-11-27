#include "auth.h"

#include <ncurses.h>
#include <cstring>

#define MAX_INPUT 50

static char username_akun[MAX_INPUT] = "pemain";
static char password_akun[MAX_INPUT] = "1234";
static int sudah_login = 0;

static void baca_input(const char *pesan, char *hasil, int ukuran, int rahasia)
{
    int panjang = 0;
    int baris;
    int kolom;

    getyx(stdscr, baris, kolom);
    mvprintw(baris, 0, "%s", pesan);
    clrtoeol();
    kolom = static_cast<int>(std::strlen(pesan));

    hasil[0] = '\0';
    curs_set(1);
    keypad(stdscr, TRUE);

    while (true) {
        int tombol = getch();

        if (tombol == '\n' || tombol == KEY_ENTER) {
            break;
        }

        if (tombol == KEY_BACKSPACE || tombol == 127 || tombol == 8) {
            if (panjang > 0) {
                panjang--;
                hasil[panjang] = '\0';
                mvaddch(baris, kolom + panjang, ' ');
                move(baris, kolom + panjang);
            }
        } else if (tombol >= 32 && tombol <= 126 && panjang < ukuran - 1) {
            hasil[panjang++] = static_cast<char>(tombol);
            hasil[panjang] = '\0';
            mvaddch(baris, kolom + panjang - 1, rahasia ? '*' : tombol);
        }

        refresh();
    }

    curs_set(0);
}

static void tunggu_tombol(void)
{
    mvprintw(LINES - 2, 2, "Tekan tombol apa saja untuk kembali...");
    refresh();
    timeout(-1);
    getch();
}

int pengguna_sudah_login(void)
{
    return sudah_login;
}

int proses_login(void)
{
    char nama[MAX_INPUT];
    char sandi[MAX_INPUT];

    clear();
    mvprintw(2, 2, "=== LOGIN ===");
    move(4, 2);
    baca_input("Username: ", nama, sizeof(nama), 0);
    move(5, 2);
    baca_input("Password: ", sandi, sizeof(sandi), 1);

    if (std::strcmp(nama, username_akun) == 0 &&
        std::strcmp(sandi, password_akun) == 0) {
        sudah_login = 1;
        clear();
        mvprintw(3, 2, "Login berhasil. Selamat datang, %s!", nama);
        tunggu_tombol();
        return 1;
    }

    clear();
    mvprintw(3, 2, "Username atau password salah.");
    tunggu_tombol();
    return 0;
}

void reset_password(void)
{
    char nama[MAX_INPUT];
    char sandi_baru[MAX_INPUT];

    clear();
    mvprintw(2, 2, "=== RESET PASSWORD ===");
    move(4, 2);
    baca_input("Username akun: ", nama, sizeof(nama), 0);

    if (std::strcmp(nama, username_akun) != 0) {
        mvprintw(6, 2, "Username tidak ditemukan.");
        tunggu_tombol();
        return;
    }

    move(5, 2);
    baca_input("Password baru: ", sandi_baru, sizeof(sandi_baru), 1);

    if (std::strlen(sandi_baru) == 0) {
        mvprintw(7, 2, "Password tidak boleh kosong.");
    } else {
        std::strcpy(password_akun, sandi_baru);
        mvprintw(7, 2, "Password berhasil diubah.");
    }

    tunggu_tombol();
}
