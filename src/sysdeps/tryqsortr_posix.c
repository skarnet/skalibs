/* ISC license. */

#include <stdlib.h>

static int f (void const *a, void const *b, void *c)
{
  int aa = *(int *)a ;
  int bb = *(int *)b ;
  (void)c ;
  return aa < bb ? -1 : aa > bb ;
}

int main (void)
{
  char *x = "blah" ;
  int x[2] = { 2, 1 } ;
  qsort_r(x, 2, sizeof(int), &f, x) ;
  return 0 ;
}
