#!/bin/sh

IFS=$'\n'

# for arg in `find . -type f -name "*.jpg"`
for arg in *.jpg
do
    # echo $arg
    curr="${arg%.*}"
    [ -f $curr.jpg -a -f $curr.png ] && echo "$curr.png already exists"
    convert $curr.jpg $curr.png
    rm $curr.jpg
done
