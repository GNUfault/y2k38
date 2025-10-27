#include <ncurses.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>

void print_binary(WINDOW *win, int32_t t, int y, int x) {
    wmove(win, y, x);
    for (int i = 31; i >= 0; i--) {
        waddch(win, ((t >> i) & 1) ? '1' : '0');
        if (i % 8 == 0) waddch(win, ' ');
    }
}

int main() {
    initscr();
    noecho();
    curs_set(FALSE);

    WINDOW *win = newwin(10, 80, 1, 1);

    while (1) {
        werase(win);

        time_t raw_time = time(NULL);
        int32_t unix_time = (int32_t)raw_time;
        struct tm *tm_info = gmtime(&raw_time);

        mvwprintw(win, 1, 2, "Unix Time: %d", unix_time);
        mvwprintw(win, 3, 2, "Binary:");
        print_binary(win, unix_time, 3, 13);

        char buffer[64];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S UTC", tm_info);
        mvwprintw(win, 5, 2, "Time:      %s", buffer);

        wrefresh(win);
        sleep(1);
    }

    endwin();
    return 0;
}
