/* ISC license. */

#ifndef SKACLIENT_INTERNAL_H
#define SKACLIENT_INTERNAL_H

#include <sys/types.h>
#include <skalibs/kolbak.h>
#include <skalibs/unixmessage.h>
#include <skalibs/skaclient.h>

extern int skaclient_init (skaclient_t *, int, char *, size_t, char *, size_t, char *, size_t, char *, size_t, kolbak_closure_t *, size_t, char const *, size_t) ;
extern int skaclient_start_cb (unixmessage_t const *, skaclient_cbdata_t *) ;

#endif
