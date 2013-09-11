#!/usr/bin/perl

use strict;
use warnings;

if (@ARGV == 0) {
    print "invalid arguments.\n";
    exit 1;
}

# for each poem?.txt
#   (for each line)
#   for each word
#     sum log_p for each poet
#   sort poets by log_p
#   return the one with top log_p

foreach my $arg (@ARGV) {

    my %log_p = ();

    open(UNK, "<$arg") or die "Cannot open file: $arg";
    while(<UNK>) {

        my $sumlog = 0;

        $_ =~ tr/A-Z/a-z/;
        foreach my $toMatch (split(/[^A-Za-z]+/, $_)) {

            foreach my $file (glob "poets/*.txt") {

                open(FILE, "<$file") or die "Cannot open file: $file";
                my $wordcount = 0;
                my $matchcount = 0;
                while (<FILE>) {
                    $_ =~ tr/A-Z/a-z/;
                    foreach my $candidate (split(/[^A-Za-z]+/, $_)) {
                        if (not $candidate eq '') {
                            $wordcount++;
                            if ($candidate eq $toMatch) {
                                $matchcount++;
                            }
                        }
                    }
                }
                my $log = log(++$matchcount/$wordcount);
                $sumlog += $log;
                $matchcount--;
                $file =~ s/poets\///g;
                $file =~ s/\.txt//g;
                $file =~ s/_/ /g;
                $log_p{"$file"}=$sumlog;

            }
        }
        print %log_p;

    }

}
