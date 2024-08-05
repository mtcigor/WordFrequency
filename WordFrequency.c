/**
 * @igormtc
 * July 2024
 * File with all word frequency manipulation functions
 */

#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

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

int compare_word_freq(const void* a, const void* b) {
    return ((WordFreq*)b)->frequency - ((WordFreq*)a)->frequency;
}

void PrintWordFrequencies(FileCounted* file) {
    if (file == NULL) {
        printf("Error: File is NULL\n");
        return;
    }

    // Count total unique words
    int uniqueWords = 0;
    for (int i = 0; i < file->numberOfWords; i++) {
        Word* current = file->words[i];
        while (current != NULL) {
            if (current->word != NULL) {
                uniqueWords++;
            }
            current = current->next;
        }
    }
    
    WordFreq* wordFreqArray = RankedFrequencies(file, uniqueWords);

    // Print ranked results
    printf("Ranked Word Frequencies:\n");
    printf("------------------------\n");
    for (int i = 0; i < uniqueWords; i++) {
        printf("%d. %s: %d\n", i+1, wordFreqArray[i].word, wordFreqArray[i].frequency);
    }

    printf("------------------------\n");
    printf("Total words: %d\n", file->numberOfWords);
    printf("Unique words: %d\n", uniqueWords);

    // Free the allocated memory
    free(wordFreqArray);
}

WordFreq* RankedFrequencies(FileCounted* file, int uniqueWords){
    WordFreq* wordFreqArray = malloc(uniqueWords * sizeof(WordFreq));
    if (wordFreqArray == NULL) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }

    // Populate the array
    int index = 0;
    int totalWords = 0;
    for (int i = 0; i < file->numberOfWords; i++) {
        Word* current = file->words[i];
        while (current != NULL) {
            if (current->word != NULL) {
                wordFreqArray[index].word = current->word;
                wordFreqArray[index].frequency = current->frequencies;
                totalWords += current->frequencies;
                index++;
            }
            current = current->next;
        }
    }

    // Sort the array
    qsort(wordFreqArray, uniqueWords, sizeof(WordFreq), compare_word_freq);
    return wordFreqArray;
}