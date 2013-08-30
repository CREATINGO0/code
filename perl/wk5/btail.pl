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
        open(INPUT,"< $arg") or die("tail.pl: can't open $arg\n");
        print "==> $arg <==\n" if (@ARGV > 2);
        p(\*INPUT,$num);
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

sub p {
    my ($handle,$nlim) = @_;
    my $content = '';
    {
        local $/;
        $content = <$handle>
    }

    $.=0;
    ()=$content;
    my $countdown = $nlim;
    my $curr = $. - $nlim;
    # open(INPUT,"< $arg");
    seek($content,0,0);
    while (my $line = $content) {
        if ($curr <= 0 && $countdown > 0) {
            print $line;
            $countdown--;
        }
        $curr--;
    }
}
