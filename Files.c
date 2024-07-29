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



void RemovePunctuation(char* word){
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
    char wordAux[256];
    while(fscanf(file, "%255s", wordAux) == 1){
        wordCount++;
    }

    fclose(file);
    return wordCount;
}

FileCounted* LoadFile(const char* filename, bool* error){
    
    int size;
    size = CountAllWords(filename);
    FileCounted* fileCounted = InitializeCounter(size);
    FILE* file = fopen(filename, "r");
    if(fileCounted == NULL){
        *error = true;
        return NULL;
    }
    if(file == NULL){
        FreeFileCouted(fileCounted);
        *error = true;
        return NULL;
    }
    char wordAux[255];
    while(fscanf(file, "%255s", wordAux) == 1){
        //Sanitization
        printf("%lu\n", strlen(wordAux));
        char* wordPointer = (char*)malloc(strlen(wordAux)*sizeof(char));
        if(wordPointer == NULL){
            *error = true;
            return NULL;
        }
        printf("foi0\n");
        RemovePunctuation(wordPointer);
        printf("foi1\n");
        ToLowercase(wordPointer);
        
        Word* word = AddOrIncrement(fileCounted, wordPointer);
        if(word == NULL){
            *error=true;
            return fileCounted;
        }
    }
    return fileCounted;
}
