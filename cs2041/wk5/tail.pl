#!/usr/bin/perl

use strict;
use warnings;

my $num = 10;

if (@ARGV == 0) { # from STDIN
    $.=0;
    ()=<STDIN>;
    my $countdown = $num;
    my $curr = $. - $num;
    seek(STDIN,0,0);
    while (my $line = <STDIN>) {
        if ($curr <= 0 && $countdown > 0) {
            print $line;
            $countdown--;
        }
        $curr--;
    }
} else { # from ARG
    foreach my $arg (@ARGV) {
        if ($arg =~ /^-\d+$/) {
            $num = -$arg;
            next;
        }
        if (!open(INPUT,"< $arg")) {
            print STDERR "tail.pl: can't open $arg\n";
            next;
        } elsif (@ARGV > 2) {
            print "==> $arg <==\n";
        }
        $.=0;
        ()=<INPUT>;
        my $countdown = $num;
        my $curr = $. - $num;
        # open(INPUT,"< $arg");
        seek(INPUT,0,0);
        while (my $line = <INPUT>) {
            if ($curr <= 0 && $countdown > 0) {
                print $line;
                $countdown--;
            }
            $curr--;
        }
    }
}
