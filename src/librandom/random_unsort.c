/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>
#include <skalibs/random.h>

void random_unsort (char *s, unsigned int n, unsigned int chunksize)
{
  char tmp[chunksize] ;
  while (n--)
  {
    register uint32 i = random_uint32(n+1) ;
    byte_copy(tmp, chunksize, s + i * chunksize) ;
    byte_copy(s + i * chunksize, chunksize, s + n * chunksize) ;
    byte_copy(s + n * chunksize, chunksize, tmp) ;
  }
}
