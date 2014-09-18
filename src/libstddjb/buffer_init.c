/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>

int buffer_init_aux (buffer *b, buffer_io_func_t *op, int fd, char *s, unsigned int len, void *aux)
{
  if (!cbuffer_init(&b->c, s, len)) return 0 ;
  b->fd = fd ;
  b->op = op ;
  b->aux = aux ;
  return 1 ;
}
