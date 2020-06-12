// BitS - bit-string interface
// Not quite an ADT, because it reveals
// some details of the implementation

#ifndef BITS_H
#define BITS_H

#define NBITS 1024
#define NWORDS (NBITS/32)

typedef unsigned int Word;

typedef Word BitS[NWORDS];

// bitwise-OR of entire bit-string
void BitUnion(BitS a, BitS b, BitS c);

// bitwise-AND of entire bit-string
void BitIntersect(BitS a, BitS b, BitS c);

// get i'th bit from bit-string
int getBit(BitS a, int i);

// set i'th bit in bit-string
void setBit(BitS a, int i);

// unset i'th bit in bit-string
void unsetBit(BitS a, int i);

#endif
