/* ISC license. */

#ifndef SKALIBS_GOL_H
#define SKALIBS_GOL_H

 /* Parsing of long (and short) options. */

#include <stdint.h>

#include <skalibs/uint64.h>

typedef struct gol_bool_s gol_bool, *gol_bool_ref ;
struct gol_bool_s
{
  uint64_t set ;
  uint64_t clear ;
  char const *lo ;
  uint8_t so ;
} ;

typedef struct gol_arg_s gol_arg, *gol_arg_ref ;
struct gol_arg_s
{
  char const *lo ;
  unsigned int i ;
  uint8_t so ;
} ;

extern int gol (char const *const *, gol_bool const *, unsigned int, gol_arg const *a, unsigned int, uint64_t *, char const **, int *) ;
extern unsigned int gol_argv (char const *const *, gol_bool const *, unsigned int, gol_arg const *a, unsigned int, uint64_t *, char const **) ;
extern unsigned int gol_main (int, char const *const *, gol_bool const *, unsigned int, gol_arg const *a, unsigned int, uint64_t *, char const **) ;

#endif
