/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/avltree.h>
#include <skalibs/bigkv.h>

static void *bigkv_dtok (uint32_t d, void *p)
{
  bigkv_t *b = p ;
  return b->storage.s + genalloc_s(bigkv_node_t, &b->nodes)[d].k ;
}

static int bigkv_cmp (void const *a, void const *b, void *p)
{
  (void)p ;
  return strcmp((char const *)a, (char const *)b) ;
}

int bigkv_init (bigkv_t *b, char const *const *argv, char delim, char const *prefix, char const *stop, uint32_t options)
{
  size_t prefixlen = prefix ? strlen(prefix) : 0 ;
  avltree_init(&b->map, 3, 3, 8, &bigkv_dtok, &bigkv_cmp, b) ;
  for (; *argv && !(stop && !strcmp(*argv, stop)) ; argv++)
  {
    bigkv_node_t node = { .k = b->storage.len } ;
    uint32_t d ;
    char const *s = *argv ;
    char *p ;
    if (prefixlen)
    {
      if (!strncmp(s, prefix, prefixlen)) break ;
      s += prefixlen ;
    }
    if (avltree_search(&b->map, s, &d))
    {
      if (options & BIGKV_OPTIONS_NODUP) goto invalid ;
      else avltree_delete(&b->map, s) ;
    }
    if (!stralloc_cats(&b->storage, s) || !stralloc_0(&b->storage)) goto err ;
    p = strchr(s, delim) ;
    if (p)
    {
      node.v = node.k + (p - s) + 1 ;
      b->storage.s[node.k + (p - s)] = 0 ;
    }
    else node.v = b->storage.len - 1 ;
    d = genalloc_len(bigkv_node_t, &b->nodes) ;
    if (!genalloc_append(bigkv_node_t, &b->nodes, &node)) goto err ;
    if (!avltree_insert(&b->map, d)) goto err ;
  }
  return 1 ;

 invalid:
   errno = EINVAL ;
 err:
  bigkv_free(b) ;
  return 0 ;
}
