#!/usr/bin/perl

use strict;
use warnings;

sub mySub {
    @args = @_;
    print "I got ",$#args+1," args\n";
    print "They are (@args)\n";
}

mySub(a,b,c);
