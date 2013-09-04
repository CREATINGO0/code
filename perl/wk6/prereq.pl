#!/usr/bin/perl

use strict;
use warnings;

my $course = $ARGV[0];

if (@ARGV == 0) {
    print "unvalid arguments.\n";
} else {
    my $postg = "http://www.handbook.unsw.edu.au/postgraduate/courses/2013/$course.html";
    my $underg = "http://www.handbook.unsw.edu.au/undergraduate/courses/2013/$course.html";
    my $line;

# search postgrats
    open F, "wget -q -O- $postg|" or die;
    while ($line = <F>) {
        if ($line =~ /Prerequisite/) {
            $line =~ s/Excluded.*$//g;
            $line =~ s/Equivalent.*$//g;
            my (@pre) = $line =~ /[A-Z]{4}\d{4}/g;
            print join("\n",@pre), "\n";
        }
    }

# search undergrats
    open F, "wget -q -O- $underg|" or die;
    while ($line = <F>) {
        if ($line =~ /Prerequisite/) {
            $line =~ s/Excluded.*$//g;
            $line =~ s/Equivalent.*$//g;
            my (@pre) = $line =~ /[A-Z]{4}\d{4}/g;
            print join("\n",@pre), "\n";
        }
    }
}
