#include "game.h"

#include <ncurses.h>
#include <cstdlib>

#define JUMLAH_MOBIL_LAWAN 5
#define LEBAR_MOBIL 13
#define TINGGI_MOBIL 4

static const char *gambar_art[TINGGI_MOBIL] = {
    "  ______",
    " /|_||_\\`.__",
    "(   _    _ _\\",
    "=`-(_)--(_)-'"
};

int pilih_level(void)
{
    int pilihan = 0;
    const char *nama_level[] = {
        "Level 1 - Santai",
        "Level 2 - Sedang",
        "Level 3 - Cepat"
    };

    while (true) {
        int tombol;

        clear();
        mvprintw(2, 2, "=== PILIH LEVEL ===");
        mvprintw(4, 2, "Gunakan panah atas/bawah, lalu Enter.");

        for (int i = 0; i < 3; i++) {
            if (i == pilihan) attron(A_REVERSE);
            mvprintw(6 + i, 4, "%s", nama_level[i]);
            if (i == pilihan) attroff(A_REVERSE);
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
static void gambar_mobil(int x, int y, int tebal)
{
    int kiri = x - LEBAR_MOBIL / 2;

    if (tebal) attron(A_BOLD);
    for (int i = 0; i < TINGGI_MOBIL; i++) {
        int baris = y + i;
        if (baris >= 1 && baris < LINES - 1) {
            mvprintw(baris, kiri, "%s", gambar_art[i]);
        }
    }
    if (tebal) attroff(A_BOLD);
}

static void tunggu_tombol(void)
{
    mvprintw(LINES - 2, 2, "Tekan tombol apa saja untuk kembali...");
    refresh();
    timeout(-1);
    getch();
}

void mainkan_game(int level)
{
    const int batas_kiri = 3;
    int batas_kanan;
    int posisi_x;
    int posisi_y;
    int skor = 0;
    int jeda_ms;
    int mobil_x[JUMLAH_MOBIL_LAWAN];
    int mobil_y[JUMLAH_MOBIL_LAWAN];
    int selesai = 0;

    if (COLS < 50 || LINES < 20) {
        clear();
        mvprintw(2, 2, "Ukuran terminal terlalu kecil.");
        mvprintw(3, 2, "Perbesar terminal (minimal 50 kolom x 20 baris).");
        tunggu_tombol();
        return;
    }

    batas_kanan = COLS - 4;
    posisi_x = (batas_kiri + batas_kanan) / 2;
    posisi_y = LINES - 5;
    jeda_ms = level == 1 ? 120 : (level == 2 ? 85 : 55);

    for (int i = 0; i < JUMLAH_MOBIL_LAWAN; i++) {
        mobil_x[i] = batas_kiri + 8 +
                     std::rand() % (batas_kanan - batas_kiri - 15);
        mobil_y[i] = -(i * 7 + std::rand() % 4) - TINGGI_MOBIL;
    }

    while (!selesai) {
        int tombol;

        clear();
        mvprintw(0, 2, "Level %d | Skor: %d | Panah: kemudi | ESC: kembali",
                 level, skor);

        for (int y = 1; y < LINES - 1; y++) {
            mvaddch(y, batas_kiri, '|');
            mvaddch(y, batas_kanan, '|');
            if (y % 2 == 0) {
                mvaddch(y, (batas_kiri + batas_kanan) / 2, ':');
            }
        }

        for (int i = 0; i < JUMLAH_MOBIL_LAWAN; i++) {
            gambar_mobil(mobil_x[i], mobil_y[i], 0);
        }
        gambar_mobil(posisi_x, posisi_y, 1);
        refresh();

        timeout(jeda_ms);
        tombol = getch();

        if (tombol == 27) {
            selesai = 1;
            continue;
        } else if (tombol == KEY_LEFT && posisi_x - 2 >= batas_kiri + 8) {
            posisi_x -= 2;
        } else if (tombol == KEY_RIGHT && posisi_x + 2 <= batas_kanan - 8) {
            posisi_x += 2;
        } else if (tombol == KEY_UP && posisi_y > LINES / 2) {
            posisi_y--;
        } else if (tombol == KEY_DOWN && posisi_y < LINES - 5) {
            posisi_y++;
        }

        for (int i = 0; i < JUMLAH_MOBIL_LAWAN; i++) {
            mobil_y[i]++;

            if (mobil_y[i] >= LINES - 1) {
                mobil_y[i] = -TINGGI_MOBIL;
                mobil_x[i] = batas_kiri + 8 +
                             std::rand() % (batas_kanan - batas_kiri - 15);
                skor += 10;
            }

            if (std::abs(mobil_x[i] - posisi_x) < LEBAR_MOBIL &&
                std::abs(mobil_y[i] - posisi_y) < TINGGI_MOBIL) {
                selesai = 1;
            }
        }
    }

    timeout(-1);
    clear();
    mvprintw(3, 2, "Balapan selesai! Skor Anda: %d", skor);
    mvprintw(5, 2, "Tekan tombol apa saja untuk kembali ke menu.");
    refresh();
    getch();
}
