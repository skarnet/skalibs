/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASPTHREAD

#include <string.h>
#include <pthread.h>

#include <skalibs/functypes.h>

struct spawndata_s
{
  pthread_cond_t cond ;
  pthread_mutex_t mutex ;
  generic_func_ref start ;
  void *arg ;
  size_t argsize ;
} ;

static void *bootstrap (void *arg)
{
  struct spawndata_s *data = arg ;
  char newarg[data->argsize ? data->argsize : 1] ;
  memcpy(newarg, data->arg, data->argsize) ;
  int e = pthread_mutex_lock(&data->mutex) ;
  if (e) return 0 ;
  pthread_cond_signal(&data->cond) ;
  pthread_mutex_unlock(&data->mutex) ;
  return (*data->start)(newarg) ;
}

int pthread_create_flat (pthread_t *restrict th, pthread_attr_t const *restrict attr, generic_func_ref start, void *restrict arg, size_t argsize)
{
  struct spawndata_s data =
  {
    .cond = PTHREAD_COND_INITIALIZER,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .start = start,
    .arg = arg,
    .argsize = argsize
  } ;
  pthread_t tth ;
  int e = pthread_mutex_lock(&data.mutex) ;
  if (e) return e ;
  e = pthread_create(&tth, attr, &bootstrap, &data) ;
  if (e) return e ;
  e = pthread_cond_wait(&data.cond, &data.mutex) ;
  if (e) pthread_cancel(tth) ; else *th = tth ;
  pthread_mutex_unlock(&data.mutex) ;
  pthread_cond_destroy(&data.cond) ;
  pthread_mutex_destroy(&data.mutex) ;
  return e ;
}

#endif
