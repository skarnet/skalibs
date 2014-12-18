/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/functypes.h>
#include <skalibs/skamisc.h>
#include <skalibs/tai.h>
#include <skalibs/unix-timed.h>

struct blah_s
{
  buffer *b ;
  char *d ;
  unsigned int max ;
  unsigned int w ;
  char sep ;
} ;

static int getfd (struct blah_s *blah)
{
  return buffer_fd(blah->b) ;
}

static int get (struct blah_s *blah)
{
  return sanitize_read(getlnmax(blah->b, blah->d, blah->max, &blah->w, blah->sep)) ;
}

int timed_getlnmax (buffer *b, char *d, unsigned int max, unsigned int *w, char sep, tain_t const *deadline, tain_t *stamp)
{
  struct blah_s blah = { .b = b, .d = d, .max = max, .w = *w, .sep = sep } ;
  register int r = timed_get(&blah, (initfunc_t_ref)&getfd, (initfunc_t_ref)&get, deadline, stamp) ;
  *w = blah.w ;
  return r ;
}
