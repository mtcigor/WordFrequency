/**
 * @igormtc
 * July 2024
 * Header file for all hash functions and data structures
 */

#ifndef HASH_STUFF_H
#define HASH_STUFF_H

#include "WordFrequency.h"

Word* AddHash(FileCounted* file, char* word, int* errorCode);

Word* ColissionHandlingHash(Word* current, char* word);

Word* FindWord(FileCounted* file, char* word);

unsigned int ComputeHash(char* word, int arraySize);

#endif // HASH_STUFF_H