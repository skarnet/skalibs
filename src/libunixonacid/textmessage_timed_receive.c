/* ISC license. */

#include <sys/uio.h>
#include <skalibs/functypes.h>
#include <skalibs/unix-timed.h>
#include <skalibs/textmessage.h>

typedef struct textmessage_get_s textmessage_get_t, *textmessage_get_t_ref ;
struct textmessage_get_s
{
  textmessage_receiver_t *tr ;
  struct iovec *v ;
} ;

static int getfd (textmessage_get_t *g)
{
  return textmessage_receiver_fd(g->tr) ;
}

static ssize_t get (textmessage_get_t *g)
{
  return textmessage_receive(g->tr, g->v) ;
}

int textmessage_timed_receive (textmessage_receiver_t *tr, struct iovec *v, tain_t const *deadline, tain_t *stamp)
{
  textmessage_get_t g = { .tr = tr, .v = v } ;
  return timed_get(&g, (initfunc_t_ref)&getfd, (getfunc_t_ref)&get, deadline, stamp) ;
}
