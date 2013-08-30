#!/usr/bin/perl
use strict;
use warnings;

use Path::Class;
use autodie;

my $dir = dir("/tmp");
my $file = $dir->file("file.txt");
my $content = $file->slurp();
my $file_handle = $file->openr();
while( my $line = $file_handle->getline() ) {
    print $line;
}
