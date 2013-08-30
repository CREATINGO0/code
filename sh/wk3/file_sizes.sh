#!/bin/sh

small=""
medium=""
large=""

for arg in `ls`
do
    linenum=`wc -l $arg | cut -f1 -d' '`
    if test $linenum -lt 10
    then
        small="$small $arg"
    elif test $linenum -lt 100
    then
        medium="$medium $arg"
    else
        large="$large $arg"
    fi
done

echo "Small files: $small"
echo "Medium-sized files: $medium"
echo "Large files: $large"
