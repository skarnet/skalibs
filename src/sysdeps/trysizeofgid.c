#include <sys/types.h>
#include <stdio.h>

int main (void)
{
  printf("%u\n", (unsigned int)sizeof(gid_t)) ;
  return 0 ;
}
