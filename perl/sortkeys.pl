#!/usr/bin/perl

print "content-type: text/html \n\n";

# DEFINE A HASH
%coins = ( "Quarter" , 25,
    "Dime" ,    10,
    "Nickel",    5 );
# FOREACH LOOP
foreach $key (sort keys %coins) {
    print "$key: $coins{$key}<br />";
}
