#!/bin/sh -e

sysdeps="$1"
shift

getbits() {
  expr 8 '*' `grep -F sizeof$2: < "$1" | awk '{print $2;}'`
}

cat < src/headers/types-header

for i in short int long ; do
  I=$(echo "$i" | tr a-z A-Z)
  bits=$(getbits "$sysdeps" u$i)
  tools/gen-types-internal.sh u$i U$I $bits < src/headers/unsigned-template
  tools/gen-types-internal.sh $i $I $bits < src/headers/signed-template
done

for i in "$@" ; do
  un=un
  I=$(echo "$i" | tr a-z A-Z)
  bits=$(getbits "$sysdeps" $i)
  if grep -qF "signed$i: yes" < "$sysdeps" ; then
    un=
  fi
  tools/gen-types-internal.sh $i $I $bits < src/headers/"$un"signed-template
done

exec cat < src/headers/types-footer
