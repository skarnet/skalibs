/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/tai.h>
#include <skalibs/unix-timed.h>
#include <skalibs/unixmessage.h>

static int unixmessage_sender_isnonempty (unixmessage_sender_t *b)
{
  return !unixmessage_sender_isempty(b) ;
}

int unixmessage_sender_timed_flush (unixmessage_sender_t *b, tain_t const *deadline, tain_t *stamp)
{
  return timed_flush(b, (initfunc_t_ref)&unixmessage_sender_getfd, (initfunc_t_ref)&unixmessage_sender_isnonempty, (initfunc_t_ref)&unixmessage_sender_flush, deadline, stamp) ;
}
