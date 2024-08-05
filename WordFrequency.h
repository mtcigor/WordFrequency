/**
 * @igormtc
 * July 2024
 * Header file for all word frequency functions and data structures
 */

#ifndef WORD_FREQUENCY_H
#define WORD_FREQUENCY_H

typedef struct FileCounted{
    int numberOfWords; //Number of words counted
    int capacity; //Amount filled in the array
    int* activeHash; //Array with all hash numbers for the words array
    struct Word* words[]; //Array of words
}FileCounted;

typedef struct Word{
    char* word;
    int frequencies;
    struct Word* next;
    
}Word;

typedef struct {
    char* word;
    int frequency;
} WordFreq;

Word* AddOrIncrement(FileCounted* file, char* word);

FileCounted* InitializeCounter(int size);

Word* InitializeWord();

void FreeWord(Word* word);

void FreeFileCouted(FileCounted* file);

int compare_word_freq(const void* a, const void* b);

void PrintWordFrequencies(FileCounted* file);

WordFreq* RankedFrequencies(FileCounted* file, int uniqueWords);

#endif // WORD_FREQUENCY_H