/* ISC license. */

#include <skalibs/sysdeps.h>
#ifdef SKALIBS_HASANCILAUTOCLOSE
#include <unistd.h>
#endif
#include <string.h>
#include <errno.h>
#include <skalibs/bitarray.h>
#include <skalibs/disize.h>
#include <skalibs/error.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/siovec.h>
#include <skalibs/unixmessage.h>

static inline int copyfds (char *s, int const *fds, unsigned int n, unsigned char const *bits, unixmessage_sender_closecb_func_t_ref closecb, void *closecbdata)
{
  unsigned int i = 0 ;
  for (; i < n ; i++)
  {
    int fd = fds[i] ;
    if (fd < 0) return (errno = EINVAL, -1) ;
    if (bitarray_peek(bits, i)) fd = - fd - 1 ;
#ifdef SKALIBS_HASANCILAUTOCLOSE
    else
    {
      fd = dup(fd) ;
      if (fd < 0)
      {
        int e = errno ;
        while (i--)
        {
          s -= sizeof(int) ;
          memcpy((char *)fd, s, sizeof(int)) ;
          if (fd >= 0) (*closecb)(fd, closecbdata) ;
        }
        errno = e ;
        return 0 ;
      }
    }
#endif
    memcpy(s, (char const *)&fd, sizeof(int)) ;
    s += sizeof(int) ;
  }
  return 1 ;
}

static int reserve_and_copy (unixmessage_sender_t *b, size_t len, int const *fds, unsigned int nfds, unsigned char const *bits)
{
  disize cur = { .left = b->data.len, .right = genalloc_len(int, &b->fds) } ;
  if (len > UNIXMESSAGE_MAXSIZE || nfds > UNIXMESSAGE_MAXFDS)
    return (errno = EPROTO, 0) ;
  if (!genalloc_readyplus(disize, &b->offsets, 1)
   || !genalloc_readyplus(int, &b->fds, nfds)
   || !stralloc_readyplus(&b->data, len))
    return 0 ;
  if (!copyfds(b->fds.s + b->fds.len, fds, nfds, bits, b->closecb, b->closecbdata)) return 0 ;
  genalloc_setlen(int, &b->fds, cur.right + nfds) ;
  return genalloc_append(disize, &b->offsets, &cur) ;
}

int unixmessage_put_and_close (unixmessage_sender_t *b, unixmessage_t const *m, unsigned char const *bits)
{
  if (!reserve_and_copy(b, m->len, m->fds, m->nfds, bits)) return 0 ;
  memmove(b->data.s + b->data.len, m->s, m->len) ;
  b->data.len += m->len ;
  return 1 ;
}

int unixmessage_putv_and_close (unixmessage_sender_t *b, unixmessage_v_t const *m, unsigned char const *bits)
{
  size_t len = siovec_len(m->v, m->vlen) ;
  if (!reserve_and_copy(b, len, m->fds, m->nfds, bits)) return 0 ;
  siovec_gather(m->v, m->vlen, b->data.s + b->data.len, len) ;
  return 1 ;
}
