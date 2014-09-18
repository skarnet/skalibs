/* ISC license. */

#include <skalibs/bytestr.h>

int str_start (register char const *s, register char const *t)
{
  register char x ;

  for (;;)
  {
    x = *t++; if (!x) return 1; if (x != *s++) return 0;
    x = *t++; if (!x) return 1; if (x != *s++) return 0;
    x = *t++; if (!x) return 1; if (x != *s++) return 0;
    x = *t++; if (!x) return 1; if (x != *s++) return 0;
  }
}
