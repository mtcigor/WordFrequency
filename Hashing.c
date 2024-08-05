/**
 * @igormtc
 * July 2024
 * File with all hash functions
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "WordFrequency.h"
#include "HashStuff.h"

//Only to add, not to increment
Word* AddHash(FileCounted* file, char* word, int* errorCode) {
    if (file == NULL) {
        *errorCode = 2;
        return NULL;
    }
    Word* aux = FindWord(file, word);

    // There is no word in the chosen hash
    if (aux == NULL) {
       // printf("Word not found\n\n");
        int hash = ComputeHash(word, file->numberOfWords);
        
        aux = file->words[hash];
        aux->frequencies = 1;

        // Allocate memory for the word field
        aux->word = (char*)realloc(aux->word, (strlen(word) + 1) * sizeof(char));
        if (aux->word == NULL) {
            *errorCode = 2;
            return NULL;
        }

        strcpy(aux->word, word);
        file->capacity++;
        if(file->activeHash[0] == -1 && file->capacity == 1){
			file->activeHash[0] = hash;
		}
        else {
            int* newActiveHash = realloc(file->activeHash, file->capacity * sizeof(int));
            if (newActiveHash == NULL) {
                *errorCode = 2;
				return NULL;
            }
            file->activeHash = newActiveHash;
            file->activeHash[file->capacity - 1] = hash;
        }
        *errorCode = 0; // No error
        return aux;
    }
    // The word already exists
    if (strcmp(aux->word, word) == 0) {
        //printf("Word found\n\n");
        *errorCode = 1; // Already exists (best to increment)
        return aux;
    }
    // There is another word in the same hash, colliding
    if (aux->frequencies > 0 && strcmp(aux->word, word) != 0) {
        //printf("Collision\n\n");
        Word* temp = ColissionHandlingHash(aux, word);
        if (temp == NULL) {
            *errorCode = 2; // Failed to add
            return NULL;
        }
        *errorCode = 0;
        return temp;
    }
    *errorCode = 2;
    return NULL;
}

Word* ColissionHandlingHash(Word* current, char* word){
    current->next = (Word*)malloc(sizeof(Word));
    if(current->next == NULL) return NULL;
    Word* aux = current->next;
    aux->frequencies=1;
    aux->word = NULL;
    aux->next = NULL;

    // Allocate memory for the word field
    aux->word = (char*)realloc(aux->word, (strlen(word) + 1) * sizeof(char));
    if (aux->word == NULL) return NULL;

    strcpy(aux->word, word);
    return aux;
}

Word* FindWord(FileCounted* file, char* word) {
    int hash = ComputeHash(word, file->numberOfWords); //Convert to hash
    //printf("Hash: %d\n", hash);
    if (hash < 0) return NULL;

    Word* aux = file->words[hash];
    if (aux == NULL) {
        printf("Critical error");
        return NULL;
    }

    if (aux->word == NULL) return NULL;
    if(strcmp(aux->word, word) == 0) return aux;

    while (aux->next != NULL) {
        if (strcmp(aux->next->word, word) == 0) {
            return aux->next;
        }
        aux = aux->next;
    }
    return aux;
}

unsigned int ComputeHash(char* word, int arraySize){
    const int p = 31; //Prime number of lowercase letters of the English alphabet
    const int m = 1e9 + 9; //Large prime number
    unsigned int hashValue = 0;
    int pPow = 1; 
    for(int i = 0; word[i] != '\0'; i++){
		hashValue = (hashValue + (word[i] - 'a' + 1) * pPow) % m;
		pPow = (pPow * p) % m;
	}
    return hashValue % arraySize;
}