/**
 * @igormtc
 * July 2024
 * Header file for all hash functions and data structures
 */

#ifndef FILES_H
#define FILES_H

#include "WordFrequency.h"

#define BUFFER 256

FileCounted* LoadFile(const char* filename, bool* error);

void RemovePunctuation(char* word);
void ToLowercase(char *word);
int CountAllWords(const char* filename);

#endif //FILES_H