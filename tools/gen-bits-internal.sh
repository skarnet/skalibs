#!/bin/sh -e

bits="$1"
dfmt="$2"
ofmt="$3"
xfmt="$4"
bfmt="$5"

exec sed -e "s/@BITS@/$bits/g; s/@DFMT@/$dfmt/g; s/@OFMT@/$ofmt/g; s/@XFMT@/$xfmt/g; s/@BFMT@/$bfmt/g;" < src/headers/bits-template
