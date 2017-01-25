/* ISC license. */

#ifndef FMTSCAN_INTERNAL_H
#define FMTSCAN_INTERNAL_H

#include <sys/types.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>

#define SCANB(bits) \
size_t uint##bits##_scan_base (char const *s, uint##bits##_t *u, unsigned int base) \
{ \
  static uint##bits##_t const max = UINT##bits##_MAX ; \
  uint##bits##_t result = 0 ; \
  size_t pos = 0 ; \
  for (;; pos++) \
  { \
    register unsigned char c = fmtscan_num(s[pos], base) ; \
    if ((c >= base) || (result > ((max - c) / base))) break ; \
    result = result * base + c ; \
  } \
  if (pos) *u = result ; \
  return pos ; \
} \

#define SCANB0(bits) \
size_t uint##bits##0_scan_base (char const *s, uint##bits##_t *u, unsigned int base) \
{ \
  register size_t pos = uint##bits##_scan_base(s, u, base) ; \
  if (!pos) return (errno = EINVAL, 0) ; \
  if (!s[pos]) return pos ; \
  errno = (fmtscan_num(s[pos], base) < base) ? EDOM : EINVAL ; \
  return 0 ; \
} \

#define SCANS(bits) \
size_t int##bits##_scan (char const *s, int##bits##_t *n) \
{ \
  uint##bits##_t tmp ; \
  register size_t r = 0 ; \
  register unsigned int sign = 0 ; \
  if (*s == '-') \
  { \
    r = 1 + uint##bits##_scan(s+1, &tmp) ; \
    if (r == 1) return 0 ; \
    if (tmp == 0) *n = 0 ; \
    else \
    { \
      if (tmp-1 > -(INT##bits##_MIN+1)) \
      { \
        tmp /= 10 ; \
        r-- ; \
      } \
      *n = INT##bits##_MIN + (-(INT##bits##_MIN+1) - (tmp-1)) ; \
    } \
    return r ; \
  } \
  if (*s == '+') (s++, sign++) ; \
  r = uint##bits##_scan(s, &tmp) ; \
  if (!r) return 0 ; \
  r += sign ; \
  if (tmp > INT##bits##_MAX) \
  { \
    tmp /= 10 ; \
    r-- ; \
  } \
  *n = tmp ; \
  return r ; \
} \

#define SCANS0(bits) \
size_t int##bits##0_scan (char const *s, int##bits##_t *u) \
{ \
  register size_t pos = int##bits##_scan(s, u) ; \
  if (!pos) return (errno = EINVAL, 0) ; \
  if (!s[pos]) return pos ; \
  errno = (fmtscan_num(s[pos], 10) < 10) ? EDOM : EINVAL ; \
  return 0 ; \
} \

#define SCANL(bits) \
size_t uint##bits##_scanlist (uint##bits##_t *tab, size_t max, char const *s, size_t *num) \
{ \
  size_t i = 0, len = 0 ; \
  for (; s[len] && (i < max) ; i++) \
  { \
    register size_t w = uint##bits##_scan(s + len, tab + i) ; \
    if (!w) break ; \
    len += w ; \
    while (byte_chr(",:; \t\r\n", 7, s[len]) < 7) len++ ; \
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
    register size_t w = int##bits##_scan(s + len, tab + i) ; \
    if (!w) break ; \
    len += w ; \
    while (byte_chr(",:; \t\r\n", 7, s[len]) < 7) len++ ; \
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
    register size_t w = uint##bits##_fmt(s, tab[i]) ; \
    len += w ; \
    if (s) \
    { \
      s += w ; \
      if (i < n-1) { *s++ = ',' ; len++ ; } \
    } \
  } \
  return len ; \
} \

#define FMTB(bits) \
size_t uint##bits##_fmt_base (char *s, uint##bits##_t x, unsigned int base) \
{ \
  register size_t len = 1 ; \
  { \
    register uint##bits##_t q = x ; \
    while (q >= base) { len++ ; q /= base ; } \
  } \
  if (s) \
  { \
    s += len ; \
    do { *--s = fmtscan_asc(x % base) ; x /= base ; } while (x) ; \
  } \
  return len ; \
} \

#define FMTB0(bits) \
size_t uint##bits##0_fmt_base (char *s, uint##bits##_t x, register size_t n, unsigned int base) \
{ \
  register size_t len = uint##bits##_fmt_base(0, x, base) ; \
  while (n-- > len) *s++ = '0' ; \
  return uint##bits##_fmt_base(s, x, base) ; \
} \

#define FMTS(bits) \
size_t int##bits##_fmt (char *fmt, int##bits##_t n) \
{ \
  if (n >= 0) return uint##bits##_fmt(fmt, n) ; \
  if (fmt) *fmt++ = '-' ; \
  return 1 + uint##bits##_fmt(fmt, -n) ; \
} \

#define FMTSL(bits) \
size_t int##bits##_fmtlist (char *s, int##bits##_t const *tab, size_t n) \
{ \
  size_t i = 0, len = 0 ; \
  for (; i < n ; i++) \
  { \
    register size_t w = int##bits##_fmt(s, tab[i]) ; \
    len += w ; \
    if (s) \
    { \
      s += w ; \
      if (i < n-1) { *s++ = ',' ; len++ ; } \
    } \
  } \
  return len ; \
} \

#endif
