// COMP2521 20T2 Assignment 1
// stemmer.h ... interface to stemming module

#ifndef STEMMER_H
#define STEMMER_H

// In stem(p,i,j), p is a char pointer, and the string to be stemmed is from
// p[i] to p[j] inclusive. Typically i is zero and j is the offset to the last
// character of a string, (p[j+1] == '\0'). The stemmer adjusts the
// characters p[i] ... p[j] and returns the new end-point of the string, k.
// Stemming never increases word length, so i <= k <= j.

int stem(char *p, int i, int j);

#endif
