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

if ($printMode != 2) {

    foreach my $course (@ARGV) {

        $course = uc $course;
        my $url = "http://www.timetable.unsw.edu.au/2013/".$course.".html";
        open F, "wget -q -O- $url|" or die "failed to retrieve courses";

        while (my $line=<F>) {
            if ($line =~ /Lecture<\/a>/) {
                $line=<F>;
                $line =~ /[^0-9]*T([12])<\/a/;
                my $sem = "S".$1;
                if ($printMode == 0) { # normal
                    print "$course: $sem";
                }
                for (my $i=0;$i<5;$i++) {
                    $line=<F>;
                }
                $line =~ s/<\/td>$//g;
                $line =~ s/^\s*<.*>//g;
                if ($printMode == 0) { # normal
                    print " $line";
                } elsif ($printMode == 1) {
                    foreach my $slot (split(/,\s+/,$line)) {
                        $slot =~ /([A-Za-z]{3})[^0-9]*([0-9]{2}):[0-9]{2}[\s\-]+([0-9]{2})/;
                        my ($week,$start,$end) = ($1,$2,$3);
                        while ($start < $end) {
                            print "$sem $course $week $start\n";
                            $start++;
                        }
                    }
                }
            }
        }

    }
}

if ($printMode == 2) { # table
    print "S1       Mon   Tue   Wed   Thu   Fri\n";
    for (my $i=9;$i<21;$i++) {
        printf "%2d:00\n",$i
    }
    print "S2       Mon   Tue   Wed   Thu   Fri\n";
    for (my $i=9;$i<21;$i++) {
        printf "%2d:00\n",$i
    }
}
