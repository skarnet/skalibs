/* ISC license. */

#include <stdint.h>
#include <skalibs/bytestr.h>
#include <skalibs/random.h>

void random_unsort (char *s, size_t n, size_t chunksize)
{
  char tmp[chunksize] ;
  while (n--)
  {
    register uint32_t i = random_uint32(n+1) ;
    byte_copy(tmp, chunksize, s + i * chunksize) ;
    byte_copy(s + i * chunksize, chunksize, s + n * chunksize) ;
    byte_copy(s + n * chunksize, chunksize, tmp) ;
  }
}
