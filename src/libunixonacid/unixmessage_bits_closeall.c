/* ISC license. */

#include <skalibs/bitarray.h>
#include <skalibs/unixmessage.h>

static unsigned char _unixmessage_bits_closeall[bitarray_div8(UNIXMESSAGE_MAXFDS)] = "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377" ;
unsigned char const *const unixmessage_bits_closeall = _unixmessage_bits_closeall ;
