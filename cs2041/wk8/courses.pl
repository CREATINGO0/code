#!/usr/bin/perl

use strict;
use warnings;

if (@ARGV != 1) {
    print "please specify course prefix.\n";
    exit 1;
}

my $url = "http://www.timetable.unsw.edu.au/current/".(uc $ARGV[0])."KENS.html";

open F, "wget -q -O- $url|" or die "failed to retrieve courses";
while (my $line=<F>) {
    if ($line =~ /[A-Z]{4}[0-9]{4}<\/a>/) {
        $line =~ s/<\/a><\/td>//g;
        $line =~ s/^\s*<.*>//g;
        print $line;
    }
}
