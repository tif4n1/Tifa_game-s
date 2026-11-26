#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT 50
#define JUMLAH_MOBIL_LAWAN 5
#define LEBAR_MOBIL 13
#define TINGGI_MOBIL 4

static char username_akun[MAX_INPUT] = "pemain";
static char password_akun[MAX_INPUT] = "1234";
static int level = 1;
static int sudah_login = 0;

static const char *gambar_art[TINGGI_MOBIL] = {
    "  ______",
    " /|_||_\\`.__",
    "(   _    _ _\\",
    "=`-(_)--(_)-'"
};

void baca_input(const char *pesan, char *hasil, int ukuran, int rahasia)
{
    int panjang = 0;
    int baris, kolom;

    getyx(stdscr, baris, kolom);
    mvprintw(baris, 0, "%s", pesan);
    clrtoeol();
    kolom = (int)strlen(pesan);

    hasil[0] = '\0';
    curs_set(1);
    keypad(stdscr, TRUE);

    while (1) {
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
        } else if (tombol >= 32 && tombol <= 126 &&
                   panjang < ukuran - 1) {
            hasil[panjang++] = (char)tombol;
            hasil[panjang] = '\0';
            mvaddch(baris, kolom + panjang - 1, rahasia ? '*' : tombol);
        }

        refresh();
    }

    curs_set(0);
}

void tunggu_tombol(void)
{
    mvprintw(LINES - 2, 2, "Tekan tombol apa saja untuk kembali...");
    refresh();
    timeout(-1);
    getch();
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

    if (strcmp(nama, username_akun) == 0 &&
        strcmp(sandi, password_akun) == 0) {
        sudah_login = 1;
        clear();
        mvprintw(3, 2, "Login berhasil. Selamat datang, %s!", nama);
        tunggu_tombol();
        return 1;
