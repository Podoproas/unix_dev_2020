#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#if WITHOUT_UTF == 0
#define PCRE2_UCP_CUSTOM PCRE2_UCP
#else
#define PCRE2_UCP_CUSTOM 0
#endif

#include <ncurses.h>
//#include <cursesw.h>
#include <pcre2.h>
#include <stdio.h>

#define DX 3
#define ONLELINE 3
#define MAXSTR 80


int main(int argc, char** argv) {
    WINDOW *winA, *winB, *winO;
    char inA[MAXSTR], inB[MAXSTR];
    int c = 0;
    int half;

    initscr();
    cbreak();
    printw("Input:");
    refresh();

    half = (COLS - 2 * DX) / 2;
    winA = newwin(ONLELINE, half, DX, DX);
    winB = newwin(ONLELINE, half, DX, DX + half);
    winO = newwin(LINES - ONLELINE - DX * 2, (COLS - 2 * DX), DX + ONLELINE, DX);
    keypad(winA, TRUE);
    keypad(winB, TRUE);
    scrollok(winO, TRUE);
    wmove(winO, 1, 0);
    do {
        werase(winA);
        box(winA, 0, 0);
        mvwgetnstr(winA, 1, 1, inA, MAXSTR);
        werase(winB);
        box(winB, 0, 0);
        mvwgetnstr(winB, 1, 1, inB, MAXSTR);

        wprintw(winO, "  '%s' : '%s'\n", inA, inB);
        pcre2_code *re;
        PCRE2_SPTR pattern = (PCRE2_SPTR) inA;;     /* PCRE2_SPTR is a pointer to unsigned code units of */
        PCRE2_SPTR subject = (PCRE2_SPTR) inB;;     /* the appropriate width (in this case, 8 bits). */

        int errnum;
        int i, rc;

        PCRE2_SIZE erroffs;
        PCRE2_SIZE *ovector;
        PCRE2_SIZE subject_length;

        pcre2_match_data *match_data;

        subject_length = (PCRE2_SIZE) strlen((char *) subject);

        re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);

        if (re == NULL) {
            PCRE2_UCHAR buffer[256];
            pcre2_get_error_message(errnum, buffer, sizeof(buffer));
            wprintw(winO, "\tPCRE2 compilation failed at offset %d: %s\n", (int) erroffs, buffer);
            continue;
        }

        match_data = pcre2_match_data_create_from_pattern(re, NULL);

        rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

        if (rc < 0) {
            if (rc == PCRE2_ERROR_NOMATCH)
                wprintw(winO, "\tNo match\n");
            else
                wprintw(winO, "\tMatching error %d\n", rc);
        } else {
            ovector = pcre2_get_ovector_pointer(match_data);
            for (i = 0; i < rc; i++)
                wprintw(winO, "\t%2ld: %.*s\n", ovector[2 * i], (int) (ovector[2 * i + 1] - ovector[2 * i]),
                        subject + ovector[2 * i]);


        }
        pcre2_match_data_free(match_data);  /* Release the memory that was used */
        pcre2_code_free(re);                /* for the match data and the pattern. */
        wprintw(winO, "\n");
        box(winO, 0, 0);
        wrefresh(winO);
    } while (*inA);

    endwin();
    return 0;
}