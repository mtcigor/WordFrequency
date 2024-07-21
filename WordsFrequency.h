/**
 * @igormtc
 * July 2024
 * Header file for all word frequency functions and data structures
 */

typedef struct FileCounted{
    int numberOfWords;
    struct Word* words[];
}FileCounted;

typedef struct Word{
    int WordASCII;
    int frequencies;
    struct Word* next;
    
}Word;

void AddOrIncrement(char* word, bool* error);

FileCounted* InitializeCounter(int size, bool* error);

Word* InitializeWord(bool* error);

void FreeWord(Word* word);

void FreeFileCouted(FileCounted* file);