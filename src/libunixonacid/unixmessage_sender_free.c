/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/diuint.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/unixmessage.h>

void unixmessage_sender_free (unixmessage_sender_t *b)
{
#ifdef SKALIBS_HASANCILAUTOCLOSE
  {
    diuint *offsets = genalloc_s(unsigned int, &b->offsets) ;
    unsigned int n = genalloc_len(unsigned int, &b->offsets) ;
    int *fds = genalloc_s(int, &b->fds) ;
    unsigned int nfds = genalloc_len(int, &b->fds) ;
    for (; b->head < n ; b->head++)
    {
      register unsigned int last = b->head+1 < n ? offsets[b->head+1].right : nfds ;
      register unsigned int i = offsets[b->head].right ;
      for (; i < last ; i++) if (fds[i] >= 0) fd_close(fds[i]) ;
    }
  }
#endif
  genalloc_free(diuint, &b->offsets) ;
  genalloc_free(int, &b->fds) ;
  stralloc_free(&b->data) ;
  *b = unixmessage_sender_zero ;
}
