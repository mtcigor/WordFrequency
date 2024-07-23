/**
 * @igormtc
 * July 2024
 * Header file for all word frequency functions and data structures
 */

#ifndef WORD_FREQUENCY_H
#define WORD_FREQUENCY_H

typedef struct FileCounted{
    int numberOfWords;
    struct Word* words[];
}FileCounted;

typedef struct Word{
    int WordASCII;
    int frequencies;
    struct Word* next;
    
}Word;

void AddOrIncrement(char* word);

FileCounted* InitializeCounter(int size);

Word* InitializeWord();

void FreeWord(Word* word);

void FreeFileCouted(FileCounted* file);

#endif // WORD_FREQUENCY_H