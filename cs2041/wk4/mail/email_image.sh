#!/bin/sh

for arg in "$@"
do

    # echo $arg
    display $arg

    read -p "Address to e-mail this image to? " addr
    read -p "Message to accompany image? " info

    # echo $addr
    # echo $info
    echo "$info" | mutt -s "$info" -a $arg -- $addr

done
