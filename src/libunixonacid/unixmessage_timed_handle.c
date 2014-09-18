/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/tai.h>
#include <skalibs/unix-timed.h>
#include <skalibs/unixmessage.h>

typedef struct unixmessage_handler_blah_s unixmessage_handler_blah_t, *unixmessage_handler_blah_t_ref ;
struct unixmessage_handler_blah_s
{
  unixmessage_receiver_t *b ;
  unixmessage_handler_func_t *f ;
  void *p ;
} ;

static int getfd (unixmessage_handler_blah_t *blah)
{
  return unixmessage_receiver_fd(blah->b) ;
}

static int get (unixmessage_handler_blah_t *blah)
{
  return unixmessage_handle(blah->b, blah->f, blah->p) ;
}

int unixmessage_timed_handle (unixmessage_receiver_t *b, unixmessage_handler_func_t *f, void *p, tain_t const *deadline, tain_t *stamp)
{
  unixmessage_handler_blah_t blah = { .b = b, .f = f, .p = p } ;
  return timed_get(&blah, (initfunc_t_ref)&getfd, (initfunc_t_ref)&get, deadline, stamp) ;
}
