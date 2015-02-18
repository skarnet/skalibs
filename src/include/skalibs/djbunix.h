/* ISC license. */

#ifndef DJBUNIX_H
#define DJBUNIX_H

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <skalibs/gccattributes.h>
#include <skalibs/uint64.h>
#include <skalibs/siovec.h>
#include <skalibs/stralloc.h>
#include <skalibs/envalloc.h>
#include <skalibs/env.h>        /* compatibility */

#define DJBUNIX_FLAG_NB  0x01U
#define DJBUNIX_FLAG_COE 0x02U

extern int coe (int) ;
extern int uncoe (int) ;
extern int ndelay_on (int) ;
extern int ndelay_off (int) ;
extern int pipe_internal (int *, unsigned int) ;
#define pipenb(p) pipe_internal(p, DJBUNIX_FLAG_NB)
#define pipecoe(p) pipe_internal(p, DJBUNIX_FLAG_COE)
#define pipenbcoe(p) pipe_internal(p, DJBUNIX_FLAG_NB|DJBUNIX_FLAG_COE)
extern int fd_copy (int, int) ;
extern int fd_copy2 (int, int, int, int) ;
extern int fd_move (int, int) ;
extern int fd_move2 (int, int, int, int) ;
extern int fd_close (int) ;
extern int fd_chmod (int, unsigned int) ;
extern int fd_chown (int, unsigned int, unsigned int) ;
extern int fd_sync (int) ;
extern int fd_cat (int, int) ;
extern unsigned int fd_catn (int, int, unsigned int) ;
extern int fd_ensure_open (int, int) ;
#define fd_sanitize() (fd_ensure_open(0, 0) && fd_ensure_open(1, 1) && fd_ensure_open(2, 1))
extern int lock_ex (int) ;
extern int lock_exnb (int) ;
extern int lock_sh (int) ;
extern int lock_shnb (int) ;
extern int lock_un (int) ;
extern int open2 (char const *, unsigned int) ;
extern int open3 (char const *, unsigned int, unsigned int) ;
extern int open_read (char const *) ;
extern int open_readb (char const *) ;
extern int open_excl (char const *) ;
extern int open_append (char const *) ;
extern int open_create (char const *) ;
extern int open_trunc (char const *) ;
extern int open_write (char const *) ;
extern int socket_internal (int, int, int, unsigned int) ;
extern int socketpair_internal (int, int, int, unsigned int, int *) ;

extern int pathexec_env (char const *, char const *) ;
extern void pathexec_r (char const *const *, char const *const *, unsigned int, char const *, unsigned int) ;
extern void pathexec_r_name (char const *, char const *const *, char const *const *, unsigned int, char const *, unsigned int) ;
extern void pathexec_fromenv (char const *const *, char const *const *, unsigned int) ;
extern void execvep (char const *, char const *const *, char const *const *, char const *) ;
extern void pathexec_run (char const *, char const *const *, char const *const *) ;
extern void pathexec0_run (char const *const *, char const *const *) ;
extern void pathexec (char const *const *) ;
extern void pathexec0 (char const *const *) ;

#define prot_gid(gid) setgid(gid)
#define prot_uid(uid) setuid(uid)
extern int prot_readgroups (char const *, gid_t *, unsigned int) ;
extern int prot_grps (char const *) ;
extern int prot_setuidgid (char const *) ;

extern long seek_cur (int) ;
extern int seek_set (int, long) ;
extern int seek_end (int) ;
extern int seek_trunc (int, long) ;
#define seek_begin(fd) (seek_set((fd), 0))

extern pid_t wait_nointr (int *) ;
extern pid_t waitpid_nointr (pid_t, int *, int) ;
#define wait_pid(pid, wstat) waitpid_nointr(pid, (wstat), 0)
#define wait_nohang(wstat) waitpid_nointr(-1, (wstat), WNOHANG)
extern pid_t wait_pid_nohang (pid_t, int *) ;
extern int wait_pids_nohang (pid_t const *, unsigned int, int *) ;
#define wait_status(w) (WIFSIGNALED(w) ? 256 : WEXITSTATUS(w))
extern unsigned int wait_reap (void) ;
extern int waitn (pid_t *, unsigned int) ;
extern int waitn_reap (pid_t *, unsigned int) ;

extern pid_t doublefork (void) ;

extern int fd_chdir (int) ;

#define absolutepath(sa, s) sarealpath(sa, s)
/* extern char *realpath (char const *, char *) ; */
extern char *realpath_tmp (char const *, char *, stralloc *) ;
extern int sarealpath (stralloc *, char const *) ;
extern int sarealpath_tmp (stralloc *, char const *, stralloc *) ;
/* extern char *basename (char *) ; */
extern int sabasename (stralloc *, char const *, unsigned int) ;
/* extern char *dirname (char *) ; */
extern int sadirname (stralloc *, char const *, unsigned int) ;
extern int sagetcwd (stralloc *) ;
extern int sareadlink (stralloc *, char const *) ;
extern int sagethostname (stralloc *) ;

extern int slurp (stralloc *, int) ;
extern int openslurpclose (stralloc *, char const *) ;
extern int openreadclose (char const *, stralloc *, unsigned int) ;
extern int openreadnclose (char const *, char *, unsigned int) ;
extern int openreadfileclose (char const *, stralloc *, unsigned int) ;

#define openwritenclose_unsafe(f, s, n) openwritenclose_unsafe_internal(f, s, (n), 0, 0, 0)
#define openwritenclose_unsafe_sync(f, s, n) openwritenclose_unsafe_internal(f, s, (n), 0, 0, 1)
#define openwritenclose_unsafe_devino(f, s, n, dev, ino) openwritenclose_unsafe_internal(f, s, n, dev, (ino), 0)
#define openwritenclose_unsafe_devino_sync(f, s, n, dev, ino) openwritenclose_unsafe_internal(f, s, n, dev, (ino), 1)
extern int openwritenclose_unsafe_internal (char const *, char const *, unsigned int, uint64 *, uint64 *, int) ;

#define openwritenclose_suffix(f, s, n, t) openwritenclose_suffix_internal(f, s, n, 0, 0, 0, t)
#define openwritenclose_suffix_sync(f, s, n, t) openwritenclose_suffix_internal(f, s, n, 0, 0, 1, t)
#define openwritenclose_suffix_devino(f, s, n, t, dev, ino) openwritenclose_suffix_internal(f, s, n, dev, (ino), 0, t)
#define openwritenclose_suffix_devino_sync(f, s, n, t, dev, ino) openwritenclose_suffix_internal(f, s, n, dev, (ino), 1, t)
extern int openwritenclose_suffix_internal (char const *, char const *, unsigned int, uint64 *, uint64 *, int, char const *) ;

#define openwritevnclose_unsafe(f, v, n) openwritevnclose_unsafe_internal(f, v, (n), 0, 0, 0)
#define openwritevnclose_unsafe_sync(f, v, n) openwritevnclose_unsafe_internal(f, v, (n), 0, 0, 1)
#define openwritevnclose_unsafe_devino(f, v, n, dev, ino) openwritevnclose_unsafe_internal(f, v, n, dev, (ino), 0)
#define openwritevnclose_unsafe_devino_sync(f, v, n, dev, ino) openwritevnclose_unsafe_internal(f, v, n, dev, (ino), 1)
extern int openwritevnclose_unsafe_internal (char const *, siovec_t const *, unsigned int, uint64 *, uint64 *, int) ;

#define openwritevnclose_suffix(f, v, n, t) openwritevnclose_suffix_internal(f, v, n, 0, 0, 0, t)
#define openwritevnclose_suffix_sync(f, v, n, t) openwritevnclose_suffix_internal(f, v, n, 0, 0, 1, t)
#define openwritevnclose_suffix_devino(f, v, n, t, dev, ino) openwritevnclose_suffix_internal(f, v, n, dev, (ino), 0, t)
#define openwritevnclose_suffix_devino_sync(f, v, n, t, dev, ino) openwritevnclose_suffix_internal(f, v, n, dev, (ino), 1, t)
extern int openwritevnclose_suffix_internal (char const *, siovec_t const *, unsigned int, uint64 *, uint64 *, int, char const *) ;

extern int rm_rf (char const *) ;
extern int rm_rf_tmp (char const *, stralloc *) ;
extern int rm_rf_in_tmp (stralloc *, unsigned int) ; /* caution ! */
extern int rmstar (char const *) ;
extern int rmstar_tmp (char const *, stralloc *) ;


 /* Simple spawn functions with 0 or 1 communicating fds. */

extern pid_t child_spawn0 (char const *, char const *const *, char const *const *) ;
extern pid_t child_spawn1_pipe (char const *, char const *const *, char const *const *, int *, int) ;
extern pid_t child_spawn1_socket (char const *, char const *const *, char const *const *, int *) ;


 /*
    Unified function to fork a child with communication canals.
    * uses posix_spawn() if available, else uses fork+exec
    * requests n (the last arg) communication fds between parent and child
    * if n=1, equivalent to child_spawn1_pipe; child writes, parent reads.
    * if n>=2, the fds are pipes, parent reads on even and writes on odd.
 */

extern pid_t child_spawn (char const *, char const *const *, char const *const *, int *, unsigned int) ;

#endif
