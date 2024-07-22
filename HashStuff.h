/**
 * @igormtc
 * July 2024
 * Header file for all hash functions and data structures
 */


Word* FindWordHash(FileCounted* file, int ASCII);

Word* AddHash(FileCounted* file, int ASCII, int* errorCode);

int GenerateHash(int ASCII, int size);