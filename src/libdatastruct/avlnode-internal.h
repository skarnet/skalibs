/* ISC license. */

#ifndef AVLNODE_INTERNAL_H
#define AVLNODE_INTERNAL_H

#include <skalibs/avlnode.h>

#define avlnode_ufroms(c) ((c) > 0)
#define avlnode_sfromu(h) ((h) ? 1 : -1)

extern unsigned int avlnode_rotate (avlnode *, unsigned int, unsigned int, int) ;
extern unsigned int avlnode_doublerotate (avlnode *, unsigned int, unsigned int, int) ;
#define avlnode_rotate_maydouble(s, max, r, h, isdouble) ((isdouble) ? avlnode_doublerotate(s, max, r, h) : avlnode_rotate(s, max, r, h))

#endif
