/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/unix-timed.h>
#include <skalibs/textmessage.h>

static int textmessage_sender_isnonempty (textmessage_sender_t *ts)
{
  return !textmessage_sender_isempty(ts) ;
}

int textmessage_sender_timed_flush (textmessage_sender_t *ts, tain_t const *deadline, tain_t *stamp)
{
  return timed_flush(ts, (initfunc_t_ref)&textmessage_sender_getfd, (initfunc_t_ref)&textmessage_sender_isnonempty, (initfunc_t_ref)&textmessage_sender_flush, deadline, stamp) ;
}
