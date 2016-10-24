/* ISC license. */

#ifndef ALARM_H
#define ALARM_H

#include <skalibs/tai.h>

extern int alarm_milliseconds (unsigned int) ;
extern int alarm_timeout (tain_t const *) ;
extern int alarm_deadline (tain_t const *) ;
extern void alarm_disable (void) ;

#endif
