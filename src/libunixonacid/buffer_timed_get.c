/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/buffer.h>
#include <skalibs/unix-timed.h>

struct blah_s
{
  buffer *b ;
  char *s ;
  size_t len ;
  size_t w ;
} ;

static int getfd (struct blah_s *blah)
{
  return buffer_fd(blah->b) ;
}

static ssize_t get (struct blah_s *blah)
{
  return buffer_getall(blah->b, blah->s, blah->len, &blah->w) ;
}

size_t buffer_timed_get (buffer *b, char *s, size_t len, tain_t const *deadline, tain_t *stamp)
{
  struct blah_s blah = { .b = b, .s = s, .len = len, .w = 0 } ;
  timed_get(&blah, (initfunc_t_ref)&getfd, (getfunc_t_ref)&get, deadline, stamp) ;
  return blah.w ;
}
