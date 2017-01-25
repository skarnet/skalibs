#include <sys/types.h>
#include <stdio.h>

#define p(type) printf("sizeof" #type ": %u\nsigned" #type ": %s\n", \
  (unsigned int)sizeof(type##_t), \
  (type##_t)-1 < 0 ? "yes" : "no") ;

#define q(abbr, type)  printf("sizeof" #abbr ": %u\n", (unsigned int)sizeof(type)) ;

int main (void)
{
  q(ushort, unsigned short) ;
  q(uint, unsigned int) ;
  q(ulong, unsigned long) ;
  p(uid) ;
  p(gid) ;
  p(pid) ;
  p(time) ;
  p(dev) ;
  p(ino) ;
  return 0 ;
}
