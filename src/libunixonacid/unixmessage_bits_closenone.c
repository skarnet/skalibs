/* ISC license. */

#include <skalibs/bitarray.h>
#include <skalibs/unixmessage.h>

static unsigned char _unixmessage_bits_closenone[bitarray_div8(UNIXMESSAGE_MAXFDS)] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0" ;
unsigned char const *const unixmessage_bits_closenone = _unixmessage_bits_closenone ;
