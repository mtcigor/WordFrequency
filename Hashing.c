/**
 * @igormtc
 * July 2024
 * File with all hash functions
 */

//TO DO:
//Create a function to convert ASCII to hash rathen than write the operation each time

#include <stdbool.h>
#include <stdio.h>

#include "WordsFrequency.h"
#include "HashStuff.h"

Word* AddHash(FileCounted* file, int ASCII){
    //Add to verify file pointer
    int hash = ASCII%file->numberOfWords;
    Word* aux = file->words[hash];
    if(aux->WordASCII==ASCII){
        //Already exists
    }
    if(aux->frequencies > 0 && aux->WordASCII > -1){
        //Colission handling
    }
    aux->frequencies=1;
    aux->WordASCII=ASCII;
    
}

Word* FindHash(FileCounted* file, int ASCII){
    int hash = ASCII%file->numberOfWords; //Convert to hash
    Word* aux = file->words[hash];
    if(aux->WordASCII != ASCII){
        while(aux->next){
            aux = aux->next;
            if(aux->WordASCII == ASCII) return aux;
        }
    }
    return NULL;
}