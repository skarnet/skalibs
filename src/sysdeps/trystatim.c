/* ISC license. */

#undef _POSIX_C_SOURCE

#include <sys/stat.h>
#include <time.h>

struct stat st ;
struct timespec *tsa = &st.st_atim ;
struct timespec *tsm = &st.st_mtim ;
struct timespec *tsc = &st.st_ctim ;
