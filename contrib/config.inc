#  elog2sql
#  global configuration vars


#
#  set the database table names to "$table_prefix<logbookname>"
#  This is used  in case in only allowed  one database
#  and want to avoid table naming conflicts.  
#  normally, keep the default to ("") 

$table_prefix = "" ;


#
# set the default element type for mysql
#  (each elogd attribute is set to this type)
#

$default_element_type = "varchar(100)" ;

#
# set the debug flat : set to 1 if you want to see debugging output. 
#
$debug = 0 ;


#
# Do not change the variables after this line
#
$version = "0.99" ;
