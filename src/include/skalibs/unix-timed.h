/* ISC license. */

#ifndef UNIX_TIMED_H
#define UNIX_TIMED_H

#include <sys/types.h>
#include <skalibs/bufalloc.h>
#include <skalibs/buffer.h>
#include <skalibs/functypes.h>
#include <skalibs/stralloc.h>
#include <skalibs/tai.h>


 /* Timed "blocking" operations (the fd must still be non-blocking) */

extern int timed_flush (void *, initfunc_t_ref, initfunc_t_ref, initfunc_t_ref, tain_t const *, tain_t *) ;
#define timed_flush_g(b, getfd, isnonempty, flush, deadline) timed_flush(b, getfd, isnonempty, flush, (deadline_), &STAMP)
extern ssize_t timed_get (void *, initfunc_t_ref, getfunc_t_ref, tain_t const *, tain_t *) ;
#define timed_get_g (b, getfd, get, deadline) timed_get(b, getfd, get, (deadline), &STAMP)

extern ssize_t buffer_timed_fill (buffer *, tain_t const *, tain_t *) ;
#define buffer_timed_fill_g(b, deadline) buffer_timed_fill(b, (deadline), &STAMP)
extern int bufalloc_timed_flush (bufalloc *, tain_t const *, tain_t *) ;
#define bufalloc_timed_flush_g(ba, deadline) bufalloc_timed_flush(ba, (deadline), &STAMP)
extern int buffer_timed_flush (buffer *, tain_t const *, tain_t *) ;
#define buffer_timed_flush_g(b, deadline) buffer_timed_flush(b, (deadline), &STAMP)
extern size_t buffer_timed_get (buffer *, char *, size_t, tain_t const *, tain_t *) ;
#define buffer_timed_get_g(b, buf, buflen, deadline) buffer_timed_get(b, buf, buflen, (deadline), &STAMP)

extern int timed_getln (buffer *, stralloc *, char, tain_t const *, tain_t *) ;
#define timed_getln_g(b, sa, sep, deadline) timed_getln(b, sa, sep, (deadline), &STAMP)
extern ssize_t timed_getlnmax (buffer *, char *, size_t, size_t *, char, tain_t const *, tain_t *) ;
#define timed_getlnmax_g(b, max, maxlen, len, sep, deadline) timed_getlnmax(b, max, maxlen, len, sep, (deadline), &STAMP)
extern int netstring_timed_get (buffer *, stralloc *, tain_t const *, tain_t *) ;
#define netstring_timed_get_g(b, sa, deadline) netstring_timed_get(b, sa, (deadline), &STAMP)

extern int ipc_timed_send (int, char const *, size_t, tain_t const *, tain_t *) ;
#define ipc_timed_send_g(fd, s, len, deadline) ipc_timed_send(fd, s, len, (deadline), &STAMP)
extern ssize_t ipc_timed_recv (int, char *, size_t, char *, tain_t const *, tain_t *) ;
#define ipc_timed_recv_g(fd, s, len, path, deadline) ipc_timed_recv(fd, s, len, path, (deadline), &STAMP)

#endif
