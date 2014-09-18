/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/randomegd.h>

unsigned int randomegd_readnb (int s, char *x, unsigned int n)
{
  unsigned int w = 0 ;
  while ((n - w) >= 255)
  {
    char c[2] = { 0x01, 0xFF } ;
    register unsigned char wtmp ;
    if (allwrite(s, c, 2) < 2) return w ;
    if (sanitize_read(fd_read(s, c+1, 1)) < 1) return w ;
    wtmp = allread(s, x + w, c[1]) ;
    w += wtmp ;
    if ((wtmp < (unsigned char)c[1]) || ((unsigned char)c[1] < 0xFF)) return w ;
  }
  if (w < n)
  {
    char c[2] = "\001" ;
    c[1] = n - w ;
    if (allwrite(s, c, 2) < 2) return w ;
    if (sanitize_read(fd_read(s, c+1, 1)) < 1) return w ;
    w += allread(s, x + w, c[1]) ;
  }
  return w ;
}
