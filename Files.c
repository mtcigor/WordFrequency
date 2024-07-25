/**
 * @igormtc
 * July 2024
 * Header file for all hash functions and data structures
 */

#include "HashStuff.h"
#include "WordFrequency.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>



void* RemovePunctuation(char* word){
    char *aux = word, *result = word; //
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

int CountAllWords(const char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL) return -1;

    int wordCount = 0;
    char *wordAux;
    while(fscanf(file, "%s", wordAux) == 1){
        wordCount++;
    }

    free(wordAux);
    fclose(file);
    return wordCount;
}

FileCounted* LoadFile(const char* filename, bool* error){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        *error = true;
        return NULL;
    }

    int size;
    size = CountAllWords(filename);
    FileCounted* fileCounted = InitializeCounter(size);
    if(file == NULL){
        *error = true;
        return NULL;
    }
    char* wordAux;
    while(fscanf(file, "%s", wordAux) == 1){
        //Sanitization
        RemovePunctuation(wordAux);
        ToLowercase(wordAux);
        Word* word = AddOrIncrement(fileCounted, wordAux);
        if(word == NULL){
            *error=true;
            return fileCounted;
        }
    }
    return fileCounted;
}
