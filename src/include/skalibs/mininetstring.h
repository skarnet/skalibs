/* ISC license. */

#ifndef MININETSTRING_H
#define MININETSTRING_H

#include <stdint.h>
#include <skalibs/gccattributes.h>
#include <skalibs/stralloc.h>

extern int mininetstring_read (int, stralloc *, uint32_t *) gccattr_deprecated ;
extern int mininetstring_write (int, char const *, uint16_t, uint32_t *) gccattr_deprecated ;

#endif
