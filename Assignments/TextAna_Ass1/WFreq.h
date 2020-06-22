// COMP2521 20T2 Assignment 1
// WFreq.h ... definition of (word,freq) type

#ifndef WORD_H
#define WORD_H

typedef struct _WFreq {
   char  *word;  // word buffer (dynamically allocated)
   int    freq;  // count of number of occurences
} WFreq;

#endif
