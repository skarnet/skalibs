/* ISC license. */

#ifndef DJBUNIX_H
#define DJBUNIX_H

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <skalibs/gccattributes.h>
#include <skalibs/stralloc.h>
#include <skalibs/envalloc.h>
#include <skalibs/posixplz.h>

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
extern void fd_close (int) ;
extern int fd_chmod (int, unsigned int) ;
extern int fd_chown (int, uid_t, gid_t) ;
extern int fd_sync (int) ;
extern int fd_cat (int, int) ;
extern size_t fd_catn (int, int, size_t) ;
extern int fd_ensure_open (int, int) ;
#define fd_sanitize() (fd_ensure_open(0, 0) && fd_ensure_open(1, 1) && fd_ensure_open(2, 1))
extern int lock_ex (int) ;
extern int lock_exnb (int) ;
extern int lock_sh (int) ;
extern int lock_shnb (int) ;
extern int lock_un (int) ;
extern void lock_unx (int) ;
extern int open2 (char const *, unsigned int) ;
extern int open3 (char const *, unsigned int, unsigned int) ;
extern int open_read (char const *) ;
extern int openb_read (char const *) ;
extern int open_readb (char const *) ;
extern int open_excl (char const *) ;
extern int open_append (char const *) ;
extern int open_create (char const *) ;
extern int open_trunc (char const *) ;
extern int open_write (char const *) ;
extern int socket_internal (int, int, int, unsigned int) ;
extern int socketpair_internal (int, int, int, unsigned int, int *) ;

extern int pathexec_env (char const *, char const *) ;
extern void pathexec_r (char const *const *, char const *const *, size_t, char const *, size_t) ;
extern void pathexec_r_name (char const *, char const *const *, char const *const *, size_t, char const *, size_t) ;
extern void pathexec_fromenv (char const *const *, char const *const *, size_t) ;
extern void pathexec_run (char const *, char const *const *, char const *const *) ;
extern void pathexec0_run (char const *const *, char const *const *) ;
extern void pathexec (char const *const *) ;
extern void pathexec0 (char const *const *) ;

extern void xpathexec_r (char const *const *, char const *const *, size_t, char const *, size_t) gccattr_noreturn ;
extern void xpathexec_r_name (char const *, char const *const *, char const *const *, size_t, char const *, size_t) gccattr_noreturn ;
extern void xpathexec_fromenv (char const *const *, char const *const *, size_t) gccattr_noreturn ;
extern void xexecvep (char const *, char const *const *, char const *const *, char const *) gccattr_noreturn ;
extern void xpathexec_run (char const *, char const *const *, char const *const *) gccattr_noreturn ;
extern void xpathexec0_run (char const *const *, char const *const *) gccattr_noreturn ;
extern void xpathexec (char const *const *) gccattr_noreturn ;
extern void xpathexec0 (char const *const *) gccattr_noreturn ;

extern pid_t wait_nointr (int *) ;
extern pid_t waitpid_nointr (pid_t, int *, int) ;
#define wait_pid(pid, wstat) waitpid_nointr(pid, (wstat), 0)
#define wait_nohang(wstat) waitpid_nointr(-1, (wstat), WNOHANG)
extern pid_t wait_pid_nohang (pid_t, int *) ;
extern int wait_pids_nohang (pid_t const *, unsigned int, int *) ;
#define wait_status(w) (WIFSIGNALED(w) ? 256 + WTERMSIG(w) : WEXITSTATUS(w))
#define wait_estatus(w) (WIFSIGNALED(w) ? 128 + WTERMSIG(w) : WEXITSTATUS(w) >= 128 ? 128 : WEXITSTATUS(w))
extern unsigned int wait_reap (void) ;
extern int waitn (pid_t *, unsigned int) ;
extern int waitn_reap (pid_t *, unsigned int) ;

extern int fd_chdir (int) ;

extern int sarealpath (stralloc *, char const *) ;
extern int sabasename (stralloc *, char const *, size_t) ;
extern int sadirname (stralloc *, char const *, size_t) ;
extern int sagetcwd (stralloc *) ;
extern int sareadlink (stralloc *, char const *) ;
extern int sagethostname (stralloc *) ;

extern int slurp (stralloc *, int) ;
extern int openslurpclose (stralloc *, char const *) ;
extern ssize_t openreadnclose (char const *, char *, size_t) ;
extern ssize_t openreadnclose_nb (char const *, char *, size_t) ;
extern int openreadfileclose (char const *, stralloc *, size_t) ;

#define writenclose_unsafe(fd, s, n) writenclose_unsafe_internal(fd, s, (n), 0, 0, 0)
#define writenclose_unsafe_sync(fd, s, n) writenclose_unsafe_internal(fd, s, (n), 0, 0, 1)
#define writenclose_unsafe_devino(fd, s, n, dev, ino) writenclose_unsafe_internal(fd, s, n, dev, (ino), 0)
#define writenclose_unsafe_devino_sync(fd, s, n, dev, ino) writenclose_unsafe_internal(fd, s, n, dev, (ino), 1)
extern int writenclose_unsafe_internal (int, char const *, size_t, dev_t *, ino_t *, int) ;

#define openwritenclose_unsafe(f, s, n) openwritenclose_unsafe_internal(f, s, (n), 0, 0, 0)
#define openwritenclose_unsafe_sync(f, s, n) openwritenclose_unsafe_internal(f, s, (n), 0, 0, 1)
#define openwritenclose_unsafe_devino(f, s, n, dev, ino) openwritenclose_unsafe_internal(f, s, n, dev, (ino), 0)
#define openwritenclose_unsafe_devino_sync(f, s, n, dev, ino) openwritenclose_unsafe_internal(f, s, n, dev, (ino), 1)
extern int openwritenclose_unsafe_internal (char const *, char const *, size_t, dev_t *, ino_t *, int) ;

#define openwritenclose_suffix(f, s, n, t) openwritenclose_suffix_internal(f, s, n, 0, 0, 0, t)
#define openwritenclose_suffix_sync(f, s, n, t) openwritenclose_suffix_internal(f, s, n, 0, 0, 1, t)
#define openwritenclose_suffix_devino(f, s, n, t, dev, ino) openwritenclose_suffix_internal(f, s, n, dev, (ino), 0, t)
#define openwritenclose_suffix_devino_sync(f, s, n, t, dev, ino) openwritenclose_suffix_internal(f, s, n, dev, (ino), 1, t)
extern int openwritenclose_suffix_internal (char const *, char const *, size_t, dev_t *, ino_t *, int, char const *) ;

#define openwritenclose(f, s, n) openwritenclose_internal(f, s, (n), 0, 0, 0)
#define openwritenclose_sync(f, s, n) openwritenclose_internal(f, s, (n), 0, 0, 1)
#define openwritenclose_devino(f, s, n, dev, ino) openwritenclose_internal(f, s, n, dev, (ino), 0)
#define openwritenclose_devino_sync(f, s, n, dev, ino) openwritenclose_internal(f, s, n, dev, (ino), 1)
extern int openwritenclose_internal (char const *, char const *, size_t, dev_t *, ino_t *, int) ;

#define writenvclose_unsafe(fd, v, n) writevnclose_unsafe_internal(fd, v, (n), 0, 0, 0)
#define writevnclose_unsafe_sync(fd, v, n) writevnclose_unsafe_internal(fd, v, (n), 0, 0, 1)
#define writevnclose_unsafe_devino(fd, v, n, dev, ino) writevnclose_unsafe_internal(fd, v, n, dev, (ino), 0)
#define writevnclose_unsafe_devino_sync(fd, v, n, dev, ino) writevnclose_unsafe_internal(fd, v, n, dev, (ino), 1)
extern int writevnclose_unsafe_internal (int, struct iovec const *, unsigned int, dev_t *, ino_t *, int) ;

#define openwritevnclose_unsafe(f, v, n) openwritevnclose_unsafe_internal(f, v, (n), 0, 0, 0)
#define openwritevnclose_unsafe_sync(f, v, n) openwritevnclose_unsafe_internal(f, v, (n), 0, 0, 1)
#define openwritevnclose_unsafe_devino(f, v, n, dev, ino) openwritevnclose_unsafe_internal(f, v, n, dev, (ino), 0)
#define openwritevnclose_unsafe_devino_sync(f, v, n, dev, ino) openwritevnclose_unsafe_internal(f, v, n, dev, (ino), 1)
extern int openwritevnclose_unsafe_internal (char const *, struct iovec const *, unsigned int, dev_t *, ino_t *, int) ;

#define openwritevnclose_suffix(f, v, n, t) openwritevnclose_suffix_internal(f, v, n, 0, 0, 0, t)
#define openwritevnclose_suffix_sync(f, v, n, t) openwritevnclose_suffix_internal(f, v, n, 0, 0, 1, t)
#define openwritevnclose_suffix_devino(f, v, n, t, dev, ino) openwritevnclose_suffix_internal(f, v, n, dev, (ino), 0, t)
#define openwritevnclose_suffix_devino_sync(f, v, n, t, dev, ino) openwritevnclose_suffix_internal(f, v, n, dev, (ino), 1, t)
extern int openwritevnclose_suffix_internal (char const *, struct iovec const *, unsigned int, dev_t *, ino_t *, int, char const *) ;

#define openwritevnclose(f, v, n) openwritevnclose_internal(f, v, (n), 0, 0, 0)
#define openwritevnclose_sync(f, v, n) openwritevnclose_internal(f, v, (n), 0, 0, 1)
#define openwritevnclose_devino(f, v, n, dev, ino) openwritevnclose_internal(f, v, n, dev, (ino), 0)
#define openwritevnclose_devino_sync(f, v, n, dev, ino) openwritevnclose_internal(f, v, n, dev, (ino), 1)
extern int openwritevnclose_internal (char const *, struct iovec const *, unsigned int, dev_t *, ino_t *, int) ;

extern int rm_rf (char const *) ;
extern int rm_rf_tmp (char const *, stralloc *) ;
extern int rm_rf_in_tmp (stralloc *, size_t) ; /* caution ! */
extern int rmstar (char const *) ;
extern int rmstar_tmp (char const *, stralloc *) ;

extern int filecopy_unsafe (char const *, char const *, unsigned int) ;
extern int filecopy_suffix (char const *, char const *, unsigned int, char const *) ;
extern int hiercopy (char const *, char const *) ;
extern int hiercopy_tmp (char const *, char const *, stralloc *) ;


 /* Simple spawn functions with 0 or 1 communicating fds. */

extern pid_t child_spawn0 (char const *, char const *const *, char const *const *) ;
extern pid_t child_spawn1_pipe (char const *, char const *const *, char const *const *, int *, int) ;
extern pid_t child_spawn1_socket (char const *, char const *const *, char const *const *, int *) ;


 /*
    Spawn function with 2 communicating pipes. The int * points to 2 fds.
    Input: fds[0] and fds[1] are the fds to move the pipes to in the child.
    Output: fds[0] and fds[1] contain the pipes to the child.
 */

extern pid_t child_spawn2 (char const *, char const *const *, char const *const *, int *) ;


 /*
    Same, with an additional pipe from the child to the parent.
    The int * points to 3 fds.
    The additional fd# is available to the child in the defined env variable.
 */

#define SKALIBS_CHILD_SPAWN_FDS_ENVVAR "SKALIBS_CHILD_SPAWN_FDS"

extern pid_t child_spawn3 (char const *, char const *const *, char const *const *, int *) ;


 /*
    Generalization of the previous functions.
    * uses posix_spawn() if available, else uses fork+exec
    * requests n (the last arg) communication fds between parent and child. Uses pipes.
    * if n=1, equivalent to child_spawn1_pipe; child writes, parent reads.
    * if n>=2, parent reads on even and writes on odd.
 */

extern pid_t child_spawn (char const *, char const *const *, char const *const *, int *, unsigned int) ;

#endif
