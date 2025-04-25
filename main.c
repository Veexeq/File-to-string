#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_chars(FILE *file);
int count_sentences(FILE *file);
char *file_to_string(FILE *file);

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

    char *plaintext = NULL;
    plaintext = file_to_string(file);
    printf("%s\n", plaintext);

    free(plaintext);
    fclose(file);
    return 0;
}

// Read from the file and put the text into a var
char *file_to_string(FILE *file) {
    struct {
        char *plaintext;
        size_t LEN;
        size_t size;
    } text;

    text.plaintext = malloc(1024 * sizeof(char));
    text.LEN = 1024;
    text.size = 0;

    char buffer = 0;
    while ((buffer = getc(file)) != EOF) {

        // There is still place to insert a character
        if (text.LEN < text.size) {
            text.plaintext[text.size++] = buffer;
        } 

        // No place left
        else {
            text.size *= 2;
            char *temp = realloc(text.plaintext, text.size);
            if (!temp) {
                printf("REALLOCATION ERROR\n");
                return NULL;
            }

            // Correctly reallocated the memory
            text.plaintext = temp;
            free(temp);

            // Push read character back to the file
            ungetc(buffer, file);
        }
    }

    // End of reading the file
    text.plaintext[text.size] = '\0';
    return text.plaintext;
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