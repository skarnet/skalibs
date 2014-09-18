/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/diuint.h>
#include <skalibs/siovec.h>

int buffer_putvall (buffer *b, siovec_t const *v, unsigned int n, diuint *w)
{
  if (w->left > n || (w->left == n && w->right) || w->right >= v[w->left].len)
    return (errno = EINVAL, 0) ;
  for (; w->left < n ; w->left++, w->right = 0)
    if (!buffer_putall(b, v[w->left].s, v[w->left].len, &w->right)) return 0 ;
  return 1 ;
}
