/* ISC license. */

/* MT-unsafe */

#include <skalibs/uint64.h>
#include "djbtime-internal.h"

static uint64 leapsecs_here_tab[LEAPSECS_MAX+1] ;
uint64 *leapsecs_here = leapsecs_here_tab ;
