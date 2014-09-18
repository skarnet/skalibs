/* ISC license. */

#ifndef CBUFFER_H
#define CBUFFER_H

#include <skalibs/gccattributes.h>
#include <skalibs/bytestr.h>
#include <skalibs/diuint.h>
#include <skalibs/siovec.h>

typedef struct cbuffer_s cbuffer_t, *cbuffer_t_ref ;
struct cbuffer_s
{
  char *x ;
  unsigned int a ; /* total length */
  unsigned int p ; /* head */
  unsigned int n ; /* tail */
} ;
#define CBUFFER_ZERO { .x = 0, .a = 0, .p = 0, .n = 0 }

 /*
    Circular buffers need to be 1 char bigger than the storage space,
    so that the head == tail case is nonambiguous (empty).
 */

#define CBUFFER_INIT(buf, len) { .x = (buf), .a = (len), .p = 0, .n = 0 }
extern int cbuffer_init (cbuffer_t *, char *, unsigned int) ;


 /* Writing */

extern unsigned int cbuffer_put (cbuffer_t *, char const *, unsigned int) ;
extern unsigned int cbuffer_putv (cbuffer_t *, siovec_t const *, unsigned int) ;
#define cbuffer_puts(b, s) cbuffer_put(b, (s), str_len(s))

#define cbuffer_UNPUT(b, w) ((b)->n = ((b)->a + (b)->n - w) % (b)->a, w) ;
extern unsigned int cbuffer_unput (cbuffer_t *, unsigned int) ;
extern void cbuffer_wpeek (cbuffer_t *, siovec_t *) ;
#define cbuffer_WSEEK(b, w) ((b)->n = ((b)->n + (w)) % (b)->a, w)
extern unsigned int cbuffer_wseek (cbuffer_t *, unsigned int) ;


 /* Reading */

extern unsigned int cbuffer_get (cbuffer_t *, char *, unsigned int) ;
extern unsigned int cbuffer_getv (cbuffer_t *, siovec_t const *, unsigned int) ;

#define cbuffer_UNGET(b, n) ((b)->p = ((b)->a + (b)->p - n) % (b)->a, n) ;
extern unsigned int cbuffer_unget (cbuffer_t *, unsigned int) ;
extern void cbuffer_rpeek (cbuffer_t *, siovec_t *) ;
#define cbuffer_RSEEK(b, n) ((b)->p = ((b)->p + (n)) % (b)->a, n)
extern unsigned int cbuffer_rseek (cbuffer_t *, unsigned int) ;


 /* Utility */

#define cbuffer_len(b) ((unsigned int)(((b)->a - (b)->p + (b)->n) % (b)->a))
#define cbuffer_available(b) ((unsigned int)(((b)->a - (b)->n + (b)->p - 1) % (b)->a))
#define cbuffer_isempty(b) (!cbuffer_len(b))
#define cbuffer_isfull(b) (!cbuffer_available(b))

#endif
