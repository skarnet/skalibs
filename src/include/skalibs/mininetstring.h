/* ISC license. */

#ifndef MININETSTRING_H
#define MININETSTRING_H

#include <skalibs/uint16.h>
#include <skalibs/uint32.h>
#include <skalibs/stralloc.h>

extern int mininetstring_read (int, stralloc *, uint32 *) ;
extern int mininetstring_write (int, char const *, uint16, uint32 *) ;

#endif
