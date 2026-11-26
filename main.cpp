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

    if (strcmp(nama, username_akun) != 0) {
        mvprintw(6, 2, "Username tidak ditemukan.");
        tunggu_tombol();
        return;
    }

    move(5, 2);
    baca_input("Password baru: ", sandi_baru, sizeof(sandi_baru), 1);

    if (strlen(sandi_baru) == 0) {
        mvprintw(7, 2, "Password tidak boleh kosong.");
    } else {
        strcpy(password_akun, sandi_baru);
        mvprintw(7, 2, "Password berhasil diubah.");
    }

    tunggu_tombol();
}

int pilih_level(void)
{
    int pilihan = 0;
    const char *nama_level[] = {
        "Level 1 - Santai",
        "Level 2 - Sedang",
        "Level 3 - Cepat"
    };

    while (1) {
        int tombol;

        clear();
        mvprintw(2, 2, "=== PILIH LEVEL ===");
        mvprintw(4, 2, "Gunakan panah atas/bawah, lalu Enter.");

        for (int i = 0; i < 3; i++) {
            if (i == pilihan) {
                attron(A_REVERSE);
            }
            mvprintw(6 + i, 4, "%s", nama_level[i]);
            if (i == pilihan) {
                attroff(A_REVERSE);
            }
        }

        refresh();
        tombol = getch();

        if (tombol == KEY_UP && pilihan > 0) {
            pilihan--;
        } else if (tombol == KEY_DOWN && pilihan < 2) {
            pilihan++;
        } else if (tombol == '\n' || tombol == KEY_ENTER) {
            return pilihan + 1;
        } else if (tombol == 27) {
            return 0;
        }
    }
}

/* x = titik tengah mobil, y = baris paling atas mobil */
void gambar_mobil(int x, int y, int tebal)
{
    int kiri = x - LEBAR_MOBIL / 2;

    if (tebal) {
        attron(A_BOLD);
    }
    for (int i = 0; i < TINGGI_MOBIL; i++) {
        int baris = y + i;
        if (baris >= 1 && baris < LINES - 1) {
            mvprintw(baris, kiri, "%s", gambar_art[i]);
        }
