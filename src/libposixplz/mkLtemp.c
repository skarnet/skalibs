/* ISC license. */

#include <unistd.h>

#include <skalibs/posixplz.h>

int mkLtemp (char const *src, char *dst)
{
  return mklinktemp(src, dst, &link) ;
}
