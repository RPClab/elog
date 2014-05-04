#!/usr/bin/perl -w

# Copyright 2000 + Stefan Ritt
#
# ELOG is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# ELOG is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with ELOG.  If not, see <http://www.gnu.org/licenses/>.


=head1 NAME

doelog - save a mime message to elog

=head1 SYNOPSIS

    doelog <mime-msg-file> <mime-msg-file> ...
    
    someprocess | doelog -

=head1 DESCRIPTION

Takes one or more files from the command line that contain MIME
messages, and explodes their contents out into /tmp.  The parts
are sent to elog as attachments.

Modified mimeexplode of the MIME::Tools in perl


This was written as an example of the MIME:: modules in the
MIME-parser package I wrote.  It may prove useful as a quick-and-dirty
way of splitting a MIME message if you need to decode something, and
you don't have a MIME mail reader on hand.

=head1 COMMAND LINE OPTIONS

None yet.  

=head1 AUTHOR

sak@essc.psu.edu

=cut

BEGIN { unshift @INC, ".." }    # to test MIME:: stuff before installing it!

require 5.001;

use strict;
use vars qw($Msgno $cmd);

use MIME::Parser;
use Getopt::Std;

## these should be options too?
## base elog cmd
$cmd = "~/elog -h localhost -p 8080 ";

#------------------------------------------------------------
# dump_entity - dump an entity's file info
#------------------------------------------------------------
sub dump_entity {
    my $ent = shift;
    my @parts = $ent->parts;
    my $file;
    
    die "too many attachments\n" if ($#parts>10);

    if (@parts) {        # multipart...
	map { dump_entity($_) } @parts;
    }
    else {               # single part...append to elog cmd
	$file = $ent->bodyhandle->path;
	$cmd .= "-f \"$file\" ";
##	print $cmd, "\n";
##	print "    Part: ", $ent->bodyhandle->path, 
##	      " (", scalar($ent->head->mime_type), ")\n";
    }
}

#------------------------------------------------------------
# main
#------------------------------------------------------------
sub main {
    my $file;
    my $entity;
    my $subject;
    my $logbook;
    our($opt_l);

    # Sanity:
    ## (-w ".") or die "cwd not writable, you naughty boy...";

    ## check if user wants a particular logbook
    ## fix to add host and port?
    getopts('l:');
    if($opt_l) { $logbook=$opt_l;} else {$logbook="emails";}
    $cmd .= "-l $logbook ";
    
    # Go through messages:
    @ARGV or unshift @ARGV, "-";
    while (defined($file = shift @ARGV)) {


	# Create a new parser object:
	my $parser = new MIME::Parser;
    
	# Optional: set up parameters that will affect how it extracts 
	#   documents from the input stream:
	$parser->output_under("/tmp");
    
	# Parse an input stream:
	open FILE, $file or die "couldn't open $file";
	$entity = $parser->read(\*FILE) or 
	    print STDERR "Couldn't parse MIME in $file; continuing...\n";
	close FILE;

	## get the subject, assumes all logbooks have a subject 
	## attribute - not necessarily true.  Mine do...
	chomp($subject = $entity->head->get('Subject', 0));
	$cmd .= "-a subject=\"$subject\" ";
	print $cmd, "\n";

	# Congratulations: you now have a (possibly multipart) MIME entity!
	dump_entity($entity) if $entity;
	### $entity->dump_skeleton if $entity;
	### print $cmd, "\n";
	exec $cmd;
    }
    1;
}

exit (&main ? 0 : -1);
#------------------------------------------------------------
1;






