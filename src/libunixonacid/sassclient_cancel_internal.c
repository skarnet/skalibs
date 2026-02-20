/* ISC license. */

#include <sys/uio.h>
#include <stdint.h>
#include <errno.h>

#include <skalibs/uint32.h>
#include <skalibs/textclient.h>

#include "sassclient-internal.h"

int asyncnss_cancel_internal (sassclient *a, uint32_t id, tain const *deadline, tain *stamp)
{
  struct iovec answer ;
  char pack[5] = "-" ;

  uint32_pack_big(pack + 1, id) ;
  if (!textclient_exchange(&a->connection, pack, 5, &answer, deadline, stamp)) return errno ;
  if (answer.iov_len != 1) return EPROTO ;
  return *(uint8_t *)answer.iov_base ;
}
