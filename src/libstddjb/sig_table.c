 /* ISC license. */

#include <signal.h>
#include "sig-internal.h"

sigtable_t const skalibs_sigtable[] =
{
  { SIGABRT, "ABRT" },
  { SIGALRM, "ALRM" },
  { SIGBUS, "BUS" },
  { SIGCHLD, "CHLD" },
  { SIGCONT, "CONT" },
  { SIGFPE, "FPE" },
  { SIGHUP, "HUP" },
  { SIGILL, "ILL" },
  { SIGINT, "INT" },
  { SIGKILL, "KILL" },
  { SIGPIPE, "PIPE" },
  { SIGQUIT, "QUIT" },
  { SIGSEGV, "SEGV" },
  { SIGSTOP, "STOP" },
  { SIGTERM, "TERM" },
  { SIGTSTP, "TSTP" },
  { SIGTTIN, "TTIN" },
  { SIGTTOU, "TTOU" },
  { SIGUSR1, "USR1" },
  { SIGUSR2, "USR2" },
#ifdef SIGPOLL
  { SIGPOLL, "POLL" },
#endif
#ifdef SIGPROF
  { SIGPROF, "PROF" },
#endif 
#ifdef SIGSYS
  { SIGSYS, "SYS" },
#endif
#ifdef SIGTRAP
  { SIGTRAP, "TRAP" },
#endif
#ifdef SIGURG
  { SIGURG, "URG" },
#endif
#ifdef SIGVTALRM
  { SIGVTALRM, "VTALRM" },
#endif
#ifdef SIGXCPU
  { SIGXCPU, "XCPU" },
#endif
#ifdef SIGXFSZ
  { SIGXFSZ, "XFSZ" },
#endif
#ifdef SIGIOT
  { SIGIOT, "IOT" },
#endif
#ifdef SIGEMT
  { SIGEMT, "EMT" },
#endif
#ifdef SIGSTKFLT
  { SIGSTKFLT, "STKFLT" },
#endif
#ifdef SIGCLD
  { SIGCLD, "CLD" },
#endif
#ifdef SIGWINCH
  { SIGWINCH, "WINCH" },
#endif
#ifdef SIGIO
  { SIGIO, "IO" },
#endif
#ifdef SIGINFO
  { SIGINFO, "INFO" },
#endif
#ifdef SIGLOST
  { SIGLOST, "LOST" },
#endif
#ifdef SIGPWR
  { SIGPWR, "PWR" },
#endif
#ifdef SIGUNUSED
  { SIGUNUSED, "UNUSED" },
#endif
  { 0, 0 }
} ;
