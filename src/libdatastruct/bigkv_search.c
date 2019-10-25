/* ISC license. */

#include <skalibs/genalloc.h>
#include <skalibs/avltree.h>
#include <skalibs/bigkv.h>

char const *bigkv_search (bigkv_t const *b, char const *k)
{
  uint32_t i ;
  if (!avltree_search(&b->map, k, &i)) return 0 ;
  return b->storage.s + genalloc_s(bigkv_node_t, &b->nodes)[i].v ;
}
