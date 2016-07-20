/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/tai.h>
#include <skalibs/webipc.h>
#include <skalibs/unix-timed.h>

struct blah_s
{
  int fd ;
  char *s ;
  unsigned int len ;
  char *path ;
} ;

static int getfd (struct blah_s *blah)
{
  return blah->fd ;
}

static int get (struct blah_s *blah)
{
  return sanitize_read(ipc_recv(blah->fd, blah->s, blah->len, blah->path)) ;
}

int ipc_timed_get (int fd, char *s, unsigned int len, char *path, tain_t const *deadline, tain_t *stamp)
{
  struct blah_s blah = { .fd = fd, .s = s, .len = len, .path = path } ;
  return timed_get(&blah, (initfunc_t_ref)&getfd, (initfunc_t_ref)&get, deadline, stamp) ;
}
