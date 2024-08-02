/**
 * @igormtc
 * July 2024
 * File with all word frequency manipulation functions
 */

#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "HashStuff.h"
#include "WordFrequency.h"

//Use something else than void for the type of function
Word* AddOrIncrement(FileCounted* file, char* word){
    int* error = (int*)malloc(sizeof(int));
    if (error == NULL) {
        return NULL;
    }
    *error = 0;
    Word* aux = AddHash(file, word, error);

    if(*error == 1){ //already exists
        aux->frequencies++;
    }
    if(*error == 2){ //Failed to add
        return NULL;
    }
    free(error);
    return aux;

}

// size - The ammount of words in the text file
FileCounted* InitializeCounter(int size) {
    FileCounted* aux = (FileCounted*)malloc(sizeof(FileCounted) + size * sizeof(Word*));
    if (aux == NULL) return NULL;

    aux->numberOfWords = size;
    for (int i = 0; i < size; i++) {
        aux->words[i] = InitializeWord();
        if (aux->words[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(aux->words[j]);
            }
            free(aux);
            return NULL;
        }

        aux->words[i]->frequencies = 0;
        aux->words[i]->word = NULL;
        aux->words[i]->next = NULL;
        aux->activeHash = (int*)malloc(1* sizeof(int));
        if(aux->activeHash == NULL){
			for (int j = 0; j < i; j++) {
				free(aux->words[j]);
			}
			free(aux);
			return NULL;
		}
        aux->activeHash[0] = -1;
        aux->capacity = 0;
    }

    return aux;
}

Word* InitializeWord() {
    Word* aux = (Word*)calloc(1, sizeof(Word));
    if (aux == NULL) return NULL;

    // Allocate initial memory for the word field to avoid NULL pointer issues
    aux->word = (char*)calloc(1, sizeof(char));
    if (aux->word == NULL) {
        free(aux);
        return NULL;
    }

    return aux;
}

// word - Word pointer to free it in the memory
void FreeWord(Word* word) {
    if (word == NULL) return;
    while (word != NULL) {
        Word* aux = word;
        word = word->next;
        free(aux);         
    }
}

//file - FileCounted pointer to free it in the memory
void FreeFileCouted(FileCounted* file){
    if(file != NULL){
        for(int i = 0; i < file->capacity-1; i++){
            Word* current = file->words[file->activeHash[i]];
            FreeWord(current);
        }
        free(file);
    }
}