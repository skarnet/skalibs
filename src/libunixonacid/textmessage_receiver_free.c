/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/textmessage.h>

void textmessage_receiver_free (textmessage_receiver_t *ts)
{
  stralloc_free(&ts->indata) ;
  *ts = textmessage_receiver_zero ;
}
