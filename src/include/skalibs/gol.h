/* ISC license. */

#ifndef SKALIBS_GOL_H
#define SKALIBS_GOL_H

 /* Parsing of long (and short) options. */

#include <stdint.h>

#include <skalibs/uint64.h>

typedef struct gol_bool_s gol_bool, *gol_bool_ref ;
struct gol_bool_s
{
  uint64_t mask ;
  char const *lo ;
  uint8_t so : 7 ;
  uint8_t set : 1 ;
} ;

typedef struct gol_arg_s gol_arg, *gol_arg_ref ;
struct gol_arg_s
{
  char const *lo ;
  unsigned int i ;
  uint8_t so : 7 ;
} ;

extern int gol (char const *const *, unsigned int, gol_bool const *, unsigned int, gol_arg const *a, unsigned int, uint64_t *, char const **, int *) ;
extern unsigned int gol_argv (int, char const *const *, gol_bool const *, unsigned int, gol_arg const *a, unsigned int, uint64_t *, char const **) ;

#endif
