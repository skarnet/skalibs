/* ISC license. */

#ifndef BUFFER_H
#define BUFFER_H

#include <skalibs/gccattributes.h>
#include <skalibs/bytestr.h>
#include <skalibs/cbuffer.h>
#include <skalibs/diuint.h>
#include <skalibs/siovec.h>

typedef int buffer_io_func_t (int, siovec_t const *, unsigned int) ;
typedef buffer_io_func_t *buffer_io_func_t_ref ;

typedef struct buffer_s buffer, buffer_t, *buffer_ref, *buffer_t_ref ;
struct buffer_s
{
  buffer_io_func_t *op ;
  int fd ;
  cbuffer_t c ;
} ;
#define BUFFER_ZERO { .op = 0, .fd = -1, .c = CBUFFER_ZERO }


 /*
    Circular buffers need to be 1 char bigger than the storage space,
    so that the head == tail case is nonambiguous (empty, not full).
 */

#define BUFFER_INSIZE 8192
#define BUFFER_OUTSIZE 8192
#define BUFFER_ERRSIZE 1024
#define BUFFER_INSIZE_SMALL 512
#define BUFFER_OUTSIZE_SMALL 512

#define BUFFER_INIT(f, d, buf, len) { .op = (f), .fd = (d), .c = CBUFFER_INIT(buf, len) }
extern int buffer_init (buffer *, buffer_io_func_t *, int, char *, unsigned int) ;


 /* Writing */

extern int buffer_flush (buffer *) ;

#define buffer_putnoflush(b, s, len) cbuffer_put(&(b)->c, s, len)
#define buffer_putvnoflush(b, v, n) cbuffer_putv(&(b)->c, v, n)
#define buffer_putsnoflush(b, s) buffer_putnoflush(b, (s), str_len(s))

extern int buffer_putallnoflush (buffer *, char const *, unsigned int) ;
extern int buffer_putvallnoflush (buffer *, siovec_t const *, unsigned int) ;
#define buffer_putsallnoflush(b, s) buffer_putallnoflush(b, (s), str_len(s))

extern int buffer_putall (buffer *, char const *, unsigned int, unsigned int *) ;
extern int buffer_putvall (buffer *, siovec_t const *, unsigned int, diuint *) ;
#define buffer_putsall(b, s, w) buffer_putall(b, s, str_len(s), w)

#define buffer_putallflush(b, s, len, w) (buffer_putall(b, s, len, w) && buffer_flush(b))
#define buffer_putvallflush(b, v, n, w) (buffer_putvall(b, v, n, w) && buffer_flush(b))
#define buffer_putsallflush(b, s, w) buffer_putallflush(b, s, str_len(s), w)

extern int buffer_put (buffer *, char const *, unsigned int) ;
extern int buffer_putv (buffer *, siovec_t const *, unsigned int) ;
#define buffer_puts(b, s) buffer_put(b, (s), str_len(s))

extern int buffer_putflush (buffer *, char const *, unsigned int) ;
extern int buffer_putvflush (buffer *, siovec_t const *, unsigned int) ;
#define buffer_putsflush(b, s) buffer_putflush(b, (s), str_len(s))

#define buffer_unput(b, n) cbuffer_unput(&(b)->c, n)
#define buffer_wpeek(b, v) cbuffer_wpeek(&(b)->c, v)
#define buffer_wseek(b, n) cbuffer_wseek(&(b)->c, n)
extern buffer_io_func_t buffer_write ;


 /* Reading */

extern int buffer_fill (buffer *) ;

#define buffer_getnofill(b, s, len) cbuffer_get(&(b)->c, s, len)
#define buffer_getvnofill(b, v, n) cbuffer_getv(&(b)->c, v, n)

extern int buffer_getallnofill (buffer *, char *, unsigned int) ;
extern int buffer_getvallnofill (buffer *, siovec_t const *, unsigned int) ;

extern int buffer_getall (buffer *, char *, unsigned int, unsigned int *) ;
extern int buffer_getvall (buffer *, siovec_t const *, unsigned int, diuint *) ;

extern int buffer_get (buffer *, char *, unsigned int) ;
extern int buffer_getv (buffer *, siovec_t const *, unsigned int) ;

#define buffer_unget(b, n) cbuffer_unget(&(b)->c, n)
#define buffer_rpeek(b, n) cbuffer_rpeek(&(b)->c, n)
#define buffer_rseek(b, n) cbuffer_rseek(&(b)->c, n)
extern buffer_io_func_t buffer_read ;


 /* Utility */

#define buffer_len(b) cbuffer_len(&(b)->c)
extern unsigned int buffer_getlen (buffer const *) gccattr_pure ;
#define buffer_available(b) cbuffer_available(&(b)->c)
#define buffer_isempty(b) cbuffer_isempty(&(b)->c)
#define buffer_isfull(b) cbuffer_isfull(&(b)->c)
#define buffer_fd(b) ((b)->fd)
extern int buffer_getfd (buffer const *) gccattr_pure ;
#define buffer_isreadable(b) (!buffer_isfull(b))
#define buffer_iswritable(b) (!buffer_isempty(b))


 /* Globals */

extern buffer_io_func_t buffer_flush1read ;

extern buffer buffer_0_ ;
#define buffer_0 (&buffer_0_)

extern buffer buffer_0small_ ;
#define buffer_0small (&buffer_0small_)

extern buffer buffer_0f1_ ;
#define buffer_0f1 (&buffer_0f1_)

extern buffer buffer_1_ ;
#define buffer_1 (&buffer_1_)

extern buffer buffer_1small_ ;
#define buffer_1small (&buffer_1small_)

extern buffer buffer_2_ ;
#define buffer_2 (&buffer_2_)

#endif
