#!/usr/bin/perl

use strict;
use warnings;

my $argn = $#ARGV + 1;
if ($argn != 2) {
    print "Usage: ./echon.pl";
}

my $prtNum  = $ARGV[0];
my $prtCont = $ARGV[1];

while ($prtNum != 0) {
    print $prtCont."\n";
    $prtNum--;
}
