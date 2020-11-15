#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


void init_all(){
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    refresh();
}

int get_file_size(FILE *f){
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}


char** read_file(FILE *f, int cols, int *number_of_lines){
    int cur_lines_size = 1;
    int cur_line_pos = 0;
    int temp = 1024;
    char *line = calloc(temp, sizeof(char*));
    char **ans = calloc(cur_lines_size, sizeof(char*));
    size_t chars_read;
    while ((chars_read = getline(&line, &temp, f)) != -1) {
        if (cur_line_pos == cur_lines_size) {
            cur_lines_size <<= 1;
            ans = realloc(ans, cur_lines_size * sizeof(char *));
        }
        line[cols] = 13;
        ans[cur_line_pos] = calloc(cols + 1, sizeof(char));
        memcpy(ans[cur_line_pos], line, (cols + 1) * sizeof(char));
        cur_line_pos += 1;
    }
    *number_of_lines = cur_line_pos;
    return ans;
}

void main(int argc, char **argv) {
    init_all();
    FILE *f = fopen(argv[1], "r");
    int size = get_file_size(f);
    int lines = 0;
    char **text = read_file(f, COLS - 9, &lines);
    fclose(f);

    printw("file: %s, size: %d, lines: %d\n", argv[1], size, lines);
    refresh();

    WINDOW *win;
    win = newwin(LINES - 1, COLS - 2, 1, 1);
    keypad(win, TRUE);

    int c = 0;
    int begin = 0;
    do {
        if (c == KEY_UP){
            begin -= 1;
            if (begin < 0){
                begin = 0;
            }
        }
        if (c == KEY_DOWN){
            begin += 1;
            if (begin + LINES - 3 > lines){
                begin -= 1;
            }
        }
        werase(win);
        wprintw(win, "\n");
        for (int i = begin; i < begin + LINES - 3; ++i){
            wprintw(win, ">%3d: ", i);
            int j = 0;
            while (text[i][j] != 13){
                wprintw(win, "%c", text[i][j]);
                j++;
            }
            wprintw(win, "\n");
        }


        box(win, 0, 0);
        wrefresh(win);
    } while((c = wgetch(win)) != 27);
    endwin();
}