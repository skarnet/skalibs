/* ISC license. */

#ifndef WEBIPC_H
#define WEBIPC_H

 /*
    UNIX domain socket functions.
    "web" stands for William E. Baxter, the original author, who kindly
    permitted me to modify and release his code as a part of skalibs.
    It has nothing to do with the World Wide Web.
 */

#define IPCPATH_MAX 107

#include <sys/types.h>
#include <skalibs/getpeereid.h>
#include <skalibs/tai.h>
#include <skalibs/djbunix.h>

#define ipc_stream() ipc_stream_nb()
#define ipc_stream_b() ipc_stream_internal(0)
#define ipc_stream_nb() ipc_stream_internal(DJBUNIX_FLAG_NB)
#define ipc_stream_coe() ipc_stream_internal(DJBUNIX_FLAG_COE)
#define ipc_stream_nbcoe() ipc_stream_internal(DJBUNIX_FLAG_NB|DJBUNIX_FLAG_COE)
extern int ipc_stream_internal (unsigned int) ;

#define ipc_datagram() ipc_datagram_nb()
#define ipc_datagram_b() ipc_datagram_internal(0)
#define ipc_datagram_nb() ipc_datagram_internal(DJBUNIX_FLAG_NB)
#define ipc_datagram_coe() ipc_datagram_internal(DJBUNIX_FLAG_COE)
#define ipc_datagram_nbcoe() ipc_datagram_internal(DJBUNIX_FLAG_NB|DJBUNIX_FLAG_COE)
extern int ipc_datagram_internal (unsigned int) ;

#define ipc_pair(sv) ipc_pair_nb(sv)
#define ipc_pair_b(sv) ipc_pair_internal((sv), 0)
#define ipc_pair_nb(sv) ipc_pair_internal((sv), DJBUNIX_FLAG_NB)
#define ipc_pair_coe(sv) ipc_pair_internal((sv), DJBUNIX_FLAG_COE)
#define ipc_pair_nbcoe(sv) ipc_pair_internal((sv), DJBUNIX_FLAG_NB|DJBUNIX_FLAG_COE)
extern int ipc_pair_internal (int *, unsigned int) ;

extern int ipc_bind (int, char const *) ;
extern int ipc_bind_reuse (int, char const *) ;
extern int ipc_listen (int, int) ;

#define ipc_accept(s, path, len, trunc) ipc_accept_internal(s, path, len, (trunc), 0)
#define ipc_accept_nb(s, path, len, trunc) ipc_accept_internal(s, path, len, (trunc), DJBUNIX_FLAG_NB)
#define ipc_accept_coe(s, path, len, trunc) ipc_accept_internal(s, path, len, (trunc), DJBUNIX_FLAG_COE)
#define ipc_accept_nbcoe(s, path, len, trunc) ipc_accept_internal(s, path, len, (trunc), DJBUNIX_FLAG_NB|DJBUNIX_FLAG_COE)
extern int ipc_accept_internal (int, char *, size_t, int *, unsigned int) ;

#define ipc_eid getpeereid
extern int ipc_local (int, char *, size_t, int *) ;

extern int ipc_connect (int, char const *) ;
extern int ipc_connected (int) ;
extern int ipc_timed_connect (int, char const *, tain_t const *, tain_t *) ;
#define ipc_timed_connect_g(fd, path, deadline) ipc_timed_connect(fd, path, (deadline), &STAMP)

extern ssize_t ipc_send (int, char const *, size_t, char const *) ;
extern ssize_t ipc_recv (int, char *, size_t, char *) ;

#endif
