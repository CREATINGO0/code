#!/usr/bin/perl

use strict;
use warnings;

use Path::Class;
use autodie;

my $dir = dir("/tmp");
my $file = $dir->file("file.txt");
my $file_handle = $file->openw();

my @list = ('a', 'list', 'of', 'lines');

foreach my $line ( @list ) {
    $file_handle->print( $line . "\n" );
}
