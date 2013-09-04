#!/usr/bin/perl

use strict;
use warnings;

if (@ARGV == 0) {
    print "unvalid arguments.";
} else {

    foreach my $arg (@ARGV) {
        my $pline = "";
        open(INPUT,"< $arg") or die "cannot open $arg\n";
        while (my $line = <INPUT>) {
            $line =~ s/\n/\t/g;
            $pline = $pline.$line;
        }
        chop $pline;
        print $pline."\n";
    }

}
