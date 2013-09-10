#!/bin/sh

num=$1
content=$2

if test $# -ne 2
then
    echo "Usage: ./echon.sh"

elif test $1 -lt 0
then
    echo "./echon.sh: argument 1 must be a non-negative integer"

else
    while test $num -ne 0
    do
        echo $content
        num=`expr $num - 1`
    done

fi
