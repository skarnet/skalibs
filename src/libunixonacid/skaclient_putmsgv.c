/* ISC license. */

#include <skalibs/kolbak.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>

int skaclient_putmsgv_and_close (skaclient_t *a, unixmessage_v_t const *m, unsigned char const *bits, unixmessage_handler_func_t_ref cb, void *result)
{
  if (!kolbak_enqueue(&a->kq, cb, result)) return 0 ;
  if (!unixmessage_putv_and_close(&a->syncout, m, bits))
  {
    kolbak_unenqueue(&a->kq) ;
    return 0 ;
  }
  return 1 ;
}
