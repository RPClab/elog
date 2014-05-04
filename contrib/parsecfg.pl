#!/usr/bin/perl

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

parsecfg.pl - create a sql db template from a elog.cfg file

=head1 SYNOPSIS

B<parsecfg.pl> I<stdin> I<stdout>

=head1 DESCRIPTION

reads the elogd.cfg (elog config file) on stdin and writes to stdout the 
mysql statements for creating of database template for that elog configuration.

A sql template is created for each logbook, with each attribute being assigned 
to a sql column.  Default columns are automatically created for ID, Date, Reply_to, In_reply_to and the entry text ("Notes").  Additional columns are created, one  for each attribute.  

Attachments are handled by created a separate table "<$table_prefix>attachments", which can be indexed by the logbook_name and entry id.

=head1 OPTIONS

=over 4

=item Globals 

See the "config.inc" file for global parameters.  Currently, the default data type, and  table_prefix are assignable options in this file.

=back

=head1 FILES

=over 4

=item I<elogd.cfg>

a well-formed elogd.cfg file

=item I<sql output>

A mysql output command file, suitable to be used as input into "mysql", as in,
mysql -u <<user>> -p <<database>> << I<sql_output> 

=back

=head1 BUGS

this is a quick and dirty programming job, so I expect this to be a brittle program. Use at your own risk, and check the resulting output before using mysql.

=head1 LICENSE

The author issues this code under the GPL. (See GPL.txt)

=head1 AUTHOR

dave@davidfannin.com

=cut


require "config.inc" ;

# do not change these values, for development only

$opentable = 0 ;


#
# trims whitespace, and removes blanks between words  
#
sub tokenize($) {
 my $t = shift ;
 $t =~ s/^\s+// ; # get rid of leading ws
 $t =~ s/\s+$// ; # get rid of trailing ws
 $t =~ s/\s+/_/g ; #replace spaces with _
 return $t ;
}


#
# starts a new logbook
#
sub section($)  {
 my $s = shift ;
 if ($opentable && ($current_section ne "global")) { emit_table() ; }  ;

 $debug && print "#section:$s\n";
 $s=tokenize($s) ;
 $current_section=$s ;
 $opentable=1 ;
}

#
# reads a logbook's comment line
#
sub comment($)  {
 my $c = shift ;
 $debug && print "#$current_section:comment:$c\n";
 $comment{'$current_section'}=$c ;
}

#
#  parses the attribute lines
#
sub attribute($)  {
 my $a = shift ;
 @al=split(/,/,$a) ;
 foreach $av (@al) {
 $av=tokenize($av) ; 
 if ($av eq "Id") {  next ; }
 $debug && print "#$current_section:attribute:$av\n" ;
 push @attribute,$av ;
 }
}

#
#  parses the option lines (currently not used)
#
sub option($$)  {
 my $on = shift ;
 my $ov = shift ;
 @ol=split(/,/,$ov) ;
 foreach $olv (@ol) {
 $olv=tokenize($olv);
 $debug && print "#$current_section:options:$on:$olv\n";
 }
}
#
#  parses the moption lines (currently not used)
#
sub moption($$)  {
 my $mon = shift ;
 my $mov = shift ;
 $debug && print "#$current_section:moptions:$mon:$mov\n";
}
#
#  parses the ioption lines (currently not used)
#
sub ioption($$)  {
 my $ion = shift ;
 my $iov = shift ;
 $debug && print "#$current_section:ioptions:$ion :$iov\n";
}
#
#  parses the roption lines (currently not used)
#
sub roption($$)  {
 my $ron = shift ;
 my $rov = shift ;
 $debug && print "#$current_section:roptions:$ron:$rov\n";
}


#
#  writes out the sql code for a logbook (table)
#
sub emit_table {

print "\n\nCREATE TABLE `$table_prefix$current_section` (\n" ;
print "    `id` int(10) NOT NULL auto_increment,\n" ;
print "    `Reply_to` int(10) default NULL ,\n" ;
print "    `In_reply_to` int(10) default NULL,\n" ;
print "    `Date` datetime NOT NULL,\n" ;
while ($a=pop(@attribute)) {
        if ($a =~ /Date/) {
		$type="datetime" ;
	} else {
		$type=$default_element_type ;
	}
	print "    `$a` $type default NULL,\n" ;
}
print "    `Note` text  NOT NULL,\n" ;
print "    UNIQUE INDEX id (`id`)\n" ;
print ") TYPE=MyISAM;\n" ;
}

#
#  writes out the sql code for an attachment table
#
sub emit_attachment {

print "\nCREATE TABLE `".$table_prefix."attachment` (\n";
print "    `id` int(10) NOT NULL auto_increment,\n";
print "    `logname` varchar(255) ,\n";
print "    `pid` int(10) ,\n";
print "    `filename` varchar(255) ,\n";
print "    UNIQUE INDEX id  (`id`)\n";
print ") TYPE=MyISAM\n;" ;

} 

#
# main()
#

#
# loop on input, parsing out the relavant sections
#
while(<>) {
        chomp ;
	 /^\s*\[(\w+)\]\s*$/ && section($1) ;
	 /^\s*(Comment)\s*=(.*)/ && comment($2);
	 /^\s*(Attributes)\s*=(.*)/ && attribute($2);
	 /^\s*(Options)\s*(\w+)\s*=(.*)/ && option($2,$3);
	 /^\s*(MOptions)\s*(\w+)\s*=(.*)/ && moptions($2,$3);
	 /^\s*(IOptions)\s*(\w+)\s*=(.*)/ && ioptions($2,$3);
	 /^\s*(ROptions)\s*(\w+)\s*=(.*)/ && roptions($2,$3);
}

#
# close any open tables, 
if ($opentable && ($current_section ne "global")) { emit_table() ; }  ;
emit_attachment() ;
