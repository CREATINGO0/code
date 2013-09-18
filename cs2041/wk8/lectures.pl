#!/usr/bin/perl

use strict;
use warnings;

my $printMode = 0; # normal

foreach my $arg (@ARGV) {
    if ($arg eq '-d') {
        $printMode = 1; # detail
    } elsif ($arg eq '-t') {
        $printMode = 2; # table
    }
}

foreach my $course (@ARGV) {

    $course = uc $course;
    my $url = "http://www.timetable.unsw.edu.au/2013/".$course.".html";
    open F, "wget -q -O- $url|" or die "failed to retrieve courses";

    if ($printMode == 0) { # normal
        while (my $line=<F>) {
            if ($line =~ /Lecture<\/a>/) {
                $line=<F>;
                $line =~ s/.*T1.*/S1/g;
                $line =~ s/.*T2.*/S2/g;
                $line =~ s/\n//g;
                print "$course: $line";
                for (my $i=0;$i<5;$i++) {
                    $line=<F>;
                }
                $line =~ s/<\/td>$//g;
                $line =~ s/^\s*<.*>//g;
                print " $line";
            }
        }
    } elsif ($printMode == 1) { # detail
        while (my $line=<F>) {
            if ($line =~ /Lecture<\/a>/) {
                $line=<F>;
                $line =~ s/T1/S1/g;
                $line =~ s/T2/S2/g;
                $line =~ /(S[12])/;
                my $sem = $1;
                for (my $i=0;$i<5;$i++) {
                    $line=<F>;
                }
                $line =~ s/<\/td>$//g;
                $line =~ s/^\s*<.*>//g;
                foreach my $slot (split(/,\s+/,$line)) {
                    print "$slot\n";
                    $slot =~ /\s*([A-Za-z]{3})/;
                    my $week = $1;
                    $slot =~ /[^0-9]+([0-9]{2})/;
                    my ($start,$end) = ($1,$2);
# print "$week, $start, $end\n";
                }
            }
        }
    } elsif ($printMode == 2) { # table

    }
}
