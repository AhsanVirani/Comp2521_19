// Set.c ... Set ADT implementation
// Written by John Shepherd, August 2015

#ifdef USE_ARRAY
#include "Set-array.c"
#elif USE_OARRAY
#include "Set-ord-array.c"
#elif USE_XARRAY
#include "Set-flex-array.c"
#elif  USE_LIST
#include "Set-list.c"
#elif  USE_BITS
#include "Set-bits.c"
#endif
