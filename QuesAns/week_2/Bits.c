// BitS - bit-string data type

#include "Bits.h"

// BitS a, b, c;
// a: 0010101010100001100110100101100100101001...
// b: 1101000010010000000100100000010001001000...
// c: 1111101010110001100110100101110101101001...

// bitwise-OR of entire bit-string
void BitUnion(BitS a, BitS b, BitS c)
{
	int i;
	for (i = 0; i < NWORDS; i++)
		c[i] = a[i] | b[i];
}

// bitwise-AND of entire bit-string
void BitIntersect(BitS a, BitS b, BitS c)
{
	int i;
	for (i = 0; i < NWORDS; i++)
		c[i] = a[i] & b[i];
}

// get i'th bit from bit-string
int getBit(BitS a, int i)
{
	int whichWord = i/32;
	int whichBit  = i%32;

	Word mask = (1 << whichBit);
	Word result = a[whichWord] & mask;
	
	return (result != 0) ? 1 : 0;
}

// set i'th bit in bit-string
void setBit(BitS a, int i)
{
	int whichWord = i/32;
	int whichBit  = i%32;

	Word mask = (1 << whichBit);
#if 1
	a[whichWord] = a[whichWord] | mask;
#else
	a[whichWord] |= mask;
#endif
}

// unset i'th bit in bit-string
void unsetBit(BitS a, int i)
{
	int whichWord = i/32;
	int whichBit  = i%32;

	Word mask = ~(1 << whichBit);
	a[whichWord] = a[whichWord] & mask;
}
