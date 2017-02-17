/* ISC license. */

#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <skalibs/buffer.h>
#include <skalibs/lolstdio.h>

int vbprintf (buffer *b, char const *format, va_list args)
{
  int r ;
  {
    va_list ugly ;
    va_copy(ugly, args) ;
    r = vsnprintf(0, 0, format, ugly) ;
    va_end(ugly) ;
  }
  if (r < 0) return r ;
  {
    char buf[(size_t)r + 1] ;
    r = vsnprintf(buf, (size_t)r + 1, format, args) ;
    if (r < 0) return r ;
    if (buffer_put(b, buf, r) < r) return -1 ;
  }
  return r ;
}
