NAME
    elog2sql - copy an elog logbook to a MySQL database

SYNOPSIS
    parsecfg.pl - translate the elogd.cfg file to a MySQL database template

    parselog.pl - translate a elog logbook to a MySQL insert template file

DESCRIPTION
    elog2sql was created to help translate logbooks created by the program
    "elog" (http://midas.psi.ch/elog/) from the native elog flat file format
    to a MySQL database. I found elog to be one of the easiest, yet
    feature-rich web-based programs for maintaining journals and logbooks;
    The program is fast, the administration and setup are easy and simple,
    and the features are extremly well suited for the application. However,
    I was bothered by all-in-one (web server and application) design of
    elog, rather then the typical use of Apache/PHP/MySQL platform for such
    an application. IMHO, having elog on such a platform will allow easier
    and simpler integration of new functions and extensions for elog. The
    long-term goal is to create a version of elog functionality based on the
    LAMP platform.

    Therefore, I created a set of perl scripts that will allow the
    translation of elog logbooks into a MySQL database. The design and
    implementation of these scripts are a simple one, and allow the one-time
    copying of a set of logbooks.

    The elog2sql toolkit consists of two scripts. The first script,
    parsecfg.pl, reads a elogd.cfg, and creates a sql file that will create
    a set of db tables corresponding to elog logbooks. The second script,
    parselog.pl, takes a set of elog logfiles, and creates a sql file that
    will enter the logbook data into the database. The result is a copy of
    the elog logbook that can used as desired inside the framework of MySQL.
    Attachments are handled by inserting an entry of the attachment name
    into an seperate attachment table. This allows multiple attachments per
    entry.

USAGE
    1) Create a MySQL database (example: elog)
    2) Create the sql database templates
        parsecfg.pl < elogd.cfg >elog.sql

    3) Create the MySQL tables
        mysql -u user -p elog <elog.sql

    4) Translate an elog logbook (example: journal)
        cat logbook/journal/*log | parselog.pl journal >journal.sql

    5) Load the table into MySQL
        mysql -u user -p elog <journal.sql

    6) Repeat steps 4 and 5 for each logbook directory.
ISSUE and BUGS
    this is a quick and dirty programming job, so I expect this to be a
    brittle program. Use at your own risk, and check the resulting output
    before using mysql.

    Elog is sloppy on logbook formats - Extra attributes could remain in a
    elog logbook file if the user created a logbook, and then deleted
    attributes later on. These extra attribute entries will break the sql
    file, and you will need to delete them from the logbook or from the sql
    file manually.

    elog2sql only tranlates attributes to a fixed element datatype
    (varchar). It doesn't recognize the elog "options" command, and is
    braindead on things like "option boolean".

    elog2sql was tested only on limited datasets (my logbooks), and as such,
    did not test all possible elogd.cfg configuration commands. Since the
    logbook format is not specified in the documentation, I had to work on
    the information in my logbooks. Any changes to this format by the Elog
    develops may break this code.

    elog2sql was tested on elog version 2.3.8. YMMV on other versions.

LICENSE
    The author issues this code under the GPL. (See GPL.txt). Use this code
    at your own risk.

AUTHOR
    dave@davidfannin.com

VERSION
    Date: 2003-07-02 Version 0.99

