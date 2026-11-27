#include "menu.h"

#include <ncurses.h>
#include <cstdlib>
#include <ctime>

int main(void)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    jalankan_menu();

    endwin();
    return 0;
}
