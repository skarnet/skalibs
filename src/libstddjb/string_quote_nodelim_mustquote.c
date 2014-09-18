/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>
#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>

int string_quote_nodelim_mustquote (stralloc *sa, char const *s, unsigned int len, char const *delim, unsigned int delimlen)
{
  char class[256] = "dddddddaaaaaaaddddddddddddddddddcccccccccccccccceeeeeeeeeeccccccccccccccccccccccccccccccccccbcccceeeeeecccccccecccececececcccccddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd" ;

  unsigned int base = sa->len ;
  unsigned int i = 0 ;
  int wasnull = !sa->s ;

  for (; i < delimlen ; i++)
    if (class[(unsigned char)delim[i]] == 'c')
      class[(unsigned char)delim[i]] = 'b' ;
    else return (errno = EINVAL, 0) ;

  for (i = 0 ; i < len ; i++)
  {
    switch (class[(unsigned char)s[i]])
    {
      case 'a' :
      {
        static char const tab[7] = "abtnvfr" ;
        char fmt[2] = "\\" ;
        fmt[1] = tab[s[i] - 7] ;
        if (!stralloc_catb(sa, fmt, 2)) goto err ;
        break ;
      }
      case 'b' :
      {
        char fmt[2] = "\\" ;
        fmt[1] = s[i] ;
        if (!stralloc_catb(sa, fmt, 2)) goto err ;
        break ;
      }
      case 'c' :
      case 'e' :
      {
        if (!stralloc_catb(sa, s+i, 1)) goto err ;
        break ;
      }
      case 'd' :
      {
        char fmt[5] = "\\0x" ;
        ucharn_fmt(fmt+3, s+i, 1) ;
        if (!stralloc_catb(sa, fmt, 5)) goto err ;
        break ;
      }
      default : errno = EFAULT ; goto err ; /* can't happen */
    }
  }
  return 1 ;

 err:
  if (wasnull) stralloc_free(sa) ; else sa->len = base ;
  return 0 ;
}
