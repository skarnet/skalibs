/* ISC license. */

#ifndef SKALIBS_BIGKV_H
#define SKALIBS_BIGKV_H

#include <stdint.h>
#include <string.h>

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/avltree.h>

typedef struct bigkv_node_s bigkv_node_t, *bigkv_node_t_ref ;
struct bigkv_node_s
{
  size_t k ;
  size_t v ;
} ;
#define BIGKV_NODE_ZERO { .k = 0, .v = 0 }

typedef struct bigkv_s bigkv_t, *bigkv_t_ref ;
struct bigkv_s
{
  stralloc storage ;
  genalloc nodes ; /* bigkv_node_t */
  avltree map ;
} ;
#define BIGKV_ZERO { .storage = STRALLOC_ZERO, .nodes = GENALLOC_ZERO, .map = AVLTREE_ZERO }
extern bigkv_t const bigkv_zero ;

#define BIGKV_OPTIONS_NODUP 0x00000001u

#define bigkv_len(b) avltree_len(&(b)->map)

extern int bigkv_init (bigkv_t *, char const *const *, char, char const *, char const *, uint32_t) ;
#define bigkv_init_argv(b, argv) bigkv_init(b, (argv), '=', "--", "--", 0)
#define bigkv_init_envp(b, envp) bigkv_init(b, (envp), '=', 0, 0, 0)
extern char const *bigkv_search (bigkv_t const *, char const *) ;
extern void bigkv_free (bigkv_t *) ;

#endif
