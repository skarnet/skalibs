/* ISC license. */

#include <skalibs/tai.h>
#include <skalibs/iopause.h>

void deepsleepuntil (tain_t const *deadline, tain_t *stamp)
{
  iopause_fd x ;
  while (tain_less(stamp, deadline)) iopause_stamp(&x, 0, deadline, stamp) ;
}
