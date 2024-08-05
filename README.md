# WordFrequency

## Overview

Word Frequency is a C program that processes text input and provides a ranked list of words based on their frequency of occurrence.

## Technical Details

### Hash Table Implementation

The program uses a hash table to efficiently store and count words. This approach significantly improves performance compared to naive word counting methods, especially for large texts.

#### Hash Function

The hash function used is a polynomial rolling hash, based on the algorithm described in [CP-Algorithms: String Hashing](https://cp-algorithms.com/string/string-hashing.html). This method provides a good distribution of hash values for strings, reducing the likelihood of collisions.

The hash function is implemented as follows:

```c
unsigned int ComputeHash(char* word, int arraySize) {
    const int p = 31; // Prime number close to the number of lowercase letters
    const int m = 1e9 + 9; // Large prime number
    unsigned int hashValue = 0;
    int pPow = 1;
    for (int i = 0; word[i] != '\0'; i++) {
        hashValue = (hashValue + (word[i] - 'a' + 1) * pPow) % m;
        pPow = (pPow * p) % m;
    }
    return hashValue % arraySize;
}
```

This function computes a unique hash value for each word, which is then used as an index in the hash table.

#### Collision Handling

In case of hash collisions (when two different words produce the same hash value), the program uses chaining with linked lists to store multiple words at the same index.

## Features

- Efficient word counting using hash tables
- Polynomial rolling hash function for string hashing
- Collision handling for hash conflicts
- Ranking of words by frequency
- Summary statistics including total word count and unique word count

## Requirements

- C compiler (e.g., GCC)
- Standard C libraries

## Installation

1. Clone this repository:
   ```
   git clone https://github.com/mtcigor/WordFrequency.git
   ```
2. Navigate to the project directory:
   ```
   cd WordFrequency
   ```
3. Compile the program:
   ```
   make
   make clean (to delete .o object files)
   ```

## Usage

1. Run the compiled program:
   ```
   ./WordFrequency
   ```
2. Input your text.
   - Create inside the executable directory a text file with the content.
    
3. The program will output a ranked list of words and their frequencies, followed by summary statistics.

## Example Output

```
Ranked Word Frequencies:
------------------------
1. the: 15
2. and: 12
3. of: 10
4. in: 8
5. to: 7
...
------------------------
Total words: 150
Unique words: 75
```
