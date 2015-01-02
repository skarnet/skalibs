/* ISC license. */

#ifndef SKACLIENT_H
#define SKACLIENT_H

#include <sys/types.h>
#include <skalibs/kolbak.h>
#include <skalibs/siovec.h>
#include <skalibs/tai.h>
#include <skalibs/uint32.h>
#include <skalibs/unixmessage.h>


 /* Server part */

extern int skaclient_server_ack (unixmessage_t const *, unixmessage_sender_t *, unixmessage_sender_t *, char const *, unsigned int, char const *, unsigned int) ;
extern int skaclient_server_bidi_ack (unixmessage_t const *, unixmessage_sender_t *, unixmessage_sender_t *, unixmessage_receiver_t *, char *, unsigned int, char *, unsigned int, char const *, unsigned int, char const *, unsigned int) ;
extern int skaclient_server_init (unixmessage_receiver_t *, unixmessage_sender_t *, unixmessage_sender_t *, char const *, unsigned int, char const *, unsigned int, tain_t const *, tain_t *) ;
#define skaclient_server_init_g(in, out, asyncout, before, beforelen, after, afterlen, deadline) skaclient_server_init(in, out, asyncout, before, beforelen, after, afterlen, (deadline), &STAMP)
#define skaclient_server_01x_init(before, beforelen, after, afterlen, deadline, stamp) skaclient_server_init(unixmessage_receiver_0, unixmessage_sender_1, unixmessage_sender_x, before, beforelen, after, afterlen, deadline, stamp)
#define skaclient_server_01x_init_g(before, beforelen, after, afterlen, deadline) skaclient_server_01x_init(before, beforelen, after, afterlen, (deadline), &STAMP)


 /* Client part: the rest of this file */

#define SKACLIENT_KOLBAK_SIZE 64
#define SKACLIENT_OPTION_WAITPID 0x00000001U

#define skaclient_buffer_type(bufsn, auxbufsn, bufan, auxbufan, qlen) struct { char bufs[bufsn] ; char auxbufs[auxbufsn] ; char bufa[bufan] ; char auxbufa[auxbufan] ; kolbak_closure_t q[qlen] ; }
typedef skaclient_buffer_type(UNIXMESSAGE_BUFSIZE, UNIXMESSAGE_AUXBUFSIZE, UNIXMESSAGE_BUFSIZE, UNIXMESSAGE_AUXBUFSIZE, SKACLIENT_KOLBAK_SIZE) skaclient_buffer_t, *skaclient_buffer_t_ref ;


 /* Callback data for init */

typedef struct skaclient_cbdata_s skaclient_cbdata_t, *skaclient_cbdata_t_ref ;
struct skaclient_cbdata_s
{
  unixmessage_receiver_t *asyncin ;
  unixmessage_sender_t *asyncout ;
  char const *after ;
  unsigned int afterlen ;
} ;


 /* User structure */

typedef struct skaclient_s skaclient_t, *skaclient_t_ref ;
struct skaclient_s
{
  unixmessage_receiver_t syncin ;
  unixmessage_sender_t syncout ;
  kolbak_queue_t kq ;
  unixmessage_receiver_t asyncin ;
  unixmessage_sender_t asyncout ;
  pid_t pid ;
  uint32 options ;
} ;
#define SKACLIENT_ZERO { .syncin = UNIXMESSAGE_RECEIVER_ZERO, .syncout = UNIXMESSAGE_SENDER_ZERO, .kq = KOLBAK_QUEUE_ZERO, .asyncin = UNIXMESSAGE_RECEIVER_ZERO, .asyncout = UNIXMESSAGE_SENDER_ZERO, .pid = 0, .options = 0 }
extern skaclient_t const skaclient_zero ;

extern void skaclient_end (skaclient_t *) ;

extern int skaclient_start_async (skaclient_t *, char *, unsigned int, char *, unsigned int, char *, unsigned int, char *, unsigned int, kolbak_closure_t *, unsigned int, char const *, char const *, unsigned int, char const *, unsigned int, skaclient_cbdata_t *) ;
#define skaclient_start_async_b(a, sb, path, before, beforelen, after, afterlen, blah) skaclient_start_async(a, (sb)->bufs, sizeof((sb)->bufs), (sb)->auxbufs, sizeof((sb)->auxbufs), (sb)->bufa, sizeof((sb)->bufa), (sb)->auxbufa, sizeof((sb)->auxbufa), (sb)->q, sizeof((sb)->q), path, before, beforelen, after, afterlen, blah)
extern int skaclient_startf_async (skaclient_t *, char *, unsigned int, char *, unsigned int, char *, unsigned int, char *, unsigned int, kolbak_closure_t *, unsigned int, char const *, char const *const *, char const *const *, uint32, char const *, unsigned int, char const *, unsigned int, skaclient_cbdata_t *) ;
#define skaclient_startf_async_b(a, sb, prog, argv, envp, options, before, beforelen, after, afterlen, blah) skaclient_startf_async(a, (sb)->bufs, sizeof((sb)->bufs), (sb)->auxbufs, sizeof((sb)->auxbufs), (sb)->bufa, sizeof((sb)->bufa), (sb)->auxbufa, sizeof((sb)->auxbufa), (sb)->q, sizeof((sb)->q) / sizeof(kolbak_closure_t), prog, argv, envp, options, before, beforelen, after, afterlen, blah)

extern int skaclient_start (skaclient_t *, char *, unsigned int, char *, unsigned int, char *, unsigned int, char *, unsigned int, kolbak_closure_t *, unsigned int, char const *, char const *, unsigned int, char const *, unsigned int, tain_t const *, tain_t *) ;
#define skaclient_start_b(a, sb, path, before, beforelen, after, afterlen, deadline, stamp) skaclient_start(a, (sb)->bufs, sizeof((sb)->bufs), (sb)->auxbufs, sizeof((sb)->auxbufs), (sb)->bufa, sizeof((sb)->bufa), (sb)->auxbufa, sizeof((sb)->auxbufa), (sb)->q, sizeof((sb)->q) / sizeof(kolbak_closure_t), path, before, beforelen, after, afterlen, deadline, stamp)
#define skaclient_start_g(a, bufs, bufsn, auxbufs, auxbufsn, bufa, bufan, auxbufa, auxbufan, q, qlen, path, before, beforelen, after, afterlen, deadline)  skaclient_start(a, bufs, bufsn, auxbufs, auxbufsn, bufa, bufan, auxbufa, auxbufan, q, qlen, path, before, beforelen, after, afterlen, (deadline), &STAMP)
#define skaclient_start_b_g(a, sb, path, before, beforelen, after, afterlen, deadline) skaclient_start_b(a, sb, path, before, beforelen, after, afterlen, (deadline), &STAMP)

extern int skaclient_startf (skaclient_t *, char *, unsigned int, char *, unsigned int, char *, unsigned int, char *, unsigned int, kolbak_closure_t *, unsigned int, char const *, char const *const *, char const *const *, uint32, char const *, unsigned int, char const *, unsigned int, tain_t const *, tain_t *) ;
#define skaclient_startf_b(a, sb, prog, argv, envp, options, before, beforelen, after, afterlen, deadline, stamp) skaclient_startf(a, (sb)->bufs, sizeof((sb)->bufs), (sb)->auxbufs, sizeof((sb)->auxbufs), (sb)->bufa, sizeof((sb)->bufa), (sb)->auxbufa, sizeof((sb)->auxbufa), (sb)->q, sizeof((sb)->q) / sizeof(kolbak_closure_t), prog, argv, envp, options, before, beforelen, after, afterlen, deadline, stamp)
#define skaclient_startf_g(a, bufs, bufsn, auxbufs, auxbufsn, bufa, bufan, auxbufa, auxbufan, q, qlen, prog, argv, envp, options, before, beforelen, after, afterlen, deadline) skaclient_startf(a, bufs, bufsn, auxbufs, auxbufsn, bufa, bufan, auxbufa, auxbufan, q, qlen, prog, argv, envp, options, before, beforelen, after, afterlen, (deadline), &STAMP)
#define skaclient_startf_b_g(a, sb, prog, argv, envp, options, before, beforelen, after, afterlen, deadline) skaclient_startf_b(a, sb, prog, argv, envp, options, before, beforelen, after, afterlen, (deadline), &STAMP)

extern int skaclient_putmsg_and_close (skaclient_t *, unixmessage_t const *, unsigned char const *, unixmessage_handler_func_t *, void *) ;
#define skaclient_putmsg(a, m, cb, result) skaclient_putmsg_and_close(a, m, unixmessage_bits_closenone, cb, result)
extern int skaclient_putmsgv_and_close (skaclient_t *, unixmessage_v_t const *, unsigned char const *, unixmessage_handler_func_t *, void *) ;
#define skaclient_putmsgv(a, m, cb, result) skaclient_putmsgv_and_close(a, m, unixmessage_bits_closenone, cb, result)

extern int skaclient_put (skaclient_t *, char const *, unsigned int, unixmessage_handler_func_t *, void *) ;
extern int skaclient_putv (skaclient_t *, siovec_t const *, unsigned int, unixmessage_handler_func_t *, void *) ;

extern int skaclient_sendmsg_and_close (skaclient_t *, unixmessage_t const *, unsigned char const *, unixmessage_handler_func_t *, void *, tain_t const *, tain_t *) ;
#define skaclient_sendmsg_and_close_g(a, m, bits, cb, result, deadline) skaclient_sendmsg_and_close(a, m, bits, cb, result, (deadline), &STAMP)
#define skaclient_sendmsg(a, m, cb, result, deadline, stamp) skaclient_sendmsg_and_close(a, m, unixmessage_bits_closenone, cb, result, deadline, stamp)
#define skaclient_sendmsg_g(a, m, cb, result, deadline) skaclient_sendmsg(a, m, cb, result, (deadline), &STAMP)

extern int skaclient_sendmsgv_and_close (skaclient_t *, unixmessage_v_t const *, unsigned char const *, unixmessage_handler_func_t *, void *, tain_t const *, tain_t *) ;
#define skaclient_sendmsgv_and_close_g(a, m, bits, cb, result, deadline) skaclient_sendmsgv_and_close(a, m, bits, cb, result, (deadline), &STAMP)
#define skaclient_sendmsgv(a, m, cb, result, deadline, stamp) skaclient_sendmsgv_and_close(a, m, unixmessage_bits_closenone, cb, result, deadline, stamp)
#define skaclient_sendmsgv_g(a, m, cb, result, deadline) skaclient_sendmsgv(a, m, cb, result, (deadline), &STAMP)

extern int skaclient_send (skaclient_t *, char const *, unsigned int, unixmessage_handler_func_t *, void *, tain_t const *, tain_t *) ;
#define skaclient_send_g(a, s, len, cb, result, deadline) skaclient_send(a, s, len, cb, result, (deadline), &STAMP)
extern int skaclient_sendv (skaclient_t *, siovec_t const *, unsigned int, unixmessage_handler_func_t *, void *, tain_t const *, tain_t *) ;
#define skaclient_sendv_g(a, v, vlen, cb, result, deadline) skaclient_sendv(a, v, vlen, cb, result, (deadline), &STAMP)

#define skaclient_sfd(a) unixmessage_receiver_fd(&(a)->syncin)
#define skaclient_flush(a) unixmessage_sender_flush(&(a)->syncout)
#define skaclient_timed_flush(a, deadline, stamp) unixmessage_sender_timed_flush(&(a)->syncout, deadline, stamp)
#define skaclient_timed_flush_g(a, deadline) skaclient_timed_flush(a, (deadline), &STAMP)

#define skaclient_supdate(a) unixmessage_handle(&(a)->syncin, (unixmessage_handler_func_t *)&kolbak_call, &(a)->kq)
#define skaclient_timed_supdate(a, deadline, stamp) unixmessage_timed_handle(&(a)->syncin, (unixmessage_handler_func_t *)&kolbak_call, &(a)->kq, deadline, stamp)
#define skaclient_timed_supdate_g(a, deadline) skaclient_timed_supdate(a, (deadline), &STAMP)

extern int skaclient_syncify (skaclient_t *, tain_t const *, tain_t *) ;

#define skaclient_fd(a) skaclient_afd(a)
#define skaclient_afd(a) unixmessage_receiver_fd(&(a)->asyncin)
#define skaclient_update(a, f, p) skaclient_aupdate(a, f, p)
#define skaclient_aupdate(a, f, p) unixmessage_handle(&(a)->asyncin, f, p)

extern unixmessage_handler_func_t skaclient_default_cb ;

#endif
