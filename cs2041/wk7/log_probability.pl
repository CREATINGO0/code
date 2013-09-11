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
        $_ =~ tr/A-Z/a-z/;
        foreach my $candidate (split(/[^A-Za-z]+/, $_)) {
            if (not $candidate eq '') {
                $wordcount++;
                if ($candidate eq $word) {
                    $matchcount++;
                }
            }
        }
    }
    my $log = log(++$matchcount/$wordcount);
    $matchcount--;
    $file =~ s/poets\///g;
    $file =~ s/\.txt//g;
    $file =~ s/_/ /g;
    printf "log((%d+1)/%6d) = %8.4f %s\n", $matchcount, $wordcount, $log, $file;

}
