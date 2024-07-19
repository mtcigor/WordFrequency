/**
 * @igormtc
 * July 2024
 * Header file for all hash functions and data structures
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#include "HashStuff.h"
#include "WordsFrequency.h"

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

Word* LoadFile(const char* filename, bool* error){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        error = true;
        return NULL;
    }

    char *wordAux;
    while(fscanf(file, "%s", &wordAux) == 1){
        //Sanitization
        RemovePunctuation(wordAux);
        ToLowercase(wordAux);

        //To do - add the word to FileCounted word struct
    }
}
