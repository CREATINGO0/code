#!/usr/bin/perl

# use strict;
# use warnings;

my $printMode = 0; # normal
my %t_time = ();
my @weekday = ("Mon","Tue","Wed","Thu","Fri");

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
            } else {
                foreach my $slot (split(/,\s+/,$line)) {
                    $slot =~ /([A-Za-z]{3})[^0-9]*([0-9]{2}):[0-9]{2}[\s\-]+([0-9]{2})/;
                    my ($week,$start,$end) = ($1,$2,$3);
                    while ($start < $end) {
                        if ($printMode == 1) {
                            print "$sem $course $week $start\n";
                        } elsif ($printMode == 2) {
                            $t_time{"$sem"}{"$week"}{"$start"}++;
                        }
                        $start++;
                    }
                }
            }
        }
    }

}

if ($printMode == 2) {

    for (my $i=1;$i<3;$i++) {

        print "S$i       Mon   Tue   Wed   Thu   Fri\n";
        for (my $j=9;$j<21;$j++) {
            printf "%02d:00",$j;
            foreach my $day (@weekday) {
                if ($t_time{"S$i"}{"$day"}{"$j"} != 0) {
                    printf "%6d",$t_time{"S$i"}{"$day"}{"$j"};
                } else {
                    print "      ";
                }
            }
            printf "\n";
        }

    }

}
