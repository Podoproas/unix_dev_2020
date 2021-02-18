#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *comp(const void *a, const void *b, void *counters) {
    gpointer *key1 = (gpointer*) a;
    gpointer *key2 = (gpointer*) b;
    return GPOINTER_TO_INT(g_hash_table_lookup(counters, *key1)) < GPOINTER_TO_INT(g_hash_table_lookup(counters, *key2));
}


int main(int argc, char **argv) {
    char text[81] = {'\0'};
    char cur;
    char *ptr = text;

    while ((cur = getc(stdin)) != EOF) {
        (*ptr) = cur;
        ++ptr;
    }

    gchar **words = g_strsplit_set(text, "-.,!?\t\n\r ", -1);
    GHashTable *counters = g_hash_table_new(g_str_hash, g_str_equal);

    for (gchar **it = words; *it; ++it) {
        gchar *word = g_strstrip(*it);
        if (g_strcmp0(word, "")) {

            if (g_hash_table_contains(counters, word)) {
                g_hash_table_replace(counters, word,
                                     GINT_TO_POINTER(GPOINTER_TO_INT(g_hash_table_lookup(counters, word)) + 1));
            } else {
                g_hash_table_insert(counters, word, GINT_TO_POINTER(1));
            }
        }
    }
    guint len;
    gpointer* sorted_keys = g_hash_table_get_keys_as_array(counters, &len);
    qsort_r(sorted_keys, len, sizeof(gpointer), comp, counters);

    for (int i = 0; i < len; ++i){
        g_printf("%s: %d\n", sorted_keys[i], GPOINTER_TO_INT(g_hash_table_lookup(counters, sorted_keys[i])));
    }

    g_strfreev(words);
    g_hash_table_destroy(counters);
    g_free(sorted_keys);
    return 0;
}