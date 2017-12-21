/* ISC license. */

#ifndef SKALIBS_TEXTMESSAGE_H
#define SKALIBS_TEXTMESSAGE_H

#include <sys/uio.h>
#include <stdint.h>
#include <skalibs/gccattributes.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/bufalloc.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/tai.h>

#define TEXTMESSAGE_MAXREADS 128


 /* Sender */

typedef struct textmessage_sender_s textmessage_sender_t, *textmessage_sender_t_ref ;
struct textmessage_sender_s
{
  bufalloc out ;
} ;
#define TEXTMESSAGE_SENDER_ZERO { .out = BUFALLOC_ZERO }
extern textmessage_sender_t const textmessage_sender_zero ;
#define TEXTMESSAGE_SENDER_INIT(fd) { .out = BUFALLOC_INIT(&fd_write, (fd)) }

#define textmessage_sender_init(ts, fd) bufalloc_init(&(ts)->out, &fd_write, fd)
#define textmessage_sender_free(ts) bufalloc_free(&(ts)->out)
#define textmessage_sender_fd(ts) bufalloc_fd(&(ts)->out)
extern int textmessage_sender_getfd (textmessage_sender_t const *) gccattr_pure ;
#define textmessage_sender_isempty(ts) bufalloc_isempty(&(ts)->out)

extern int textmessage_put (textmessage_sender_t *, char const *, size_t) ;
extern int textmessage_putv (textmessage_sender_t *, struct iovec const *, unsigned int) ;

extern int textmessage_sender_flush (textmessage_sender_t *) ;
extern int unixmessage_sender_timed_flush (textmessage_sender_t *, tain_t const *, tain_t *) ;
#define textmessage_sender_timed_flush_g(ts, deadline) textmessage_sender_timed_flush(ts, (deadline), &STAMP)

#define textmessage_send(ts, s, len) (textmessage_put(ts, s, len) && textmessage_sender_flush(ts))
#define textmessage_sendv(ts, v, n) (textmessage_putv(ts, v, n) && textmessage_sender_flush(ts))
#define textmessage_timed_send(ts, s, len, deadline, stamp) (textmessage_put(ts, s, len) && texxtmessage_sender_timed_flush(ts, deadline, stamp))
#define textmessage_timed_sendv(ts, v, n, deadline, stamp) (textmessage_putv(ts, v, n) && texxtmessage_sender_timed_flush(ts, deadline, stamp))
#define textmessage_timed_send_g(ts, s, len, deadline) textmessage_timed_send(ts, s, len, (deadline), &STAMP)
#define textmessage_timed_sendv_g(ts, v, n, deadline) textmessage_timed_sendv(ts, v, n, (deadline), &STAMP)


 /* Receiver */

typedef struct textmessage_receiver_s textmessage_receiver_t, *textmessage_receiver_t_ref ;
struct textmessage_receiver_s
{
  buffer in ;
  stralloc indata ;
  uint32_t wanted ;
  uint32_t max ;
} ;
#define TEXTMESSAGE_RECEIVER_ZERO { .in = BUFFER_ZERO, .indata = STRALLOC_ZERO, .wanted = 0, .max = 0 }
extern textmessage_receiver_t const textmessage_receiver_zero ;
#define TEXTMESSAGE_RECEIVER_INIT(fd, buf, len, n) { .in = BUFFER_INIT(&buffer_read, (fd), buf, len), .indata = STRALLOC_ZERO, .wanted = 0, .max = n }

extern int textmessage_receiver_init (textmessage_receiver_t *, int, char *, size_t, uint32_t) ;
extern void textmessage_receiver_free (textmessage_receiver_t *) ;
#define textmessage_receiver_fd(tr) buffer_fd(&(tr)->in)
#define textmessage_receiver_isempty(tr) buffer_isempty(&(tr)->in)
#define textmessage_receiver_isfull(tr) buffer_isfull(&(tr)->in)

extern int textmessage_receiver_hasmsginbuf (textmessage_receiver_t const *) gccattr_pure ;

extern int textmessage_receive (textmessage_receiver_t *, struct iovec *) ;
extern int textmessage_timed_receive (textmessage_receiver_t *, struct iovec *, tain_t const *, tain_t *) ;
#define textmessage_timed_receive_g(tr, s, max, deadline) textmessage_timed_receive(tr, s, max, (deadline), &STAMP)

typedef int textmessage_handler_func_t (struct iovec const *, void *) ;
typedef textmessage_handler_func_t *textmessage_handler_func_t_ref ;

extern int textmessage_handle (textmessage_receiver_t *, textmessage_handler_func_t_ref, void *) ;
extern int textmessage_timed_handle (textmessage_receiver_t *, textmessage_handler_func_t_ref, void *, tain_t const *, tain_t *) ;
#define textmessage_timed_handle_g(tr, f, p, deadline) unixmessage_timed_handle(tr, f, p, (deadline), &STAMP)



 /* Globals */

extern textmessage_receiver_t textmessage_receiver_0_ ;
#define textmessage_receiver_0 (&textmessage_receiver_0_)

extern textmessage_sender_t textmessage_sender_1_ ;
#define textmessage_sender_1 (&textmessage_sender_1_)

extern textmessage_sender_t textmessage_sender_x_ ;
#define textmessage_sender_x (&textmessage_sender_x_)

#endif
