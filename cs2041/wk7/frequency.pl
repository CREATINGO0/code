#!/usr/bin/perl

use strict;
use warnings;

if (@ARGV == 0) {
    print "invalid arguments.\n";
    exit 1;
}

my $word = $ARGV[0];

foreach my $file (glob "poets/*.txt") {

    open(FILE, "<$file") or die "Cannot open file: $file";
    my $wordcount = 0;
    my $matchcount = 0;
    while (<FILE>) {
        foreach my $candidate (split(/[^A-Za-z]+/, lc $_)) {
            if (not $candidate eq '') {
                $wordcount++;
                if ($candidate eq $word) {
                    $matchcount++;
                }
            }
        }
    }
    $file =~ s/poets\///g;
    $file =~ s/\.txt//g;
    $file =~ s/_/ /g;
    my $ratio = $matchcount/$wordcount;
    printf "%4d/%6d = %.9f %s\n", $matchcount, $wordcount, $ratio, $file;

}
