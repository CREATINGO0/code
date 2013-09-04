#!/usr/bin/perl
use warnings;
use strict;

my $time = localtime();
print $time, "\n";
print ("$1 \n") if($time =~ /(\d\d:\d\d:\d\d)/);
