/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASKEVENT

#include <skalibs/allreadwrite.h>
#include <skalibs/keventbridge.h>

int keventbridge_read (keventbridge *kbp, struct kevent *ke)
{
  ssize_t r = sanitize_read(allread(kbp->p[0], (char *)ke, sizeof(struct kevent))) ;
  return r <= 0 ? r : 1 ;
}

#endif
