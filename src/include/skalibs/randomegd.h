/* ISC license. */

#ifndef RANDOMEGD_H
#define RANDOMEGD_H

extern int randomegd_open (char const *) ;
extern unsigned int randomegd_readb (int, char *, unsigned int) ;
extern unsigned int randomegd_readnb (int, char *, unsigned int) ;
  
#endif
