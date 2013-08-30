#!/usr/bin/perl

use strict;
use warnings;

my $N = 10;

if ($ARGV[0] =~ /^-[0-9]+$/)  {
    $N = -$ARGV[0];
}

while ($N > 0 and my $line = <STDIN>) {
    print $line;
    $N--;
}
