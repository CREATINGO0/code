#!/bin/perl

use strict;
use warnings;

my $word = $ARGV[0];

foreach my $file (glob "poets/*.txt") {

    open(FILE, "<$file") or die "Cannot open file: $file";
    my $wordcount = 0;
    my $matchcount = 0;
    while (<FILE>) {
        $_ =~ tr/A-Z/a-z/;
        $_ =~ s/^[ \t]*//g;
        $_ =~ s/[ \t\r\n]*$//g;
        my @line = split(/[^A-Za-z]+/, $_);
        foreach my $tomatch (@line) {
            if ($tomatch =~ /^$word$/) {
                $matchcount++;
                # print "$tomatch\n";
            }
        }
        $wordcount += scalar(@line);
    }
    print "$file\n";
    print "$matchcount/$wordcount\n";

}
