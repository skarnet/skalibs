/* ISC license. */

#ifndef FMTSCAN_INTERNAL_H
#define FMTSCAN_INTERNAL_H

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include <skalibs/uint64.h>
#include <skalibs/fmtscan.h>

extern size_t uint64_scan_base_max (char const *, uint64_t *, uint8_t, uint64_t) ;
extern size_t int64_scan_base_max (char const *, int64_t *, uint8_t, uint64_t) ;

#define SCANB0(bits) \
size_t uint##bits##0_scan_base (char const *s, uint##bits##_t *u, uint8_t base) \
{ \
  size_t pos = uint##bits##_scan_base(s, u, base) ; \
  if (!pos) return (errno = EINVAL, 0) ; \
  if (!s[pos]) return pos ; \
  errno = fmtscan_num(s[pos], base) < base ? ERANGE : EINVAL ; \
  return 0 ; \
} \

#define SCANS0(bits) \
size_t int##bits##0_scan_base (char const *s, int##bits##_t *d, uint8_t base) \
{ \
  size_t pos = int##bits##_scan(s, d) ; \
  if (!pos) return (errno = EINVAL, 0) ; \
  if (!s[pos]) return pos ; \
  errno = (fmtscan_num(s[pos], base) < base) ? ERANGE : EINVAL ; \
  return 0 ; \
} \

#define SCANL(bits) \
size_t uint##bits##_scanlist (uint##bits##_t *tab, size_t max, char const *s, size_t *num) \
{ \
  size_t i = 0, len = 0 ; \
  for (; s[len] && (i < max) ; i++) \
  { \
    size_t w = uint##bits##_scan(s + len, tab + i) ; \
    if (!w) break ; \
    len += w ; \
    while (memchr(",:; \t\r\n", s[len], 7)) len++ ; \
  } \
  *num = i ; \
  return len ; \
} \

#define SCANSL(bits) \
size_t int##bits##_scanlist (int##bits##_t *tab, size_t max, char const *s, size_t *num) \
{ \
  size_t i = 0, len = 0 ; \
  for (; s[len] && (i < max) ; i++) \
  { \
    size_t w = int##bits##_scan(s + len, tab + i) ; \
    if (!w) break ; \
    len += w ; \
    while (memchr(",:; \t\r\n", s[len], 7)) len++ ; \
  } \
  *num = i ; \
  return len ; \
} \

#define FMTL(bits) \
size_t uint##bits##_fmtlist (char *s, uint##bits##_t const *tab, size_t n) \
{ \
  size_t i = 0, len = 0 ; \
  for (; i < n ; i++) \
  { \
    size_t w = uint##bits##_fmt(s, tab[i]) ; \
    len += w ; \
    if (s) s += w ; \
    if (i < n-1) { len++ ; if (s) *s++ = ',' ; } \
  } \
  return len ; \
} \

#define FMTSL(bits) \
size_t int##bits##_fmtlist (char *s, int##bits##_t const *tab, size_t n) \
{ \
  size_t i = 0, len = 0 ; \
  for (; i < n ; i++) \
  { \
    size_t w = int##bits##_fmt(s, tab[i]) ; \
    len += w ; \
    if (s) s += w ; \
    if (i < n-1) { len++ ; if (s) *s++ = ',' ; } \
  } \
  return len ; \
} \

#endif
