/* ISC license. */

#ifndef UNIX_TRANSACTIONAL_H
#define UNIX_TRANSACTIONAL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <skalibs/uint64.h>
#include <skalibs/siovec.h>
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

extern unsigned int openreadnclose_at (int, char const *, char *, unsigned int) ;
extern int openslurpclose_at (int, char const *, stralloc *) ;
extern int opengetlnclose_at (int, char const *, stralloc *, int) ;

extern int openwritenclose (char const *, char const *, unsigned int) ;
extern int openwritenclose_devino (char const *, char const *, unsigned int, uint64 *, uint64 *) ;
extern int openwritenclose_tmp (char const *, char const *, unsigned int, stralloc *) ;
extern int openwritenclose_devino_tmp (char const *, char const *, unsigned int, uint64 *, uint64 *, stralloc *) ;
extern unsigned int openwritenclose_at (int, char const *, char const *, unsigned int) ;
extern unsigned int openwritevnclose_at (int, char const *, siovec_t const *, unsigned int) ;

extern int mkdir_unique (stralloc *, char const *, unsigned int) ;

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
extern int dd_close (dirdescriptor_t *) ;  /* after dd_open_read */
extern void dd_cancel (dirdescriptor_t *) ; /* after dd_open_write */
extern int dd_commit (dirdescriptor_t *) ; /* after dd_open_write */
extern int dd_commit_devino (dirdescriptor_t *, uint64 *, uint64 *) ; /* after dd_open_write */

#define dd_openreadnclose(blah, file, s, len) openreadnclose_at((blah)->fd, file, s, len)
#define dd_openslurpclose(blah, file, sa) openslurpclose_at((blah)->fd, file, sa)
#define dd_opengetlnclose(blah, file, sa, sep) opengetlnclose_at((blah)->fd, file, sa, sep)
#define dd_openwritenclose(blah, file, s, len) openwritenclose_at((blah)->fd, file, s, len)

#endif
