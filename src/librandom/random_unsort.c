/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/random.h>

void random_unsort (char *s, unsigned int n, unsigned int chunksize)
{
  char tmp[chunksize] ;
  while (n--)
  {
    register unsigned int i = badrandom_int(n+1) ;
    byte_copy(tmp, chunksize, s + i * chunksize) ;
    byte_copy(s + i * chunksize, chunksize, s + n * chunksize) ;
    byte_copy(s + n * chunksize, chunksize, tmp) ;
  }
}
