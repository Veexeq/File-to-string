#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_chars(FILE *file);
int count_sentences(FILE *file);

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

    printf("Characters in file: %d\n", count_chars(file));
    printf("Sentences in file: %d\n", count_sentences(file));

    fclose(file);
    return 0;
}

// Count all the sentences (assuming sentences end with ". ")
int count_sentences(FILE *file) {
    rewind(file);
    int count = 0;
    char buffer = 0;
    while ((buffer = fgetc(file)) != EOF) {
        
        // There is a possibility of an end of the sentence
        if (buffer == '.') {
            char space = fgetc(file);
            if (space == ' ') {
                char next_char = fgetc(file);
                if (next_char != EOF && (next_char == '\n' || isupper(next_char))) {
                    count++;
                }
                else if (next_char != EOF) ungetc(next_char, file);
            }
            else if (space != EOF) ungetc(space, file);
        }
    }
    return count;
}

// Count all the character, including spaces, new lines etc...
int count_chars(FILE *file) {
    rewind(file);
    char buffer = 0;
    int count = 0;
    while ((buffer = getc(file)) != EOF) {
        count++;
    }
    return count;
}