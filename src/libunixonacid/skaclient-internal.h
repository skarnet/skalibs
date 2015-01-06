/* ISC license. */

#ifndef SKACLIENT_INTERNAL_H
#define SKACLIENT_INTERNAL_H

#include <skalibs/kolbak.h>
#include <skalibs/unixmessage.h>
#include <skalibs/skaclient.h>

extern int skaclient_init (skaclient_t *, int, char *, unsigned int, char *, unsigned int, char *, unsigned int, char *, unsigned int, kolbak_closure_t *, unsigned int, char const *, unsigned int) ;
extern int skaclient_start_cb (unixmessage_t const *, skaclient_cbdata_t *) ;

#endif
