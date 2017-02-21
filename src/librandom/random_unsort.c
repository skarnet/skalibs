/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <skalibs/random.h>

void random_unsort (char *s, size_t n, size_t chunksize)
{
  char tmp[chunksize] ;
  while (n--)
  {
    uint32_t i = random_uint32(n+1) ;
    memcpy(tmp, s + i * chunksize, chunksize) ;
    memcpy(s + i * chunksize, s + n * chunksize, chunksize) ;
    memcpy(s + n * chunksize, tmp, chunksize) ;
  }
}
