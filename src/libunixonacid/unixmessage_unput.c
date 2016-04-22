 /* ISC license. */

#include <skalibs/genalloc.h>
#include <skalibs/diuint.h>
#include <skalibs/djbunix.h>
#include <skalibs/unixmessage.h>

int unixmessage_unput_and_maybe_drop (unixmessage_sender_t *b, int drop)
{
  diuint *start ;
  unsigned int n = genalloc_len(diuint, &b->offsets) ;
  register int *fds ;
  register unsigned int i ;
  if (!n) return 0 ;
  start = genalloc_s(diuint, &b->offsets) + n - 1 ;
  fds = genalloc_s(int, &b->fds) + start->right ;
  i = genalloc_len(int, &b->fds) - start->right ;
  while (i--)
    if (fds[i] < 0) (*b->closecb)(-(fds[i]+1), b->closecbdata) ;
    else if (drop) fd_close(fds[i]) ;
  b->data.len = start->left ;
  genalloc_setlen(int, &b->fds, start->right) ;
  genalloc_setlen(diuint, &b->offsets, n-1) ;
  return 1 ;
}
