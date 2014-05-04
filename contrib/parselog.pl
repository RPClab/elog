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

parselog.pl - create a sql db input file from a elog logbook

=head1 SYNOPSIS

B<parselog.pl> I<logbook-name> I<stdin> I<stdout>

=head1 DESCRIPTION

reads the *.log files (elog logbook) on stdin and writes to stdout the 
sql statements for inputing the logbook data into an MySQL database. 

You will need to create the MySQL database first by using the parsecfg.pl command file.

Default entries are created by ID, Date, Reply_to, In_reply_to, and Notes (the text of the logbook entry). Other attributes are translated as needed.
Note that any attribute name that contains "Date" is translated to the MySQL datetime variable type, and the script will attempt to convert the attribute value to the datetime format.

Attachments entries are handled by created a separate table "<$table_prefix>attachments", which can be indexed by the logbook_name and entry id.

=head1 OPTIONS

=over 4

=item I<logbook name>

Required Option: The name to use of the database table.  Should be the same name as used by elog for a logbook, and created by parsecfg.pl.

=item Globals 

See the "config.inc" file for global parameters.  Currently, the default data type, and  table_prefix are assignable options in this file.

=back

=head1 FILES

=over 4

=item I<*.log>

The log files in a elog logbook directory

=item I<sql output>

A mysql output command file, suitable to be used as input into "mysql", as in,
mysql -u <<user>> -p <<database>> << I<sql_output> 

=back

=head1 BUGS

this is a quick and dirty programming job, so I expect this to be a brittle program. Use at your own risk, and check the resulting output before using mysql.

Elog is sloppy on logbook formats - Extra attributes could remain in a elog logbook file if the user created a logbook, and then deleted attributes later on.  These extra attribute entries will break the sql file, and you will need to delete them from the logbook or from the sql file manually.

Attribute names containing "Date" are assumed to contain datetime information and are automatically converted to MySQL datetime format.  This may not be the correct action and will cause things to break.

=head1 LICENSE

The author issues this code under the GPL. (See GPL.txt)

=head1 AUTHOR

dave@davidfannin.com

=cut

use Time::ParseDate ;
use Date::Format ;

require "config.inc" ;


if ($#ARGV == 0) {
	$table_name=$ARGV[0] ;

} else {
	print "usage: parselog.pl <logbook-dbname>\n" ;
	print "you are missing the logbook name\n" ;
	exit(1) ;
};

$openentry = 0 ;

sub tokenize($) {
 my $t = shift ;
 $t =~ s/^\s+// ; # get rid of leading ws
 $t =~ s/\s+$// ; # get rid of trailing ws
 $t =~ s/\s+/_/g ; #replace spaces with _
 return $t ;
}

sub quote_sql($) {
 my $qstr = shift ;
 # escape special chars 
 $qstr =~ s/(['"\\\0])/\\$1/g ;
return "'".$qstr."'" ;
}


sub entry($)  {
 my $e = shift ;
 if ($openentry) { emit_entry() ; }  ;

 $debug && print "#entry:$e\n";
 $e=tokenize($e) ;
 $current_entry=$e ;
 $openentry=1 ;
}

sub attribute($$)  {
 my $name = shift ;
 my $value = shift ;
 $name=tokenize($name) ; 
 $debug && print "#attribute:$name:$value\n" ;
 if ( $name eq "Attachment" )  {
	if ( $value == "" ) { return ; }
	push @attachment, "$current_entry;$value" ;
	return ;
 };
 return  if ( $name eq "Id" ) ; 
 return  if ( $name eq "Encoding" ) ; 
 if ( $name  =~ /Date/ ) {  
    $value=time2str("%Y-%m-%d %X",parsedate($value)) ;
 } 
 $attribute{$name}=$value ;
}

sub encoding {

$encoding = "";
<STDIN> ;
while (<STDIN>) {
     /^\$\@MID\@\$: (\d+)$/ && return  ;
    $encoding .= $_ ;
}  

}

sub option($$)  {
 my $on = shift ;
 my $ov = shift ;
 @ol=split(/,/,$ov) ;
 foreach $olv (@ol) {
 $olv=tokenize($olv);
 $debug && print "#$current_section:options:$on:$olv\n";
 }
}
sub moption($$)  {
 my $mon = shift ;
 my $mov = shift ;
 $debug && print "#$current_section:moptions:$mon:$mov\n";
}
sub ioption($$)  {
 my $ion = shift ;
 my $iov = shift ;
 $debug && print "#$current_section:ioptions:$ion :$iov\n";
}
sub roption($$)  {
 my $ron = shift ;
 my $rov = shift ;
 $debug && print "#$current_section:roptions:$ron:$rov\n";
}

sub emit_entry {

print "\n\nINSERT INTO $table_prefix$table_name \n" ;
print "    SET id = ($current_entry),\n" ;
foreach $name (keys %attribute) {
	print "    $name = (".quote_sql($attribute{$name})."),\n" ;
} 
print "    Note = (".quote_sql($encoding).");\n";

}

sub emit_attachment {
while($value = pop(@attachment)) {
	($id,$filename)= split(/;/,$value) ;
	print "\n\nINSERT INTO ".$table_prefix."attachment \n" ;
	print "    SET logname = (\"$table_prefix$table_name\"),\n" ;
	print "    pid = ($id),\n" ;
	print "    filename = (\"$filename\");\n" ;
} 

}

while(<STDIN>) {
        chomp ;
	 /^Encoding:/ && encoding() ;
	 /^\$\@MID\@\$: (\d+)$/ && entry($1) ;
	 /^([\w\s]+): (.*)$/ && attribute($1,$2) ;
}
if ($openentry) { emit_entry() ; }  ;

emit_attachment() ;
