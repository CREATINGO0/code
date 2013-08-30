#!/bin/sh

for arg in "$@"
do

    date=`ls -l "$arg" | cut -d' ' -f6-8`
    # echo $date
    convert -gravity south -pointsize 36 -annotate 0 "$date" "$arg" "$arg"

done
