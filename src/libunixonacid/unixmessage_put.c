/* ISC license. */

#include <skalibs/sysdeps.h>
#ifdef SKALIBS_HASANCILAUTOCLOSE
#include <unistd.h>
#endif
#include <errno.h>
#include <skalibs/bitarray.h>
#include <skalibs/bytestr.h>
#include <skalibs/diuint.h>
#include <skalibs/error.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/siovec.h>
#include <skalibs/unixmessage.h>

static inline int copyfds (char *s, int const *fds, unsigned int n, unsigned char const *bits)
{
  register unsigned int i = 0 ;
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
          byte_copy((char *)fd, sizeof(int), s) ;
          if (fd >= 0) fd_close(fd) ;
        }
        errno = e ;
        return 0 ;
      }
    }
#else
#endif
    byte_copy(s, sizeof(int), (char const *)&fd) ;
    s += sizeof(int) ;
  }
  return 1 ;
}

static int reserve_and_copy (unixmessage_sender_t *b, unsigned int len, int const *fds, unsigned int nfds, unsigned char const *bits)
{
  diuint cur = { .left = b->data.len, .right = genalloc_len(int, &b->fds) } ;
  if (len > UNIXMESSAGE_MAXSIZE || nfds > UNIXMESSAGE_MAXFDS)
    return (errno = EPROTO, 0) ;
  if (!genalloc_readyplus(diuint, &b->offsets, 1)
   || !genalloc_readyplus(int, &b->fds, nfds)
   || !stralloc_readyplus(&b->data, len))
    return 0 ;
  if (!copyfds(b->fds.s + b->fds.len, fds, nfds, bits)) return 0 ;
  genalloc_setlen(int, &b->fds, cur.right + nfds) ;
  byte_copy(b->offsets.s + b->offsets.len, sizeof(diuint), (char const *)&cur) ;
  b->offsets.len += sizeof(diuint) ;
  return 1 ;
}

int unixmessage_put_and_close (unixmessage_sender_t *b, unixmessage_t const *m, unsigned char const *bits)
{
  if (!reserve_and_copy(b, m->len, m->fds, m->nfds, bits)) return 0 ;
  byte_copy(b->data.s + b->data.len, m->len, m->s) ;
  b->data.len += m->len ;
  return 1 ;
}

int unixmessage_putv_and_close (unixmessage_sender_t *b, unixmessage_v_t const *m, unsigned char const *bits)
{
  unsigned int len = 0 ;
  register unsigned int i = 0 ;
  for (; i < m->vlen ; i++) len += m->v[i].len ;
  if (!reserve_and_copy(b, len, m->fds, m->nfds, bits)) return 0 ;
  for (i = 0 ; i < m->vlen ; i++)
  {
    byte_copy(b->data.s + b->data.len, m->v[i].len, m->v[i].s) ;
    b->data.len += m->v[i].len ;
  }
  return 1 ;
}
