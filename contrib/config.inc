#  elog2sql
#  global configuration vars

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
