/* ISC license. */

#ifndef UNIX_TRANSACTIONAL_H
#define UNIX_TRANSACTIONAL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <skalibs/uint64.h>
#include <skalibs/stralloc.h>

 /* Transactional/reliable filesystem operations */

extern int open2_at (int, char const *, int) ;
extern int open3_at (int, char const *, int, unsigned int) ;

extern int opengetlnclose (char const *, stralloc *, int) ;

extern int open_readat (int, char const *) ;
extern int open_readatb (int, char const *) ;
extern int open_writeat (int, char const *) ;
extern int open_writeatb (int, char const *) ;
extern int open_truncat (int, char const *) ;
extern int open_truncatb (int, char const *) ;
extern int open_appendat (int, char const *) ;
extern int open_appendatb (int, char const *) ;

extern int stat_at (int, char const *, struct stat *) ;
extern int lstat_at (int, char const *, struct stat *) ;

extern size_t openreadnclose_at (int, char const *, char *, size_t) ;
extern int openslurpclose_at (int, char const *, stralloc *) ;
extern int opengetlnclose_at (int, char const *, stralloc *, int) ;

extern size_t openwritenclose_at (int, char const *, char const *, size_t) ;
extern size_t openwritevnclose_at (int, char const *, struct iovec const *, unsigned int) ;

extern int mkdir_unique (stralloc *, char const *, unsigned int) ;
extern int atomic_rm_rf (char const *) ;
extern int atomic_rm_rf_tmp (char const *, stralloc *) ;


typedef struct dirdescriptor_s dirdescriptor_t, *dirdescriptor_t_ref ;
struct dirdescriptor_s
{
  int fd ;
  char const *lnkfn ;
  stralloc new ;
} ;

#define DIRDESCRIPTOR_ZERO { .fd = 0, .lnkfn = 0, .new = STRALLOC_ZERO }

extern int dd_open_read (dirdescriptor_t *, char const *) ;
extern int dd_open_write (dirdescriptor_t *, char const *, unsigned int) ;
extern void dd_close (dirdescriptor_t *) ;  /* after dd_open_read */
extern void dd_cancel (dirdescriptor_t *) ; /* after dd_open_write */
extern int dd_commit (dirdescriptor_t *) ; /* after dd_open_write */
extern int dd_commit_devino (dirdescriptor_t *, dev_t *, ino_t *) ; /* after dd_open_write */

#define dd_openreadnclose(blah, file, s, len) openreadnclose_at((blah)->fd, file, s, len)
#define dd_openslurpclose(blah, file, sa) openslurpclose_at((blah)->fd, file, sa)
#define dd_opengetlnclose(blah, file, sa, sep) opengetlnclose_at((blah)->fd, file, sa, sep)
#define dd_openwritenclose(blah, file, s, len) openwritenclose_at((blah)->fd, file, s, len)

#endif
