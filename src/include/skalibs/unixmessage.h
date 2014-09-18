/* ISC license. */

#ifndef UNIXMESSAGE_H
#define UNIXMESSAGE_H

#include <skalibs/buffer.h>
#include <skalibs/cbuffer.h>
#include <skalibs/gccattributes.h>
#include <skalibs/genalloc.h>
#include <skalibs/siovec.h>
#include <skalibs/stralloc.h>
#include <skalibs/tai.h>

typedef struct unixmessage_s unixmessage_t, *unixmessage_t_ref ;
struct unixmessage_s
{
  char *s ;
  unsigned int len ;
  int *fds ;
  unsigned int nfds ;
} ;
#define UNIXMESSAGE_ZERO { .s = 0, .len = 0, .fds = 0, .nfds = 0 }
extern unixmessage_t const unixmessage_zero ;

typedef struct unixmessage_v_s unixmessage_v_t, *unixmessage_v_t_ref ;
struct unixmessage_v_s
{
  siovec_t *v ;
  unsigned int vlen ;
  int *fds ;
  unsigned int nfds ;
} ;
#define UNIXMESSAGE_V_ZERO { .v = 0, .vlen = 0, .fds = 0, .nfds = 0 }
extern unixmessage_v_t const unixmessage_v_zero ;


#define UNIXMESSAGE_BUFSIZE 2049
#define UNIXMESSAGE_AUXBUFSIZE 2049
#define UNIXMESSAGE_MAXFDS 256
#define UNIXMESSAGE_MAXREADS 32

typedef struct unixmessage_sender_s unixmessage_sender_t, *unixmessage_sender_t_ref ;
struct unixmessage_sender_s
{
  int fd ;
  stralloc data ;
  genalloc fds ; /* int */
  genalloc offsets ; /* diuint */
  unsigned int head ;
} ;
#define UNIXMESSAGE_SENDER_ZERO UNIXMESSAGE_SENDER_INIT(-1)
#define UNIXMESSAGE_SENDER_INIT(s) { .fd = (s), .data = STRALLOC_ZERO, .fds = GENALLOC_ZERO, .offsets = GENALLOC_ZERO, .head = 0 }

extern unixmessage_sender_t const unixmessage_sender_zero ;
extern void unixmessage_sender_init (unixmessage_sender_t *, int) ;
extern void unixmessage_sender_free (unixmessage_sender_t *) ;
#define unixmessage_sender_fd(b) ((b)->fd)
extern int unixmessage_sender_getfd (unixmessage_sender_t const *) gccattr_pure ;

extern int unixmessage_put_and_close (unixmessage_sender_t *, unixmessage_t const *, unsigned char const *) ;
#define unixmessage_put(b, m) unixmessage_put_and_close(b, m, unixmessage_bits_closenone)
extern int unixmessage_putv_and_close (unixmessage_sender_t *, unixmessage_v_t const *, unsigned char const *) ;
#define unixmessage_putv(b, m) unixmessage_putv_and_close(b, m, unixmessage_bits_closenone)

extern unsigned char const *const unixmessage_bits_closenone ;
extern unsigned char const *const unixmessage_bits_closeall ;

extern int unixmessage_sender_flush (unixmessage_sender_t *) ;
extern int unixmessage_sender_timed_flush (unixmessage_sender_t *, tain_t const *, tain_t *) ;
#define unixmessage_sender_timed_flush_g(sender, deadline) unixmessage_sender_timed_flush(sender, (deadline), &STAMP)


typedef struct unixmessage_receiver_s unixmessage_receiver_t, *unixmessage_receiver_t_ref ;
struct unixmessage_receiver_s
{
  buffer mainb ;
  cbuffer_t auxb ;
  unsigned int mainlen ;
  unsigned int auxlen ;
  stralloc data ;
  int fds[UNIXMESSAGE_MAXFDS] ;
  unsigned int auxw ;
} ;
#define UNIXMESSAGE_RECEIVER_ZERO { .mainb = BUFFER_ZERO, .auxb = CBUFFER_ZERO, .mainlen = 0, .auxlen = 0, .data = STRALLOC_ZERO, .fds = { -1 }, .auxw = 0 }

extern int unixmessage_receiver_init (unixmessage_receiver_t *, int, char *, unsigned int, char *, unsigned int) ;
extern void unixmessage_receiver_free (unixmessage_receiver_t *) ;
#define unixmessage_receiver_fd(b) buffer_fd(&(b)->mainb)

extern int unixmessage_receive (unixmessage_receiver_t *, unixmessage_t *) ;
extern int unixmessage_timed_receive (unixmessage_receiver_t *, unixmessage_t *, tain_t const *, tain_t *) ;
#define unixmessage_timed_receive_g(receiver, msg, deadline) unixmessage_timed_receive(receiver, msg, (deadline), &STAMP)

extern buffer_io_func_t unixmessage_read ;

typedef int unixmessage_handler_func_t (unixmessage_t const *, void *) ;
typedef unixmessage_handler_func_t *unixmessage_handler_func_t_ref ;

extern int unixmessage_handle (unixmessage_receiver_t *, unixmessage_handler_func_t *, void *) ;
extern int unixmessage_timed_handle (unixmessage_receiver_t *, unixmessage_handler_func_t *, void *, tain_t const *, tain_t *) ;
#define unixmessage_timed_handle_g(b, f, p, deadline) unixmessage_timed_handle(b, f, p, (deadline), &STAMP)

#endif
