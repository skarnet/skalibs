/* ISC license. */

#ifndef SKALIBS_H
#define SKALIBS_H

/*
   This header is heavy! It includes everything in skalibs except:
   - skalibs/config.h: package configuration
   - skalibs/sysdeps.h: system-dependent feature test macros
   - skalibs/nonposix.h: pre-system headers definitions for POSIX extensions
   - skalibs/posixishard.h: workarounds for failures to respect POSIX
*/

#include <skalibs/posixplz.h>
#include <skalibs/stddjb.h>
#include <skalibs/stdcrypto.h>
#include <skalibs/random.h>
#include <skalibs/datastruct.h>
#include <skalibs/biguint.h>
#include <skalibs/unixonacid.h>

#endif
