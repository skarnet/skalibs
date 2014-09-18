/* ISC license. */

#include <errno.h>
#include <skalibs/uint64.h>
#include <skalibs/djbunix.h>
#include "djbtime-internal.h"

static unsigned int leapsecs_len (uint64 const *data)
{
  register unsigned int i = 1 ;
  while (data[i]) i++ ;
  return i ;
}

static int leapsecs_read (char const *file, uint64 *data)
{
  char s[LEAPSECS_MAX * sizeof(uint64)] ;
  register int n = openreadnclose(file, s, LEAPSECS_MAX * sizeof(uint64)) ;
  if (n < 0) return -1 ;
  if (n % sizeof(uint64)) return (errno = EINVAL, -1) ;
  n /= sizeof(uint64) ;
  {
    register unsigned int i = 0 ;
    for (; i < (unsigned int)n ; i++)
      uint64_unpack_big(s + i * sizeof(uint64), data + i) ;
  }
  data[n] = 0 ;
  return n ;
}

int leapsecs_init_r (char const *file, uint64 *data)
{
  return data[0] ? (int)leapsecs_len(data) : leapsecs_read(file, data) ;
}
