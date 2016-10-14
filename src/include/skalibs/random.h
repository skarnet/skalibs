/* ISC license. */

#ifndef RANDOM_H
#define RANDOM_H

#include <skalibs/uint32.h>
#include <skalibs/stralloc.h>

extern void random_makeseed (char *) ; /* fills 160 bytes */

extern int random_init (void) ;
extern void random_finish (void) ;

extern unsigned char random_char (void) ;
extern void random_string (char *, unsigned int) ;
extern uint32 random_uint32 (uint32) ;
extern void random_name (char *, unsigned int) ;
extern void random_unsort (char *, unsigned int, unsigned int) ;
extern int random_sauniquename (stralloc *, unsigned int) ;

#endif
