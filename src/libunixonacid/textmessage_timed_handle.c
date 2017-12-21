/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/unix-timed.h>
#include <skalibs/textmessage.h>

typedef struct textmessage_handler_blah_s textmessage_handler_blah_t, *textmessage_handler_blah_t_ref ;
struct textmessage_handler_blah_s
{
  textmessage_receiver_t *tr ;
  textmessage_handler_func_t_ref f ;
  void *p ;
} ;

static int getfd (textmessage_handler_blah_t *blah)
{
  return textmessage_receiver_fd(blah->tr) ;
}

static ssize_t get (textmessage_handler_blah_t *blah)
{
  return textmessage_handle(blah->tr, blah->f, blah->p) ;
}

int textmessage_timed_handle (textmessage_receiver_t *tr, textmessage_handler_func_t_ref f, void *p, tain_t const *deadline, tain_t *stamp)
{
  textmessage_handler_blah_t blah = { .tr = tr, .f = f, .p = p } ;
  return timed_get(&blah, (initfunc_t_ref)&getfd, (getfunc_t_ref)&get, deadline, stamp) ;
}
