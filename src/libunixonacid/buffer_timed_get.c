/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/tai.h>
#include <skalibs/unix-timed.h>

struct blah_s
{
  buffer *b ;
  char *s ;
  unsigned int len ;
  unsigned int w ;
} ;

static int getfd (struct blah_s *blah)
{
  return buffer_fd(blah->b) ;
}

static int get (struct blah_s *blah)
{
  return buffer_getall(blah->b, blah->s, blah->len, &blah->w) ;
}

unsigned int buffer_timed_get (buffer *b, char *s, unsigned int len, tain_t const *deadline, tain_t *stamp)
{
  struct blah_s blah = { .b = b, .s = s, .len = len, .w = 0 } ;
  timed_get(&blah, (initfunc_t_ref)&getfd, (initfunc_t_ref)&get, deadline, stamp) ;
  return blah.w ;
}
