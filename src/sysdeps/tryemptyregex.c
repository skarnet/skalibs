/* ISC license. */

#include <regex.h>

int main (void)
{
  regex_t re ;
  int r = regcomp(&re, "", REG_EXTENDED | REG_NOSUB) ;
  switch (r)
  {
    case 0 : break ;
    case REG_ESPACE : return 111 ;
    default : return 1 ;
  }
  return !!regexec(&re, "a", 0, 0, 0) ;
}
