/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <unistd.h>
int main () { return revoke("/") ; }
