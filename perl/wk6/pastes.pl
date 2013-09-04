#!/usr/bin/perl

use strict;
use warnings;

if (@ARGV == 0) {
    print "unvalid arguments.";
} else {

    foreach my $arg (@ARGV) {
        open(INPUT,"< $arg") or die "cannot open $arg\n";
        while (my $line = <INPUT>) {
            $line =~ s/\n/\t/g;
            $line =~ s/\t\Z/\Z/g;
            print $line;
        }
        print "\n";
    }

}
