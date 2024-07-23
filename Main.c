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

int main (){
    bool* error = (bool*)malloc(sizeof(bool));
    if (error == NULL) {
        printf("Malloc error memory allocation failed\n");
        exit(1);
    }
    *error = false;
    FileCounted* file = InitializeCounter(10);
    if(file == NULL){
        printf("FileCounted memory allocation failed\n");
        exit(1);
    }
    return 0;
}