/* ISC license. */

#ifndef IOBUFFER_H
#define IOBUFFER_H

#define IOBUFFER_SIZE 65536U

 /* iobufferu */

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>

#define IOBUFFERU_SIZE (IOBUFFER_SIZE+1)

typedef struct iobufferu_s iobufferu, *iobufferu_ref ;
struct iobufferu_s
{
  buffer b[2] ;
  char *buf ;
} ;

extern int iobufferu_init (iobufferu_ref, int, int) ;
extern int iobufferu_fill (iobufferu_ref) ;
extern int iobufferu_flush (iobufferu_ref) ;
extern void iobufferu_finish (iobufferu_ref) ;

#define iobufferu_len(u) buffer_len(&(u)->b[0])
#define iobufferu_available(u) buffer_available(&(u)->b[1])
#define iobufferu_isempty(u) buffer_isempty(&(u)->b[0])
#define iobufferu_isfull(u) buffer_isfull(&(u)->b[1])
#define iobufferu_fd(u, h) buffer_fd((u)->b[h])
#define iobufferu_isreadable(u) iobufferu_available(u)
#define iobufferu_iswritable(u) iobufferu_len(u)
#define iobufferu_nonblock(u, h) ndelay_on(iobufferu_fd(u, h))
#define iobufferu_block(u, h) ndelay_off(iobufferu_fd(u, h))
#define iobufferu_nbstate(u, h, j) (j ? iobufferu_nonblock(u, h) : iobufferu_block(u, h))


 /* iobufferk */

#define IOBUFFERK_SIZE IOBUFFER_SIZE

typedef struct iobufferk_s iobufferk, *iobufferk_ref ;
struct iobufferk_s
{
  int fd[2] ;
  int p[2] ;
  unsigned int n ;
  unsigned int type : 2 ;
  unsigned int nb : 2 ;
} ;

typedef int iobufferk_io_func_t (iobufferk_ref) ;
typedef iobufferk_io_func_t *iobufferk_io_func_t_ref ;
typedef void iobufferk_finish_func_t (iobufferk_ref) ;
typedef iobufferk_finish_func_t *iobufferk_finish_func_t_ref ;

extern iobufferk_io_func_t iobufferk_nosys ;
extern iobufferk_io_func_t iobufferk_isworking ;

extern int iobufferk_init (iobufferk_ref, int, int) ;
extern iobufferk_io_func_t_ref const iobufferk_fill_f[4] ;
extern iobufferk_io_func_t_ref const iobufferk_flush_f[4] ;
extern iobufferk_finish_func_t_ref const iobufferk_finish_f[4] ;

#define iobufferk_fill(k) (*iobufferk_fill_f[(k)->type])(k)
#define iobufferk_flush(k) (*iobufferk_flush_f[(k)->type])(k)
#define iobufferk_finish(k) (*iobufferk_finish_f[(k)->type])(k)
#define iobufferk_len(k) ((k)->n)
#define iobufferk_available(k) (IOBUFFERK_SIZE - (k)->n)
#define iobufferk_isempty(k) (!iobufferk_len(k))
#define iobufferk_isfull(k) (!iobufferk_available(k))
#define iobufferk_fd(k, h) ((k)->fd[h])
#define iobufferk_isreadable(k) iobufferk_available(k)
#define iobufferk_iswritable(k) iobufferk_len(k)
#define iobufferk_nonblock(k, h) ((k)->nb |= (1 << (h)), 0)
#define iobufferk_block(k, h) ((k)->nb &= (3 - (1 << (h))), 0)
#define iobufferk_nbstate(k, h, j) (j ? iobufferk_nonblock(k, h) : iobufferk_block(k, h))


 /* iobuffer */

typedef union iobufferku_u iobufferku, *iobufferku_ref ;
union iobufferku_u
{
  iobufferk k ;
  iobufferu u ;
} ;

typedef struct iobuffer_s iobuffer, *iobuffer_ref ;
struct iobuffer_s
{
  iobufferku x ;
  unsigned int isk : 1 ;
} ;

extern int iobuffer_ufromk (iobufferu_ref, iobufferk_ref) ;
extern int iobuffer_kfromu (iobufferk_ref, iobufferu_ref) ;
extern int iobuffer_salvage (iobuffer_ref) ;

extern int iobuffer_init (iobuffer_ref, int, int) ;
extern int iobuffer_fill (iobuffer_ref) ;
extern int iobuffer_flush (iobuffer_ref) ;

#define iobuffer_finish(b) ((b)->isk ? iobufferk_finish(&(b)->x.k) : iobufferu_finish(&(b)->x.u))
#define iobuffer_len(b) ((b)->isk ? iobufferk_len(&(b)->x.k) : iobufferu_len(&(b)->x.u))
#define iobuffer_available(b) ((b)->isk ? iobufferk_available(&(b)->x.k) : iobufferu_available(&(b)->x.u))
#define iobuffer_isempty(b) ((b)->isk ? iobufferk_isempty(&(b)->x.k) : iobufferu_isempty(&(b)->x.u))
#define iobuffer_isfull(b) ((b)->isk ? iobufferk_isfull(&(b)->x.k) : iobufferu_isfull(&(b)->x.u))
#define iobuffer_fd(b, h) ((b)->isk ? iobufferk_fd(&(b)->x.k, h) : iobufferu_fd(&(b)->x.u, h))
#define iobuffer_isreadable(b) ((b)->isk ? iobufferk_isreadable(&(b)->x.k) : iobufferu_isreadable(&(b)->x.u))
#define iobuffer_iswritable(b) ((b)->isk ? iobufferk_iswritable(&(b)->x.k) : iobufferu_iswritable(&(b)->x.u))
#define iobuffer_nonblock(b, h) ((b)->isk ? iobufferk_nonblock(&(b)->x.k, h) : iobufferu_nonblock(&(b)->x.u, h))
#define iobuffer_block(b, h) ((b)->isk ? iobufferk_block(&(b)->x.k, h) : iobufferu_block(&(b)->x.u, h))
#define iobuffer_nbstate(b, h, j) ((b)->isk ? iobufferk_nbstate(&(b)->x.k, h, j) : iobufferu_nbstate(&(b)->x.u, h, j))

#endif
