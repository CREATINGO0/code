#!/usr/bin/perl

use strict;
use warnings;

if (@ARGV == 0) {
    print "please specify arguments.\n";
    exit 1;
}

# for each poem?.txt
#   for each line/word
#     sum log_p for each poet
#   sort poets by log_p
#   return the one with top log_p

foreach my $arg (@ARGV) {

    my %log_p = ();

    open(UNKNOWN, "<$arg") or die "Cannot open file: $arg";
    while(<UNKNOWN>) {

        foreach my $toMatch (split(/[^A-Za-z]+/, lc $_)) {

            foreach my $file (glob "poets/*.txt") {

                open(FILE, "<$file") or die "Cannot open file: $file";

                my $wordcount = 0;
                my $matchcount = 0;

                while (<FILE>) {
                    foreach my $candidate (split(/[^A-Za-z]+/, lc $_)) {
                        if (not $candidate eq '') {
                            $wordcount++;
                            if ($candidate eq $toMatch) {
                                $matchcount++;
                            }
                        }
                    }
                }

                my $log = log(++$matchcount/$wordcount);

                for ($file) {
                    s/poets\///g;
                    s/\.txt//g;
                    s/_/ /g;
                }
                $log_p{"$file"} += $log;

            } # end iterate each known file

        } # end iterate each word from unknown file

    } # end iterate each line from unknown file

    # sort by value
    my @sortedkeys = sort { $log_p{$b} <=> $log_p{$a} } keys %log_p;
    my $result = $sortedkeys[0];
    printf "%s most resembles the work of %s (log-probablity=%.1f)\n",$arg,$result,$log_p{$result};

} # end iterate unknown files
