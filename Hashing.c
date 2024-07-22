/**
 * @igormtc
 * July 2024
 * File with all hash functions
 */

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

#include "WordsFrequency.h"
#include "HashStuff.h"

//Only to add, not to increment
Word* AddHash(FileCounted* file, int ASCII, int* errorCode){
    if(file == NULL){
        errorCode=2;
        return NULL;
    }

    Word* aux = FindWordHash(file, ASCII);
    //There is no word in the chosen hash
    if(aux == NULL){
        aux->frequencies=1;
        aux->WordASCII=ASCII;
        errorCode = 0; //No error
        return aux;
    }
    //The word already exists
    if(aux->WordASCII == ASCII){
        errorCode = 1; //Already exists (best to increment)
        return NULL;
    }
    //There is another word in the same hash, colliding
    if(aux->frequencies > 0 && aux->WordASCII > -1){
        Word* temp = ColissionHandlingHash(aux, ASCII);
        if(temp == NULL){
            errorCode=2; //Failed to add
            return NULL;
        }
        errorCode=0;
        return temp;
    }
    
}

Word* ColissionHandlingHash(Word* current, int ASCII){
    current->next = (Word*)malloc(sizeof(Word*));
    if(current->next == NULL) return NULL;
    Word* aux = current->next;
    aux->frequencies=1;
    aux->WordASCII;
    return aux;
}

Word* FindWordHash(FileCounted* file, int ASCII){
    int hash = GenerateHash(ASCII, file->numberOfWords); //Convert to hash
    if(hash < 0) return NULL;

    Word* aux = file->words[hash];

    if(aux->WordASCII == -1) return NULL;

    if(aux->WordASCII == ASCII) return aux;
    else{
        while(aux->next){
            aux = aux->next;
            if(aux->WordASCII == ASCII) return aux;
        }
    }
    return NULL;
}

int GenerateHash(int ASCII, int size){
    if(size <= 0 || ASCII < 0) return -1;
    return ASCII%size;
}