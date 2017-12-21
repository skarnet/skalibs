/* ISC license. */

#ifndef MININETSTRING_H
#define MININETSTRING_H

#include <stdint.h>
#include <skalibs/stralloc.h>

extern int mininetstring_read (int, stralloc *, uint32_t *) ;
extern int mininetstring_write (int, char const *, uint16_t, uint32_t *) ;

#endif
