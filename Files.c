/**
 * @igormtc
 * July 2024
 * File with the LoadFile function and auxiliaries functions
 */

#include "HashStuff.h"
#include "WordFrequency.h"
#include "Files.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>



void RemovePunctuation(char* word){
    char *aux = word, *result = word;
    while (*aux) {
        if (isalpha((unsigned char)*aux) || *aux == ' ') {
            *result++ = *aux;
        }
        aux++;
    }
    *result = '\0';
}

void ToLowercase(char *word) {
    for (; *word; ++word) {
        *word = tolower((unsigned char)*word);
    }
}

int CountAllWords(const char* filename) {
    FILE* file = NULL;
    int err = fopen_s(&file, filename, "r");
    if (err != 0 || file == NULL) return -1;

    int wordCount = 0;
    char wordAux[BUFFER];

    while (fscanf_s(file, "%255s", wordAux, (unsigned)sizeof(wordAux)) == 1) {
        wordCount++;
    }

    fclose(file);
    return wordCount;
}

FileCounted* LoadFile(const char* filename, bool* error) {
    int size = CountAllWords(filename);
    FileCounted* fileCounted = InitializeCounter(size);
    FILE* file = NULL;
    int err;

    if (fileCounted == NULL) {
        *error = true;
        return NULL;
    }

    err = fopen_s(&file, filename, "r");
    if (err != 0 || file == NULL) {
        FreeFileCouted(fileCounted);
        *error = true;
        return NULL;
    }

    char wordAux[BUFFER];
    while (fscanf_s(file, "%255s", wordAux, (unsigned)sizeof(wordAux)) == 1) {
        char* wordPointer = (char*)malloc((strlen(wordAux) + 1) * sizeof(char));
        if (wordPointer == NULL) {
            *error = true;
            fclose(file);
            return fileCounted;
        }

        strcpy_s(wordPointer, strlen(wordAux) + 1, wordAux);
        // Sanitization
        RemovePunctuation(wordPointer);
        ToLowercase(wordPointer);

        printf("%zu\n", strlen(wordAux));
        printf("%s\n", wordPointer);
        Word* word = AddOrIncrement(fileCounted, wordPointer);
        if (word == NULL) {
            *error = true;
            free(wordPointer);
            fclose(file);
            return fileCounted;
        }

        free(wordPointer);
    }

    fclose(file);
    return fileCounted;
}