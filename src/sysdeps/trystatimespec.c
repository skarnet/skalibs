/* ISC license. */

#include <sys/stat.h>
#include <time.h>

struct stat st ;
struct timespec *tsa = &st.st_atimespec ;
struct timespec *tsm = &st.st_mtimespec ;
struct timespec *tsc = &st.st_ctimespec ;
