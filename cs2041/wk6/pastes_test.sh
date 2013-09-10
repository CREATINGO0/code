#!/bin/sh

echo "Running /usr/bin/paste -s $@"
/usr/bin/paste -s $@ > o1
echo "Running ./pastes.pl $@"
./pastes.pl $@ > o2
echo "Running diff on the output"
if diff o1 o2 > /dev/null; then
    echo "Test succeeded - output of ./pastes.pl matched /usr/bin/paste"
else
    echo "Test failed - out of ./pastes.pl dismatched /usr/bin/paste"
fi
rm o1 o2
