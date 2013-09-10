#!/bin/sh

for arg in *.jpg
do
    file="`echo $arg | sed 's/.jpg//g' |sed 's/$/.png/g'`"
    if [ `find $file`=$file ]
    then
        echo $file already exists
    else
        convert $arg $file
    fi
done
