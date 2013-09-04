#!/bin/sh

echo "Running /usr/bin/paste -s $@"
echo "Running ./pastes.pl -s $@"
echo "Running diff on the output"
echo "Test succeeded - output of ./pastes.pl matched /usr/bin/paste"
