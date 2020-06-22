// COMP2521 20T2 Assignment 1
// Dict.h ... interface to Dictionary ADT

#ifndef DICT_H
#define DICT_H

#include "WFreq.h"

typedef struct _DictRep *Dict;

// create new empty Dictionary
Dict newDict();

// insert new word into Dictionary
// return pointer to (w,f) pair for Word
WFreq *DictInsert(Dict d, char *w);

// find Word in Dictionary
// return pointer to (w,f) pair for Word
WFreq *DictFind(Dict d, char *w);

// find top N frequently occurring words in Dict
// input: Dictionary, array of WFreqs, size of array
// returns: #WFreqs in array, modified array
int findTopN(Dict d, WFreq *wfs, int n);

// print a dictionary
void showDict(Dict d);

#endif
