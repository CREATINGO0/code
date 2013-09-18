#!/usr/bin/perl

use strict;
use warnings;
use autodie;
use File::Slurp;

sub my_slurp {
    my ($fname) = @_;
    my $content = read_file($fname);

    print $content; # or do something else with $content

    return 1;
}

my $filename = <STDIN>;
my_slurp($filename);

exit 0;
