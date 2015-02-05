/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/unirandom.h>
#include <skalibs/unirandomdev.h>

int unirandomdev_sinit (union unirandominfo *u, char const *file)
{
  register int fd = open_read(file) ;
  if (fd < 0) return 0 ;
  if (coe(fd) < 0)
  {
    register int e = errno ;
    fd_close(fd) ;
    errno = e ;
    return 0 ;
  }
  buffer_init(&u->device.b, &fd_readsv, fd, u->device.buf, RANDOMBUF_BUFSIZE) ;
  u->device.nb = 1 ;
  return 1 ;
}

int unirandomdev_finish (union unirandominfo *u)
{
  return fd_close(buffer_fd(&u->device.b)) < 0 ;
}

static unsigned int unirandomdev_read (union unirandominfo *u, char *s, unsigned int n, unsigned int h)
{
  unsigned int w = 0 ;
  if (u->device.nb != h)
  {
    if ((h ? ndelay_on(buffer_fd(&u->device.b)) : ndelay_off(buffer_fd(&u->device.b))) < 0) return 0 ;
    u->device.nb = h ;
  }
  buffer_getall(&u->device.b, s, n, &w) ;
  return w ;
}

unsigned int unirandomdev_readb (union unirandominfo *u, char *s, unsigned int n)
{
  return unirandomdev_read(u, s, n, 0) ;
}

unsigned int unirandomdev_readnb (union unirandominfo *u, char *s, unsigned int n)
{
  return unirandomdev_read(u, s, n, 1) ;
}
