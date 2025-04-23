#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Use: ./a.out file.txt\n");
        return 1;
    }

    const char *FILE_NAME = argv[1];
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Couldn't open file \"%s\"\n", FILE_NAME);
        return 1;
    }

    fclose(file);
    return 0;
}