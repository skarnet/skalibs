/* ISC license. */

#ifndef SKACLIENT_INTERNAL_H
#define SKACLIENT_INTERNAL_H

#include <skalibs/kolbak.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>

extern int skaclient_init (skaclient_t *, int, char *, unsigned int, char *, unsigned int, char *, unsigned int, char *, unsigned int, kolbak_closure_t *, unsigned int, char const *, unsigned int) ;
extern int skaclient_start_async_th (skaclient_t *, char *, unsigned int, char *, unsigned int, char *, unsigned int, char *, unsigned int, kolbak_closure_t *, unsigned int, char const *, char const *, unsigned int) ;
extern int skaclient_startf_async_th (skaclient_t *, char *, unsigned int, char *, unsigned int, char *, unsigned int, char *, unsigned int, kolbak_closure_t *, unsigned int, char const *, char const *const *, char const *const *, uint32, char const *, unsigned int) ;
extern int skaclient_start_cb (unixmessage_t const *, skaclient_cbdata_t *) ;

#endif
