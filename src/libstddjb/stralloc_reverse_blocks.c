/* ISC license. */

#include <sys/types.h>
#include <string.h>
#include <skalibs/stralloc.h>

void stralloc_reverse_blocks (stralloc *sa, size_t size)
{
  register size_t n = sa->len / (size << 1) ;
  register size_t i = 0 ;
  char tmp[size] ;
  for (; i < n ; i++)
  {
    memcpy(tmp, sa->s + i * size, size) ;
    memcpy(sa->s + i * size, sa->s + (2*n - 1 - i) * size, size) ;
    memcpy(sa->s + (2*n - 1 - i) * size, tmp, size) ;
  }
}
