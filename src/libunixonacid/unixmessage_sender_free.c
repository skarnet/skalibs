/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/diuint.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/djbunix.h>
#include <skalibs/unixmessage.h>

void unixmessage_sender_free (unixmessage_sender_t *b)
{
  unsigned int n = genalloc_len(int, &b->fds) ;
  if (n)
  {
    unsigned int i = genalloc_s(diuint, &b->offsets)[b->head].right ;
    for (; i < n ; i++)
    {
      register int fd = genalloc_s(int, &b->fds)[i] ;
      if (fd < 0) fd_close(-(fd+1)) ;
#ifdef SKALIBS_HASANCILAUTOCLOSE
      else fd_close(fd) ;
#endif
    }
  }
  genalloc_free(diuint, &b->offsets) ;
  genalloc_free(int, &b->fds) ;
  stralloc_free(&b->data) ;
  *b = unixmessage_sender_zero ;
}
