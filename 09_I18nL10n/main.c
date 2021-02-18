#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <unistd.h>


#define _(STRING) gettext(STRING)


int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("this", ".");
    textdomain("this");

    int min = 1, max = 100, mid;

    printf(_("Come up with a number between %d and %d (tsss, don't tell it anybody)\n"), min, max);
    printf(_("I'll try to guess it\n"));
//    sleep(2);

    while (min != max) {
        mid = (max + min) / 2;
        printf(_("Your number is greater than %d, isn't it? (y - yes, n - no)\n"), mid);
        char buffer[16] = {"\0"};
        scanf("%s", buffer);
        printf("<%s>\n", buffer);
        buffer[2] = '\0';
        printf("<%s>\n", buffer);

        if (!strcmp(_("y"), buffer))
            min = mid + 1;
        else if (!strcmp(_("n"), buffer))
            max = mid;
        else
            printf(_("Didn't get it\n"));
    }
    printf(_("Oh, It is definitely %d\n"), max);
    return 0;
}