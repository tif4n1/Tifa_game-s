#include "auth.h"
#include "game.h"
#include "menu.h"

#include <ncurses.h>

void jalankan_menu(void)
{
    const char *menu[] = {
        "Login",
        "Reset password",
        "Pilih level / Mulai balapan",
        "Keluar"
    };
    int pilihan = 0;

    while (true) {
        int tombol;

        clear();
        mvprintw(1, 2, "=== GAME CAR RACE ===");
        mvprintw(3, 2, "Status: %s",
                 pengguna_sudah_login() ? "sudah login" : "belum login");
        mvprintw(4, 2, "Gunakan panah atas/bawah dan Enter.");

        for (int i = 0; i < 4; i++) {
            if (i == pilihan) attron(A_REVERSE);
            mvprintw(6 + i, 4, "%s", menu[i]);
            if (i == pilihan) attroff(A_REVERSE);
        }

        refresh();
        tombol = getch();

        if (tombol == KEY_UP && pilihan > 0) {
            pilihan--;
        } else if (tombol == KEY_DOWN && pilihan < 3) {
            pilihan++;
        } else if (tombol == '\n' || tombol == KEY_ENTER) {
            switch (pilihan) {
                case 0:
                    proses_login();
                    break;
                case 1:
                    reset_password();
                    break;
                case 2:
                    if (!pengguna_sudah_login()) {
                        clear();
                        mvprintw(3, 2, "Silakan login terlebih dahulu.");
                        mvprintw(LINES - 2, 2,
                                 "Tekan tombol apa saja untuk kembali...");
                        refresh();
                        getch();
                    } else {
                        int level_dipilih = pilih_level();
                        if (level_dipilih != 0) {
                            mainkan_game(level_dipilih);
                        }
                    }
                    break;
                case 3:
                    return;
            }
        }
    }
}
