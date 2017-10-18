/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <skalibs/uint32.h>

void uint32_pack (char *s, uint32_t u)
{
  u = uint32_little(u) ;
  memcpy(s, &u, sizeof(uint32_t)) ;
}
