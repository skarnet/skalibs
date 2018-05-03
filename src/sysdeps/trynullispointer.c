/* ISC license. */

/* Explanation: http://www.openwall.com/lists/musl/2013/01/09/13 */

#include <stddef.h>

int main (void)
{
  char s[1][1+(int)NULL] ;
  int i = 0 ;
  return sizeof s[i++], !i ;
}
