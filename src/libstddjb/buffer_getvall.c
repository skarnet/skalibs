/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/diuint.h>
#include <skalibs/siovec.h>

int buffer_getvall (buffer *b, siovec_t const *v, unsigned int n, diuint *w)
{
  if (w->left > n || (w->left == n && w->right) || w->right >= v[w->left].len)
    return (errno = EINVAL, -1) ;
  for (; w->left < n ; w->left++, w->right = 0)
  {
    register int r = buffer_getall(b, v[w->left].s, v[w->left].len, &w->right) ;
    if (r <= 0) return r ;
  }
  return 1 ;
}
