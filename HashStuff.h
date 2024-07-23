/**
 * @igormtc
 * July 2024
 * Header file for all hash functions and data structures
 */

#ifndef HASH_STUFF_H
#define HASH_STUFF_H

#include "WordFrequency.h"

Word* FindWordHash(FileCounted* file, int ASCII);

Word* AddHash(FileCounted* file, int ASCII, int* errorCode);

int GenerateHash(int ASCII, int size);

Word* ColissionHandlingHash(Word* current, int ASCII);

#endif // HASH_STUFF_H