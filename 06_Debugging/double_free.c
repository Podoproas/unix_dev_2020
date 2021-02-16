#include <stdlib.h>

int main(int argc, char** argv) {
    int num_to_gen = atol(argv[1]);
    int **a = malloc(sizeof(int*) * num_to_gen);

    for (int i = 0; i < num_to_gen; ++i){
        a[i] = malloc(sizeof(int) * num_to_gen);
        for (int j = 0; j < num_to_gen; ++j){
            a[i][j] = i + j * 5;

        }
        free(a[i]);
    }
    free(a);
    free(a);
    return 0;
}