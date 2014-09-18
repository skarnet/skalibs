/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>

void stralloc_reverse_blocks (stralloc *sa, unsigned int size)
{
  register unsigned int n = sa->len / (size << 1) ;
  register unsigned int i = 0 ;
  char tmp[size] ;
  for (; i < n ; i++)
  {
    byte_copy(tmp, size, sa->s + i * size) ;
    byte_copy(sa->s + i * size, size, sa->s + (2*n - 1 - i) * size) ;
    byte_copy(sa->s + (2*n - 1 - i) * size, size, tmp) ;
  }
}
