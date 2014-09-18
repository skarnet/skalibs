/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/avlnode.h>
#include "avlnode-internal.h"

unsigned int avlnode_delete (avlnode_ref s, unsigned int max, unsigned int *root, void const *k, dtokfunc_t_ref dtok, cmpfunc_t_ref f, void *p)
{
  unsigned int stack[AVLNODE_MAXDEPTH] ;
  int spin[AVLNODE_MAXDEPTH] ;
  unsigned int sp = 0 ;
  unsigned int r = *root ;
  unsigned int itodel ;

  for (; r < max ; sp++)
  {
    register int c = (*f)(k, (*dtok)(s[r].data, p), p) ;
    if (!c) break ;
    spin[sp] = avlnode_ufroms(c) ;
    stack[sp] = r ;
    r = s[r].child[spin[sp]] ;
  }
  if (r >= max) return max ;
  itodel = r ;

  if ((s[r].child[0] < max) || (s[r].child[1] < max))
  {
    int subspin = s[r].child[1] < max ;
    stack[sp] = r ;
    spin[sp++] = subspin ;
    r = s[r].child[subspin] ;
    for (; r < max ; sp++)
    {
      stack[sp] = r ;
      spin[sp] = !subspin ;
      r = s[r].child[!subspin] ;
    }
    r = stack[--sp] ;
    s[itodel].data = s[r].data ;
    itodel = s[r].child[subspin] ;
    if (itodel < max)
    {
      s[r].data = s[itodel].data ;
      stack[sp] = r ;
      spin[sp++] = subspin ;
    }
    else itodel = r ;
  }

  r = max ; 
  while (sp--)
  {
    s[stack[sp]].child[spin[sp]] = r ;
    r = stack[sp] ;
    if (!s[r].balance) goto easyfix ;
    else if (spin[sp] == avlnode_ufroms(s[r].balance)) s[r].balance = 0 ;
    else if (!s[s[r].child[!spin[sp]]].balance) goto hardfix ;
    else r = avlnode_rotate_maydouble(s, max, r, spin[sp], spin[sp] == avlnode_ufroms(s[s[r].child[!spin[sp]]].balance)) ;
  }
  *root = r ;
  return itodel ;

 easyfix:
  s[r].balance = -avlnode_sfromu(spin[sp]) ;
  return itodel ;

 hardfix:
  r = avlnode_rotate(s, max, r, spin[sp]) ;
  if (!sp--) *root = r ;
  else s[stack[sp]].child[spin[sp]] = r ;
  return itodel ;
}
