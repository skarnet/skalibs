/* ISC license. */

#ifndef DIRENTRY_H
#define DIRENTRY_H

#include <dirent.h>

typedef struct dirent direntry, direntry_t, *direntry_ref, *direntry_t_ref ;

extern void dir_close (DIR *) ;
extern int dir_fd (DIR *) ;  /* Solaris doesn't have dirfd() */

#endif
