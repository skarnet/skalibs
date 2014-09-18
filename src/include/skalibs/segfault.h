/* ISC license. */

#ifndef SEGFAULT_H
#define SEGFAULT_H

extern int sigsegv (void) ;
extern int sigfpe (void) ;

#define segfault() sigsegv()

#endif
