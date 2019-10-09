#!/bin/sh

cat <<EOF
/* ISC license. */

#ifndef SYSDEPS_H
#define SYSDEPS_H

#undef SKALIBS_TARGET
#define SKALIBS_TARGET "$1"

EOF

while read k v ; do
  k=$(echo "${k%%:}" | tr a-z A-Z)
  if test ${k} != ${k##SIGNED} ; then
    echo "#undef SKALIBS_HASUN$k"
    echo "#undef SKALIBS_HAS$k"
    if test $v = yes ; then
      echo "#define SKALIBS_HAS$k"
    else
      echo "#define SKALIBS_HASUN$k"
    fi
  elif test ${k} != ${k##SIZEOF} ; then
    echo "#undef SKALIBS_$k"
    echo "#define SKALIBS_$k $v"
  elif test ${k} = ENDIANNESS ; then
    echo '#undef SKALIBS_ENDIANNESS'
    echo "#define SKALIBS_ENDIANNESS $v"
  else
    echo "#undef SKALIBS_HAS$k"
    if test $v = yes ; then
      echo "#define SKALIBS_HAS$k"
    fi
  fi
  echo
done

echo '#endif'
