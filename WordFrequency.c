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
void AddOrIncrement(char* word){
    int ASCII;
    for (int i = 0; word[i] != '\0'; i++) {
        ASCII += (int)word[i]; //Convert to ASCII each char
    }
    //Use a find Hash first

}

// size - The ammount of words in the text file
FileCounted* InitializeCounter(int size) {
    FileCounted* aux = (FileCounted*)malloc(sizeof(FileCounted));
    if (aux == NULL) return NULL;

    aux->numberOfWords = size;
    for (int i = 0; i < size; i++) {
        aux->words[i] = (Word*)malloc(sizeof(Word));
        if (aux->words[i] == NULL) {
            for (int j = 0; j < i; j++) { //If needed elsewhere make this free memory words loop a function
                free(aux->words[j]);
            }
            free(aux);
            return NULL;
        }
        
        aux->words[i]->frequencies = 0;
        aux->words[i]->WordASCII = -1;
        aux->words[i]->next = NULL;
    }

    return aux;
}

Word* InitializeWord(){
    Word* aux = (Word*)malloc(sizeof(Word));
    if(aux == NULL) return NULL;

    return aux;
}

// word - Word pointer to free it in the memory
void FreeWord(Word* word){
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
}

//file - FileCounted pointer to free it in the memory
void FreeFileCouted(FileCounted* file){
    if(file != NULL){
        for(int i = 0; i < file->numberOfWords; i++){
            Word* current = file->words[i];
            while (current != NULL)
            {
                Word* next = current->next;
                FreeWord(current); //See possible errors
                current = next;
            }
            
        }
        free(file);
    }
}