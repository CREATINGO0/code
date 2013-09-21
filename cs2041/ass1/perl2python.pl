#!/usr/bin/perl

use strict;
use warnings;

my $g_indent = 0;

while (my $line = <>) {

    # rip off original indentations
    $line =~ s/^\s*//g;

    if ($line =~ /^\s*}\s*$/) {
        # meets closing bracket indicating reducing indentation
        $g_indent--;
    }

    if ($line =~ /^#!/ && $. == 1) {
        # translate #! line

        print "#!/usr/bin/python\n";

    } elsif ($line =~ /^\s*#/ || $line =~ /^\s*$/) {
        # Blank & comment lines can be passed unchanged
        &printIndent();

        print $line;

    } elsif ($line =~ /^\s*print\s*"(.*)\\n"[\s;]*$/) {
        # Python's print adds a new-line character by default
        # so we need to delete it from the Perl print statement
        &printIndent();

        print "print \"$1\"\n";

    } else {
        # Lines we can't translate are turned into comments
        &printIndent();

        print "#$line\n";

    }

    if ($line =~ /{\s*$/) {
        # handle increase indent finally so that won't indent
        # lines with {
        $g_indent++;
    }


}

sub printIndent {
    # 4 spaces not tabs
    for(my $i=$g_indent;$i>0;$i--) {
        print "    ";
    }
}
