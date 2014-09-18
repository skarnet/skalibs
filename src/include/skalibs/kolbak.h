/* ISC license. */

#ifndef KOLBAK_H
#define KOLBAK_H

#include <skalibs/unixmessage.h>

typedef struct kolbak_closure_s kolbak_closure_t, *kolbak_closure_t_ref ;
struct kolbak_closure_s
{
  unixmessage_handler_func_t_ref f ;
  void *data ;
} ;
#define KOLBAK_CLOSURE_ZERO { .f = 0, .data = 0 }

typedef struct kolbak_queue_s kolbak_queue_t, *kolbak_queue_t_ref ;
struct kolbak_queue_s
{
  kolbak_closure_t *x ;
  unsigned int n ;
  unsigned int head ;
  unsigned int tail ;
} ;
#define KOLBAK_QUEUE_ZERO { .x = 0, .n = 0, .head = 0, .tail = 0 }
#define KOLBAK_QUEUE_INIT(s, len) { .x = (s), .n = (len), .head = 0, .tail = 0 }

extern int kolbak_queue_init (kolbak_queue_t *, kolbak_closure_t *, unsigned int) ;
extern int kolbak_enqueue (kolbak_queue_t *, unixmessage_handler_func_t_ref, void *) ;
extern int kolbak_unenqueue (kolbak_queue_t *) ;
extern int kolbak_call (unixmessage_t const *, kolbak_queue_t *) ; 

#endif
