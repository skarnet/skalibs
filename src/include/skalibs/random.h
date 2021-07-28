/* ISC license. */

#ifndef SKALIBS_RANDOM_H
#define SKALIBS_RANDOM_H

#include <sys/types.h>
#include <stdint.h>

#include <skalibs/stralloc.h>

extern void random_makeseed (char *) ; /* fills 160 bytes */

extern int random_init (void) ;
extern void random_finish (void) ;

extern unsigned char random_char (void) ;
extern void random_string (char *, size_t) ;
extern uint32_t random_uint32 (uint32_t) ;
extern void random_name (char *, size_t) ;
extern void random_unsort (char *, size_t, size_t) ;
extern int random_sauniquename (stralloc *, size_t) ;

#endif
