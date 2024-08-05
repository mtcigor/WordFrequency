/**
 * @igormtc
 * July 2024
 * Main function
 */

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "WordFrequency.h"
#include "HashStuff.h"
#include "Files.h"

int main (){
    bool* error = (bool*)malloc(sizeof(bool));
    if(error == NULL){
        printf("Failed to allocate memory to error pointer\n");
        return 1;
    }
    FileCounted* file = LoadFile("text.txt", error);
    if(*error == true){
        printf("Failed to load the file\n");
    }
    PrintWordFrequencies(file);
    FreeFileCouted(file);
    return 0;
}