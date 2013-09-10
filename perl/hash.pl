#!/bin/perl

%coins = ("Quarter",25,"Dine",10,"Nickel",5);
# print %coins;

while (($key,$value) = each(%coins)) {
    print $key.", ".$value."\n";
}

print "***\n";

$coins{Dollar}=1;

while (($key,$value) = each(%coins)) {
    print $key.", ".$value."\n";
}
