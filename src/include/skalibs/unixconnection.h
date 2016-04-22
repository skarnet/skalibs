 /* ISC license. */

#ifndef UNIXCONNECTION_H
#define UNIXCONNECTION_H

#include <skalibs/unixmessage.h>

typedef struct unixconnection_s unixconnection_t, *unixconnection_t_ref ;
struct unixconnection_s
{
  unixmessage_sender_t out ;
  unixmessage_receiver_t in ;
  char mainbuf[UNIXMESSAGE_BUFSIZE] ;
  char auxbuf[UNIXMESSAGE_AUXBUFSIZE] ;
} ;
#define UNIXCONNECTION_ZERO { .out = UNIXMESSAGE_SENDER_ZERO, .in = UNIXMESSAGE_RECEIVER_ZERO }
extern unixconnection_t const unixconnection_zero ;

extern void unixconnection_init (unixconnection_t *, int, int) ;
extern void unixconnection_init_withclosecb (unixconnection_t *, int, int, unixmessage_sender_closecb_func_t_ref, void *) ;
extern void unixconnection_free (unixconnection_t *) ;

#define unixconnection_flush(io) unixmessage_sender_flush(&(io)->out)
#define unixconnection_receive(io, m) unixmessage_receive(&(io)->in, m)

#endif
