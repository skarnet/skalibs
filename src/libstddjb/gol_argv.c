/* ISC license. */

#include <string.h>

#include <skalibs/gol.h>
#include <skalibs/strerr.h>

unsigned int gol_argv (int argc, char const *const *argv, gol_bool const *b, unsigned int bn, gol_arg const *a, unsigned int an, uint64_t *br, char const **ar)
{
  int problem = 0 ;
  int r ;
  if (!argc) strerr_diefu1x(100, "gol: invalid argv") ;
  if (argc == 1) return 1 ;
  r = gol(argv + 1, argc - 1, b, bn, a, an, br, ar, &problem) ;

  if (r < 0)
  {
    if (problem >= 0)
    {
      char s[2] = { argv[-r][problem], 0 } ;
      strerr_dief4x(100, "unrecognized ", "short", "option: ", s) ;
    }
    else strerr_dief3x(100, "unrecognized ", "option: ", argv[-r]) ;
  }
  else return r + 1 ;
}
