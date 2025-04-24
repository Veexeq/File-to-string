#include <stdio.h>
#include <string.h>

int count_chars(FILE *file);

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

    printf("%d\n", count_chars(file));

    fclose(file);
    return 0;
}

// Count all the character, including spaces, new lines etc...
int count_chars(FILE *file) {
    char buffer = 0;
    int count = 0;
    while ((buffer = getc(file)) != EOF) {
        count++;
    }
    return count;
}