#!/usr/bin/perl

use strict;
use warnings;

foreach my $course (@ARGV) {

    $course = uc $course;
    my $url = "http://www.timetable.unsw.edu.au/2013/".$course.".html";

    open F, "wget -q -O- $url|" or die "failed to retrieve courses";
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

}
