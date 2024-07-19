/**
 * @igormtc
 * July 2024
 * File with all word frequency manipulation functions
 */

#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include "HashStuff.h"
#include "WordsFrequency.h"

// size - The ammount of words in the text file
// error - Pointer dereference to set the error flag 
FileCounted* InitializeCounter(int size, bool* error) {
    *error = false;

    // Allocate memory for FileCounted structure and the flexible array member in one step
    FileCounted* aux = (FileCounted*)malloc(sizeof(FileCounted) + size * sizeof(Word*));
    if (aux == NULL) {
        *error = true;
        return NULL;
    }

    aux->numberOfWords = size;
    for (int i = 0; i < size; i++) {
        aux->words[i]->frequencies=0;
        aux->words[i]->WordASCII=-1;
        aux->words[i]->next=NULL;
    }

    return aux;
}

// error - Pointer dereference to set the error flag
Word* InitializeWord(bool* error){
    Word* aux = (Word*)malloc(sizeof(Word));
    if(aux == NULL){
        *error=true;
        return NULL;
    }

    return aux;
}

// word - Word pointer to free it in the memory
bool FreeWord(Word* word){
    bool error = true;

    // while(word != NULL){
    //     Word* aux;
    //     if(word->next != NULL) aux = word->next;
    //     free(word);
    //     word = aux;
    // }
    while (word != NULL)
    {
        free(word->next); //Pode dar erro
        free(word);
    }
    
    error = false;
    return error;
}

//file - FileCounted pointer to free it in the memory
bool FreeFileCouted(FileCounted* file){
    bool error = true;
    if(file != NULL){
        for(int i = 0; i < file->numberOfWords; i++){
            Word* current = file->words[i];
            while (current != NULL)
            {
                Word* next = current->next;
                error = FreeWord(current);
                if(error == true) return true; //Qualquer erro durante a execução da função a mesma aborta
                current = next;
            }
            
        }
        free(file);
        error = false;
    }
    return error;
}