/* ISC license. */

#include <stdio.h>

int main (void)
{
  unsigned long i = 0xdeadbeefUL ;
  if (sizeof(unsigned long) == 4)
    if ((((unsigned char *)(&i))[0] == 0xef)
     && (((unsigned char *)(&i))[1] == 0xbe)
     && (((unsigned char *)(&i))[2] == 0xad)
     && (((unsigned char *)(&i))[3] == 0xde))
      return (puts("little"), 0) ;
    else if ((((unsigned char *)(&i))[0] == 0xde)
     && (((unsigned char *)(&i))[1] == 0xad)
     && (((unsigned char *)(&i))[2] == 0xbe)
     && (((unsigned char *)(&i))[3] == 0xef))
      return (puts("big"), 0) ;
    else return (puts("unknown"), 1) ;
  else if (sizeof(unsigned long) == 8)
    if ((((unsigned char *)(&i))[0] == 0xef)
     && (((unsigned char *)(&i))[1] == 0xbe)
     && (((unsigned char *)(&i))[2] == 0xad)
     && (((unsigned char *)(&i))[3] == 0xde)
     && (((unsigned char *)(&i))[4] == 0x00)
     && (((unsigned char *)(&i))[5] == 0x00)
     && (((unsigned char *)(&i))[6] == 0x00)
     && (((unsigned char *)(&i))[7] == 0x00))
      return (puts("little"), 0) ;
    else if (sizeof(unsigned long) == 8)
      if ((((unsigned char *)(&i))[0] == 0x00)
       && (((unsigned char *)(&i))[1] == 0x00)
       && (((unsigned char *)(&i))[2] == 0x00)
       && (((unsigned char *)(&i))[3] == 0x00)
       && (((unsigned char *)(&i))[4] == 0xde)
       && (((unsigned char *)(&i))[5] == 0xad)
       && (((unsigned char *)(&i))[6] == 0xbe)
       && (((unsigned char *)(&i))[7] == 0xef))
        return (puts("big"), 0) ;
      else return (puts("unknown"), 1) ;
    else return 1 ;
  else return (puts("unknown unsigned long size"), 1) ;
}
