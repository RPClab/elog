/********************************************************************\

  Name:         elogd.c
  Created by:   Stefan Ritt

  Contents:     Web server program for Electronic Logbook ELOG

  $Log$
  Revision 2.57  2002/08/06 09:03:41  midas
  Removed itoa()

  Revision 2.56  2002/08/06 08:57:39  midas
  Added email notify flag to password file

  Revision 2.55  2002/08/05 15:37:21  midas
  First version of self-registration

  Revision 2.54  2002/08/02 11:00:10  midas
  Started working on user configuration page

  Revision 2.53  2002/07/31 11:48:08  midas
  Added page wise display

  Revision 2.52  2002/07/30 12:44:54  midas
  Added sortable columns

  Revision 2.51  2002/07/27 14:09:24  midas
  Fixed processing of password file

  Revision 2.50  2002/07/27 06:52:14  midas
  Added guest menu and user_email

  Revision 2.49  2002/07/26 08:40:56  midas
  Fixed type

  Revision 2.48  2002/07/25 15:37:26  midas
  Fixed bug with ss_find_file under unix

  Revision 2.47  2002/07/25 09:22:05  midas
  Removed scandir() for Solaris compatibility

  Revision 2.46  2002/07/23 13:50:11  midas
  Improved speed for threaded display

  Revision 2.45  2002/07/23 11:31:33  midas
  Store encoded user name in 'new' page for expired cookies

  Revision 2.44  2002/07/11 08:49:49  midas
  Fixed caching problem in Konqueror

  Revision 2.43  2002/07/11 08:13:31  midas
  Fixed problem of submitting messages with konqueror

  Revision 2.42  2002/07/11 07:22:42  midas
  Made 'elog:<logbook>/<id>' reference work

  Revision 2.41  2002/07/09 07:37:37  midas
  Fixed bug that 'last xx entries?mode=threaded' was displayed

  Revision 2.40  2002/07/09 07:31:13  midas
  Removed alphasort() for Solaris compatibility

  Revision 2.39  2002/07/09 07:22:12  midas
  Fixed bug in error display on save config file

  Revision 2.38  2002/07/08 08:39:18  midas
  Fixed various small bugs

  Revision 2.37  2002/07/02 07:33:48  midas
  Added attribute lists with commas

  Revision 2.36  2002/07/01 09:32:32  midas
  Fixed problem with submitting '------' as only text

  Revision 2.35  2002/07/01 08:29:08  midas
  Propagage '?mode=xxx' though 'lastxx' commands

  Revision 2.34  2002/07/01 08:13:46  midas
  Fixed problem with wrong color in command '?cmd=Search'

  Revision 2.33  2002/06/26 11:53:43  midas
  Use ts->tm_isdst instead daylight

  Revision 2.32  2002/06/26 11:44:54  midas
  Fixed bug when deleting last message in logbook

  Revision 2.31  2002/06/25 12:08:32  midas
  Version 2.0.3

  Revision 2.30  2002/06/25 11:52:24  midas
  Fixed problem with changeing passwords

  Revision 2.29  2002/06/20 14:53:33  midas
  Synchronize indices if several logbooks share the same data directory

  Revision 2.28  2002/06/20 09:41:11  midas
  Added syntax help link to configuration page

  Revision 2.27  2002/06/20 09:19:10  midas
  Fixed problems with find

  Revision 2.26  2002/06/19 10:58:57  midas
  Fixed bug that 'date format = %A...' always produced 'Sunday'

  Revision 2.25  2002/06/18 13:15:29  midas
  Version 2.0.1

  Revision 2.24  2002/06/18 07:48:33  midas
  Fixed bug with previous submission

  Revision 2.23  2002/06/18 07:32:03  midas
  Add logbook name when URL is specified

  Revision 2.22  2002/06/18 07:22:28  midas
  Removed width from logbook selection page

  Revision 2.21  2002/06/14 18:34:38  midas
  Fixed bug in el_build_index()

  Revision 2.20  2002/06/14 09:28:40  midas
  Show error for URLs like '/logbook/<id>/'

  Revision 2.19  2002/06/14 07:21:38  midas
  Corrected parameters to qsort()

  Revision 2.18  2002/06/14 07:15:22  midas
  Fixed <keep> on resubmits

  Revision 2.17  2002/06/14 06:55:33  midas
  Rebuild index if data file got deleted

  Revision 2.16  2002/06/14 06:46:41  midas
  Introduced wrapping logbook tabs

  Revision 2.15  2002/06/14 06:08:19  midas
  Sort index by date

  Revision 2.14  2002/06/13 12:46:09  midas
  Fixed problem wiht 'reply to:' in subject

  Revision 2.13  2002/06/13 08:59:53  midas
  Made '../last10?mode=summary' work

  Revision 2.12  2002/06/12 10:18:16  midas
  Added redirection if '/' is missing after logbook

  Revision 2.11  2002/06/12 09:30:03  midas
  Added elog:x HTML link

  Revision 2.10  2002/06/12 07:48:56  midas
  Display message ID's

  Revision 2.9  2002/06/11 12:01:56  midas
  Added 'download' command

  Revision 2.8  2002/06/10 11:46:36  midas
  Changed comma display in search result page

  Revision 2.7  2002/06/10 11:22:41  midas
  Added 'Subst on reply' option

  Revision 2.6  2002/06/10 10:38:22  midas
  Added 'top level only' flag

  Revision 2.5  2002/06/07 14:56:53  midas
  Fixed time offset due to DST when using 'Date format'

  Revision 2.4  2002/06/07 14:40:37  midas
  Check URL tail before displaying logbook page

  Revision 2.3  2002/06/07 14:22:00  midas
  Workaround for Konqueror browser

  Revision 2.2  2002/06/07 11:58:43  midas
  'Display search' can now supress display of '#', 'Logbook' and 'Date'

  Revision 2.1  2002/06/07 09:37:02  midas
  Added 'HTML default = 3'

  Revision 2.0  2002/06/06 15:16:39  midas
  First version with new database scheme

  Revision 1.31  2002/06/03 09:55:08  midas
  Added 'start page=' option

  Revision 1.30  2002/06/03 09:37:47  midas
  Fixed bug with MOptions in Email notification

  Revision 1.29  2002/06/03 08:30:44  midas
  Add <br> for replies in HTML format

  Revision 1.28  2002/06/03 08:12:24  midas
  Reversed setuid() and creation of elogd.pid

  Revision 1.27  2002/06/03 08:07:47  midas
  elogd.pid is now created from child

  Revision 1.26  2002/06/03 07:32:27  midas
  Added 'Title image URL' in theme file

  Revision 1.25  2002/05/31 14:20:50  midas
  Added 'user' and 'group' statements in configuration file

  Revision 1.24  2002/05/31 13:24:18  midas
  Use Referer for mail notification URL

  Revision 1.23  2002/05/31 12:51:58  midas
  First version with truely relative paths

  Revision 1.22  2002/05/13 20:50:53  midas
  Fixed problem with daylight savings time

  Revision 1.21  2002/05/03 07:39:16  midas
  Fixed bug with "Content-Length"

  Revision 1.20  2002/05/02 15:42:06  midas
  Removed lingering and do a REUSEADDR by default

  Revision 1.19  2002/05/02 14:45:10  midas
  Evaluage 'HEAD' request (for wget)

  Revision 1.18  2002/04/30 13:40:33  midas
  Version 1.3.5

  Revision 1.17  2002/04/29 08:11:38  midas
  Added icons via IOptions configuration

  Revision 1.16  2002/04/22 10:32:35  midas
  Version 1.3.4

  Revision 1.15  2002/04/22 10:31:58  midas
  Added "logfile", fixed hightlighting problems, thanks to
  Heiko.Schleit@mpi-hd.mpg.de

  Revision 1.14  2002/03/14 11:48:43  midas
  Added .jpeg file extension

  Revision 1.13  2002/02/25 16:12:26  midas
  Added BGImage and BDTImage in themes

  Revision 1.12  2002/02/25 15:31:04  midas
  Made "move to", "copy to" and "submit" (from elog) work in other languages

  Revision 1.11  2002/02/12 16:06:10  midas
  Fixed small bug

  Revision 1.10  2002/01/31 00:51:41  midas
  Small patch to make elogd run under Mac OS X (Darwin), thanks to Dominik Westner <westner@logicunited.com>

  Revision 1.9  2002/01/30 04:26:05  midas
  Added flag 'restrict edit = 0/1'

  Revision 1.8  2002/01/29 10:06:23  midas
  Fixed various bugs with fixed attributes

  Revision 1.7  2002/01/23 08:41:42  midas
  Added "Search all logbooks" flag

  Revision 1.6  2002/01/15 10:23:59  midas
  - Remove "back" button from error display (NS4.7 does not support it)
  - Fixed wrong URL in email notification
  - Submission of new messages possible even if cookie expired during editing

  Revision 1.5  2002/01/14 13:05:41  midas
  - Check for JavaScript in error display
  - Improved decoding of POST message (needed for lynx)

  Revision 1.4  2001/12/21 16:03:23  midas
  Moved themes directories under "themes/"

  Revision 1.3  2001/12/21 15:28:51  midas
  Initial version as separate package, corresponds to V1.3.2


\********************************************************************/

/* Version of ELOG */
#define VERSION "2.0.6"

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#ifdef _MSC_VER
#define OS_WINNT

#define DIR_SEPARATOR '\\'
#define DIR_SEPARATOR_STR "\\"

#define snprintf _snprintf

#include <windows.h>
#include <io.h>
#include <time.h>
#else

#define OS_UNIX

#define TRUE 1
#define FALSE 0

#define DIR_SEPARATOR '/'
#define DIR_SEPARATOR_STR "/"

#define __USE_XOPEN /* needed for crypt() */

typedef int BOOL;

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>

#define closesocket(s) close(s)
#ifndef O_BINARY
#define O_BINARY 0
#endif
#endif

typedef int INT;

#define TELL(fh) lseek(fh, 0, SEEK_CUR)

#define NAME_LENGTH 256
#define SUCCESS       1

#define EL_SUCCESS    1
#define EL_FIRST_MSG  2
#define EL_LAST_MSG   3
#define EL_NO_MSG     4
#define EL_FILE_ERROR 5
#define EL_UPGRADE    6
#define EL_EMPTY      7
#define EL_MEM_ERROR  8

#define EL_FIRST      1
#define EL_LAST       2
#define EL_NEXT       3
#define EL_PREV       4

#define WEB_BUFFER_SIZE 2000000

char return_buffer[WEB_BUFFER_SIZE];
int  strlen_retbuf;
int  keep_alive;
char header_buffer[1000];
int  return_length;
char host_name[256];
char referer[256];
char browser[256];
char cfg_file[256];
char cfg_dir[256];
char tcp_hostname[256];
int  tcp_port = 80;

#define MAX_GROUPS       32
#define MAX_PARAM       100
#define MAX_ATTACHMENTS  10
#define MAX_N_LIST      100
#define MAX_N_ATTR       50
#define VALUE_SIZE      256
#define PARAM_LENGTH    256
#define TEXT_SIZE    100000
#define MAX_PATH_LENGTH 256

char _param[MAX_PARAM][PARAM_LENGTH];
char _value[MAX_PARAM][VALUE_SIZE];
char _text[TEXT_SIZE];
char *_attachment_buffer[MAX_ATTACHMENTS];
INT  _attachment_size[MAX_ATTACHMENTS];
struct in_addr rem_addr;
char rem_host[256];
INT  _sock;
BOOL verbose, use_keepalive;

char *mname[] = {
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"
};

char type_list[MAX_N_LIST][NAME_LENGTH] = {
  "Routine",
  "Other"
};

char category_list[MAX_N_LIST][NAME_LENGTH] = {
  "General",
  "Other",
};

char author_list[MAX_N_LIST][NAME_LENGTH] = {
  ""
};

/* attribute flags */
#define AF_REQUIRED           (1<<0)
#define AF_LOCKED             (1<<1)
#define AF_MULTI              (1<<2)
#define AF_FIXED              (1<<3)
#define AF_ICON               (1<<4)

char attr_list[MAX_N_ATTR][NAME_LENGTH];
char attr_options[MAX_N_ATTR][MAX_N_LIST][NAME_LENGTH];
int  attr_flags[MAX_N_ATTR];

char attr_list_default[][NAME_LENGTH] = {
  "Author",
  "Type",
  "Category",
  "Subject",
  ""
};

char attr_options_default[][MAX_N_LIST][NAME_LENGTH] = {
  { "" },
  { "Routine", "Other" },
  { "General", "Other" },
  { "" }
};

int attr_flags_default[] = {
  AF_REQUIRED,
  0,
  0,
  0
};


struct {
  char ext[32];
  char type[32];
  } filetype[] = {

  { ".JPG",   "image/jpeg" },
  { ".JPEG",  "image/jpeg" },
  { ".GIF",   "image/gif" },
  { ".PNG",   "image/png" },
  { ".PS",    "application/postscript" },
  { ".EPS",   "application/postscript" },
  { ".HTML",  "text/html" },
  { ".HTM",   "text/html" },
  { ".XLS",   "application/x-msexcel" },
  { ".DOC",   "application/msword" },
  { ".PDF",   "application/pdf" },
  { ".TXT",   "text/plain" },
  { ".ASC",   "text/plain" },
  { ".ZIP",   "application/x-zip-compressed" },
  { "" },
};


typedef struct {
  int    message_id;
  char   file_name[32];
  time_t file_time;
  int    offset;
  BOOL   thread_head;
} EL_INDEX;

typedef struct {
  char      name[256];
  char      name_enc[256];
  char      data_dir[256];
  EL_INDEX  *el_index;
  int       *n_el_index;
  int       n_attr;
} LOGBOOK;

typedef struct {
  LOGBOOK   *lbs;
  int       index;
  char      string[256];
} MSG_LIST;

LOGBOOK *lb_list = NULL;

void show_error(char *error);
void show_http_header();
BOOL enum_user_line(LOGBOOK *lbs, int n, char *user);
BOOL get_user_line(LOGBOOK *lbs, char *user, char *password, char *full_name, char *email, char *email_notify);

/*---- Funcions from the MIDAS library -----------------------------*/

BOOL equal_ustring(char *str1, char *str2)
{
  if (str1 == NULL && str2 != NULL)
    return FALSE;
  if (str1 != NULL && str2 == NULL)
    return FALSE;
  if (str1 == NULL && str2 == NULL)
    return TRUE;

  while (*str1)
    if (toupper(*str1++) != toupper(*str2++))
      return FALSE;

  if (*str2)
    return FALSE;

  return TRUE;
}

/*-------------------------------------------------------------------*/

void strsubst(char *string, char name[][NAME_LENGTH], char value[][NAME_LENGTH], int n)
/* subsitute "$name" with value corresponding to name */
{
int  i, j;
char tmp[1000], str[256], uattr[256], *ps, *pt, *p;

  pt = tmp;
  ps = string;
  for (p = strchr(ps, '$') ; p != NULL ; p = strchr(ps, '$'))
    {
    /* copy leading characters */
    j = (int)(p-ps);
    memcpy(pt, ps, j);
    pt += j;
    p++;

    /* extract name */
    strcpy(str, p);
    for (j=0 ; j<(int)strlen(str) ; j++)
      str[j] = toupper(str[j]);

    /* search name */
    for (i=0 ; i<n ; i++)
      {
      strcpy(uattr, name[i]);
      for (j=0 ; j<(int)strlen(uattr) ; j++)
        uattr[j] = toupper(uattr[j]);

      if (strncmp(str, uattr, strlen(uattr)) == 0)
        break;
      }

    /* copy value */
    if (i<n)
      {
      strcpy(pt, value[i]);
      pt += strlen(pt);
      ps = p + strlen(uattr);
      }
    else
      {
      *pt++ = '$';
      ps = p;
      }
    }

  /* copy remainder */
  strcpy(pt, ps);

  /* return result */
  strcpy(string, tmp);
}

/*-------------------------------------------------------------------*/

char *map= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int cind(char c)
{
int i;

  if (c == '=')
    return 0;

  for (i=0 ; i<64 ; i++)
    if (map[i] == c)
      return i;

  return -1;
}

void base64_decode(char *s, char *d)
{
unsigned int t;

  while (*s)
    {
    t = (cind(*s++) << 18) |
        (cind(*s++) << 12) |
        (cind(*s++) << 6)  |
        (cind(*s++) << 0);

    *(d+2) = (char) (t & 0xFF);
    t >>= 8;
    *(d+1) = (char) (t & 0xFF);
    t >>= 8;
    *d = (char) (t & 0xFF);

    d += 3;
    }
  *d = 0;
}

void base64_encode(char *s, char *d)
{
unsigned int t, pad;

  pad = 3 - strlen(s) % 3;
  while (*s)
    {
    t =   (*s++) << 16;
    if (*s)
      t |=  (*s++) << 8;
    if (*s)
      t |=  (*s++) << 0;

    *(d+3) = map[t & 63];
    t >>= 6;
    *(d+2) = map[t & 63];
    t >>= 6;
    *(d+1) = map[t & 63];
    t >>= 6;
    *(d+0) = map[t & 63];

    d += 4;
    }
  *d = 0;
  while (pad--)
    *(--d) = '=';
}

void do_crypt(char *s, char *d)
{
#ifdef USE_CRYPT
  strcpy(d, crypt(s, "el"));
#else
  base64_encode(s, d);
#endif
}

/*-------------------------------------------------------------------*/

INT recv_string(int sock, char *buffer, INT buffer_size, INT millisec)
{
INT            i, n;
fd_set         readfds;
struct timeval timeout;

  n = 0;
  memset(buffer, 0, buffer_size);

  do
    {
    if (millisec > 0)
      {
      FD_ZERO(&readfds);
      FD_SET(sock, &readfds);

      timeout.tv_sec  = millisec / 1000;
      timeout.tv_usec = (millisec % 1000) * 1000;

      select(FD_SETSIZE, (void *) &readfds, NULL, NULL, (void *) &timeout);

      if (!FD_ISSET(sock, &readfds))
        break;
      }

    i = recv(sock, buffer+n, 1, 0);

    if (i<=0)
      break;

    n++;

    if (n >= buffer_size)
      break;

    } while (buffer[n-1] && buffer[n-1] != 10);

  return n-1;
}


INT sendmail(char *smtp_host, char *from, char *to, char *subject, char *text)
{
struct sockaddr_in   bind_addr;
struct hostent       *phe;
int                  s, offset;
char                 buf[80];
char                 str[TEXT_SIZE+1000];
time_t               now;
struct tm            *ts;

  if (verbose)
    printf("\n\nEmail from %s to %s, SMTP host %s:\n", from, to, smtp_host);

  /* create a new socket for connecting to remote server */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1)
    return -1;

  /* connect to remote node port 25 */
  memset(&bind_addr, 0, sizeof(bind_addr));
  bind_addr.sin_family      = AF_INET;
  bind_addr.sin_port        = htons((short) 25);

  phe = gethostbyname(smtp_host);
  if (phe == NULL)
    return -1;
  memcpy((char *)&(bind_addr.sin_addr), phe->h_addr, phe->h_length);

  if (connect(s, (void *) &bind_addr, sizeof(bind_addr)) < 0)
    {
    closesocket(s);
    return -1;
    }

  recv_string(s, str, sizeof(str), 10000);
  if (verbose) puts(str);

  /* drain server messages */
  do
    {
    str[0] = 0;
    recv_string(s, str, sizeof(str), 300);
    if (verbose) puts(str);
    } while (str[0]);

  snprintf(str, sizeof(str) - 1, "HELO %s\r\n", host_name);
  send(s, str, strlen(str), 0);
  if (verbose) puts(str);
  recv_string(s, str, sizeof(str), 3000);
  if (verbose) puts(str);

  snprintf(str, sizeof(str) - 1, "MAIL FROM: <%s>\r\n", from);
  send(s, str, strlen(str), 0);
  if (verbose) puts(str);
  recv_string(s, str, sizeof(str), 3000);
  if (verbose) puts(str);

  snprintf(str, sizeof(str) - 1, "RCPT TO: <%s>\r\n", to);
  send(s, str, strlen(str), 0);
  if (verbose) puts(str);
  recv_string(s, str, sizeof(str), 3000);
  if (verbose) puts(str);

  snprintf(str, sizeof(str) - 1, "DATA\r\n");
  send(s, str, strlen(str), 0);
  if (verbose) puts(str);
  recv_string(s, str, sizeof(str), 3000);
  if (verbose) puts(str);

  snprintf(str, sizeof(str) - 1, "To: %s\r\nFrom: %s\r\nSubject: %s\r\n", to, from, subject);
  send(s, str, strlen(str), 0);
  if (verbose) puts(str);

  time(&now);
  ts = localtime(&now);
  strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S", ts);
  offset = (-(int)timezone);
  if (ts->tm_isdst)
    offset += 3600;
  snprintf(str, sizeof(str) - 1, "Date: %s %+03d%02d\r\n\r\n", buf,
          (int) (offset/3600), (int) ((abs((int)offset)/60) % 60));
  send(s, str, strlen(str), 0);
  if (verbose) puts(str);

  snprintf(str, sizeof(str) - 1, "%s\r\n.\r\n", text);
  send(s, str, strlen(str), 0);
  if (verbose) puts(str);
  recv_string(s, str, sizeof(str), 3000);
  if (verbose) puts(str);

  snprintf(str, sizeof(str) - 1, "QUIT\r\n");
  send(s, str, strlen(str), 0);
  if (verbose) puts(str);
  recv_string(s, str, sizeof(str), 3000);
  if (verbose) puts(str);

  closesocket(s);

  return 1;
}

/*-------------------------------------------------------------------*/

INT ss_daemon_init()
{
#ifdef OS_UNIX

  /* only implemented for UNIX */
  int i, fd, pid;

  if ( (pid = fork()) < 0)
    return 0;
  else if (pid != 0)
    exit(0); /* parent finished */

  /* child continues here */

  /* try and use up stdin, stdout and stderr, so other
     routines writing to stdout etc won't cause havoc. Copied from smbd */
  for (i=0 ; i<3 ; i++)
    {
    close(i);
    fd = open("/dev/null", O_RDWR, 0);
    if (fd < 0)
      fd = open("/dev/null", O_WRONLY, 0);
    if (fd < 0)
      {
      printf("Can't open /dev/null");
      return 0;
      }
    if (fd != i)
      {
      printf("Did not get file descriptor");
      return 0;
      }
    }

  setsid();               /* become session leader */
  chdir("/");             /* change working direcotry (not on NFS!) */
  umask(0);               /* clear our file mode creation mask */

#endif

  return SUCCESS;
}

/*------------------------------------------------------------------*/

/* Parameter extraction from configuration file similar to win.ini */

char *cfgbuffer;

int getcfg(char *group, char *param, char *value)
{
char *str, *p, *pstr;
int  length;
int  fh;

  value[0] = 0;

  /* read configuration file on init */
  if (!cfgbuffer)
    {
    fh = open(cfg_file, O_RDONLY | O_BINARY);
    if (fh < 0)
      return 0;
    length = lseek(fh, 0, SEEK_END);
    lseek(fh, 0, SEEK_SET);
    cfgbuffer = malloc(length+1);
    if (cfgbuffer == NULL)
      {
      close(fh);
      return 0;
      }
    read(fh, cfgbuffer, length);
    cfgbuffer[length] = 0;
    close(fh);
    }

  /* search group */
  str = malloc(10000);
  p = cfgbuffer;
  do
    {
    if (*p == '[')
      {
      p++;
      pstr = str;
      while (*p && *p != ']' && *p != '\n')
        *pstr++ = *p++;
      *pstr = 0;
      if (equal_ustring(str, group))
        {
        /* search parameter */
        p = strchr(p, '\n');
        if (p)
          p++;
        while (p && *p && *p != '[')
          {
          pstr = str;
          while (*p && *p != '=' && *p != '\n')
            *pstr++ = *p++;
          *pstr-- = 0;
          while (pstr > str && (*pstr == ' ' || *pstr == '=' || *pstr == '\t'))
            *pstr-- = 0;

          if (equal_ustring(str, param))
            {
            if (*p == '=')
              {
              p++;
              while (*p == ' ' || *p == '\t')
                p++;
              pstr = str;
              while (*p && *p != '\n' && *p != '\r')
                *pstr++ = *p++;
              *pstr-- = 0;
              while (*pstr == ' ' || *pstr == '\t')
                *pstr-- = 0;

              strcpy(value, str);
              free(str);
              return 1;
              }
            }

          if (p)
            p = strchr(p, '\n');
          if (p)
            p++;
          }
        }
      }
    if (p)
      p = strchr(p, '\n');
    if (p)
      p++;
    } while (p);


  free(str);

  /* if parameter not found in logbook, look in [global] section */
  if (!equal_ustring(group, "global"))
    return getcfg("global", param, value);

  return 0;
}

/*------------------------------------------------------------------*/

int enumcfg(char *group, char *param, char *value, int index)
{
char str[10000], *p, *pstr;
int  i;

  /* open configuration file */
  if (!cfgbuffer)
    getcfg("dummy", "dummy", str);
  if (!cfgbuffer)
    return 0;

  /* search group */
  p = cfgbuffer;
  do
    {
    if (*p == '[')
      {
      p++;
      pstr = str;
      while (*p && *p != ']' && *p != '\n' && *p != '\r')
        *pstr++ = *p++;
      *pstr = 0;
      if (equal_ustring(str, group))
        {
        /* enumerate parameters */
        i = 0;
        p = strchr(p, '\n');
        if (p)
          p++;
        while (p && *p && *p != '[')
          {
          pstr = str;
          while (*p && *p != '=' && *p != '\n' && *p != '\r')
            *pstr++ = *p++;
          *pstr-- = 0;
          while (pstr > str && (*pstr == ' ' || *pstr == '='))
            *pstr-- = 0;

          if (i == index)
            {
            strcpy(param, str);
            if (*p == '=')
              {
              p++;
              while (*p == ' ')
                p++;
              pstr = str;
              while (*p && *p != '\n' && *p != '\r')
                *pstr++ = *p++;
              *pstr-- = 0;
              while (*pstr == ' ')
                *pstr-- = 0;

              if (value)
                strcpy(value, str);
              }
            return 1;
            }

          if (p)
            p = strchr(p, '\n');
          if (p)
            p++;
          i++;
          }
        }
      }
    if (p)
      p = strchr(p, '\n');
    if (p)
      p++;
    } while (p);

  return 0;
}

/*------------------------------------------------------------------*/

int enumgrp(int index, char *group)
{
char str[10000], *p, *pstr;
int  i;

  /* open configuration file */
  if (!cfgbuffer)
    getcfg("dummy", "dummy", str);
  if (!cfgbuffer)
    return 0;

  /* search group */
  p = cfgbuffer;
  i = 0;
  do
    {
    if (*p == '[')
      {
      p++;
      pstr = str;
      while (*p && *p != ']' && *p != '\n' && *p != '\r')
        *pstr++ = *p++;
      *pstr = 0;

      if (i == index)
        {
        strcpy(group, str);
        return 1;
        }

      i++;
      }

    while (*p && *p != '\r' && *p != '\n')
      p++;
    while (*p && (*p == '\r' || *p == '\n'))
      p++;
    } while (*p);

  return 0;
}

/*-------------------------------------------------------------------*/

char *locbuffer = NULL;
char **porig, **ptrans;

/* localization support */
char *loc(char *orig)
{
char language[256], file_name[256], *p;
int  fh, length, n;
static char old_language[256];

  getcfg("global", "Language", language);

  if (!equal_ustring(language, old_language))
    {
    if (equal_ustring(language, "english") ||
        language[0] == 0)
      {
      if (locbuffer)
        {
        free(locbuffer);
        locbuffer = NULL;
        }
      }
    else
      {
      strcpy(file_name, cfg_dir);
      strcat(file_name, "eloglang.");
      strcat(file_name, language);

      fh = open(file_name, O_RDONLY | O_BINARY);
      if (fh < 0)
        return orig;

      length = lseek(fh, 0, SEEK_END);
      lseek(fh, 0, SEEK_SET);
      locbuffer = malloc(length+1);
      if (locbuffer == NULL)
        {
        close(fh);
        return orig;
        }
      read(fh, locbuffer, length);
      locbuffer[length] = 0;
      close(fh);

      /* scan lines, setup orig-translated pointers */
      p = locbuffer;
      n = 0;
      do
        {
        while (*p && (*p == '\r' || *p == '\n'))
          p++;

        if (*p && (*p == ';' || *p == '#' || *p == ' ' || *p == '\t'))
          {
          while (*p && *p != '\n' && *p != '\r')
            p++;
          continue;
          }

        if (n == 0)
          {
          porig = malloc(sizeof(char *) * 2);
          ptrans = malloc(sizeof(char *) * 2);
          }
        else
          {
          porig = realloc(porig, sizeof(char *) * (n + 2));
          ptrans = realloc(ptrans, sizeof(char *) * (n + 2));
          }

        porig[n] = p;
        while (*p && (*p != '=' && *p != '\r' && *p != '\n'))
          p++;

        if (*p && *p != '=')
          continue;

        ptrans[n] = p + 1;
        while (*ptrans[n] == ' ')
          ptrans[n] ++;

        /* remove '=' and surrounding blanks */
        while (*p == '=' || *p == ' ')
          *p-- = 0;

        p = ptrans[n];
        while (*p && *p != '\n' && *p != '\r')
          p++;

        if (p)
          *p++ = 0;

        n++;
        } while (p && *p);

      porig[n] = NULL;
      }

    strcpy(old_language, language);
    }

  if (!locbuffer)
    return orig;

  /* search string and return translation */
  for (n = 0; porig[n] ; n++)
    if (strcmp(orig, porig[n]) == 0)
      {
      if (*ptrans[n])
        return ptrans[n];
      return orig;
      }

  return orig;
}

/*------------------------------------------------------------------*/

/* Parameter extraction from themes file  */

typedef struct {
  char name[32];
  char value[256];
  } THEME;

THEME default_theme [] = {

  { "Table width",            "100%"    },
  { "Frame color",            "#486090" },
  { "Cell BGColor",           "#E6E6E6" },
  { "Border width",           "0"       },

  { "Title BGColor",          "#486090" },
  { "Title Fontcolor",        "#FFFFFF" },
  { "Title Cellpadding",      "0"       },
  { "Title Image",            ""        },
  { "Title Image URL",        ""        },

  { "Merge menus",            "1"       },
  { "Use buttons",            "0"       },

  { "Menu1 BGColor",          "#E0E0E0" },
  { "Menu1 Align",            "left"    },
  { "Menu1 Cellpadding",      "0"       },

  { "Menu2 BGColor",          "#FFFFB0" },
  { "Menu2 Align",            "center"  },
  { "Menu2 Cellpadding",      "0"       },
  { "Menu2 use images",       "0"       },

  { "Categories cellpadding", "3"       },
  { "Categories border",      "0"       },
  { "Categories BGColor1",    "#CCCCFF" },
  { "Categories BGColor2",    "#DDEEBB" },

  { "Text BGColor",           "#FFFFFF" },

  { "List bgcolor1",          "#DDEEBB" },
  { "List bgcolor2",          "#FFFFB0" },

  { "BGImage",                ""        },
  { "BGTImage",               ""        },

  { "Thread image",           ""        },
  { "Thread reply image",     ""        },

  { "" }

};

THEME *theme = NULL;
char  theme_name[80];

/*------------------------------------------------------------------*/

void loadtheme(char *tn)
{
FILE *f;
char *p, line[256], item[256], value[256], file_name[256];
int  i;

  if (theme == NULL)
    theme = malloc(sizeof(default_theme));

  /* copy default theme */
  memcpy(theme, default_theme, sizeof(default_theme));

  /* use default if no name is given */
  if (tn == NULL)
    return;

  memset(file_name, 0, sizeof(file_name));

  strcpy(file_name, cfg_dir);
  strcat(file_name, "themes");
  strcat(file_name, DIR_SEPARATOR_STR);
  strcat(file_name, tn);
  strcat(file_name, DIR_SEPARATOR_STR);
  strcat(file_name, "theme.cfg");

  f = fopen(file_name, "r");
  if (f == NULL)
    return;

  strcpy(theme_name, tn);

  do
    {
    line[0] = 0;
    fgets(line, sizeof(line), f);

    /* ignore comments */
    if (line[0] == ';' || line[0] == '#')
      continue;

    if (strchr(line, '='))
      {
      /* split line into item and value, strop blanks */
      strcpy(item, line);
      p = strchr(item, '=');
      while ((*p == '=' || *p == ' ') && p > item)
        *p-- = 0;
      p = strchr(line, '=');
      while (*p && (*p == '=' || *p == ' '))
        p++;
      strcpy(value, p);
      if (strlen(value) > 0)
        {
        p = value+strlen(value)-1;
        while (p >= value && (*p == ' ' || *p == '\r' || *p == '\n'))
          *(p--) = 0;
        }

      /* find field in _theme and set it */
      for (i=0 ; theme[i].name[0] ; i++)
        if (equal_ustring(item, theme[i].name))
          {
          strcpy(theme[i].value, value);
          break;
          }
      }

    } while (!feof(f));

  fclose(f);

  return;
}

/*------------------------------------------------------------------*/

/* get a certain theme attribute from currently loaded file */

char *gt(char *name)
{
int i;

  if (theme == NULL)
    loadtheme(NULL);

  for (i=0 ; theme[i].name[0] ; i++)
    if (equal_ustring(theme[i].name, name))
      return theme[i].value;

  return "";
}

/*------------------------------------------------------------------*/

void el_decode(char *message, char *key, char *result)
{
char *pc, *ph;

  if (result == NULL)
    return;

  *result = 0;

  ph = strstr(message, "========================================\n");

  if ((pc = strstr(message, key)) != NULL &&
       pc < ph && (*(pc-1) == '\n' || *(pc-1) == '\r'))
    {
    for (pc=strstr(message, key)+strlen(key) ; *pc != '\n' && *pc != '\r' ; )
      *result++ = *pc++;
    *result = 0;
    }
  else
    *result = 0;
}

/*------------------------------------------------------------------*/

/* Simplified copy of fnmatch() for Cygwin where fnmatch is not defined */

#define EOS '\0'

int fnmatch1(const char *pattern, const char *string)
{
const char *stringstart;
char c, test;

  for (stringstart = string;;)
    switch (c = *pattern++) {
    case EOS:
      return (*string == EOS ? 0 : 1);
    case '?':
      if (*string == EOS)
        return (1);
      ++string;
      break;
    case '*':
      c = *pattern;
      /* Collapse multiple stars. */
      while (c == '*')
        c = *++pattern;

      /* Optimize for pattern with * at end or before /. */
      if (c == EOS)
        return (0);

      /* General case, use recursion. */
      while ((test = *string) != EOS)
        {
        if (!fnmatch1(pattern, string))
          return (0);
        ++string;
        }
      return (1);
      /* FALLTHROUGH */
    default:
      if (c != *string)
        return (1);
      string++;
      break;
    }
}

/*------------------------------------------------------------------*/

INT ss_file_find(char *path, char *pattern, char **plist)
/********************************************************************\

  Routine: ss_file_find

  Purpose: Return list of files matching 'pattern' from the 'path' location

  Input:
    char  *path             Name of a file in file system to check
    char  *pattern          pattern string (wildcard allowed)

  Output:
    char  **plist           pointer to the file list

  Function value:
    int                     Number of files matching request

\********************************************************************/
{
#ifdef OS_UNIX
  DIR *dir_pointer;
  struct dirent *dp;
  int i;

  if ((dir_pointer = opendir(path)) == NULL)
    return 0;
  *plist = (char *) malloc(MAX_PATH_LENGTH);
  i = 0;
  for (dp = readdir(dir_pointer); dp != NULL; dp = readdir(dir_pointer))
    {
    if (fnmatch1(pattern, dp->d_name) == 0)
      {
      *plist = (char *)realloc(*plist, (i+1)*MAX_PATH_LENGTH);
      strncpy(*plist+(i*MAX_PATH_LENGTH), dp->d_name, strlen(dp->d_name));
      *(*plist+(i*MAX_PATH_LENGTH)+strlen(dp->d_name)) = '\0';
      i++;
      seekdir(dir_pointer, telldir(dir_pointer));
      }
    }
  closedir(dir_pointer);
  return i;
#endif

#ifdef OS_WINNT
  HANDLE pffile;
  LPWIN32_FIND_DATA lpfdata;
  char str[255];
  int  i, first;

  strcpy(str,path);
  strcat(str,"\\");
  strcat(str,pattern);
  first = 1;
  i = 0;
  lpfdata = malloc(sizeof(WIN32_FIND_DATA));
  *plist = (char *) malloc(MAX_PATH_LENGTH);
  pffile = FindFirstFile(str, lpfdata);
  if (pffile == INVALID_HANDLE_VALUE)
    return 0;
  first = 0;
  *plist = (char *)realloc(*plist, (i+1)*MAX_PATH_LENGTH);
  strncpy(*plist+(i*MAX_PATH_LENGTH), lpfdata->cFileName, strlen(lpfdata->cFileName));
  *(*plist+(i*MAX_PATH_LENGTH)+strlen(lpfdata->cFileName)) = '\0';
  i++;
  while (FindNextFile(pffile, lpfdata))
    {
    *plist = (char *)realloc(*plist, (i+1)*MAX_PATH_LENGTH);
    strncpy(*plist+(i*MAX_PATH_LENGTH), lpfdata->cFileName, strlen(lpfdata->cFileName));
    *(*plist+(i*MAX_PATH_LENGTH)+strlen(lpfdata->cFileName)) = '\0';
    i++;
    }
  free(lpfdata);
  return i;
#endif
}

/*------------------------------------------------------------------*/

int eli_compare(const void *e1, const void *e2)
{

  if (((EL_INDEX *)e1)->file_time < ((EL_INDEX *)e2)->file_time)
    return -1;
  if (((EL_INDEX *)e1)->file_time > ((EL_INDEX *)e2)->file_time)
    return 1;
  return 0;
}

/*------------------------------------------------------------------*/

int el_build_index(LOGBOOK *lbs, BOOL rebuild)
/* scan all ??????a.log files and build an index table in eli[] */
{
char      *file_list, str[256], date[256], dir[256], file_name[256], *buffer, *p,
          in_reply_to[80];
int       index, n, length;
int       i, fh;
time_t    ltime;
struct tm tms;

  if (rebuild)
    {
    free(lbs->el_index);
    free(lbs->n_el_index);
    }

  /* check if this logbook has same data dir as previous */
  for (i=0 ; lb_list[i].name[0] && &lb_list[i] != lbs; i++)
    if (equal_ustring(lb_list[i].data_dir, lbs->data_dir))
      break;

  if (equal_ustring(lb_list[i].data_dir, lbs->data_dir) && &lb_list[i] != lbs)
    {
    if (verbose)
      printf("  Same index as logbook %s\n", lb_list[i].name);

    lbs->el_index = lb_list[i].el_index;
    lbs->n_el_index = lb_list[i].n_el_index;
    return EL_SUCCESS;
    }

  lbs->n_el_index = malloc(sizeof(int));
  *lbs->n_el_index = 0;
  lbs->el_index = malloc(0);

  /* get data directory */
  strcpy(dir, lbs->data_dir);

  file_list = NULL;
  n = ss_file_find(dir, "??????a.log", &file_list);
  if (n == 0)
    {
    if (file_list)
      free(file_list);
    file_list = NULL;

    n = ss_file_find(dir, "??????.log", &file_list);
    if (n > 0)
      return EL_UPGRADE;

    return EL_EMPTY;
    }

  /* go through all files */
  for (index=0 ; index<n ; index++)
    {
    strcpy(file_name, dir);
    strcat(file_name, file_list+index*MAX_PATH_LENGTH);

    fh = open(file_name, O_RDWR | O_BINARY, 0644);

    if (fh < 0)
      return EL_FILE_ERROR;

    /* read file into buffer */
    length = lseek(fh, 0, SEEK_END);

    if (length > 0)
      {
      buffer = malloc(length+1);
      if (buffer == NULL)
        {
        printf("Not enough memory to allocate file buffer (%d bytes)\n", length);
        return EL_MEM_ERROR;
        }

      lseek(fh, 0, SEEK_SET);
      read(fh, buffer, length);
      buffer[length] = 0;
      close(fh);

      /* go through buffer */
      p = buffer;

      do
        {
        p = strstr(p, "$@MID@$:");

        if (p)
          {
          lbs->el_index = realloc(lbs->el_index, sizeof(EL_INDEX)*(*lbs->n_el_index+1));
          if (lbs->el_index == NULL)
            {
            printf("Not enough memory to allocate message index\n");
            return EL_MEM_ERROR;
            }

          strcpy(str, file_list+index*MAX_PATH_LENGTH);
          strcpy(lbs->el_index[*lbs->n_el_index].file_name, str);

          el_decode(p, "Date: ", date);
          el_decode(p, "In reply to: ", in_reply_to);

          memset(&tms, 0, sizeof(struct tm));

          for (i=0 ; i<12 ; i++)
            if (strncmp(date+4, mname[i], 3) == 0)
              break;
          tms.tm_mon = i;

          tms.tm_mday  = atoi(date+8);
          tms.tm_hour  = atoi(date+11);
          tms.tm_min   = atoi(date+14);
          tms.tm_sec   = atoi(date+17);
          tms.tm_year  = atoi(date+20)-1900;
          tms.tm_isdst = -1;

          if (tms.tm_year < 90)
            tms.tm_year += 100;
          ltime = mktime(&tms);

          lbs->el_index[*lbs->n_el_index].file_time = ltime;

          lbs->el_index[*lbs->n_el_index].message_id = atoi(p+8);
          lbs->el_index[*lbs->n_el_index].offset = (int) p - (int) buffer;
          lbs->el_index[*lbs->n_el_index].thread_head = (in_reply_to[0] == 0);

          if (lbs->el_index[*lbs->n_el_index].message_id > 0)
            {
            if (verbose)
              printf("  ID %3d in %s, offset %5d, %s\n",
                lbs->el_index[*lbs->n_el_index].message_id, str,
                lbs->el_index[*lbs->n_el_index].offset,
                lbs->el_index[*lbs->n_el_index].thread_head ? "thread head" : "reply");

            /* valid ID */
            (*lbs->n_el_index)++;
            }

          p += 8;
          }

        } while (p);

      free(buffer);
      }

    }

  free(file_list);

  /* sort entries according to date */
  qsort(lbs->el_index, *lbs->n_el_index, sizeof(EL_INDEX), eli_compare);

  if (verbose)
    {
    printf("After sort:\n");
    for (i=0 ; i<*lbs->n_el_index ; i++)
      printf("  ID %3d in %s, offset %5d\n",
        lbs->el_index[i].message_id, lbs->el_index[i].file_name,
        lbs->el_index[i].offset);
    }

  return EL_SUCCESS;
}

/*------------------------------------------------------------------*/

int el_search_message(LOGBOOK *lbs, int mode, int message_id, BOOL head_only)
/********************************************************************\

  Routine: el_search_message

  Purpose: Search for a specific message in a logbook

  Input:
    int   mode              Search mode, EL_FIRST, EL_LAST, EL_NEXT, EL_PREV
    int   message_id        Message id for EL_NEXT and EL_PREV

  Function value:
    int                     New message id

\********************************************************************/
{
int i;

  if (lbs->n_el_index == 0)
    return 0;

  if (mode == EL_FIRST)
    {
    if (head_only)
      {
      for (i=0 ; i<*lbs->n_el_index ; i++)
        if (lbs->el_index[i].thread_head)
          return lbs->el_index[i].message_id;

      return 0;
      }
    if (*lbs->n_el_index == 0)
      return 0;
    return lbs->el_index[0].message_id;
    }

  if (mode == EL_LAST)
    {
    if (head_only)
      {
      for (i=*lbs->n_el_index-1 ; i>=0 ; i--)
        if (lbs->el_index[i].thread_head)
          return lbs->el_index[i].message_id;

      return 0;
      }
    if (*lbs->n_el_index == 0)
      return 0;
    return lbs->el_index[*lbs->n_el_index-1].message_id;
    }

  if (mode == EL_NEXT)
    {
    for (i=0 ; i<*lbs->n_el_index ; i++)
      if (lbs->el_index[i].message_id == message_id)
        break;

    if (i == *lbs->n_el_index)
      return 0; // message not found

    if (i == *lbs->n_el_index-1)
      return 0; // last message

    if (head_only)
      {
      for (i++ ; i<*lbs->n_el_index ; i++)
        if (lbs->el_index[i].thread_head)
          return lbs->el_index[i].message_id;

      return 0;
      }

    return lbs->el_index[i+1].message_id;
    }

  if (mode == EL_PREV)
    {
    for (i=0 ; i<*lbs->n_el_index ; i++)
      if (lbs->el_index[i].message_id == message_id)
        break;

    if (i == *lbs->n_el_index)
      return 0; // message not found

    if (i == 0)
      return 0; // first message

    if (head_only)
      {
      for (i-- ; i>=0 ; i--)
        if (lbs->el_index[i].thread_head)
          return lbs->el_index[i].message_id;

      return 0;
      }

    return lbs->el_index[i-1].message_id;
    }

  return 0;
}

/*------------------------------------------------------------------*/

INT el_retrieve(LOGBOOK *lbs,
                int message_id, char *date, char attr_list[MAX_N_ATTR][NAME_LENGTH],
                char attrib[MAX_N_ATTR][NAME_LENGTH], int n_attr,
                char *text, int *textsize,
                char *in_reply_to, char *reply_to,
                char attachment[MAX_ATTACHMENTS][256],
                char *encoding)
/********************************************************************\

  Routine: el_retrieve

  Purpose: Retrieve an ELog entry by its message tab

  Input:
    LOGBOOK lbs             Logbook structure
    int    message_id       Message ID to retrieve
    int    *size            Size of text buffer

  Output:
    char   *tag             tag of retrieved message
    char   *date            Date/time of message recording
    char   attr_list        Names of attributes
    char   attrib           Values of attributes
    int    n_attr           Number of attributes
    char   *text            Message text
    char   *in_reply_to     Original message if this one is a reply
    char   *reply_to        Replies for current message
    char   *attachment[]    File attachments
    char   *encoding        Encoding of message
    int    *size            Actual message text size

  Function value:
    EL_SUCCESS              Successful completion
    EL_EMPTY                Logbook is empty
    EL_NO_MSG               Message doesn't exist
    EL_FILE_ERROR           Internal error

\********************************************************************/
{
int     i, index, size, fh;
char    str[256], file_name[256], *p;
char    message[TEXT_SIZE+1000], attachment_all[64*MAX_ATTACHMENTS];

  if (message_id == 0)
    /* open most recent message */
    message_id = el_search_message(lbs, EL_LAST, 0, FALSE);

  if (message_id == 0)
    return EL_EMPTY;

  for (index = 0 ; index < *lbs->n_el_index ; index++)
    if (lbs->el_index[index].message_id == message_id)
      break;

  if (index == *lbs->n_el_index)
    return EL_NO_MSG;

  sprintf(file_name, "%s%s", lbs->data_dir, lbs->el_index[index].file_name);
  fh = open(file_name, O_RDWR | O_BINARY, 0644);
  if (fh < 0)
    {
    /* file might have been deleted, rebuild index */
    el_build_index(lbs, TRUE);
    return el_retrieve(lbs, message_id, date, attr_list, attrib, n_attr, text,
                       textsize, in_reply_to, reply_to, attachment, encoding);
    }

  lseek(fh, lbs->el_index[index].offset, SEEK_SET);
  i = read(fh, message, sizeof(message)-1);
  if (i <= 0)
    {
    close(fh);
    return EL_FILE_ERROR;
    }

  message[i] = 0;
  close(fh);

  if (strncmp(message, "$@MID@$:", 8) != 0)
    {
    /* file might have been edited, rebuild index */
    el_build_index(lbs, TRUE);
    return el_retrieve(lbs, message_id, date, attr_list, attrib, n_attr, text,
                       textsize, in_reply_to, reply_to, attachment, encoding);
    }

  /* check for correct ID */
  if (atoi(message+8) != message_id)
    return EL_FILE_ERROR;

  /* decode message size */
  p = strstr(message+8, "$@MID@$:");
  if (p == NULL)
    size = strlen(message);
  else
    size = (int) p - (int) message;

  message[size] = 0;

  /* decode message */
  if (date)
    el_decode(message, "Date: ", date);
  if (reply_to)
    el_decode(message, "Reply to: ", reply_to);
  if (in_reply_to)
    el_decode(message, "In reply to: ", in_reply_to);

  if (attrib)
    for (i=0 ; i<n_attr ; i++)
      {
      sprintf(str, "%s: ", attr_list[i]);
      el_decode(message, str, attrib[i]);
      }

  el_decode(message, "Attachment: ", attachment_all);
  if (encoding)
    el_decode(message, "Encoding: ", encoding);

  if (attachment)
    {
    /* break apart attachements */
    for (i=0 ; i<MAX_ATTACHMENTS ; i++)
      if (attachment[i] != NULL)
        attachment[i][0] = 0;

    for (i=0 ; i<MAX_ATTACHMENTS ; i++)
      {
      if (attachment[i] != NULL)
        {
        if (i == 0)
          p = strtok(attachment_all, ",");
        else
          p = strtok(NULL, ",");

        if (p != NULL)
          strcpy(attachment[i], p);
        else
          break;
        }
      }
    }

  p = strstr(message, "========================================\n");

  /* check for \n -> \r conversion (e.g. zipping/unzipping) */
  if (p == NULL)
    p = strstr(message, "========================================\r");

  if (text)
    {
    if (p != NULL)
      {
      p += 41;
      if ((int) strlen(p) >= *textsize)
        {
        strncpy(text, p, *textsize-1);
        text[*textsize-1] = 0;
        show_error("Message too long to display. Please increase TEXT_SIZE and recompile elogd.");
        return EL_FILE_ERROR;
        }
      else
        {
        strcpy(text, p);

        /* strip CR at end */
        if (text[strlen(text)-1] == '\n')
          {
          text[strlen(text)-1] = 0;
          if (text[strlen(text)-1] == '\r')
            text[strlen(text)-1] = 0;
          }

        *textsize = strlen(text);
        }
      }
    else
      {
      text[0] = 0;
      *textsize = 0;
      }
    }

  return EL_SUCCESS;
}

/*------------------------------------------------------------------*/

int el_submit(LOGBOOK *lbs, int message_id,
              char *date,
              char attr_name[MAX_N_ATTR][NAME_LENGTH],
              char attr_value[MAX_N_ATTR][NAME_LENGTH],
              int n_attr, char *text,
              char *in_reply_to, char *reply_to,
              char *encoding,
              char afilename[MAX_ATTACHMENTS][256],
              char *buffer[MAX_ATTACHMENTS],
              INT buffer_size[MAX_ATTACHMENTS])
/********************************************************************\

  Routine: el_submit

  Purpose: Submit an ELog entry

  Input:
    LOGBOOK lbs             Logbook structure
    int    message_id       Message id for existing message, 0 for
                            new message
    char   *date            Message date
    char   attr_name[][]    Name of attributes
    char   attr_value[][]   Value of attributes
    int    n_attr           Number of attributes

    char   *text            Message text
    char   *in_reply_to     In reply to this message
    char   *reply_to        Replie(s) to this message
    char   *encoding        Text encoding, either HTML or plain

    char   *afilename[]     File name of attachments
    char   *buffer[]        Attachment contents
    INT    *buffer_size[]   Size of attachment in bytes
    char   *tag             If given, edit existing message
    INT    *tag_size        Maximum size of tag

  Function value:
    int                     New message ID

\********************************************************************/
{
INT     n, i, j, size, fh, index, tail_size, orig_size, delta, reply_id;
struct  tm tms;
char    file_name[256], afile_name[MAX_ATTACHMENTS][256], dir[256], str[256],
        attachment_all[64*MAX_ATTACHMENTS],
        rep1[256], rep2[256];
time_t  now, ltime;
char    message[TEXT_SIZE+100], *p;
BOOL    bedit;

  for (index = 0 ; index < MAX_ATTACHMENTS ; index++)
    {
    /* generate filename for attachment */
    afile_name[index][0] = file_name[0] = 0;

    if (equal_ustring(afilename[index], loc("<delete>")))
      {
      strcpy(afile_name[index], loc("<delete>"));
      }
    else if (afilename[index][0] && buffer_size[index] == 0)
      {
      /* resubmission of existing attachment */
      strcpy(afile_name[index], afilename[index]);
      }
    else
      {
      if (afilename[index][0])
        {
        /* strip directory, add date and time to filename */

        strcpy(file_name, afilename[index]);
        p = file_name;
        while (strchr(p, ':'))
          p = strchr(p, ':')+1;
        while (strchr(p, '\\'))
          p = strchr(p, '\\')+1; /* NT */
        while (strchr(p, '/'))
          p = strchr(p, '/')+1;  /* Unix */

        /* assemble ELog filename */
        if (p[0])
          {
          strcpy(dir, lbs->data_dir);

          time(&now);
          memcpy(&tms, localtime(&now), sizeof(struct tm));

          strcpy(str, p);
          sprintf(afile_name[index], "%02d%02d%02d_%02d%02d%02d_%s",
                  tms.tm_year % 100, tms.tm_mon+1, tms.tm_mday,
                  tms.tm_hour, tms.tm_min, tms.tm_sec, str);
          sprintf(file_name, "%s%02d%02d%02d_%02d%02d%02d_%s", dir,
                  tms.tm_year % 100, tms.tm_mon+1, tms.tm_mday,
                  tms.tm_hour, tms.tm_min, tms.tm_sec, str);

          /* save attachment */
          fh = open(file_name, O_CREAT | O_RDWR | O_BINARY, 0644);
          if (fh < 0)
            {
            printf("Cannot write attachment file \"%s\"", file_name);
            }
          else
            {
            write(fh, buffer[index], buffer_size[index]);
            close(fh);
            }
          }
        }
      }
    }

  /* generate new file name YYMMDD.log in data directory */
  strcpy(dir, lbs->data_dir);

  bedit = (message_id > 0);
  rep1[0] = rep2[0] = 0;

  if (bedit)
    {
    /* edit existing message */
    for (index=0 ; index<*lbs->n_el_index ; index++)
      if (lbs->el_index[index].message_id == message_id)
        break;

    if (index == *lbs->n_el_index)
      return -1;

    sprintf(file_name, "%s%s", lbs->data_dir, lbs->el_index[index].file_name);
    fh = open(file_name, O_CREAT | O_RDWR | O_BINARY, 0644);
    if (fh < 0)
      return -1;

    lseek(fh, lbs->el_index[index].offset, SEEK_SET);
    i = read(fh, message, sizeof(message)-1);
    message[i] = 0;

    /* check for valid message */
    if (strncmp(message, "$@MID@$:", 8) != 0)
      {
      close(fh);

      /* file might have been edited, rebuild index */
      el_build_index(lbs, TRUE);
      return el_submit(lbs, message_id, date, attr_name, attr_value, n_attr, text,
                       in_reply_to, reply_to, encoding, afilename, buffer, buffer_size);
      }

    /* check for correct ID */
    if (atoi(message+8) != message_id)
      {
      close(fh);
      return -1;
      }

    /* decode message size */
    p = strstr(message+8, "$@MID@$:");
    if (p == NULL)
      size = strlen(message);
    else
      size = (int) p - (int) message;

    message[size] = 0;

    if (equal_ustring(date, "<keep>"))
      el_decode(message, "Date: ", date);
    if (equal_ustring(reply_to, "<keep>"))
      el_decode(message, "Reply to: ", reply_to);
    if (equal_ustring(in_reply_to, "<keep>"))
      el_decode(message, "In reply to: ", in_reply_to);
    el_decode(message, "Attachment: ", attachment_all);

    /* buffer tail of logfile */
    lseek(fh, 0, SEEK_END);
    orig_size = size;
    tail_size = TELL(fh) - (lbs->el_index[index].offset+size);

    if (tail_size > 0)
      {
      buffer = malloc(tail_size);
      if (buffer == NULL)
        {
        close(fh);
        return -1;
        }

      lseek(fh, lbs->el_index[index].offset+size, SEEK_SET);
      n = read(fh, buffer, tail_size);
      }
    lseek(fh, lbs->el_index[index].offset, SEEK_SET);
    }
  else
    {
    /* create new message */
    if (!date[0])
      {
      time(&now);
      strcpy(date, ctime(&now));
      date[24] = 0;
      }

    for (i=0 ; i<12 ; i++)
      if (strncmp(date+4, mname[i], 3) == 0)
        break;

    memset(&tms, 0, sizeof(struct tm));
    tms.tm_mon = i;
    tms.tm_mday = atoi(date+8);
    tms.tm_hour = atoi(date+11);
    tms.tm_min  = atoi(date+14);
    tms.tm_sec  = atoi(date+17);
    tms.tm_year = atoi(date+20)-1900;

    if (tms.tm_year < 90)
      tms.tm_year += 100;
    ltime = mktime(&tms);

    if (date[8] == ' ')
      date[8] = '0';

    sprintf(file_name, "%c%c%02d%c%ca.log",
            date[22], date[23], i+1, date[8], date[9]);

    sprintf(str, "%s%s", dir, file_name);
    fh = open(str, O_CREAT | O_RDWR | O_BINARY, 0644);
    if (fh < 0)
      return -1;

    lseek(fh, 0, SEEK_END);

    /* new message id is old plus one */
    message_id = 1;
    for (i= 0 ; i<*lbs->n_el_index ; i++)
      if (lbs->el_index[i].message_id >= message_id)
        message_id = lbs->el_index[i].message_id + 1;

    /* enter message in index */
    (*lbs->n_el_index)++;
    lbs->el_index = realloc(lbs->el_index, sizeof(EL_INDEX)*(*lbs->n_el_index));
    lbs->el_index[*lbs->n_el_index-1].message_id = message_id;
    strcpy(lbs->el_index[*lbs->n_el_index-1].file_name, file_name);
    lbs->el_index[*lbs->n_el_index-1].file_time = ltime;
    lbs->el_index[*lbs->n_el_index-1].offset = TELL(fh);
    lbs->el_index[*lbs->n_el_index-1].thread_head = (in_reply_to[0] == 0);

    /* if index not ordered, sort it */
    i = *lbs->n_el_index;
    if (i > 1 && lbs->el_index[i-1].file_time < lbs->el_index[i-2].file_time)
      qsort(lbs->el_index, i, sizeof(EL_INDEX), eli_compare);

    /* if other logbook has same index, update pointers */
    for (i=0 ; lb_list[i].name[0] ; i++)
      if (&lb_list[i] != lbs && lb_list[i].n_el_index == lbs->n_el_index)
        lb_list[i].el_index = lbs->el_index;
    }

  /* compose message */

  sprintf(message, "$@MID@$: %d\n", message_id);
  sprintf(message+strlen(message), "Date: %s\n", date);

  if (reply_to[0])
    sprintf(message+strlen(message), "Reply to: %s\n", reply_to);

  if (in_reply_to[0])
    sprintf(message+strlen(message), "In reply to: %s\n", in_reply_to);

  for (i=0 ; i<n_attr ; i++)
    sprintf(message+strlen(message), "%s: %s\n", attr_name[i], attr_value[i]);

  /* keep original attachment if edit and no new attachment */

  if (bedit)
    {
    for (i=n=0 ; i<MAX_ATTACHMENTS ; i++)
      {
      if (i == 0)
        p = strtok(attachment_all, ",");
      else
        if (p != NULL)
          p = strtok(NULL, ",");

      if (p && (afile_name[i][0] || equal_ustring(afile_name[i], loc("<delete>"))))
        {
        /* delete old attachment */
        strcpy(str, lbs->data_dir);
        strcat(str, p);
        remove(str);
        }

      if (afile_name[i][0] && !equal_ustring(afile_name[i], loc("<delete>")))
        {
        if (n == 0)
          {
          sprintf(message+strlen(message), "Attachment: %s", afile_name[i]);
          n++;
          }
        else
          sprintf(message+strlen(message), ",%s", afile_name[i]);
        }

      else if (p && !equal_ustring(afile_name[i], loc("<delete>")))
        {
        if (n == 0)
          {
          sprintf(message+strlen(message), "Attachment: %s", p);
          n++;
          }
        else
          sprintf(message+strlen(message), ",%s", p);
        }

      }
    }
  else
    {
    sprintf(message+strlen(message), "Attachment: %s", afile_name[0]);
    for (i=1 ; i<MAX_ATTACHMENTS ; i++)
      if (afile_name[i][0])
        sprintf(message+strlen(message), ",%s", afile_name[i]);
    }
  sprintf(message+strlen(message), "\n");

  sprintf(message+strlen(message), "Encoding: %s\n", encoding);
  sprintf(message+strlen(message), "========================================\n");
  strcat(message, text);
  strcat(message, "\n");

  write(fh, message, strlen(message));

  if (bedit)
    {
    if (tail_size > 0)
      {
      n = write(fh, buffer, tail_size);
      free(buffer);

      /* correct offsets for remaining messages in same file */
      delta = strlen(message) - orig_size;

      for (i=0 ; i<*lbs->n_el_index ; i++)
        if (lbs->el_index[i].message_id == message_id)
          break;

      for (j = i+1 ; j<*lbs->n_el_index &&
           equal_ustring(lbs->el_index[i].file_name, lbs->el_index[j].file_name); j++)
        lbs->el_index[j].offset += delta;
      }

    /* truncate file here */
#ifdef _MSC_VER
    chsize(fh, TELL(fh));
#else
    ftruncate(fh, TELL(fh));
#endif
    }

  close(fh);

  /* if reply, mark original message */
  if (in_reply_to[0] && !bedit && atoi(in_reply_to) > 0)
    {
    char date[80], attr[MAX_N_ATTR][NAME_LENGTH], enc[80],
         att[MAX_ATTACHMENTS][256], reply_to[256];

    reply_id = atoi(in_reply_to);

    /* retrieve original message */
    size = sizeof(message);
    el_retrieve(lbs, reply_id, date, attr_list, attr, n_attr,
                message, &size, in_reply_to, reply_to, att, enc);

    if (reply_to[0])
      strcat(reply_to, ", ");
    sprintf(reply_to + strlen(reply_to), "%d", message_id);

    /* don't resubmit attachments */
    memset(att, 0, sizeof(att));

    /* write modified message */
    el_submit(lbs, reply_id, date, attr_list, attr, n_attr,
              message, in_reply_to, reply_to, enc, att, NULL, NULL);
    }

  return message_id;
}

/*------------------------------------------------------------------*/

void remove_reference(LOGBOOK *lbs, int message_id, int remove_id, BOOL reply_to_flag)
{
char date[80], attr[MAX_N_ATTR][NAME_LENGTH], enc[80], in_reply_to[80], reply_to[256],
     att[MAX_ATTACHMENTS][256];
char *p, *ps, message[TEXT_SIZE+1000];
int  size, status;

  /* retrieve original message */
  size = sizeof(message);
  status = el_retrieve(lbs, message_id, date, attr_list, attr, lbs->n_attr,
                       message, &size, in_reply_to, reply_to, att, enc);
  if (status != EL_SUCCESS)
    return;

  if (reply_to_flag)
    p = reply_to;
  else
    p = in_reply_to;

  while (*p)
    {
    while (*p && (*p == ',' || *p == ' '))
      p++;

    ps = p;
    while (isdigit(*ps))
      ps++;

    while (*ps && (*ps == ',' || *ps == ' '))
      ps++;

    if (atoi(p) == remove_id)
      strcpy(p, ps);
    else
      while (isdigit(*p))
        p++;
    }

  /* don't resubmit attachments */
  memset(att, 0, sizeof(att));

  /* write modified message */
  el_submit(lbs, message_id, date, attr_list, attr, lbs->n_attr,
            message, in_reply_to, reply_to, enc, att, NULL, NULL);
}

/*------------------------------------------------------------------*/

INT el_delete_message(LOGBOOK *lbs, int message_id, BOOL delete_attachments,
                      char attachment[MAX_ATTACHMENTS][256], BOOL delete_bw_ref)
/********************************************************************\

  Routine: el_delete_message

  Purpose: Delete an ELog entry including attachments

  Input:
      LOGBOOK *lbs          Pointer to logbook structure
      int     message_id    Message ID
      BOOL    delete_attachments   Delete attachments if TRUE
      char    attachment    Used to return attachments (on move)

  Output:
    <none>

  Function value:
    EL_SUCCESS              Successful completion

\********************************************************************/
{
INT  i, index, n, size, fh, tail_size;
char str[256], file_name[256], reply_to[80], in_reply_to[256];
char *buffer, *p;
char message[TEXT_SIZE+1000], attachment_all[64*MAX_ATTACHMENTS];

  for (index = 0 ; index < *lbs->n_el_index ; index++)
    if (lbs->el_index[index].message_id == message_id)
      break;

  if (index == *lbs->n_el_index)
    return -1;

  sprintf(file_name, "%s%s", lbs->data_dir, lbs->el_index[index].file_name);
  fh = open(file_name, O_RDWR | O_BINARY, 0644);
  if (fh < 0)
    return EL_FILE_ERROR;

  lseek(fh, lbs->el_index[index].offset, SEEK_SET);
  i = read(fh, message, sizeof(message)-1);
  if (i <= 0)
    {
    close(fh);
    return EL_FILE_ERROR;
    }

  message[i] = 0;

  if (strncmp(message, "$@MID@$:", 8) != 0)
    {
    close(fh);

    /* file might have been edited, rebuild index */
    el_build_index(lbs, TRUE);
    return el_delete_message(lbs, message_id, delete_attachments,
                             attachment, delete_bw_ref);
    }

  /* check for correct ID */
  if (atoi(message+8) != message_id)
    {
    close(fh);
    return EL_FILE_ERROR;
    }

  /* decode message size */
  p = strstr(message+8, "$@MID@$:");
  if (p == NULL)
    size = strlen(message);
  else
    size = (int) p - (int) message;

  message[size] = 0;

  /* delete attachments */
  el_decode(message, "Attachment: ", attachment_all);

  for (i=0 ; i<MAX_ATTACHMENTS ; i++)
    {
    if (i == 0)
      p = strtok(attachment_all, ",");
    else
      p = strtok(NULL, ",");

    if (attachment != NULL)
      {
      if (attachment[i][0] && p)
        {
        /* delete old attachment if new one exists */
        strcpy(str, lbs->data_dir);
        strcat(str, p);
        remove(str);
        }

      /* return old attachment if no new one */
      if (!attachment[i][0] && p)
        strcpy(attachment[i], p);
      }

    if (delete_attachments && p)
      {
      strcpy(str, lbs->data_dir);
      strcat(str, p);
      remove(str);
      }
    }

  /* decode references */
  el_decode(message, "Reply to: ", reply_to);
  el_decode(message, "In reply to: ", in_reply_to);

  /* buffer tail of logfile */
  lseek(fh, 0, SEEK_END);
  tail_size = TELL(fh) - (lbs->el_index[index].offset+size);

  if (tail_size > 0)
    {
    buffer = malloc(tail_size);
    if (buffer == NULL)
      {
      close(fh);
      return EL_FILE_ERROR;
      }

    lseek(fh, lbs->el_index[index].offset+size, SEEK_SET);
    n = read(fh, buffer, tail_size);
    }
  lseek(fh, lbs->el_index[index].offset, SEEK_SET);

  if (tail_size > 0)
    {
    n = write(fh, buffer, tail_size);
    free(buffer);
    }

  /* truncate file here */
#ifdef OS_WINNT
  chsize(fh, TELL(fh));
#else
  ftruncate(fh, TELL(fh));
#endif

  /* if file length gets zero, delete file */
  tail_size = lseek(fh, 0, SEEK_END);
  close(fh);

  if (tail_size == 0)
    remove(file_name);

  /* remove message from index */
  strcpy(str, lbs->el_index[index].file_name);
  for (i=index ; i<*lbs->n_el_index-1 ; i++)
    {
    memcpy(&lbs->el_index[i], &lbs->el_index[i+1], sizeof(EL_INDEX));
    if (equal_ustring(lbs->el_index[i].file_name, str))
      lbs->el_index[i].offset -= size;
    }
  (*lbs->n_el_index)--;
  lbs->el_index = realloc(lbs->el_index, sizeof(EL_INDEX)*(*lbs->n_el_index));

  /* if other logbook has same index, update pointers */
  for (i=0 ; lb_list[i].name[0] ; i++)
    if (&lb_list[i] != lbs && lb_list[i].n_el_index == lbs->n_el_index)
      lb_list[i].el_index = lbs->el_index;

  /* delete also replies to this message */
  if (reply_to[0])
    {
    p = reply_to;
    if (isdigit(*p))
      do
        {
        if (atoi(p))
          el_delete_message(lbs, atoi(p), TRUE, NULL, FALSE);

        while (*p && isdigit(*p))
          p++;
        while (*p && (*p == ',' || *p == ' '))
          p++;
        } while(*p);
    }

  /* delete backward references */
  if (in_reply_to[0] && delete_bw_ref)
    {
    p = in_reply_to;
    do
      {
      if (atoi(p))
        remove_reference(lbs, atoi(p), message_id, TRUE);

      while (*p && isdigit(*p))
        p++;
      while (*p && (*p == ',' || *p == ' '))
        p++;
      } while(*p);
    }

  return EL_SUCCESS;
}

/*------------------------------------------------------------------*/

void logf(const char *format, ...)
{
char    fname[2000];
va_list argptr;
char    str[10000];
FILE*   f;
time_t  now;
char    buf[256];

  if (!getcfg("global", "logfile", fname))
    return;

  va_start(argptr, format);
  vsprintf(str, (char *) format, argptr);
  va_end(argptr);

  f=fopen(fname,"a");
  if (!f)
    return;

  now=time(0);
  strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M:%S", localtime(&now));
  fprintf(f,"%s: %s",buf,str);

  if (str[strlen(str)-1] != '\n')
    fprintf(f,"\n");

  fclose(f);
}

/*------------------------------------------------------------------*/

void rsputs(const char *str)
{
  if (strlen_retbuf + strlen(str) > sizeof(return_buffer))
    strcpy(return_buffer, "<H1>Error: return buffer too small</H1>");
  else
    strcpy(return_buffer+strlen_retbuf, str);

  strlen_retbuf += strlen(str);
}

/*------------------------------------------------------------------*/

void rsputs2(const char *str)
{
int i, j, k;
char *p, link[256];

  if (strlen_retbuf + strlen(str) > sizeof(return_buffer))
    strcpy(return_buffer, "<H1>Error: return buffer too small</H1>");
  else
    {
    j = strlen_retbuf;
    for (i=0 ; i<(int)strlen(str) ; i++)
      {
      if (strncmp(str+i, "http://", 7) == 0)
        {
        p = (char *) (str+i+7);
        i += 7;
        for (k=0 ; *p && *p != ' ' && *p != ',' && *p != '\t' && *p != '\n' && *p != '\r'; k++,i++)
          link[k] = *p++;
        link[k] = 0;
        i--;

        sprintf(return_buffer+j, "<a href=\"http://%s\">http://%s</a>", link, link);
        j += strlen(return_buffer+j);
        }
      else if (strncmp(str+i, "https://", 8) == 0)
        {
        p = (char *) (str+i+8);
        i += 8;
        for (k=0 ; *p && *p != ' ' && *p != ',' && *p != '\t' && *p != '\n' && *p != '\r'; k++,i++)
          link[k] = *p++;
        link[k] = 0;
        i--;

        sprintf(return_buffer+j, "<a href=\"https://%s\">https://%s</a>", link, link);
        j += strlen(return_buffer+j);
        }
      else if (strncmp(str+i, "ftp://", 6) == 0)
        {
        p = (char *) (str+i+6);
        i += 6;
        for (k=0 ; *p && *p != ' ' && *p != ',' && *p != '\t' && *p != '\n' && *p != '\r'; k++,i++)
          link[k] = *p++;
        link[k] = 0;
        i--;

        sprintf(return_buffer+j, "<a href=\"ftp://%s\">ftp://%s</a>", link, link);
        j += strlen(return_buffer+j);
        }
      else if (strncmp(str+i, "mailto:", 7) == 0)
        {
        p = (char *) (str+i+7);
        i += 7;
        for (k=0 ; *p && *p != '>' && *p != ' ' && *p != ',' && *p != '\t' && *p != '\n' && *p != '\r'; k++,i++)
          link[k] = *p++;
        link[k] = 0;
        i--;

        sprintf(return_buffer+j, "<a href=\"mailto:%s\">%s</a>", link, link);
        j += strlen(return_buffer+j);
        }
      else if (strncmp(str+i, "elog:", 5) == 0)
        {
        p = (char *) (str+i+5);
        i += 5;
        for (k=0 ; *p && *p != '>' && *p != ' ' && *p != ',' && *p != '\t' && *p != '\n' && *p != '\r'; k++,i++)
          link[k] = *p++;
        link[k] = 0;
        i--;

        /* if link contains '/' (reference to other logbook), add ".." in front */
        if (strchr(link, '/'))
          sprintf(return_buffer+j, "<a href=\"../%s\">elog:%s</a>", link, link);
        else
          sprintf(return_buffer+j, "<a href=\"%s\">elog:%s</a>", link, link);
        j += strlen(return_buffer+j);
        }
      else
        switch (str[i])
          {
          case '<': strcat(return_buffer, "&lt;"); j+=4; break;
          case '>': strcat(return_buffer, "&gt;"); j+=4; break;

          /* the translation for the search highliting */
          case '\001' : strcat(return_buffer, "<");    j++;  break;
          case '\002' : strcat(return_buffer, ">");    j++;  break;
          case '\003' : strcat(return_buffer, "\"");   j++;  break;
          case '\004' : strcat(return_buffer, " ");    j++;  break;

          default: return_buffer[j++] = str[i];
          }
      }

    return_buffer[j] = 0;
    strlen_retbuf = j;
    }
}

/*------------------------------------------------------------------*/

void rsprintf(const char *format, ...)
{
va_list argptr;
char    str[10000];

  va_start(argptr, format);
  vsprintf(str, (char *) format, argptr);
  va_end(argptr);

  if (strlen_retbuf + strlen(str) > sizeof(return_buffer))
    strcpy(return_buffer, "<H1>Error: return buffer too small</H1>");
  else
    strcpy(return_buffer+strlen_retbuf, str);

  strlen_retbuf += strlen(str);
}

/*------------------------------------------------------------------*/

/* Parameter handling functions similar to setenv/getenv */

void initparam()
{
  memset(_param, 0, sizeof(_param));
  memset(_value, 0, sizeof(_value));
  _text[0] = 0;
}

int setparam(char *param, char *value)
{
int i;
char str[256];

  if (equal_ustring(param, "text"))
    {
    if (strlen(value) >= TEXT_SIZE)
      {
      sprintf(str, "Error: Message text too big (%d bytes). Please increase TEXT_SIZE and recompile elogd\n",
              strlen(value));
      show_error(str);
      return 0;
      }

    strncpy(_text, value, TEXT_SIZE);
    _text[TEXT_SIZE-1] = 0;
    return 1;
    }

  /* paremeters can be superseeded */
  for (i=0 ; i<MAX_PARAM ; i++)
    if (_param[i][0] == 0 || equal_ustring(param, _param[i]))
      break;

  if (i<MAX_PARAM)
    {
    strcpy(_param[i], param);

    if (strlen(value) >= VALUE_SIZE)
      {
      show_error("Error: Parameter value too big. Please increase VALUE_SIZE and recompile elogd\n");
      return 0;
      }

    strncpy(_value[i], value, VALUE_SIZE);
    _value[i][VALUE_SIZE-1] = 0;
    }
  else
    {
    printf("Error: parameter array too small\n");
    }

  return 1;
}

char *getparam(char *param)
{
int i;

  if (equal_ustring(param, "text"))
    return _text;

  for (i=0 ; i<MAX_PARAM && _param[i][0]; i++)
    if (equal_ustring(param, _param[i]))
      break;

  if (i<MAX_PARAM)
    return _value[i];

  return NULL;
}

BOOL isparam(char *param)
{
int i;

  for (i=0 ; i<MAX_PARAM && _param[i][0]; i++)
    if (equal_ustring(param, _param[i]))
      break;

  if (i<MAX_PARAM && _param[i][0])
    return TRUE;

  return FALSE;
}

void unsetparam(char *param)
{
int i;

  for (i=0 ; i<MAX_PARAM ; i++)
    if (equal_ustring(param, _param[i]))
      break;

  if (i<MAX_PARAM)
    {
    for ( ; i<MAX_PARAM-1 ; i++)
      {
      strcpy(_param[i], _param[i+1]);
      strcpy(_value[i], _value[i+1]);
      }
    _param[MAX_PARAM-1][0] = 0;
    _value[MAX_PARAM-1][0] = 0;
    }
}

/*------------------------------------------------------------------*/

void url_decode(char *p)
/********************************************************************\
   Decode the given string in-place by expanding %XX escapes
\********************************************************************/
{
char *pD, str[3];
int  i;

  pD = p;
  while (*p)
    {
    if (*p=='%')
      {
      /* Escape: next 2 chars are hex representation of the actual character */
      p++;
      if (isxdigit(p[0]) && isxdigit(p[1]))
        {
        str[0] = p[0];
        str[1] = p[1];
        str[2] = 0;
        sscanf(p, "%02X", &i);

        *pD++ = (char) i;
        p += 2;
        }
      else
        *pD++ = '%';
      }
    else if (*p == '+')
      {
      /* convert '+' to ' ' */
      *pD++ = ' ';
      p++;
      }
    else
      {
      *pD++ = *p++;
      }
    }
   *pD = '\0';
}

void url_encode(char *ps)
/********************************************************************\
   Encode the given string in-place by adding %XX escapes
\********************************************************************/
{
char *pd, *p, str[256];

  pd = str;
  p  = ps;
  while (*p)
    {
    if (strchr(" %&=#", *p))
      {
      sprintf(pd, "%%%02X", *p);
      pd += 3;
      p++;
      }
    else
      {
      *pd++ = *p++;
      }
    }
   *pd = '\0';
   strcpy(ps, str);
}

/*------------------------------------------------------------------*/

void redirect(char *path)
{
  /* redirect */
  rsprintf("HTTP/1.1 302 Found\r\n");
  rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
  if (use_keepalive)
    {
    rsprintf("Connection: Keep-Alive\r\n");
    rsprintf("Keep-Alive: timeout=60, max=10\r\n");
    }

  rsprintf("Location: %s\r\n\r\n<html>redir</html>\r\n", path);
}

void redirect2(char *path)
{
  redirect(path);
  send(_sock, return_buffer, strlen(return_buffer)+1, 0);
  closesocket(_sock);
  return_length = -1;
}

/*------------------------------------------------------------------*/

int strbreak(char *str, char list[][NAME_LENGTH], int size)
/* break comma-separated list into char array, stripping leading
   and trailing blanks */
{
int i;
char *p;

  memset(list, 0, size*NAME_LENGTH);
  p = str;
  if (!p || !*p)
    return 0;

  while (*p == ' ')
    p++;

  for (i=0 ; *p && i<size ; i++)
    {
    if (*p == '"')
      {
      p++;

      strncpy(list[i], p, NAME_LENGTH-1);
      list[i][NAME_LENGTH-1] = 0;

      if (strchr(list[i], '"'))
        *strchr(list[i], '"') = 0;

      p += strlen(list[i]) + 1;
      while (*p == ' ' || *p == ',')
        p++;
      }
    else
      {
      strncpy(list[i], p, NAME_LENGTH-1);
      list[i][NAME_LENGTH-1] = 0;

      if (strchr(list[i], ','))
        *strchr(list[i], ',') = 0;

      p += strlen(list[i]);
      while (*p == ' ' || *p == ',')
        p++;
      }

    while (list[i][strlen(list[i])-1] == ' ')
      list[i][strlen(list[i])-1] = 0;

    if (!*p)
      break;
    }

  if (i == size)
    return size;

  return i+1;
}

/*------------------------------------------------------------------*/

int scan_attributes(char *logbook)
/* scan configuration file for attributes and fill attr_list, attr_options
   and attr_flags arrays */
{
char list[10000], str[256], tmp_list[MAX_N_ATTR][NAME_LENGTH];
int  i, j, n, m;

  if (getcfg(logbook, "Attributes", list))
    {
    /* reset attribute flags */
    memset(attr_flags, 0, sizeof(attr_flags));

    /* get attribute list */
    memset(attr_list, 0, sizeof(attr_list));
    n = strbreak(list, attr_list, MAX_N_ATTR);

    /* get options lists for attributes */
    memset(attr_options, 0, sizeof(attr_options));
    for (i=0 ; i<n ; i++)
      {
      sprintf(str, "Options %s", attr_list[i]);
      if (getcfg(logbook, str, list))
        strbreak(list, attr_options[i], MAX_N_LIST);

      sprintf(str, "MOptions %s", attr_list[i]);
      if (getcfg(logbook, str, list))
        {
        strbreak(list, attr_options[i], MAX_N_LIST);
        attr_flags[i] |= AF_MULTI;
        }

      sprintf(str, "IOptions %s", attr_list[i]);
      if (getcfg(logbook, str, list))
        {
        strbreak(list, attr_options[i], MAX_N_LIST);
        attr_flags[i] |= AF_ICON;
        }
      }

    /* check if attribut required */
    getcfg(logbook, "Required Attributes", list);
    m = strbreak(list, tmp_list, MAX_N_ATTR);
    for (i=0 ; i<m ; i++)
      {
      for (j=0 ; j<n ; j++)
        if (equal_ustring(attr_list[j], tmp_list[i]))
          attr_flags[j] |= AF_REQUIRED;
      }

    /* check if locked attribut */
    getcfg(logbook, "Locked Attributes", list);
    m = strbreak(list, tmp_list, MAX_N_ATTR);
    for (i=0 ; i<m ; i++)
      {
      for (j=0 ; j<n ; j++)
        if (equal_ustring(attr_list[j], tmp_list[i]))
          attr_flags[j] |= AF_LOCKED;
      }

    /* check if fixed attribut */
    getcfg(logbook, "Fixed Attributes", list);
    m = strbreak(list, tmp_list, MAX_N_ATTR);
    for (i=0 ; i<m ; i++)
      {
      for (j=0 ; j<n ; j++)
        if (equal_ustring(attr_list[j], tmp_list[i]))
          attr_flags[j] |= AF_FIXED;
      }
    }
  else
    {
    memcpy(attr_list, attr_list_default, sizeof(attr_list_default));
    memcpy(attr_options, attr_options_default, sizeof(attr_options_default));
    memcpy(attr_flags, attr_flags_default, sizeof(attr_flags_default));
    n = 4;
    }

  return n;
}

/*------------------------------------------------------------------*/

void show_upgrade_page(LOGBOOK *lbs)
{
char str[1000];

  show_http_header();

  rsprintf("<html><head>\n");
  rsprintf("<title>ELOG Electronic Logbook Upgrade Information</title>\n");
  rsprintf("</head>\n\n");

  rsprintf("<body>\n");

  rsprintf("<table border=%s width=100%% bgcolor=%s cellpadding=1 cellspacing=0 align=center>",
            gt("Border width"), gt("Frame color"));
  rsprintf("<tr><td><table cellpadding=5 cellspacing=0 border=0 width=100%% bgcolor=%s>\n", gt("Frame color"));

  rsprintf("<tr><td align=center bgcolor=%s><font size=5 color=%s>ELog Electronic Logbook Upgrade Information</font></td></tr>\n",
            gt("Title bgcolor"), gt("Title fontcolor"));

  rsprintf("<tr><td bgcolor=#FFFFFF><br>\n");

  rsprintf("You probably use an <b>elogd.cfg</b> configuration file for a ELOG version\n");
  rsprintf("1.1.x, since it contains a <b><code>\"Types = ...\"</code></b> entry. From version\n");
  rsprintf("1.2.0 on, the fixed attributes <b>Type</b> and <b>Category</b> have been\n");
  rsprintf("replaced by arbitrary attributes. Please replace these two lines with the\n");
  rsprintf("following entries:<p>\n");
  rsprintf("<pre>\n");
  rsprintf("Attributes = Author, Type, Category, Subject\n");
  rsprintf("Required Attributes = Author\n");
  getcfg(lbs->name, "Types", str);
  rsprintf("Options Type = %s\n", str);
  getcfg(lbs->name, "Categories", str);
  rsprintf("Options Category = %s\n", str);
  rsprintf("Page title = $subject\n");
  rsprintf("</pre>\n");
  rsprintf("<p>\n");

  rsprintf("It is of course possible to change the attributes or add new ones. The new\n");
  rsprintf("options in the configuration file are described under <a href=\"\n");
  rsprintf("http://midas.psi.ch/elog/config.html\">http://midas.psi.ch/elog/config.html\n");
  rsprintf("</a>.\n");

  rsprintf("</td></tr>\n");
  rsprintf("</td></tr></table></td></tr></table>\n\n");

  rsprintf("<hr>\n");
  rsprintf("<address>\n");
  rsprintf("<a href=\"http://midas.psi.ch/~stefan\">S. Ritt</a>, 18 October 2001");
  rsprintf("</address>");

  rsprintf("</body></html>\r\n");
}

/*------------------------------------------------------------------*/

void show_http_header()
{
  rsprintf("HTTP/1.1 200 Document follows\r\n");
  rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
  rsprintf("Content-Type: text/html\r\n");
  rsprintf("Pragma: no-cache\r\n");
  if (use_keepalive)
    {
    rsprintf("Connection: Keep-Alive\r\n");
    rsprintf("Keep-Alive: timeout=60, max=10\r\n");
    }
  rsprintf("Expires: Fri, 01 Jan 1983 00:00:00 GMT\r\n\r\n");
}

void show_standard_header(char *title, char *path)
{
  show_http_header();

  rsprintf("<html><head><title>%s</title></head>\n", title);

  if (*gt("BGImage"))
    rsprintf("<body bgcolor=#FFFFFF background=\"%s\">\n", gt("BGImage"));
  else
    rsprintf("<body bgcolor=#FFFFFF>\n");

  if (path)
    rsprintf("<form name=form1 method=\"GET\" action=\"%s\">\n\n", path);
  else
    rsprintf("<form name=form1 method=\"GET\" action=\"\">\n\n");
}

/*------------------------------------------------------------------*/

void show_standard_title(char *logbook, char *text, int printable)
{
char str[256], ref[256];
int  i, j;

  /* overall table, containing title, menu and message body */
  if (printable)
    rsprintf("<table width=600 border=%s cellpadding=0 cellspacing=0 bgcolor=%s>\n\n",
             gt("Border width"), gt("Frame color"));
  else
    rsprintf("<table width=%s border=%s cellpadding=0 cellspacing=0 bgcolor=%s>\n\n",
             gt("Table width"), gt("Border width"), gt("Frame color"));

  /*---- logbook selection row ----*/

  if (!printable && getcfg(logbook, "logbook tabs", str) && atoi(str) == 1)
    {
    rsprintf("<tr><td bgcolor=#FFFFFF>\n");

    if (getcfg("global", "main tab", str))
      rsprintf("<font size=3 face=verdana,arial,helvetica,sans-serif style=\"background-color:#E0E0E0\">&nbsp;<a href=\"../\">%s</a>&nbsp;</font>&nbsp\n", str);

    for (i=0 ;  ; i++)
      {
      if (!enumgrp(i, str))
        break;

      if (equal_ustring(str, "global"))
        continue;

      strcpy(ref, str);
      url_encode(ref);

      if (equal_ustring(str, logbook))
        {
        rsprintf("<font size=3 face=verdana,arial,helvetica,sans-serif style=\"color:%s;background-color:%s\">&nbsp;",
                 gt("Title fontcolor"), gt("Title BGColor"));

        for (j=0 ; j<(int)strlen(str) ; j++)
          if (str[j] == ' ')
            rsprintf("&nbsp;");
          else
            rsprintf("%c", str[j]);

        rsprintf("&nbsp;</font>&nbsp;\n");
        }
      else
        {
        rsprintf("<font size=3 face=verdana,arial,helvetica,sans-serif style=\"background-color:#E0E0E0\">&nbsp;");
        rsprintf("<a style=\"text-decoration:none\" href=\"../%s/\">", ref);

        for (j=0 ; j<(int)strlen(str) ; j++)
          if (str[j] == ' ')
            rsprintf("&nbsp;");
          else
            rsprintf("%c", str[j]);

        rsprintf("</a>&nbsp;</font>&nbsp\n");
        }
      }
    rsprintf("</td></tr>\n\n");

    }

  /*---- title row ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=0 bgcolor=#FFFFFF>\n",
            gt("Title cellpadding"));

  /* left cell */
  rsprintf("<tr><td bgcolor=%s align=left>", gt("Title BGColor"));

  /* use comment as title if available, else logbook name */
  if (!getcfg(logbook, "Comment", str))
    strcpy(str, logbook);

  rsprintf("<font size=3 face=verdana,arial,helvetica,sans-serif color=%s><b>&nbsp;&nbsp;%s%s<b></font>\n",
            gt("Title fontcolor"), str, text);
  rsprintf("&nbsp;</td>\n");

  /* middle cell */
  if (*getparam("full_name"))
    {
    rsprintf("<td bgcolor=%s align=center>", gt("Title BGColor"));
    rsprintf("<font size=3 face=verdana,arial,helvetica,sans-serif color=%s><b>&nbsp;&nbsp;%s \"%s\"<b></font></td>\n",
              gt("Title fontcolor"), loc("Logged in as"), getparam("full_name"));
    }
  else
    {
    if (getcfg(logbook, "Guest menu commands", str))
      {
      rsprintf("<td bgcolor=%s align=center>", gt("Title BGColor"));
      rsprintf("<font size=3 face=verdana,arial,helvetica,sans-serif color=%s><b>&nbsp;&nbsp;%s<b></font></td>\n",
                gt("Title fontcolor"), loc("Not logged in"));
      }
    }

  /* right cell */
  rsprintf("<td bgcolor=%s align=right>", gt("Title BGColor"));

  if (*gt("Title image URL"))
    rsprintf("<a href=\"%s\">\n", gt("Title image URL"));

  if (*gt("Title image"))
    rsprintf("<img border=0 src=\"%s\">", gt("Title image"));
  else
    rsprintf("<font size=3 face=verdana,arial,helvetica,sans-serif color=%s><b>ELOG V%s&nbsp;&nbsp</b></font>",
              gt("Title fontcolor"), VERSION);

  if (*gt("Title image URL"))
    rsprintf("</a>\n");

  rsprintf("</td>\n");

  rsprintf("</tr></table></td></tr>\n\n");
}

/*------------------------------------------------------------------*/

void show_error(char *error)
{
  /* header */
  show_standard_header("ELOG error", "");

  rsprintf("<p><p><p><table border=%s width=50%% bgcolor=%s cellpadding=1 cellspacing=0 align=center>",
            gt("Border width"), gt("Frame color"));
  rsprintf("<tr><td><table cellpadding=5 cellspacing=0 border=0 width=100%% bgcolor=%s>\n", gt("Frame color"));
  rsprintf("<tr><td bgcolor=#FFB0B0 align=center>");

  rsprintf("%s</tr>\n", error);

  rsprintf("<tr><td bgcolor=%s align=center>", gt("Cell BGColor"));

  /*
  rsprintf("<script language=\"javascript\" type=\"text/javascript\">\n");
  rsprintf("if (!navigator.javaEnabled()) {\n");
  rsprintf("  document.write(\"%s\")\n", loc("Please use your browser's back button to go back"));
  rsprintf("} else {\n");
  rsprintf("  document.write(\"<button type=button onClick=history.back()>%s</button>\")\n", loc("Back"));
  rsprintf("} \n");
  rsprintf("</script>\n");

  rsprintf("<noscript>\n");
  */

  rsprintf("%s\n", loc("Please use your browser's back button to go back"));

  /*
  rsprintf("</noscript>\n");
  */

  rsprintf("</td></tr>\n</table></td></tr></table>\n");
  rsprintf("</body></html>\n");
}

/*------------------------------------------------------------------*/

void set_login_cookies(LOGBOOK *lbs, char *user, char *enc_pwd)
{
char   str[256], str2[256];
double exp;
time_t now;
struct tm *gmt;

  rsprintf("HTTP/1.1 302 Found\r\n");
  rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
  if (use_keepalive)
    {
    rsprintf("Connection: Keep-Alive\r\n");
    rsprintf("Keep-Alive: timeout=60, max=10\r\n");
    }

  /* get optional expriation from configuration file */
  exp = 0;
  if (getcfg(lbs->name, "Login expiration", str))
    exp = atof(str);

  if (exp == 0)
    {
    if (getcfg("global", "Password file", str))
      {
      rsprintf("Set-Cookie: upwd=%s; path=/\r\n", enc_pwd);
      rsprintf("Set-Cookie: unm=%s; path=/\r\n", user);
      }
    else
      {
      rsprintf("Set-Cookie: upwd=%s\r\n", enc_pwd);
      rsprintf("Set-Cookie: unm=%s\r\n", user);
      }
    }
  else
    {
    time(&now);
    now += (int) (3600*exp);
    gmt = gmtime(&now);
    strftime(str, sizeof(str), "%A, %d-%b-%y %H:%M:%S GMT", gmt);

    if (getcfg("global", "Password file", str2))
      {
      rsprintf("Set-Cookie: upwd=%s; path=/; expires=%s\r\n", enc_pwd, str);
      rsprintf("Set-Cookie: unm=%s; path=/; expires=%s\r\n", user, str);
      }
    else
      {
      rsprintf("Set-Cookie: upwd=%s; expires=%s\r\n", enc_pwd, str);
      rsprintf("Set-Cookie: unm=%s; expires=%s\r\n", user, str);
      }
    }

  sprintf(str, "%s", getparam("redir"));
  if (!str[0])
    sprintf(str, "../%s/", lbs->name_enc);

  rsprintf("Location: %s\r\n\r\n<html>redir</html>\r\n", str);
  return;
}

/*------------------------------------------------------------------*/

void send_file(char *file_name)
{
int    fh, i, length;
char   str[256];
time_t now;
struct tm *gmt;

  fh = open(file_name, O_RDONLY | O_BINARY);
  if (fh > 0)
    {
    lseek(fh, 0, SEEK_END);
    length = TELL(fh);
    lseek(fh, 0, SEEK_SET);

    rsprintf("HTTP/1.1 200 Document follows\r\n");
    rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
    rsprintf("Accept-Ranges: bytes\r\n");

    time(&now);
    now += (int) (3600*3);
    gmt = gmtime(&now);
    strftime(str, sizeof(str), "%A, %d-%b-%y %H:%M:%S GMT", gmt);
    rsprintf("Expires: %s\r\n", str);

    if (use_keepalive)
      {
      rsprintf("Connection: Keep-Alive\r\n");
      rsprintf("Keep-Alive: timeout=60, max=10\r\n");
      }

    /* return proper header for file type */
    for (i=0 ; i<(int)strlen(file_name) ; i++)
      str[i] = toupper(file_name[i]);
    str[i] = 0;

    for (i=0 ; filetype[i].ext[0] ; i++)
      if (strstr(str, filetype[i].ext))
        break;

    if (filetype[i].ext[0])
      rsprintf("Content-Type: %s\r\n", filetype[i].type);
    else if (strchr(str, '.') == NULL)
      rsprintf("Content-Type: text/plain\r\n");
    else
      rsprintf("Content-Type: application/octet-stream\r\n");

    rsprintf("Content-Length: %d\r\n\r\n", length);

    /* return if file too big */
    if (length > (int) (sizeof(return_buffer) - strlen(return_buffer)))
      {
      printf("return buffer too small\n");
      close(fh);
      return;
      }

    return_length = strlen(return_buffer)+length;
    read(fh, return_buffer+strlen(return_buffer), length);

    close(fh);
    }
  else
    {
    rsprintf("HTTP/1.1 404 Not Found\r\n");
    rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
    rsprintf("Connection: close\r\n");
    rsprintf("Content-Type: text/html\r\n\r\n");
    rsprintf("<html><head><title>404 Not Found</title></head>\r\n");
    rsprintf("<body><h1>Not Found</h1>\r\n");
    rsprintf("The requested file <b>%s</b> was not found on this server<p>\r\n", file_name);
    rsprintf("<hr><address>ELOG version %s</address></body></html>\r\n\r\n", VERSION);
    return_length = strlen_retbuf;
    keep_alive = 0;
    }
}

/*------------------------------------------------------------------*/

void strencode(char *text)
{
int i;

  for (i=0 ; i<(int) strlen(text) ; i++)
    {
    switch (text[i])
      {
      case '\n': rsprintf("<br>\n"); break;
      case '<': rsprintf("&lt;"); break;
      case '>': rsprintf("&gt;"); break;
      case '&': rsprintf("&amp;"); break;
      case '\"': rsprintf("&quot;"); break;
      case ' ': rsprintf("&nbsp;"); break;

      /* the translation for the search highliting */
      case '\001': rsprintf("<"); break;
      case '\002': rsprintf(">"); break;
      case '\003': rsprintf("\""); break;
      case '\004': rsprintf(" "); break;

      default: rsprintf("%c", text[i]);
      }
    }
}

/*------------------------------------------------------------------*/

void strencode2(char *b, char *text)
{
int i;

  for (i=0 ; i<(int) strlen(text) ; b++,i++)
    {
    switch (text[i])
      {
      case '\n': sprintf(b, "<br>\n"); break;
      case '<': sprintf(b, "&lt;"); break;
      case '>': sprintf(b, "&gt;"); break;
      case '&': sprintf(b, "&amp;"); break;
      case '\"': sprintf(b, "&quot;"); break;
      default: sprintf(b, "%c", text[i]);
      }
    }
  *b = 0;
}

/*------------------------------------------------------------------*/

int build_subst_list(LOGBOOK *lbs, char list[][NAME_LENGTH],
                     char value[][NAME_LENGTH], char attrib[][NAME_LENGTH])
{
int            i;
char           str[256], format[256];
time_t         now;
struct tm      *ts;

  /* copy attribute list */
  for (i=0 ; i<lbs->n_attr ; i++)
    {
    strcpy(list[i], attr_list[i]);
    if (attrib)
      strcpy(value[i], attrib[i]);
    else
      strcpy(value[i], getparam(attr_list[i]));
    }

  /* add remote host */
  strcpy(list[i], "remote_host");
  strcpy(value[i++], rem_host);

  /* add local host */
  strcpy(list[i], "host");
  strcpy(value[i++], host_name);

  /* add user names */
  strcpy(list[i], "short_name");
  strcpy(value[i++], getparam("unm"));
  strcpy(list[i], "long_name");
  strcpy(value[i++], getparam("full_name"));

  /* add email */
  strcpy(list[i], "user_email");
  strcpy(value[i], "mailto:");
  strcat(value[i++], getparam("user_email"));

  /* add logbook */
  strcpy(list[i], "logbook");
  strcpy(value[i++], lbs->name);

  /* add date */
  strcpy(list[i], "date");
  time(&now);
  ts = localtime(&now);
  if (getcfg(lbs->name, "Date format", format))
    strftime(str, sizeof(str), format, ts);
  else
    strcpy(str, ctime(&now));
  strcpy(value[i++], str);

  return i;
}

/*------------------------------------------------------------------*/

void show_change_pwd_page(LOGBOOK *lbs)
{
char   str[256], str2[256], file_name[256], line[256], *p, *pl, old_pwd[32], 
       new_pwd[32], new_pwd2[32], user[80];
char   *buf;
FILE   *f;
int    i, wrong_pwd, size;

  do_crypt(getparam("oldpwd"), old_pwd);
  do_crypt(getparam("newpwd"), new_pwd);
  do_crypt(getparam("newpwd2"), new_pwd2);

  strcpy(user, getparam("unm"));
  if (isparam("config"))
    strcpy(user, getparam("config"));

  getcfg(lbs->name, "Password file", str);

  if (str[0] == DIR_SEPARATOR || str[1] == ':')
    strcpy(file_name, str);
  else
    {
    strcpy(file_name, cfg_dir);
    strcat(file_name, str);
    }

  wrong_pwd = FALSE;

  if (old_pwd[0] || new_pwd[0])
    {
    f = fopen(file_name, "r+b");
    if (f != NULL)
      {
      fseek(f, 0, SEEK_END);
      size = TELL(fileno(f));
      fseek(f, 0, SEEK_SET);

      buf = malloc(size+1);
      fread(buf, 1, size, f);
      buf[size] = 0;
      pl = buf;

      while (pl < buf+size)
        {
        for (i=0 ; pl[i] && pl[i] != '\r' && pl[i] != '\n' ; i++)
          line[i] = pl[i];
        line[i] = 0;

        if (line[0] == ';' || line[0] == '#' || line[0] == 0)
          {
          pl += strlen(line);
          while (*pl && (*pl == '\r' || *pl == '\n'))
            pl++;
          continue;
          }

        strcpy(str, line);
        if (strchr(str, ':'))
          *strchr(str, ':') = 0;
        if (strcmp(str, user) == 0)
          break;

        pl += strlen(line);
        while (*pl && (*pl == '\r' || *pl == '\n'))
          pl++;
        }

      /* if user found, check old password */
      if (user[0] && (strcmp(str, user) == 0))
        {
        p = line+strlen(str);
        if (*p)
          p++;

        strcpy(str2, p);
        if (strchr(str2, ':'))
          *strchr(str2, ':') = 0;

        if (getcfg(lbs->name, "Admin user", str) &&
            strstr(str, getparam("unm")) != 0)
          wrong_pwd = 0;
        else
          {
          if (strcmp(old_pwd, str2) != 0)
            wrong_pwd = 1;
          }

        if (strcmp(new_pwd, new_pwd2) != 0)
          wrong_pwd = 2;
        }

      /* replace password */
      if (!wrong_pwd)
        {
        fseek(f, 0, SEEK_SET);
        fwrite(buf, 1, pl-buf, f);

        sprintf(str, "%s:%s:%s:%s", user, new_pwd, 
                getparam("full_name"), getparam("user_email"));
        fprintf(f, "%s\n", str);

        pl += strlen(line);
        while (*pl && (*pl == '\r' || *pl == '\n'))
          pl++;

        fwrite(pl, 1, strlen(pl), f);

#ifdef _MSC_VER
        chsize(fileno(f), TELL(fileno(f)));
#else
        ftruncate(fileno(f), TELL(fileno(f)));
#endif
        }

      free(buf);
      fclose(f);

      if (!wrong_pwd && strcmp(user, getparam("unm")) == 0)
        {
        set_login_cookies(lbs, user, new_pwd);
        return;
        }

      if (!wrong_pwd)
        {
        redirect(".");
        return;
        }
      }
    }

  show_standard_header(loc("ELOG change password"), NULL);

  rsprintf("<p><p><p><table border=%s width=50%% bgcolor=%s cellpadding=1 cellspacing=0 align=center>",
            gt("Border width"), gt("Frame color"));
  rsprintf("<tr><td><table cellpadding=5 cellspacing=0 border=0 width=100%% bgcolor=%s>\n", gt("Frame color"));

  if (wrong_pwd == 1)
    rsprintf("<tr><th bgcolor=#FF0000>%s!</th></tr>\n", loc("Wrong password"));

  if (wrong_pwd == 2)
    rsprintf("<tr><th bgcolor=#FF0000>%s!</th></tr>\n", loc("New passwords do not match, please retype"));

  rsprintf("<tr><td align=center bgcolor=%s>\n", gt("Title bgcolor"));

  rsprintf("<input type=hidden name=config value=\"%s\">", user);

  rsprintf("<font color=%s>%s \"%s\"</font></td></tr>\n",
           gt("Title fontcolor"), loc("Change password for user"), user);

  if (!getcfg(lbs->name, "Admin user", str) ||
      !strstr(str, getparam("unm")) != 0)
    {
    rsprintf("<tr><td align=center bgcolor=%s>%s:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=password name=oldpwd></td></tr>\n",
             gt("Cell BGColor"), loc("Old Password"));
    }

  rsprintf("<tr><td align=center bgcolor=%s>%s:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=password name=newpwd></td></tr>\n",
           gt("Cell BGColor"), loc("New Password"));
  rsprintf("<tr><td align=center bgcolor=%s>%s:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=password name=newpwd2></td></tr>\n",
           gt("Cell BGColor"), loc("Retype new password"));

  rsprintf("<tr><td align=center bgcolor=%s><input type=submit value=\"%s\"></td></tr>",
           gt("Cell BGColor"), loc("Submit"));

  rsprintf("</table></td></tr></table>\n");

  rsprintf("</body></html>\r\n");
}

/*------------------------------------------------------------------*/

BOOL allow_user(LOGBOOK *lbs, char *command)
{
char str[1000], users[2000];
char list[MAX_N_LIST][NAME_LENGTH];
int  i, n;

  /* check for user level access */
  if (!getcfg(lbs->name, "Password file", str))
    return TRUE;

  /* allow by default */
  sprintf(str, "Allow %s", command);
  if (!getcfg(lbs->name, str, users))
    return TRUE;

  /* check if current user in list */
  n = strbreak(users, list, MAX_N_LIST);
  for (i=0 ; i<n ; i++)
    if (equal_ustring(list[i], getparam("unm")))
      return TRUE;

  sprintf(str, loc("Error: Command \"<b>%s</b>\" is not allowed for user \"<b>%s</b>\""),
          command, getparam("full_name"));
  show_error(str);

  return FALSE;
}

/*------------------------------------------------------------------*/

int get_last_index(LOGBOOK *lbs, int index)
{
int    i, message_id;
char   str[80], date[80], attrib[MAX_N_ATTR][NAME_LENGTH],
       in_reply_to[80], reply_to[256], att[MAX_ATTACHMENTS][256], encoding[80];

  str[0] = 0;
  message_id = el_search_message(lbs, EL_LAST, 0, FALSE);

  el_retrieve(lbs, message_id, date, attr_list, attrib, lbs->n_attr,
              NULL, 0, in_reply_to, reply_to, att, encoding);

  strcpy(str, attrib[index]);

  /* look for first digit, return value */
  for (i=0 ; i<(int)strlen(str) ; i++)
    if (isdigit(str[i]))
      break;

  return atoi(str+i);
}

/*------------------------------------------------------------------*/

void show_elog_new(LOGBOOK *lbs, int message_id, BOOL bedit)
{
int    i, j, n, index, size, width, fh, length;
char   str[1000], preset[1000], *p, star[80], comment[10000];
char   list[MAX_N_ATTR][NAME_LENGTH], file_name[256], *buffer, format[256];
char   date[80], attrib[MAX_N_ATTR][NAME_LENGTH], text[TEXT_SIZE],
       orig_tag[80], reply_tag[80], att[MAX_ATTACHMENTS][256], encoding[80],
       slist[MAX_N_ATTR+10][NAME_LENGTH], svalue[MAX_N_ATTR+10][NAME_LENGTH];
time_t now;

  for (i=0 ; i<MAX_ATTACHMENTS ; i++)
    att[i][0] = 0;

  for (i=0 ; i<lbs->n_attr ; i++)
    attrib[i][0] = 0;

  if (message_id)
    {
    /* get message for reply */

    size = sizeof(text);
    el_retrieve(lbs, message_id, date, attr_list, attrib, lbs->n_attr,
                text, &size, orig_tag, reply_tag, att, encoding);
    }
  else
    {
    /* get preset attributes */
    for (i=0 ; i<lbs->n_attr ; i++)
      {
      sprintf(str, "p%s", attr_list[i]);
      strcpy(attrib[i], getparam(str));
      }
    }

  /* check for author */
  if (bedit && getcfg(lbs->name, "Restrict edit", str) && atoi(str) == 1)
    {
    /* search attribute which contains author */
    for (i=0 ; i<lbs->n_attr ; i++)
      {
      sprintf(str, "Preset %s", attr_list[i]);
      if (getcfg(lbs->name, str, preset))
        {
        if (strstr(preset, "$short_name"))
          {
          if (strstr(attrib[i], getparam("unm")) == NULL)
            {
            sprintf(str, loc("Only user <i>%s</i> can edit this entry"), attrib[i]);
            show_error(str);
            return;
            }
          }
        if (strstr(preset, "$long_name"))
          {
          if (strstr(attrib[i], getparam("full_name")) == NULL)
            {
            sprintf(str, loc("Only user <i>%s</i> can edit this entry"), attrib[i]);
            show_error(str);
            return;
            }
          }
        }
      }
    }

  /* remove attributes for replies */
  if (message_id && !bedit)
    {
    getcfg(lbs->name, "Remove on reply", str);
    n = strbreak(str, list, MAX_N_ATTR);
    for (i=0 ; i<n ; i++)
      for (j=0 ; j<lbs->n_attr ; j++)
        {
        if (equal_ustring(attr_list[j], list[i]))
          attrib[j][0] = 0;
        }
    }

  /* subst attributes for replies */
  if (message_id && !bedit)
    {
    for (index = 0 ; index < lbs->n_attr ; index++)
      {
      sprintf(str, "Subst on reply %s", attr_list[index]);
      if (getcfg(lbs->name, str, preset))
        {
        /* check if already second reply */
        if (orig_tag[0] == 0)
          {
          i = build_subst_list(lbs, slist, svalue, attrib);
          strsubst(preset, slist, svalue, i);
          strcpy(attrib[index], preset);
          }
        }
      }
    }

  /* header */
  show_http_header();

  rsprintf("<html><head><title>ELOG</title></head>\n");
  rsprintf("<body><form method=\"POST\" action=\".\" enctype=\"multipart/form-data\">\n");

  /*---- add password in case cookie expires during edit ----*/

  if (getcfg(lbs->name, "Write password", str))
    rsprintf("<input type=hidden name=\"wpwd\" value=\"%s\">\n", str);

  if (getcfg(lbs->name, "Password file", str))
    {
    rsprintf("<input type=hidden name=\"unm\" value=\"%s\">\n", getparam("unm"));
    rsprintf("<input type=hidden name=\"upwd\" value=\"%s\">\n", getparam("upwd"));
    }

  /*---- title row ----*/

  show_standard_title(lbs->name, "", 0);

  /*---- menu buttons ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Menu1 cellpadding"), gt("Frame color"));

  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Submit"));
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Back"));
  rsprintf("</td></tr></table></td></tr>\n\n");

  /*---- entry form ----*/

  /* overall table for message giving blue frame */
  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Categories border"), gt("Categories cellpadding"), gt("Frame color"));

  /* print required message if one of the attributes has it set */
  for (i= 0 ; i < lbs->n_attr ; i++)
    {
    if (attr_flags[i] & AF_REQUIRED)
      {
      rsprintf("<tr><td colspan=2 bgcolor=%s>%s <font color=red>*</font> %s</td></tr>\n",
               gt("Categories bgcolor1"), loc("Fields marked with"), loc("are required"));
      break;
      }
    }

  time(&now);
  if (bedit)
    {
    if (getcfg(lbs->name, "Date format", format))
      {
      struct tm ts;

      memset(&ts, 0, sizeof(ts));

      for (i=0 ; i<12 ; i++)
        if (strncmp(date+4, mname[i], 3) == 0)
          break;
      ts.tm_mon = i;

      ts.tm_mday = atoi(date+8);
      ts.tm_hour = atoi(date+11);
      ts.tm_min  = atoi(date+14);
      ts.tm_sec  = atoi(date+17);
      ts.tm_year = atoi(date+20)-1900;
      ts.tm_isdst = -1; /* let mktime compute DST */

      mktime(&ts);
      strftime(str, sizeof(str), format, &ts);
      }
    else
      strcpy(str, date);

    rsprintf("<tr><td nowrap bgcolor=%s width=10%%><b>%s:</b></td><td bgcolor=%s>%s</td></tr>\n\n",
             gt("Categories bgcolor1"), loc("Entry date"), gt("Categories bgcolor2"), str);
    }
  else
    {
    if (getcfg(lbs->name, "Date format", format))
      strftime(str, sizeof(str), format, localtime(&now));
    else
      strcpy(str, ctime(&now));

    rsprintf("<tr><td nowrap bgcolor=%s width=10%%><b>%s:</b></td><td bgcolor=%s>%s</td></tr>\n\n",
             gt("Categories bgcolor1"), loc("Entry date"), gt("Categories bgcolor2"), str);
    }

  /* display attributes */
  for (index = 0 ; index < lbs->n_attr ; index++)
    {
    strcpy(star, (attr_flags[index] & AF_REQUIRED) ? "<font color=red>*</font>" : "");

    /* check for preset string */
    sprintf(str, "Preset %s", attr_list[index]);
    if (getcfg(lbs->name, str, preset))
      {
      if (!bedit || (attr_flags[index] & AF_FIXED) == 0)
        {
        i = build_subst_list(lbs, slist, svalue, NULL);
        strsubst(preset, slist, svalue, i);

        /* check for index substitution */
        if (!bedit && strchr(preset, '%'))
          {
          /* get index */
          i = get_last_index(lbs, index);

          strcpy(str, preset);
          sprintf(preset, str, i+1);
          }

        if (!strchr(preset, '%'))
          strcpy(attrib[index], preset);
        }
      }

    /* display text box */
    rsprintf("<tr><td nowrap bgcolor=%s><b>%s%s:</b></td>", gt("Categories bgcolor1"), attr_list[index], star);

    /* if attribute cannot be changed, just display text */
    if ((attr_flags[index] & AF_LOCKED) || (bedit && (attr_flags[index] & AF_FIXED)))
      {
      rsprintf("<td bgcolor=%s>\n", gt("Categories bgcolor2"));
      rsputs2(attrib[index]);

      if (attr_flags[index] & AF_MULTI)
        {
        for (i=0 ; i<MAX_N_LIST && attr_options[index][i][0] ; i++)
          {
          sprintf(str, "%s%d", attr_list[index], i);

          if (strstr(attrib[index], attr_options[index][i]))
            rsprintf("<input type=\"hidden\" name=\"%s\" value=\"%s\">\n", str, attr_options[index][i]);
          }
        }
      else if (attr_flags[index] & AF_ICON)
        {
        for (i=0 ; i<MAX_N_LIST && attr_options[index][i][0] ; i++)
          {
          sprintf(str, "%s%d", attr_list[index], i);

          if (strstr(attrib[index], attr_options[index][i]))
            rsprintf("<input type=\"hidden\" name=\"%s\" value=\"%s\">\n", str, attr_options[index][i]);
          }
        }
      else
        rsprintf("<input type=\"hidden\" name=\"%s\" value=\"%s\"></td></tr>\n",
                 attr_list[index], attrib[index]);
      }
    else
      {
      if (attr_options[index][0][0] == 0)
        {
        rsprintf("<td bgcolor=%s><input type=\"text\" size=80 maxlength=%d name=\"%s\" value=\"%s\"></td></tr>\n",
                  gt("Categories bgcolor2"), NAME_LENGTH, attr_list[index], attrib[index]);
        }
      else
        {
        if (equal_ustring(attr_options[index][0], "boolean"))
          {
          /* display checkbox */
          rsprintf("<td bgcolor=%s><input type=checkbox name=\"%s\" value=1>\n",
                   gt("Categories bgcolor2"), attr_list[index]);
          }
        else
          {
          if (attr_flags[index] & AF_MULTI)
            {
            /* display multiple check boxes */
            rsprintf("<td bgcolor=%s>\n", gt("Categories bgcolor2"));

            for (i=0 ; i<MAX_N_LIST && attr_options[index][i][0] ; i++)
              {
              sprintf(str, "%s%d", attr_list[index], i);

              if (strstr(attrib[index], attr_options[index][i]))
                rsprintf("<input type=checkbox checked name=\"%s\" value=\"%s\">%s&nbsp;\n",
                  str, attr_options[index][i], attr_options[index][i]);
              else
                rsprintf("<input type=checkbox name=\"%s\" value=\"%s\">%s&nbsp;\n",
                  str, attr_options[index][i], attr_options[index][i]);
              }

            rsprintf("</td></tr>\n");
            }
          else if (attr_flags[index] & AF_ICON)
            {
            /* display icons */
            rsprintf("<td bgcolor=%s>\n", gt("Categories bgcolor2"));

            for (i=0 ; i<MAX_N_LIST && attr_options[index][i][0] ; i++)
              {
              if (strstr(attrib[index], attr_options[index][i]))
                rsprintf("<input type=radio checked name=\"%s\" value=\"%s\">", attr_list[index], attr_options[index][i]);
              else
                rsprintf("<input type=radio name=\"%s\" value=\"%s\">", attr_list[index], attr_options[index][i]);

              rsprintf("<img src=\"icons/%s\">&nbsp;\n", attr_options[index][i]);
              }

            rsprintf("</td></tr>\n");
            }
          else
            {
            /* display drop-down box */
            rsprintf("<td bgcolor=%s><select name=\"%s\">\n",
                     gt("Categories bgcolor2"), attr_list[index]);

            /* display emtpy option */
            rsprintf("<option value=\"\">- %s -\n", loc("please select"));

            for (i=0 ; i<MAX_N_LIST && attr_options[index][i][0] ; i++)
              {
              if (equal_ustring(attr_options[index][i], attrib[index]))
                rsprintf("<option selected value=\"%s\">%s\n", attr_options[index][i], attr_options[index][i]);
              else
                rsprintf("<option value=\"%s\">%s\n", attr_options[index][i], attr_options[index][i]);
              }

            rsprintf("</select></td></tr>\n");
            }
          }
        }
      }
    }

  if (message_id)
    {
    /* hidden text for original message */
    rsprintf("<input type=hidden name=orig value=\"%d\">\n", message_id);

    if (bedit)
      rsprintf("<input type=hidden name=edit value=1>\n");
    }

  rsprintf("</td></tr>\n");

  /* set textarea width */
  width = 76;

  if (getcfg(lbs->name, "Message width", str))
    width = atoi(str);

  /* increased wrapping width for replies (leave space for '> ' */
  if (message_id && !bedit)
    width += 2;

  rsprintf("<tr><td colspan=2 bgcolor=#FFFFFF>\n");

  if (getcfg(lbs->name, "Message comment", comment) && !bedit && !message_id)
    {
    rsputs(comment);
    rsputs("<br>\n");
    }

  if (!getcfg(lbs->name, "Show text", str) || atoi(str) == 1)
    {
    rsprintf("<textarea rows=20 cols=%d wrap=hard name=Text>", width);

    if (message_id)
      {
      if (bedit)
        {
        rsputs(text);
        }
      else
        {
        p = text;
        do
          {
          if (strchr(p, '\n'))
            {
            *strchr(p, '\n') = 0;

            if (encoding[0] == 'H')
              rsprintf("&gt; %s<br>\n", p);
            else
              rsprintf("> %s\n", p);

            p += strlen(p)+1;
            if (*p == '\n')
              p++;
            }
          else
            {
            if (encoding[0] == 'H')
              rsprintf("&gt; %s<p>\n", p);
            else
              rsprintf("> %s\n\n", p);

            break;
            }

          } while (TRUE);
        }
      }

    if (!message_id && getcfg(lbs->name, "Preset text", str))
      {
      /* check if file */
      strcpy(file_name, cfg_dir);
      strcat(file_name, str);

      fh = open(file_name, O_RDONLY | O_BINARY);
      if (fh > 0)
        {
        length = lseek(fh, 0, SEEK_END);
        lseek(fh, 0, SEEK_SET);
        buffer = malloc(length+1);
        read(fh, buffer, length);
        buffer[length] = 0;
        close(fh);
        rsputs(buffer);
        free(buffer);
        }
      else
        rsputs(str);
      }

    rsprintf("</textarea><br>\n");

    /* HTML check box */
    if (message_id)
      {
      if (getcfg(lbs->name, "HTML default", str))
        {
        if (atoi(str) < 2)
          {
          if (encoding[0] == 'H')
            rsprintf("<input type=checkbox checked name=html value=1>%s\n", loc("Submit as HTML text"));
          else
            rsprintf("<input type=checkbox name=html value=1>%s\n", loc("Submit as HTML text"));
          }
        else if (atoi(str) == 3)
          {
          rsprintf("<input type=hidden name=html value=1>\n");
          }
        }
      else
        {
        if (encoding[0] == 'H')
          rsprintf("<input type=checkbox checked name=html value=1>%s\n", loc("Submit as HTML text"));
        else
          rsprintf("<input type=checkbox name=html value=1>%s\n", loc("Submit as HTML text"));
        }
      }
    else
      {
      if (getcfg(lbs->name, "HTML default", str))
        {
        if (atoi(str) == 0)
          {
          rsprintf("<input type=checkbox name=html value=1>%s\n", loc("Submit as HTML text"));
          }
        else if (atoi(str) == 1)
          {
          rsprintf("<input type=checkbox checked name=html value=1>%s\n", loc("Submit as HTML text"));
          }
        else if (atoi(str) == 3)
          {
          rsprintf("<input type=hidden name=html value=1>\n");
          }
        }
      else
        rsprintf("<input type=checkbox name=html value=1>%s\n", loc("Submit as HTML text"));
      }
    }

  /* Suppress check box */
  if (getcfg(lbs->name, "Suppress default", str))
    {
    if (atoi(str) == 0)
      {
      rsprintf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
      rsprintf("<input type=checkbox name=suppress value=1>%s\n", loc("Suppress Email notification"));
      }
    else if (atoi(str) == 1)
      {
      rsprintf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
      rsprintf("<input type=checkbox checked name=suppress value=1>%s\n", loc("Suppress Email notification"));
      }
    }
  else
    {
    rsprintf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
    rsprintf("<input type=checkbox name=suppress value=1>%s\n", loc("Suppress Email notification"));
    }

  if (bedit)
    {
    /* Resubmit check box */
    if (getcfg(lbs->name, "Resubmit default", str))
      {
      if (atoi(str) == 0)
        {
        rsprintf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
        rsprintf("<input type=checkbox name=resubmit value=1>%s\n", loc("Resubmit as new entry"));
        }
      else if (atoi(str) == 1)
        {
        rsprintf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
        rsprintf("<input type=checkbox checked name=resubmit value=1>%s\n", loc("Resubmit as new entry"));
        }
      }
    else
      {
      rsprintf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
      rsprintf("<input type=checkbox name=resubmit value=1>%s\n", loc("Resubmit as new entry"));
      }
    }

  rsprintf("</tr>\n");

  if (getcfg(lbs->name, "Number attachments", str))
    n = atoi(str);
  else
    n = 5;

  if (n > MAX_ATTACHMENTS)
    n = MAX_ATTACHMENTS;

  if (n > 0)
    {
    if (bedit)
      {
      rsprintf("<tr><td colspan=2 align=left bgcolor=%s>%s.<br>\n",
                gt("Categories bgcolor1"), loc("If no attachments are resubmitted, the original ones are kept"));
      rsprintf("%s.</td></tr>\n", loc("To delete an old attachment, enter <code>&lt;delete&gt;</code> in the new attachment field"));

      for (i=0 ; i<n ; i++)
        {
        if (att[i][0])
          {
          rsprintf("<tr><td align=right nowrap bgcolor=%s>%s %d:<br>%s %d:</td>",
                    gt("Categories bgcolor1"), loc("Original attachment"), i+1, loc("New attachment"), i+1);

          rsprintf("<td bgcolor=%s>%s<br>", gt("Categories bgcolor2"), att[i]+14);
          rsprintf("<input type=\"file\" size=\"60\" maxlength=\"200\" name=\"attfile%d\" accept=\"filetype/*\"></td></tr>\n",
                    i+1);
          }
        else
          rsprintf("<tr><td bgcolor=%s>%s %d:</td><td bgcolor=%s><input type=\"file\" size=\"60\" maxlength=\"200\" name=\"attfile%d\" accept=\"filetype/*\"></td></tr>\n",
                    gt("Categories bgcolor1"), loc("Attachment"), i+1, gt("Categories bgcolor2"), i+1);
        }

      }
    else
      {
      /* attachment */
      for (i=0 ; i<n ; i++)
        rsprintf("<tr><td nowrap bgcolor=%s><b>%s %d:</b></td><td bgcolor=%s><input type=\"file\" size=\"60\" maxlength=\"200\" name=\"attfile%d\" accept=\"filetype/*\"></td></tr>\n",
                 gt("Categories bgcolor1"), loc("Attachment"), i+1, gt("Categories bgcolor2"), i+1);
      }
    }

  rsprintf("</td></tr></table>\n");

  /*---- menu buttons again ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Menu1 cellpadding"), gt("Frame color"));

  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Submit"));
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Back"));
  rsprintf("</td></tr></table></td></tr>\n\n");

  rsprintf("</td></tr></table>\n");
  rsprintf("</form></body></html>\r\n");
}

/*------------------------------------------------------------------*/

void show_elog_find(LOGBOOK *lbs)
{
int    i, j;
char   str[256], mode[256];

  /*---- header ----*/

  show_standard_header(loc("ELOG find"), NULL);

  /*---- title ----*/

  show_standard_title(lbs->name, "", 0);

  /*---- menu buttons ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Menu1 cellpadding"), gt("Frame color"));

  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Search"));
  rsprintf("<input type=reset value=\"%s\">\n", loc("Reset Form"));
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Back"));
  rsprintf("</td></tr></table></td></tr>\n\n");

  /*---- entry form ----*/

  /* overall table for message giving blue frame */
  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Categories border"), gt("Categories cellpadding"), gt("Frame color"));

  rsprintf("<tr><td colspan=2 bgcolor=%s>", gt("Categories bgcolor2"));
  rsprintf("<b>Mode:</b>&nbsp;&nbsp;");

  if (!getcfg(lbs->name, "Display mode", mode))
    strcpy(mode, "Full");

  if (!getcfg(lbs->name, "Show text", str) || atoi(str) == 1)
    {
    if (equal_ustring(mode, "Full"))
      rsprintf("<input type=radio name=mode value=\"full\" checked>%s&nbsp;&nbsp;\n", loc("Display full message"));
    else
      rsprintf("<input type=radio name=mode value=\"full\">%s&nbsp;&nbsp;\n", loc("Display full message"));

    if (equal_ustring(mode, "Summary"))
      rsprintf("<input type=radio name=mode value=\"summary\" checked>%s&nbsp;&nbsp;\n", loc("Summary only"));
    else
      rsprintf("<input type=radio name=mode value=\"summary\">%s&nbsp;&nbsp;\n", loc("Summary only"));

    if (equal_ustring(mode, "Threaded"))
      rsprintf("<input type=radio name=mode value=\"threaded\" checked>%s&nbsp;&nbsp;\n", loc("Display threads"));
    else
      rsprintf("<input type=radio name=mode value=\"threaded\">%s&nbsp;&nbsp;\n", loc("Display threads"));
    }

  rsprintf("</td></tr>\n");

  if (!getcfg(lbs->name, "Number attachments", str) || atoi(str) > 0)
    {
    rsprintf("<td colspan=2 bgcolor=%s>", gt("Categories bgcolor2"));
    rsprintf("<input type=checkbox name=attach value=1>%s</td></tr>\n", loc("Show attachments"));
    }

  rsprintf("<td colspan=2 bgcolor=%s>", gt("Categories bgcolor2"));
  rsprintf("<input type=checkbox name=printable value=1>%s</td></tr>\n", loc("Printable output"));

  rsprintf("<td colspan=2 bgcolor=%s>", gt("Categories bgcolor2"));
  rsprintf("<input type=checkbox name=reverse value=1>%s</td></tr>\n", loc("Sort in reverse order"));

  /* count logbooks */
  for (i=0 ;  ; i++)
    {
    if (!enumgrp(i, str))
      break;

    if (equal_ustring(str, "global"))
      continue;
    }

  if (i > 2)
    {
    if (!getcfg(lbs->name, "Search all logbooks", str) || atoi(str) == 1)
      {
      rsprintf("<td colspan=2 bgcolor=%s>", gt("Categories bgcolor2"));
      rsprintf("<input type=checkbox name=all value=1>%s</td></tr>\n", loc("Search all logbooks"));
      }
    }

  rsprintf("<td colspan=2 bgcolor=%s>", gt("Categories bgcolor2"));
  rsprintf(loc("Display"));
  if (!getcfg(lbs->name, "Entries per page", str))
    strcpy(str, "20");
  rsprintf(" <input type=text name=npp size=3 value=%s> ", str);
  rsprintf(loc("entries per page"));

  rsprintf("<tr><td nowrap width=10%% bgcolor=%s>%s:</td>", gt("Categories bgcolor1"), loc("Start date"));
  rsprintf("<td bgcolor=%s><select name=\"m1\">\n", gt("Categories bgcolor2"));

  rsprintf("<option value=\"\">\n");
  for (i=0 ; i<12 ; i++)
    rsprintf("<option value=\"%s\">%s\n", mname[i], mname[i]);
  rsprintf("</select>\n");

  rsprintf("<select name=\"d1\">");
  rsprintf("<option selected value=\"\">\n");
  for (i=0 ; i<31 ; i++)
    rsprintf("<option value=%d>%d\n", i+1, i+1);
  rsprintf("</select>\n");

  rsprintf("&nbsp;%s: <input type=\"text\" size=5 maxlength=5 name=\"y1\">", loc("Year"));
  rsprintf("</td></tr>\n");

  rsprintf("<tr><td bgcolor=%s>%s:</td>", gt("Categories bgcolor1"), loc("End date"));
  rsprintf("<td bgcolor=%s><select name=\"m2\">\n", gt("Categories bgcolor2"));

  rsprintf("<option value=\"\">\n");
  for (i=0 ; i<12 ; i++)
    rsprintf("<option value=\"%s\">%s\n", mname[i], mname[i]);
  rsprintf("</select>\n");

  rsprintf("<select name=\"d2\">");
  rsprintf("<option selected value=\"\">\n");
  for (i=0 ; i<31 ; i++)
    rsprintf("<option value=%d>%d\n", i+1, i+1);
  rsprintf("</select>\n");

  rsprintf("&nbsp;%s: <input type=\"text\" size=5 maxlength=5 name=\"y2\">", loc("Year"));
  rsprintf("</td></tr>\n");

  rsprintf("</td></tr>\n");

  for (i=0 ; i<lbs->n_attr ; i++)
    {
    rsprintf("<tr><td nowrap bgcolor=%s>%s:</td>", gt("Categories bgcolor1"), attr_list[i]);
    rsprintf("<td bgcolor=%s>", gt("Categories bgcolor2"));
    if (attr_options[i][0][0] == 0)
      {
      rsprintf("<input type=\"text\" size=\"30\" maxlength=\"80\" name=\"%s\">\n", attr_list[i]);
      rsprintf("<i>%s</i>\n", loc("(case insensitive substring)"));
      }
    else
      {
      if (equal_ustring(attr_options[i][0], "boolean"))
        rsprintf("<input type=checkbox name=\"%s\" value=1>\n", attr_list[i]);

      /* display image for icon */
      else if (attr_flags[i] & AF_ICON)
        {
        for (j=0 ; j<MAX_N_LIST && attr_options[i][j][0] ; j++)
          {
          rsprintf("<input type=radio name=\"%s\" value=\"%s\">", attr_list[i], attr_options[i][j]);
          rsprintf("<img src=\"icons/%s\">&nbsp;\n", attr_options[i][j]);
          }
        }

      else
        {
        rsprintf("<select name=\"%s\">\n", attr_list[i]);
        rsprintf("<option value=\"\">\n");
        for (j=0 ; j<MAX_N_LIST && attr_options[i][j][0] ; j++)
          rsprintf("<option value=\"%s\">%s\n", attr_options[i][j], attr_options[i][j]);
        rsprintf("</select>\n");
        }
      }
    rsprintf("</td></tr>\n");
    }

  if (!getcfg(lbs->name, "Show text", str) || atoi(str) == 1)
    {
    rsprintf("<tr><td bgcolor=%s>%s:</td>",  gt("Categories bgcolor1"), loc("Text"));
    rsprintf("<td bgcolor=%s><input type=\"text\" size=\"30\" maxlength=\"80\" name=\"subtext\">\n",
               gt("Categories bgcolor2"));
    rsprintf("<i>%s</i></td></tr>\n", loc("(case insensitive substring)"));
    }

  rsprintf("</table></td></tr></table>\n");
  rsprintf("</body></html>\r\n");
}

/*------------------------------------------------------------------*/

void show_admin_page(LOGBOOK *lbs)
{
int  fh, length;
char *buffer;

  /*---- header ----*/

  show_http_header();

  rsprintf("<html><head><title>ELOG config</title></head>\n");
  rsprintf("<body><form method=\"POST\" action=\".\" enctype=\"multipart/form-data\">\n");

  /*---- title ----*/

  show_standard_title(lbs->name, "", 0);

  /*---- menu buttons ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Menu1 cellpadding"), gt("Frame color"));

  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Save"));
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Cancel"));
  rsprintf("</td></tr></table></td></tr>\n\n");

  /*---- entry form ----*/

  /* overall table for message giving blue frame */
  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Categories border"), gt("Categories cellpadding"), gt("Frame color"));

  rsprintf("<tr><td colspan=2 bgcolor=%s>", gt("Categories bgcolor2"));

  fh = open(cfg_file, O_RDONLY | O_BINARY);
  if (fh < 0)
    {
    rsprintf("Cannot read configuration file <b>\"%s\"</b>", cfg_file);
    rsprintf("</table></td></tr></table>\n");
    rsprintf("</body></html>\r\n");
    return;
    }
  length = lseek(fh, 0, SEEK_END);
  lseek(fh, 0, SEEK_SET);
  buffer = malloc(length+1);
  if (buffer == NULL)
    {
    close(fh);
    rsprintf("Error: out of memory<p>");
    rsprintf("</table></td></tr></table>\n");
    rsprintf("</body></html>\r\n");
    return;
    }
  read(fh, buffer, length);
  buffer[length] = 0;
  close(fh);

  rsprintf("<textarea rows=40 cols=80 wrap=virtual name=Text>");

  rsputs(buffer);
  free(buffer);

  rsprintf("</textarea>\n");

  /* put link for config page */
  rsprintf("<a target=\"_blank\" href=\"http://midas.psi.ch/elog/config.html\">Syntax Help</a>");

  rsprintf("</table></td></tr>\n");

  /*---- menu buttons ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Menu1 cellpadding"), gt("Frame color"));

  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Save"));
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Cancel"));
  rsprintf("</td></tr></table>\n\n");

  rsprintf("</td></tr></table>\n\n");
  rsprintf("</body></html>\r\n");
}

/*------------------------------------------------------------------*/

int save_admin_config()
{
int  fh, i;
char str[80];

  fh = open(cfg_file, O_RDWR | O_BINARY | O_TRUNC, 644);
  if (fh < 0)
    {
    sprintf(str, loc("Cannot open file <b>%s</b>"), cfg_file);
    strcat(str, ": ");
    strcat(str, strerror(errno));
    show_error(str);
    return 0;
    }
  i = write(fh, _text, strlen(_text));
  if (i < (int)strlen(_text))
    {
    sprintf(str, loc("Cannot write to <b>%s</b>"), cfg_file);
    strcat(str, ": ");
    strcat(str, strerror(errno));
    show_error(str);
    close(fh);
    return 0;
    }

  close(fh);
  return 1;
}

/*------------------------------------------------------------------*/

int save_user_config(LOGBOOK *lbs, char *user, BOOL new_user)
{
FILE   *f;
char   file_name[256], str[256], line[256], *buf, *pl, new_pwd[80], new_pwd2[80];
int    i, size;

  /* check for hidden password */
  if (isparam("hpwd"))
    {
    strcpy(new_pwd, getparam("hpwd"));
    }
  else
    {
    /* check if passwords match */
    do_crypt(getparam("newpwd"), new_pwd);
    do_crypt(getparam("newpwd2"), new_pwd2);

    if (strcmp(new_pwd, new_pwd2) != 0)
      {
      show_error(loc("New passwords do not match, please retype"));
      return 0;
      }
    }

  getcfg(lbs->name, "Password file", str);

  if (str[0] == DIR_SEPARATOR || str[1] == ':')
    strcpy(file_name, str);
  else
    {
    strcpy(file_name, cfg_dir);
    strcat(file_name, str);
    }

  f = fopen(file_name, "r+b");
  if (f == NULL)
    {
    show_error("");
    return 0;
    }

  fseek(f, 0, SEEK_END);
  size = TELL(fileno(f));
  fseek(f, 0, SEEK_SET);

  buf = malloc(size+1);
  fread(buf, 1, size, f);
  buf[size] = 0;
  pl = buf;

  while (pl < buf+size)
    {
    for (i=0 ; pl[i] && pl[i] != '\r' && pl[i] != '\n' ; i++)
      line[i] = pl[i];
    line[i] = 0;

    if (line[0] == ';' || line[0] == '#' || line[0] == 0)
      {
      pl += strlen(line);
      while (*pl && (*pl == '\r' || *pl == '\n'))
        pl++;
      continue;
      }

    strcpy(str, line);
    if (strchr(str, ':'))
      *strchr(str, ':') = 0;
    if (strcmp(str, user) == 0)
      {
      if (new_user)
        {
        sprintf(str, "%s \"%s\" %s", loc("Login name"), user, loc("exists already"));
        show_error(str);
        free(buf);
        fclose(f);
        return 0;
        }
      break;
      }

    pl += strlen(line);
    while (*pl && (*pl == '\r' || *pl == '\n'))
      pl++;
    }

  if (new_user)
    {
    fseek(f, 0, SEEK_END);
    if (strlen(buf) != 0 &&
        (buf[strlen(buf)-1] != '\r' && buf[strlen(buf)-1] != '\n'))
      fprintf(f, "\n");

    sprintf(str, "%s:%s:%s:%s:%s", getparam("new_user_name"), new_pwd, 
            getparam("new_full_name"), getparam("new_user_email"), getparam("email_notify"));
    fprintf(f, "%s\n", str);
    }
  else
    {
    /* replace line */
    fseek(f, 0, SEEK_SET);
    fwrite(buf, 1, pl-buf, f);

    sprintf(str, "%s:%s:%s:%s:%s", getparam("new_user_name"), new_pwd, 
            getparam("new_full_name"), getparam("new_user_email"), getparam("email_notify"));
    fprintf(f, "%s\n", str);

    pl += strlen(line);
    while (*pl && (*pl == '\r' || *pl == '\n'))
      pl++;

    fwrite(pl, 1, strlen(pl), f);

#ifdef _MSC_VER
    chsize(fileno(f), TELL(fileno(f)));
#else
    ftruncate(fileno(f), TELL(fileno(f)));
#endif
    }

  free(buf);
  fclose(f);

  /* if user name changed, set cookie */
  if (strcmp(user, getparam("new_user_name")) != 0 &&
      strcmp(user, getparam("unm")) == 0)
    {
    set_login_cookies(lbs, getparam("new_user_name"), new_pwd);
    return 0;
    }  

  /* if new user, login as this user */
  if (new_user && !*getparam("unm"))
    {
    set_login_cookies(lbs, getparam("new_user_name"), new_pwd);
    return 0;
    }

  return 1;
}

/*------------------------------------------------------------------*/

int remove_user(LOGBOOK *lbs, char *user)
{
FILE   *f;
char   file_name[256], str[256], line[256], *buf, *pl;
int    i, size;

  getcfg(lbs->name, "Password file", str);

  if (str[0] == DIR_SEPARATOR || str[1] == ':')
    strcpy(file_name, str);
  else
    {
    strcpy(file_name, cfg_dir);
    strcat(file_name, str);
    }

  f = fopen(file_name, "r+b");
  if (f == NULL)
    {
    show_error("");
    return 0;
    }

  fseek(f, 0, SEEK_END);
  size = TELL(fileno(f));
  fseek(f, 0, SEEK_SET);

  buf = malloc(size+1);
  fread(buf, 1, size, f);
  buf[size] = 0;
  pl = buf;

  while (pl < buf+size)
    {
    for (i=0 ; pl[i] && pl[i] != '\r' && pl[i] != '\n' ; i++)
      line[i] = pl[i];
    line[i] = 0;

    if (line[0] == ';' || line[0] == '#' || line[0] == 0)
      {
      pl += strlen(line);
      while (*pl && (*pl == '\r' || *pl == '\n'))
        pl++;
      continue;
      }

    strcpy(str, line);
    if (strchr(str, ':'))
      *strchr(str, ':') = 0;
    if (strcmp(str, user) == 0)
      break;

    pl += strlen(line);
    while (*pl && (*pl == '\r' || *pl == '\n'))
      pl++;
    }

  /* remove line */
  fseek(f, 0, SEEK_SET);
  fwrite(buf, 1, pl-buf, f);

  pl += strlen(line);
  while (*pl && (*pl == '\r' || *pl == '\n'))
    pl++;

  fwrite(pl, 1, strlen(pl), f);

#ifdef _MSC_VER
  chsize(fileno(f), TELL(fileno(f)));
#else
  ftruncate(fileno(f), TELL(fileno(f)));
#endif

  free(buf);
  fclose(f);
  
  return 1;
}

/*------------------------------------------------------------------*/

void show_config_page(LOGBOOK *lbs)
{
char str[256], user[80], password[80], full_name[80], user_email[80], email_notify[256];
int  i;

  /*---- header ----*/

  show_standard_header(loc("ElOG user config"), "");

  /*---- title ----*/

  show_standard_title(lbs->name, "", 0);


  /* get user */
  strcpy(user, getparam("unm"));
  if (isparam("cfg_user"))
    strcpy(user, getparam("cfg_user"));

  /*---- menu buttons ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Menu1 cellpadding"), gt("Frame color"));

  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  rsprintf("<input type=hidden name=cmd value=\"Config\">\n", user); // for select javascript
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Save"));
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Cancel"));
  rsprintf("<input type=hidden name=config value=\"%s\">\n", user);
  rsprintf("</td></tr></table></td></tr>\n\n");

  /* overall table for message giving blue frame */
  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Categories border"), gt("Categories cellpadding"), gt("Frame color"));

  /*---- if admin user, show user list ----*/

  if (getcfg(lbs->name, "Admin user", str) && 
      strstr(str, getparam("unm")) != 0)
    {
    rsprintf("<tr><td width=10%% bgcolor=%s>%s:</td>\n", gt("Categories bgcolor1"), loc("Select user"));
    rsprintf("<td bgcolor=%s><select name=cfg_user onChange=\"document.form1.submit()\">\n", gt("Categories bgcolor2"));

    for (i=0 ; ; i++)
      {
      if (enum_user_line(lbs, i, str))
        {
        if (strcmp(str, user) == 0)
          rsprintf("<option selected value=\"%s\">%s\n", str, str);
        else
          rsprintf("<option value=\"%s\">%s\n", str, str);
        }
      else
        break;
      }

    rsprintf("</select></td></tr>\n");
    }

  /*---- entry form ----*/

  get_user_line(lbs, user, password, full_name, user_email, email_notify);

  rsprintf("<tr><td width=10%% bgcolor=%s>%s:</td>\n", gt("Categories bgcolor1"), loc("Login name"));
  rsprintf("<td bgcolor=%s><input type=text name=new_user_name value=\"%s\"></td></tr>\n", 
            gt("Categories bgcolor2"), user);

  rsprintf("<tr><td width=10%% bgcolor=%s>%s:</td>\n", gt("Categories bgcolor1"), loc("Full name"));
  rsprintf("<td bgcolor=%s><input type=text name=new_full_name value=\"%s\"></tr>\n", 
            gt("Categories bgcolor2"), full_name);

  rsprintf("<tr><td width=10%% bgcolor=%s>Email:</td>\n", gt("Categories bgcolor1"));
  rsprintf("<td bgcolor=%s><input type=text name=new_user_email value=\"%s\">&nbsp;&nbsp;&nbsp;&nbsp;\n", 
            gt("Categories bgcolor2"), user_email);

  rsprintf("%s:\n", loc("Automatic email notifications"));
  
  if (email_notify[0])
    rsprintf("<input type=checkbox checked name=email_notify value=all></td></tr>\n");
  else
    rsprintf("<input type=checkbox name=email_notify value=all></td></tr>\n");

  rsprintf("<tr><td colspan=2 bgcolor=%s>", gt("Categories bgcolor2"));
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Change password"));

  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Remove user"));

  if (getcfg(lbs->name, "Admin user", str) && 
      strstr(str, getparam("unm")) != 0)
    {
    rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("New user"));
    }

  /* hidden field for password */
  rsprintf("<input type=hidden name=hpwd value=\"%s\">\n", password);
  
  rsprintf("</td></tr></table></td></tr>\n");

  rsprintf("</td></tr></table>\n\n");
  rsprintf("</body></html>\r\n");
}

/*------------------------------------------------------------------*/

void show_new_user_page(LOGBOOK *lbs)
{

  /*---- header ----*/

  show_standard_header(loc("ElOG new user"), "");

  /*---- title ----*/

  show_standard_title(lbs->name, "", 0);

  /*---- menu buttons ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Menu1 cellpadding"), gt("Frame color"));

  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Save"));
  rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Cancel"));
  rsprintf("</td></tr></table></td></tr>\n\n");

  /* overall table for message giving blue frame */
  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Categories border"), gt("Categories cellpadding"), gt("Frame color"));

  /*---- entry form ----*/

  rsprintf("<tr><td width=20%% bgcolor=%s>%s:</td>\n", gt("Categories bgcolor1"), loc("Login name"));
  rsprintf("<td bgcolor=%s><input type=text name=new_user_name> <i>(%s)</i></td></tr>\n", 
            gt("Categories bgcolor2"), loc("name may not contain blanks"));

  rsprintf("<tr><td width=20%% bgcolor=%s>%s:</td>\n", gt("Categories bgcolor1"), loc("Full name"));
  rsprintf("<td bgcolor=%s><input type=text name=new_full_name></tr>\n", 
            gt("Categories bgcolor2"));

  rsprintf("<tr><td width=20%% bgcolor=%s>Email:</td>\n", gt("Categories bgcolor1"));
  rsprintf("<td bgcolor=%s><input type=text name=new_user_email></tr>\n", 
            gt("Categories bgcolor2"));

  rsprintf("<tr><td width=20%% bgcolor=%s>%s:</td>\n", gt("Categories bgcolor1"), loc("Automatic email notifications"));
  rsprintf("<td bgcolor=%s><input type=checkbox name=email_notify value=all></tr>\n", gt("Categories bgcolor2"));

  rsprintf("<tr><td width=20%% bgcolor=%s>%s:</td>\n", gt("Categories bgcolor1"), loc("Password"));
  rsprintf("<td bgcolor=%s><input type=password name=newpwd>\n", gt("Categories bgcolor2"));

  rsprintf("<tr><td width=20%% bgcolor=%s>%s:</td>\n", gt("Categories bgcolor1"), loc("Retype password"));
  rsprintf("<td bgcolor=%s><input type=password name=newpwd2>\n", gt("Categories bgcolor2"));

  rsprintf("</td></tr></table></td></tr>\n");

  rsprintf("</td></tr></table>\n\n");
  rsprintf("</body></html>\r\n");
}

/*------------------------------------------------------------------*/

void show_elog_delete(LOGBOOK *lbs, int message_id)
{
int    status;
char   str[256], in_reply_to[80], reply_to[256];

  /* redirect if confirm = NO */
  if (getparam("confirm") && *getparam("confirm") &&
      strcmp(getparam("confirm"), loc("No")) == 0)
    {
    sprintf(str, "%d", message_id);
    redirect(str);
    return;
    }

  /* header */
  sprintf(str, "%d", message_id);
  show_standard_header("Delete ELog entry", str);

  rsprintf("<p><p><p><table border=%s width=50%% bgcolor=%s cellpadding=1 cellspacing=0 align=center>",
            gt("Border width"), gt("Frame color"));
  rsprintf("<tr><td><table cellpadding=5 cellspacing=0 border=0 width=100%% bgcolor=%s>\n", gt("Frame color"));

  if (getparam("confirm") && *getparam("confirm"))
    {
    if (strcmp(getparam("confirm"), loc("Yes")) == 0)
      {
      /* delete message */
      status = el_delete_message(lbs, message_id, TRUE, NULL, TRUE);
      rsprintf("<tr><td bgcolor=#80FF80 align=center>");
      if (status == EL_SUCCESS)
        rsprintf("<b>%s</b></tr>\n", loc("Message successfully deleted"));
      else
        rsprintf("<b>%s = %d</b></tr>\n", loc("Error deleting message: status"), status);

      rsprintf("<input type=hidden name=cmd value=\"%s\">\n", loc("Last"));
      rsprintf("<tr><td bgcolor=%s align=center><input type=submit value=\"%s\"></td></tr>\n",
                gt("Cell BGColor"), loc("Goto last message"));
      }
    }
  else
    {
    /* define hidden field for command */
    rsprintf("<input type=hidden name=cmd value=\"%s\">\n", loc("Delete"));

    rsprintf("<tr><td bgcolor=%s align=center>", gt("Title bgcolor"));
    rsprintf("<font color=%s><b>%s</b></font></td></tr>\n", gt("Title fontcolor"),
            loc("Are you sure to delete this message?"));

    /* check for replies */

    /* retrieve original message */
    el_retrieve(lbs, message_id, NULL, attr_list, NULL, 0,
                NULL, NULL, in_reply_to, reply_to, NULL, NULL);

    if (reply_to[0])
      rsprintf("<tr><td bgcolor=%s align=center>%d<br>%s</td></tr>\n", gt("Cell BGColor"), message_id, loc("and all its replies"));
    else
      rsprintf("<tr><td bgcolor=%s align=center>%d</td></tr>\n", gt("Cell BGColor"), message_id);

    rsprintf("<tr><td bgcolor=%s align=center><input type=submit name=confirm value=\"%s\">\n",
              gt("Cell BGColor"), loc("Yes"));
    rsprintf("<input type=submit name=confirm value=\"%s\">\n", loc("No"));
    rsprintf("</td></tr>\n\n");
    }

  rsprintf("</table></td></tr></table>\n");
  rsprintf("</body></html>\r\n");
}

/*------------------------------------------------------------------*/

int show_download_page(LOGBOOK *lbs, char *path)
{
char   file_name[256], str[256];
int    index, message_id, fh, i, size;
char   message[TEXT_SIZE+1000], *p;
time_t now;
struct tm *gmt;

  message_id = atoi(path);

  for (index = 0 ; index < *lbs->n_el_index ; index++)
    if (lbs->el_index[index].message_id == message_id)
      break;

  if (index == *lbs->n_el_index)
    return EL_NO_MSG;

  sprintf(file_name, "%s%s", lbs->data_dir, lbs->el_index[index].file_name);
  fh = open(file_name, O_RDWR | O_BINARY, 0644);
  if (fh < 0)
    return EL_FILE_ERROR;

  lseek(fh, lbs->el_index[index].offset, SEEK_SET);
  i = read(fh, message, sizeof(message)-1);
  if (i <= 0)
    {
    close(fh);
    return EL_FILE_ERROR;
    }

  message[i] = 0;
  close(fh);

  /* decode message size */
  p = strstr(message+8, "$@MID@$:");
  if (p == NULL)
    size = strlen(message);
  else
    size = (int) p - (int) message;

  message[size] = 0;

  /* header */
  rsprintf("HTTP/1.1 200 Document follows\r\n");
  rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
  rsprintf("Accept-Ranges: bytes\r\n");

  time(&now);
  now += (int) (3600*3);
  gmt = gmtime(&now);
  strftime(str, sizeof(str), "%A, %d-%b-%y %H:%M:%S GMT", gmt);
  rsprintf("Expires: %s\r\n", str);

  if (use_keepalive)
    {
    rsprintf("Connection: Keep-Alive\r\n");
    rsprintf("Keep-Alive: timeout=60, max=10\r\n");
    }

  rsprintf("Content-Type: text/plain\r\n");
  rsprintf("Content-Length: %d\r\n\r\n", size);

  /* return if file too big */
  if (size > (int) (sizeof(return_buffer) - strlen(return_buffer)))
    {
    printf("return buffer too small\n");
    return EL_MEM_ERROR;
    }

  return_length = strlen(return_buffer)+size;
  strcat(return_buffer, message);

  return EL_SUCCESS;
}

/*------------------------------------------------------------------*/

void display_line(LOGBOOK *lbs, int message_id, int number, char *mode,
                  int level, BOOL printable, int n_line, int show_attachments,
                  char *date, char *reply_to,
                  int n_attr_disp, char disp_attr[MAX_N_ATTR+4][NAME_LENGTH],
                  char attrib[MAX_N_ATTR][NAME_LENGTH],
                  int n_attr, char *text,
                  char attachment[MAX_ATTACHMENTS][256], char *encoding)
{
char str[256], ref[256], *nowrap, col[80], format[256], file_name[256];
char slist[MAX_N_ATTR+10][NAME_LENGTH], svalue[MAX_N_ATTR+10][NAME_LENGTH];
char display[256], attr_icon[80];
int  i, j, size, i_line, index, colspan;
BOOL link_displayed, skip_comma;
FILE *f;

  sprintf(ref, "../%s/%d", lbs->name_enc, message_id);

  if (equal_ustring(mode, "Summary"))
    {
    if (number % 2 == 1)
      strcpy(col, gt("List bgcolor1"));
    else
      strcpy(col, gt("List bgcolor2"));
    }
  else if (equal_ustring(mode, "Full"))
    strcpy(col, gt("List bgcolor1"));
  else if (equal_ustring(mode, "Threaded"))
    {
    if (level == 0)
      strcpy(col, gt("List bgcolor1"));
    else
      strcpy(col, gt("List bgcolor2"));
    }

  rsprintf("<tr>");

  /* only single cell for threaded display */
  if (equal_ustring(mode, "Threaded"))
    {
    rsprintf("<td align=left bgcolor=%s>", col);
    for (i=0 ; i<level ; i++)
      rsprintf("&nbsp;&nbsp;&nbsp;");
    }

  size = printable ? 2 : 3;
  nowrap = printable ? "" : "nowrap";
  link_displayed = FALSE;
  skip_comma = FALSE;

  if (equal_ustring(mode, "Threaded") && getcfg(lbs->name, "Thread display", display))
    {
    /* check if to use icon from attributes */
    attr_icon[0] = 0;
    if (getcfg(lbs->name, "Thread icon", attr_icon))
      {
      for (i=0 ; i<n_attr ; i++)
        if (equal_ustring(attr_list[i], attr_icon))
          break;
      if (i<n_attr && attrib[i][0])
        strcpy(attr_icon, attrib[i]);
      else
        attr_icon[0] = 0;
      }

    if (attr_icon[0])
      rsprintf("<a href=\"%s\"><img border=0 src=\"icons/%s\"></a>&nbsp;", ref, attr_icon);
    else
      {
      /* if top level only, display reply icon if message has a reply */
      if (getcfg(lbs->name, "Top level only", str) && atoi(str) == 1 && reply_to[0])
        {
        if (*gt("Thread reply image"))
          rsprintf("<a href=\"%s\"><img border=0 src=\"%s\"></a>&nbsp;", ref, gt("Thread reply image"));
        else
          rsprintf("<font size=%d><a href=\"%s\">&nbsp;%d >&nbsp;</a></font>",
                    size, ref, message_id);
        }
      else
        {
        /* display standard icons */
        if (level == 0)
          {
          if (*gt("Thread image"))
            rsprintf("<a href=\"%s\"><img border=0 src=\"%s\"></a>&nbsp;", ref, gt("Thread image"));
          else
            rsprintf("<font size=%d><a href=\"%s\">&nbsp;%d&nbsp;</a></font>",
                      size, ref, message_id);
          }
        else
          {
          if (*gt("Thread reply image"))
            rsprintf("<a href=\"%s\"><img border=0 src=\"%s\"></a>&nbsp;", ref, gt("Thread reply image"));
          else
            rsprintf("<font size=%d><a href=\"%s\">&nbsp;%d&nbsp;</a></font>",
                      size, ref, message_id);
          }
        }
      }

    j = build_subst_list(lbs, slist, svalue, attrib);
    strsubst(display, slist, svalue, j);
    rsputs2(display);
    }
  else
    {
    for (index=0 ; index<n_attr_disp ; index++)
      {
      if (equal_ustring(disp_attr[index], "#"))
        {
        if (equal_ustring(mode, "Threaded"))
          {
          if (level == 0)
            {
            if (*gt("Thread image"))
              rsprintf("<a href=\"%s\"><img border=0 src=\"%s\"></a>&nbsp;", ref, gt("Thread image"));
            else
              rsprintf("<font size=%d><a href=\"%s\">&nbsp;%d&nbsp;</a></font>",
                        size, ref, message_id);
            }
          else
            {
            if (*gt("Thread reply image"))
              rsprintf("<a href=\"%s\"><img border=0 src=\"%s\"></a>&nbsp;", ref, gt("Thread reply image"));
            else
              rsprintf("<font size=%d><a href=\"%s\">&nbsp;%d&nbsp;</a></font>",
                        size, ref, message_id);
            }

          skip_comma = TRUE;
          }
        else
          rsprintf("<td align=center bgcolor=%s><font size=%d><a href=\"%s\">&nbsp;&nbsp;%d&nbsp;&nbsp;</a></font></td>",
            col, size, ref, message_id);

        link_displayed = TRUE;
        }

      if (equal_ustring(disp_attr[index], "Logbook"))
        {
        if (equal_ustring(mode, "Threaded"))
          {
          if (!link_displayed)
            {
            rsprintf("<font size=%d><a href=\"%s\">%s</a></font>",
                     size, ref, lbs->name);
            link_displayed = TRUE;
            }
          else
            if (skip_comma)
              {
              rsprintf("<font size=%d>%s</font>", size, lbs->name);
              skip_comma = FALSE;
              }
            else
              rsprintf("<font size=%d>, %s</font>", size, lbs->name);
          }
        else
          {
          if (!link_displayed)
            {
            rsprintf("<td align=center %s bgcolor=%s><font size=%d><a href=\"%s\">%s</a></font></td>",
              nowrap, col, size, ref, lbs->name);
            link_displayed = TRUE;
            }
          else
            rsprintf("<td align=center %s bgcolor=%s><font size=%d>%s</font></td>", nowrap, col, size, lbs->name);
          }
        }

      if (equal_ustring(disp_attr[index], "Date"))
        {
        if (getcfg(lbs->name, "Date format", format))
          {
          struct tm ts;

          memset(&ts, 0, sizeof(ts));

          for (i=0 ; i<12 ; i++)
            if (strncmp(date+4, mname[i], 3) == 0)
              break;
          ts.tm_mon = i;

          ts.tm_mday = atoi(date+8);
          ts.tm_hour = atoi(date+11);
          ts.tm_min  = atoi(date+14);
          ts.tm_sec  = atoi(date+17);
          ts.tm_year = atoi(date+20)-1900;
          ts.tm_isdst = -1; /* let mktime compute DST */

          mktime(&ts);
          strftime(str, sizeof(str), format, &ts);
          }
        else
          strcpy(str, date);

        if (equal_ustring(mode, "Threaded"))
          {
          if (!link_displayed)
            {
            rsprintf("<font size=%d><a href=\"%s\">%s</a></font>",
                     size, ref, str);
            link_displayed = TRUE;
            }
          else
            if (skip_comma)
              {
              rsprintf("<font size=%d>  %s</font>", size, str);
              skip_comma = FALSE;
              }
            else
              rsprintf("<font size=%d>, %s</font>", size, str);
          }
        else
          {
          if (!link_displayed)
            {
            rsprintf("<td align=center %s bgcolor=%s><font size=%d><a href=\"%s\">%s</a></font></td>",
              nowrap, col, size, ref, str);
            link_displayed = TRUE;
            }
          else
            rsprintf("<td align=center %s bgcolor=%s><font size=%d>%s</font></td>", nowrap, col, size, str);
          }
        }

      for (i=0 ; i<n_attr ; i++)
        if (equal_ustring(disp_attr[index], attr_list[i]))
          {
          if (equal_ustring(mode, "Threaded"))
            {
            if (equal_ustring(attr_options[i][0], "boolean"))
              {
              if (atoi(attrib[i]) == 1)
                {
                rsprintf("<font size=%d>", size);
                if (!link_displayed)
                  {
                  rsprintf("<a href=\"%s\">", ref);
                  rsputs2(attr_list[i]);
                  rsprintf("</a>");
                  link_displayed = TRUE;
                  }
                else
                  {
                  if (skip_comma)
                    {
                    rsprintf(" ");
                    skip_comma = FALSE;
                    }
                  else
                    rsprintf(", ");

                  rsputs2(attrib[i]);
                  }
                rsprintf("&nbsp</font>");
                }
              }

            else if (attr_flags[i] & AF_ICON)
              {
              if (attrib[i][0])
                rsprintf("&nbsp;<img src=\"icons/%s\">&nbsp;", attrib[i]);
              }

            else
              {
              rsprintf("<font size=%d>", size);
              if (!link_displayed)
                {
                rsprintf("<a href=\"%s\">", ref);
                rsputs2(attrib[i]);
                rsprintf("</a>");
                link_displayed = TRUE;
                }
              else
                {
                if (skip_comma)
                  {
                  rsprintf(" ");
                  skip_comma = FALSE;
                  }
                else
                  rsprintf(", ");

                rsputs2(attrib[i]);
                }
              rsprintf("</font>");
              }
            }
          else
            {
            if (equal_ustring(attr_options[i][0], "boolean"))
              {
              if (atoi(attrib[i]) == 1)
                rsprintf("<td align=center bgcolor=%s><input type=checkbox checked disabled></td>\n", col);
              else
                rsprintf("<td align=center bgcolor=%s><input type=checkbox disabled></td>\n", col);
              }

            else if (attr_flags[i] & AF_ICON)
              {
              rsprintf("<td align=center bgcolor=%s>", col);
              if (attrib[i][0])
                rsprintf("<img src=\"icons/%s\">", attrib[i]);
              rsprintf("&nbsp</td>");
              }

            else
              {
              rsprintf("<td align=center bgcolor=%s><font size=%d>", col, size);
              if (!link_displayed)
                {
                rsprintf("<a href=\"%s\">", ref);
                rsputs2(attrib[i]);
                rsprintf("</a>");
                link_displayed = TRUE;
                }
              else
                rsputs2(attrib[i]);
              rsprintf("&nbsp</font></td>");
              }
            }
          }
        }
    }

  if (equal_ustring(mode, "Threaded"))
    rsprintf("</td>\n");

  if (equal_ustring(mode, "Summary") && n_line > 0)
    {
    rsprintf("<td bgcolor=%s><font size=%d>", col, size);
    for (i=i_line=0 ; i<sizeof(str)-1 ; i++)
      {
      str[i] = text[i];
      if (str[i] == '\n')
        i_line++;

      if (i_line == n_line)
        break;
      }
    str[i] = 0;

    /* always encode, not to rip apart HTML documents,
       e.g. only the start of a table */
    strencode(str);

    rsprintf("&nbsp;</font></td>\n");
    }

  rsprintf("</tr>\n");

  colspan = n_attr_disp;

  if (equal_ustring(mode, "Full"))
    {
    if (!getcfg(lbs->name, "Show text", str) || atoi(str) == 1)
      {
      rsprintf("<tr><td bgcolor=#FFFFFF colspan=%d><font size=%d>", colspan, size);

      if (equal_ustring(encoding, "plain"))
        {
        rsputs("<pre>");
        rsputs2(text);
        rsputs("</pre>");
        }
      else
        rsputs(text);

      rsprintf("</font></td></tr>\n");
      }

    if (!show_attachments && attachment[0][0])
      {
      rsprintf("<tr><td bgcolor=#FFFFFF colspan=%d><font size=%d>", colspan, size);

      if (attachment[1][0])
        rsprintf("%s: ", loc("Attachments"));
      else
        rsprintf("%s: ", loc("Attachment"));
      }

    for (index = 0 ; index < MAX_ATTACHMENTS ; index++)
      {
      if (attachment[index][0])
        {
        strcpy(str, attachment[index]);
        str[13] = 0;
        sprintf(ref, "../%s/%s/%s", lbs->name_enc, str, attachment[index]+14);

        for (i=0 ; i<(int)strlen(attachment[index]) ; i++)
          str[i] = toupper(attachment[index][i]);
        str[i] = 0;

        if (!show_attachments)
          {
          rsprintf("<a href=\"%s\"><b>%s</b></a>&nbsp;&nbsp;&nbsp;&nbsp; ",
                    ref, attachment[index]+14);
          }
        else
          {
          if (strstr(str, ".GIF") ||
              strstr(str, ".JPG") ||
              strstr(str, ".JPEG") ||
              strstr(str, ".PNG"))
            {
            rsprintf("<tr><td colspan=%d bgcolor=%s><b>%s %d:</b> <a href=\"%s\">%s</a>\n",
                      colspan, gt("List bgcolor2"), loc("Attachment"), index+1, ref, attachment[index]+14);
            if (show_attachments)
              rsprintf("</td></tr><tr><td colspan=%d bgcolor=#FFFFFF><img src=\"%s\"></td></tr>", colspan, ref);
            }
          else
            {
            rsprintf("<tr><td colspan=%d bgcolor=%s><b>%s %d:</b> <a href=\"%s\">%s</a>\n",
                      colspan, gt("List bgcolor2"), loc("Attachment"), index+1, ref, attachment[index]+14);

            if ((strstr(str, ".TXT") ||
                 strstr(str, ".ASC") ||
                 strchr(str, '.') == NULL) && show_attachments)
              {
              /* display attachment */
              rsprintf("<br><font size=%d><pre>", size);

              strcpy(file_name, lbs->data_dir);

              strcat(file_name, attachment[index]);

              f = fopen(file_name, "rt");
              if (f != NULL)
                {
                while (!feof(f))
                  {
                  str[0] = 0;
                  fgets(str, sizeof(str), f);
                  rsputs2(str);
                  }
                fclose(f);
                }

              rsprintf("</pre>\n");
              }
            rsprintf("</font></td></tr>\n");
            }
          }
        }
      }

    if (!show_attachments && attachment[0][0])
      rsprintf("</font></td></tr>\n");
    }
}

/*------------------------------------------------------------------*/

void display_reply(LOGBOOK *lbs, int message_id, int printable, int n_attr_disp,
                   char disp_attr[MAX_N_ATTR+4][NAME_LENGTH], int level)
{
char   date[80], *text, in_reply_to[80], reply_to[256], encoding[80],
       attachment[MAX_ATTACHMENTS][NAME_LENGTH], attrib[MAX_N_ATTR][NAME_LENGTH];
int    status, size;
char   *p;

  text = malloc(TEXT_SIZE);

  reply_to[0] = 0;
  size = TEXT_SIZE;
  status = el_retrieve(lbs, message_id, date, attr_list, attrib, lbs->n_attr,
                       text, &size, in_reply_to, reply_to,
                       attachment, encoding);

  if (status != EL_SUCCESS)
    {
    free(text);
    return;
    }

  display_line(lbs, message_id, 0, "threaded", level, printable, 0,
               FALSE, date, reply_to, n_attr_disp, disp_attr,
               attrib, lbs->n_attr, NULL, NULL, encoding);

  if (reply_to[0])
    {
    p = reply_to;
    do
      {
      display_reply(lbs, atoi(p), printable, n_attr_disp, disp_attr, level+1);

      while (*p && isdigit(*p))
        p++;
      while (*p && (*p == ',' || *p == ' '))
        p++;
      } while(*p);
    }

  free(text);
}

/*------------------------------------------------------------------*/

int msg_compare(const void *m1, const void *m2)
{
  return strcmp(((MSG_LIST *)m1)->string, ((MSG_LIST *)m2)->string);
}

int msg_compare_reverse(const void *m1, const void *m2)
{
  return strcmp(((MSG_LIST *)m2)->string, ((MSG_LIST *)m1)->string);
}

/*------------------------------------------------------------------*/

void show_page_navigation(int n_msg, int page_n, int n_page)
{
int i;
char ref[256];

  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1>\n",
            gt("Border width"), gt("Categories cellpadding"));
  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  rsprintf("<font size=1 face=verdana,arial,helvetica,sans-serif><b>");

  if (n_msg > n_page)
    rsprintf("Goto page \n");

  if (page_n > 1)
    {
    sprintf(ref, "page%d", page_n - 1);
    if (strstr(getparam("cmdline"), "cmd=Search&"))
      {
      strcat(ref, "?");
      strcat(ref, strstr(getparam("cmdline"), "cmd=Search&")+11);
      }
    else if (strchr(getparam("cmdline"), '?'))
      strcat(ref, strchr(getparam("cmdline"), '?'));
    rsprintf("<a href=\"%s\">Previous</a>&nbsp;&nbsp;", ref);
    }

  for (i=0 ; i<(n_msg-1)/n_page+1 ; i++)
    {
    sprintf(ref, "page%d", i+1);
    if (strstr(getparam("cmdline"), "cmd=Search&"))
      {
      strcat(ref, "?");
      strcat(ref, strstr(getparam("cmdline"), "cmd=Search&")+11);
      }
    else if (strchr(getparam("cmdline"), '?'))
      strcat(ref, strchr(getparam("cmdline"), '?'));

    if (i == (n_msg-1)/n_page)
      {
      if (page_n == i+1)
        rsprintf("%d&nbsp;&nbsp", i+1);
      else
        rsprintf("<a href=\"%s\">%d</a>&nbsp;&nbsp", ref, i+1);
      }
    else
      {
      if (page_n == i+1)
        rsprintf("%d, ", i+1);
      else
        rsprintf("<a href=\"%s\">%d</a>, ", ref, i+1);
      }
    }

  if (page_n != -1 && page_n * n_page < n_msg)
    {
    sprintf(ref, "page%d", page_n + 1);
    if (strstr(getparam("cmdline"), "cmd=Search&"))
      {
      strcat(ref, "?");
      strcat(ref, strstr(getparam("cmdline"), "cmd=Search&")+11);
      }
    else if (strchr(getparam("cmdline"), '?'))
      strcat(ref, strchr(getparam("cmdline"), '?'));
    rsprintf("<a href=\"%s\">Next</a>&nbsp;&nbsp;", ref);
    }

  if (page_n != -1 && n_page < n_msg)
    {
    sprintf(ref, "page");
    if (strstr(getparam("cmdline"), "cmd=Search&"))
      {
      strcat(ref, "?");
      strcat(ref, strstr(getparam("cmdline"), "cmd=Search&")+11);
      }
    else if (strchr(getparam("cmdline"), '?'))
      strcat(ref, strchr(getparam("cmdline"), '?'));
    rsprintf("<a href=\"%s\">All</a>\n", ref);
    }

  rsprintf("</b></font></td></tr></table></td></tr>\n\n");
}

/*------------------------------------------------------------------*/

void show_elog_submit_find(LOGBOOK *lbs, INT past_n, INT last_n, INT page_n)
{
int    i, j, n, index, size, status, d1, m1, y1, d2, m2, y2, n_line;
int    current_year, current_month, current_day, printable, n_logbook,
       reverse, n_attr_disp, n_msg, search_all, message_id, n_page, i_start, i_stop;
char   date[80], attrib[MAX_N_ATTR][NAME_LENGTH], disp_attr[MAX_N_ATTR+4][NAME_LENGTH],
       list[10000], text[TEXT_SIZE], text1[TEXT_SIZE], text2[TEXT_SIZE],
       in_reply_to[80], reply_to[256], attachment[MAX_ATTACHMENTS][256], encoding[80];
char   str[256], col[80], ref[256], img[80];
char   mode[80];
char   menu_str[1000], menu_item[MAX_N_LIST][NAME_LENGTH];
char   *p , *pt, *pt1, *pt2;
BOOL   show_attachments, threaded, only_message_heads;
time_t ltime, ltime_start, ltime_end, now;
struct tm tms, *ptms;
MSG_LIST *msg_list;

  printable = atoi(getparam("Printable"));

  if (*getparam("Reverse"))
    reverse = atoi(getparam("Reverse"));
  else
    {
    reverse = 0;
    if (getcfg(lbs->name, "Reverse sort", str))
      reverse = atoi(str);
    }

  /* get mode */
  strcpy(mode, "Full");

  if (past_n || last_n || page_n)
    {
    if (getcfg(lbs->name, "Display Mode", str))
      strcpy(mode, str);
    if (*getparam("mode"))
      strcpy(mode, getparam("mode"));
    show_attachments = FALSE;
    }
  else
    {
    strcpy(mode, getparam("mode"));
    if (mode[0] == 0)
      strcpy(mode, "Full");

    show_attachments = (*getparam("attach") > 0);
    }

  threaded = equal_ustring(mode, "threaded");
  only_message_heads = threaded;

  /*---- convert dates to ltime ----*/

  time(&now);
  ptms = localtime(&now);
  current_year  = ptms->tm_year+1900;
  current_month = ptms->tm_mon+1;
  current_day   = ptms->tm_mday;

  ltime_end = ltime_start = 0;

  if (!past_n && !last_n)
    {
    if (*getparam("m1") || *getparam("y1") || *getparam("d1"))
      {
      /* if year not given, use current year */
      if (!*getparam("y1"))
        y1 = current_year;
      else
        y1 = atoi(getparam("y1"));
      if (y1 < 1990 || y1 > current_year)
        {
        rsprintf("</table>\r\n");
        rsprintf("<h1>Error: year %s out of range</h1>", getparam("y1"));
        rsprintf("</body></html>\r\n");
        return;
        }

      /* if month not given, use current month */
      if (*getparam("m1"))
        {
        strcpy(str, getparam("m1"));
        for (m1=0 ; m1<12 ; m1++)
          if (equal_ustring(str, mname[m1]))
            break;
        if (m1 == 12)
          m1 = 0;
        m1++;
        }
      else
        m1 = current_month;

      /* if day not given, use 1 */
      if (*getparam("d1"))
        d1 = atoi(getparam("d1"));
      else
        d1 = 1;

      memset(&tms, 0, sizeof(struct tm));
      tms.tm_year = y1 % 100;
      tms.tm_mon  = m1-1;
      tms.tm_mday = d1;
      tms.tm_hour = 0;

      if (tms.tm_year < 90)
        tms.tm_year += 100;
      ltime_start = mktime(&tms);
      }

    if (*getparam("m2") || *getparam("y2") || *getparam("d2"))
      {
      /* if year not give, use current year */
      if (*getparam("y2"))
        y2 = atoi(getparam("y2"));
      else
        y2 = current_year;

      if (y2 < 1990 || y2 > current_year)
        {
        rsprintf("</table>\r\n");
        rsprintf("<h1>Error: year %d out of range</h1>", y2);
        rsprintf("</body></html>\r\n");
        return;
        }

      /* if month not given, use current month */
      if (*getparam("m2"))
        {
        strcpy(str, getparam("m2"));
        for (m2=0 ; m2<12 ; m2++)
          if (equal_ustring(str, mname[m2]))
            break;
        if (m2 == 12)
          m2 = 0;
        m2++;
        }
      else
        m2 = current_month;

      /* if day not given, use last day of month */
      if (*getparam("d2"))
        d2 = atoi(getparam("d2"));
      else
        {
        memset(&tms, 0, sizeof(struct tm));
        tms.tm_year = y2 % 100;
        tms.tm_mon  = m2-1+1;
        tms.tm_mday = 1;
        tms.tm_hour = 12;

        if (tms.tm_year < 90)
          tms.tm_year += 100;
        ltime = mktime(&tms);
        ltime -= 3600*24;
        memcpy(&tms, localtime(&ltime), sizeof(struct tm));
        d2 = tms.tm_mday;
        }

      memset(&tms, 0, sizeof(struct tm));
      tms.tm_year = y2 % 100;
      tms.tm_mon  = m2-1;
      tms.tm_mday = d2;
      tms.tm_hour = 0;
      tms.tm_min  = 0;
      tms.tm_sec  = 0;

      if (tms.tm_year < 90)
        tms.tm_year += 100;
      ltime_end = mktime(&tms);

      /* end time is first second of next day */
      ltime_end += 3600*24;

      memcpy(&tms, localtime(&ltime_end), sizeof(struct tm));
      y2 = tms.tm_year + 1900;
      m2 = tms.tm_mon +1;
      d2 = tms.tm_mday;
      }
    }

  if (ltime_start && ltime_end && ltime_start > ltime_end)
    {
    rsprintf("</table>\r\n");
    rsprintf("<h1>Error: start time after end time</h1>", y2);
    rsprintf("</body></html>\r\n");
    return;
    }

  /*---- assemble message list ----*/

  /* check for search all */
  search_all = atoi(getparam("all"));

  if (getcfg(lbs->name, "Search all logbooks", str) && atoi(str) == 0)
    search_all = 0;

  n_msg = 0;
  if (search_all)
    {
    /* count logbooks */
    for (n_logbook=0 ;  ; n_logbook++)
      {
      if (!lb_list[n_logbook].name[0])
        break;
      n_msg += *lb_list[n_logbook].n_el_index;
      }
    }
  else
    {
    n_logbook = 1;
    n_msg = *lbs->n_el_index;
    }

  msg_list = malloc(sizeof(MSG_LIST)*n_msg);

  for (i=n=0 ; i<n_logbook ; i++)
    {
    if (search_all)
      lbs = &lb_list[i];

    for (j=0 ; j<*lbs->n_el_index ; j++)
      {
      msg_list[n].lbs = lbs;
      msg_list[n].index = j;
      sprintf(msg_list[n].string, "%d", lbs->el_index[j].file_time);
      n++;
      }
    }

  /*---- apply start/end date cut ----*/

  if (past_n)
    ltime_start = now-3600*24*past_n;

  if (last_n && last_n < n_msg)
    {
    for (i=n_msg-last_n-1 ; i>=0 ; i--)
      msg_list[i].lbs = NULL;
    }
  
  if (ltime_start)
    {
    for (i=0 ; i<n_msg ; i++)
      if (msg_list[i].lbs &&
          msg_list[i].lbs->el_index[msg_list[i].index].file_time < ltime_start)
        msg_list[i].lbs = NULL;
    }

  if (ltime_end)
    {
    for (i=0 ; i<n_msg ; i++)
      if (msg_list[i].lbs &&
          msg_list[i].lbs->el_index[msg_list[i].index].file_time > ltime_end)
        msg_list[i].lbs = NULL;
    }

  /*---- filter message list ----*/

  for (i=0 ; i<lbs->n_attr ; i++)
    if (*getparam(attr_list[i]))
      break;

  /* do filtering */
  for (index=0 ; index<n_msg ; index++)
    {
    if (!msg_list[index].lbs)
      continue;

    /* retrieve message */
    size = sizeof(text);
    message_id = msg_list[index].lbs->el_index[msg_list[index].index].message_id;

    status = el_retrieve(msg_list[index].lbs, message_id, 
                         date, attr_list, attrib, lbs->n_attr,
                         text, &size, in_reply_to, reply_to,
                         attachment,
                         encoding);
    if (status != EL_SUCCESS)
      break;

    for (i=0 ; i<lbs->n_attr ; i++)
      {
      if (*getparam(attr_list[i]))
        {
        only_message_heads = FALSE;
        strcpy(str, getparam(attr_list[i]));
        for (j=0 ; j<(int)strlen(str) ; j++)
          str[j] = toupper(str[j]);
        str[j] = 0;
        for (j=0 ; j<(int)strlen(attrib[i]) ; j++)
          text1[j] = toupper(attrib[i][j]);
        text1[j] = 0;

        if (strstr(text1, str) == NULL)
          break;
        }
      }
    if (i < lbs->n_attr)
      {
      msg_list[index].lbs = NULL;
      continue;
      }

    if (*getparam("subtext"))
      {
      only_message_heads = FALSE;
      strcpy(str, getparam("subtext"));
      for (i=0 ; i<(int)strlen(str) ; i++)
        str[i] = toupper(str[i]);
      str[i] = 0;
      for (i=0 ; i<(int)strlen(text) ; i++)
        text1[i] = toupper(text[i]);
      text1[i] = 0;

      if (strstr(text1, str) == NULL)
        {
        msg_list[index].lbs = NULL;
        continue;
        }
      }

    /* check if reply */
    if (only_message_heads && in_reply_to[0])
      {
      msg_list[index].lbs = NULL;
      continue;
      }

    /* add attribute for sorting */
    for (i=0 ; i<lbs->n_attr ; i++)
      {
      if (equal_ustring(getparam("sort"), attr_list[i]) ||
          equal_ustring(getparam("rsort"), attr_list[i]))
        {
        strncpy(msg_list[index].string, attrib[i], 255);
        msg_list[index].string[255] = 0;
        }

      if (equal_ustring(getparam("sort"), "#") ||
          equal_ustring(getparam("rsort"), "#"))
        {
        sprintf(msg_list[index].string, "%08d", message_id);
        }
      }

    if (isparam("rsort"))
      reverse = 1;

    if (isparam("sort"))
      reverse = 0;
    }

  /*---- compact messasges ----*/

  for (i=j=0 ; i<n_msg ; i++)
    if (msg_list[i].lbs)
      memcpy(&msg_list[j++], &msg_list[i], sizeof(MSG_LIST));
  n_msg = j;

  /*---- sort messasges ----*/

  qsort(msg_list, n_msg, sizeof(MSG_LIST), reverse ? msg_compare_reverse : msg_compare);

  /*---- number of messages per page ----*/

  n_page = 1000000;
  i_start = 0;
  i_stop = n_msg-1;
  if (page_n)
    {
    if (getcfg(lbs->name, "Entries per page", str))
      n_page = atoi(str);
    else
      n_page = 20;
    if (isparam("npp"))
      n_page = atoi(getparam("npp"));

    if (page_n != -1)
      {
      i_start = (page_n - 1) * n_page;
      i_stop  = i_start + n_page - 1;

      if (i_start >= n_msg)
        {
        show_error("Page doesn't exist");
        free(msg_list);
        return;
        }

      if (i_stop >= n_msg)
        i_stop = n_msg-1;
      }
    }
  
  /*---- header ----*/

  show_standard_header(loc("ELOG search result"), NULL);

  /*---- title ----*/

  strcpy(str, ", ");
  if (past_n == 1)
    strcat(str, loc("Last day"));
  else if (past_n > 1)
    sprintf(str+strlen(str), loc("Last %d days"), past_n);
  else if (last_n)
    sprintf(str+strlen(str), loc("Last %d entries"), last_n);
  else if (page_n == -1)
    sprintf(str+strlen(str), loc("all entries"));
  else if (page_n)
    sprintf(str+strlen(str), loc("Page %d of %d"), page_n, n_msg/n_page+1);
  if (strlen(str) == 2)
    str[0] = 0;

  if (printable)
    show_standard_title(lbs->name, str, 1);
  else
    show_standard_title(lbs->name, str, 0);

  /*---- menu buttons ----*/

  if (!printable)
    {
    rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
             gt("Menu1 cellpadding"), gt("Frame color"));

    rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

    if (getcfg(lbs->name, "Find menu commands", menu_str))
      {
      n = strbreak(menu_str, menu_item, MAX_N_LIST);

      if (atoi(gt("Use buttons")) == 1)
        {
        for (i=0 ; i<n ; i++)
          {
          if (equal_ustring(menu_item[i], "Last x"))
            {
            rsprintf("<input type=hidden name=mode value=\"%s\">\n", mode);

            if (past_n)
              {
              sprintf(str, loc("Last %d days"), past_n*2);
              rsprintf("<input type=submit name=past value=\"%s\">\n", str);
              }

            if (last_n)
              {
              sprintf(str, loc("Last %d entries"), last_n*2);
              rsprintf("<input type=submit name=last value=\"%s\">\n", str);
              }

            }
          else
            rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc(menu_item[i]));
          }
        }
      else
        {
        rsprintf("<small>\n");

        for (i=0 ; i<n ; i++)
          {
          if (equal_ustring(menu_item[i], "Last x"))
            {
            if (past_n)
              {
              sprintf(str, loc("Last %d days"), past_n*2);
              rsprintf("&nbsp;<a href=\"past%d?mode=%s\">%s</a>&nbsp;|\n", past_n*2, mode, str);
              }

            if (last_n)
              {
              sprintf(str, loc("Last %d entries"), last_n*2);
              rsprintf("&nbsp;<a href=\"last%d?mode=%s\">%s</a>&nbsp;|\n", last_n*2, mode, str);
              }
            }
          else
            {
            strcpy(str, loc(menu_item[i]));
            url_encode(str);

            if (i < n-1)
              rsprintf("&nbsp;<a href=\"?cmd=%s\">%s</a>&nbsp;|\n", str, loc(menu_item[i]));
            else
              rsprintf("&nbsp;<a href=\"?cmd=%s\">%s</a>&nbsp;\n", str, loc(menu_item[i]));
            }
          }

        rsprintf("</small>\n");
        }
      }
    else
      {
      if (atoi(gt("Use buttons")) == 1)
        {
        rsprintf("<input type=hidden name=mode value=\"%s\">\n", mode);

        if (past_n)
          {
          sprintf(str, loc("Last %d days"), past_n*2);
          rsprintf("<input type=submit name=past value=\"%s\">\n", str);
          }

        if (last_n)
          {
          sprintf(str, loc("Last %d entries"), last_n*2);
          rsprintf("<input type=submit name=last value=\"%s\">\n", str);
          }

        rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Find"));
        rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Back"));
        }
      else
        {
        rsprintf("<small>\n");

        if (past_n)
          {
          sprintf(str, loc("Last %d days"), past_n*2);
          rsprintf("&nbsp;<a href=\"past%d?mode=%s\">%s</a>&nbsp;|\n", past_n*2, mode, str);
          }

        if (last_n)
          {
          sprintf(str, loc("Last %d entries"), last_n*2);
          rsprintf("&nbsp;<a href=\"last%d?mode=%s\">%s</a>&nbsp;|\n", last_n*2, mode, str);
          }

        rsprintf("&nbsp;<a href=\"?cmd=%s\">%s</a>&nbsp;|\n", loc("Find"), loc("Find"));
        rsprintf("&nbsp;<a href=\"?cmd=%s\">%s</a>&nbsp;\n", loc("Back"), loc("Back"));

        rsprintf("</small>\n");
        }

      }

    rsprintf("</td></tr></table></td></tr>\n\n");
    }


  /*---- display filters ----*/

  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1>\n",
            printable ? "1" : gt("Border width"), gt("Categories cellpadding"));

  if (*getparam("m1") || *getparam("y1") || *getparam("d1"))
    rsprintf("<tr><td nowrap width=10%% bgcolor=%s><b>%s:</b></td><td bgcolor=%s>%s %d, %d</td></tr>",
              gt("Categories bgcolor1"), loc("Start date"), gt("Categories bgcolor2"), mname[m1-1], d1, y1);

  if (*getparam("m2") || *getparam("y2") || *getparam("d2"))
    {
    /* calculate previous day */
    memset(&tms, 0, sizeof(struct tm));
    tms.tm_year = y2 % 100;
    tms.tm_mon  = m2-1;
    tms.tm_mday = d2;
    tms.tm_hour = 12;

    if (tms.tm_year < 90)
      tms.tm_year += 100;
    ltime = mktime(&tms);
    ltime -= 3600*24;
    memcpy(&tms, localtime(&ltime), sizeof(struct tm));

    rsprintf("<tr><td nowrap width=10%% bgcolor=%s><b>%s:</b></td><td bgcolor=%s>%s %d, %d</td></tr>",
              gt("Categories bgcolor1"), loc("End date"), gt("Categories bgcolor2"),
              mname[tms.tm_mon], tms.tm_mday, tms.tm_year + 1900);
    }

  for (i=0 ; i<lbs->n_attr ; i++)
    {
    if (*getparam(attr_list[i]))
      rsprintf("<tr><td nowrap width=10%% bgcolor=%s><b>%s:</b></td><td bgcolor=%s>%s</td></tr>",
                gt("Categories bgcolor1"), attr_list[i], gt("Categories bgcolor2"), getparam(attr_list[i]));
    }

  if (*getparam("subtext"))
    {
    rsprintf("<tr><td nowrap width=10%% bgcolor=%s><b>%s:</b></td>", gt("Categories bgcolor1"), loc("Text"));
    rsprintf("<td bgcolor=%s><B style=\"color:black;background-color:#ffff66\">%s</B></td></tr>",
              gt("Categories bgcolor2"), getparam("subtext"));
    }

  rsprintf("</td></tr></table></td></tr>\n\n");

  /* get number of summary lines */
  n_line = 3;
  if (getcfg(lbs->name, "Summary lines", str))
    n_line = atoi(str);

  /*---- page navigation ----*/

  if (!printable && page_n && n_msg > n_page)
    show_page_navigation(n_msg, page_n, n_page);

  /*---- table titles ----*/

  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           printable ? "1" : gt("Border width"), gt("Categories cellpadding"), gt("Frame color"));

  strcpy(col, gt("Categories bgcolor1"));

  size = printable ? 2 : 3;

  if (getcfg(lbs->name, "Display search", list))
    n_attr_disp = strbreak(list, disp_attr, MAX_N_ATTR);
  else
    {
    if (search_all)
      {
      n_attr_disp = lbs->n_attr + 3;

      strcpy(disp_attr[0], "#");
      strcpy(disp_attr[1], "Logbook");
      strcpy(disp_attr[2], "Date");
      memcpy(disp_attr+3, attr_list, sizeof(attr_list));
      }
    else
      {
      n_attr_disp = lbs->n_attr + 2;

      strcpy(disp_attr[0], "#");
      strcpy(disp_attr[1], "Date");
      memcpy(disp_attr+2, attr_list, sizeof(attr_list));
      }
    }

  if (threaded)
    {
    }
  else
    {
    rsprintf("<tr>\n");

    for (i=0 ; i<n_attr_disp ; i++)
      {
      /* assemble current command line, replace sort statements */
      strcpy(ref, getparam("cmdline"));
      if (strstr(ref, "&sort="))
        {
        p = strstr(ref, "&sort=")+1;
        while (*p && *p != '&')
          p++;
        strcpy(strstr(ref, "&sort="), p);
        }
      if (strstr(ref, "&rsort="))
        {
        p = strstr(ref, "&rsort=")+1;
        while (*p && *p != '&')
          p++;
        strcpy(strstr(ref, "&rsort="), p);
        }

      strcpy(str, disp_attr[i]);
      url_encode(str);
      if (strcmp(getparam("sort"), disp_attr[i]) == 0)
        sprintf(ref+strlen(ref), "&rsort=%s", str);
      else
        sprintf(ref+strlen(ref), "&sort=%s", str);
      
      img[0] = 0;
      if (strcmp(getparam("sort"), disp_attr[i]) == 0)
        strcpy(img, "<img align=top src=\"down.gif\">");
      else if (strcmp(getparam("rsort"), disp_attr[i]) == 0)
        strcpy(img, "<img align=top src=\"up.gif\">");

      rsprintf("<td align=center bgcolor=%s><font size=%d face=verdana,arial,helvetica,sans-serif><b><a href=\"%s\">%s</a></b>%s</td>\n",
               col, size, ref, disp_attr[i], img);
      }

    if (!equal_ustring(mode, "Full") && n_line > 0)
      rsprintf("<td align=center bgcolor=%s><font size=%d face=verdana,arial,helvetica,sans-serif><b>Text</b></td>\n",
               col, size);

    rsprintf("</tr>\n\n");
    }

  /*---- display message list ----*/

  for (index=i_start ; index<=i_stop ; index++)
    {
    size = sizeof(text);
    message_id = msg_list[index].lbs->el_index[msg_list[index].index].message_id;

    status = el_retrieve(msg_list[index].lbs, message_id,
                         date, attr_list, attrib, lbs->n_attr,
                         text, &size, in_reply_to, reply_to,
                         attachment,
                         encoding);
    if (status != EL_SUCCESS)
      break;

    /*---- add highlighting for searched subtext ----*/

    if (*getparam("subtext"))
      {
      strcpy(str, getparam("subtext"));
      for (i=0 ; i<(int)strlen(str) ; i++)
        str[i] = toupper(str[i]);

      for (i=0 ; i<(int)strlen(text) ; i++)
        text1[i] = toupper(text[i]);
      text1[i] = 0;

      text2[0] = 0;
      pt = text;   /* original text */
      pt1 = text1; /* upper-case text */
      pt2 = text2; /* text with inserted coloring */
      do
        {
        p = strstr(pt1, str);
        size = (int)(p - pt1);
        if (p != NULL)
          {
          pt1 = p+strlen(str);

          /* copy first part original text */
          memcpy(pt2, pt, size);
          pt2 += size;
          pt += size;

          /* add coloring 1st part */

          /* here: \001='<', \002='>', /003='"', and \004=' ' */
          /* see also rsputs2(char* ) */

          if (equal_ustring(encoding, "plain") || !equal_ustring(mode, "Full"))
            strcpy(pt2, "\001B\004style=\003color:black;background-color:#ffff66\003\002");
          else
            strcpy(pt2, "<B style=\"color:black;background-color:#ffff66\">");

          pt2 += strlen(pt2);

          /* copy origial search text */
          memcpy(pt2, pt, strlen(str));
          pt2 += strlen(str);
          pt += strlen(str);

          /* add coloring 2nd part */
          if (equal_ustring(encoding, "plain") || !equal_ustring(mode, "Full"))
            strcpy(pt2, "\001/B\002");
          else
            strcpy(pt2, "</B>");
          pt2 += strlen(pt2);
          }
        } while (p != NULL);

      strcpy(pt2, pt);
      strcpy(text, text2);
      }

    /*---- display line ----*/

    display_line(msg_list[index].lbs, message_id, 
                 index, mode, 0, printable, n_line,
                 show_attachments, date, reply_to, n_attr_disp, disp_attr,
                 attrib, lbs->n_attr, text, attachment, encoding);

    if (threaded)
      {
      if (reply_to[0] && (!getcfg(msg_list[index].lbs->name, "Top level only", str) || atoi(str) == 0))
        {
        p = reply_to;
        do
          {
          display_reply(msg_list[index].lbs, atoi(p), printable, n_attr_disp, disp_attr, 1);

          while (*p && isdigit(*p))
            p++;
          while (*p && (*p == ',' || *p == ' '))
            p++;
          } while(*p);
        }
      }
    }

  rsprintf("</table></td></tr>\n");

  if (n_msg == 0)
    {
    rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           printable ? "1" : gt("Border width"), gt("Categories cellpadding"), gt("Frame color"));

    rsprintf("<tr><td bgcolor=#FFB0B0 align=center><b>%s<b></td></tr>", loc("No entries found"));

    rsprintf("</td></tr></table>\n");
    }

  /*---- page navigation ----*/

  if (!printable && page_n && n_msg > n_page)
    show_page_navigation(n_msg, page_n, n_page);

  
  rsprintf("</table>\n");

  /*---- bottom text ----*/
  
  if (getcfg(lbs->name, "bottom text", str))
    {
    FILE *f;
    char file_name[256], *buf;

    strcpy(file_name, cfg_dir);
    strcat(file_name, str);

    f = fopen(file_name, "r");
    if (f != NULL)
      {
      fseek(f, 0, SEEK_END);
      size = TELL(fileno(f));
      fseek(f, 0, SEEK_SET);

      buf = malloc(size+1);
      fread(buf, 1, size, f);
      buf[size] = 0;
      fclose(f);

      rsputs(buf);
      }
    }
  else
    /* add little logo */
    rsprintf("<center><font size=1 color=#A0A0A0><a href=\"http://midas.psi.ch/elog/\">ELOG V%s</a></font></center>", VERSION);

  rsprintf("</body></html>\r\n");

  free(msg_list);
}

/*------------------------------------------------------------------*/

int compose_mail(LOGBOOK *lbs, char *mail_to, int message_id, char attrib[MAX_N_ATTR][NAME_LENGTH], 
                 char *mail_param, int *n_mail)
{
int    j;
char   str[256], mail_from[256], mail_text[TEXT_SIZE+1000], smtp_host[256], subject[256];
char   slist[MAX_N_ATTR+10][NAME_LENGTH], svalue[MAX_N_ATTR+10][NAME_LENGTH];

  if (!getcfg("global", "SMTP host", smtp_host))
    {
    show_error(loc("No SMTP host defined in [global] section of configuration file"));
    return 0;
    }

  if (getcfg(lbs->name, "Use Email from", mail_from))
    {
    j = build_subst_list(lbs, slist, svalue, attrib);
    strsubst(mail_from, slist, svalue, j);
    }
  else
    sprintf(mail_from, "ELog@%s", host_name);

  sprintf(mail_text, loc("A new entry has been submitted on %s"), host_name);
  sprintf(mail_text+strlen(mail_text), "\r\n\r\n");

  sprintf(mail_text+strlen(mail_text), "%s             : %s\r\n", loc("Logbook"), lbs->name);

  for (j=0 ; j<lbs->n_attr ; j++)
    {
    strcpy(str, "                                    ");
    memcpy(str, attr_list[j], strlen(attr_list[j]));
    sprintf(str+20, ": %s\r\n", attrib[j]);

    strcpy(mail_text+strlen(mail_text), str);
    }

  /* compose subject from attributes */
  if (getcfg(lbs->name, "Use Email Subject", subject))
    {
    j = build_subst_list(lbs, slist, svalue, attrib);
    strsubst(subject, slist, svalue, j);
    }
  else
    strcpy(subject, "New ELOG entry");

  /* try to get URL from referer */

  if (!getcfg("global", "URL", str))
    {
    if (referer[0])
      strcpy(str, referer);
    else
      {
      if (tcp_port == 80)
        sprintf(str, "http://%s/", host_name);
      else
        sprintf(str, "http://%s:%d/", host_name, tcp_port);
      }
    }
  else
    {
    strcat(str, lbs->name);
    strcat(str, "/");
    }

  sprintf(mail_text+strlen(mail_text), "\r\n%s URL         : %s%d\r\n",
          loc("Logbook"), str, message_id);

  if (getcfg(lbs->name, "Email message body", str) &&
      atoi(str) == 1)
    {
    sprintf(mail_text+strlen(mail_text), "\r\n=================================\r\n\r\n%s",
      getparam("text"));
    }

  sendmail(smtp_host, mail_from, mail_to, subject, mail_text);

  if (!getcfg(lbs->name, "Display email recipients", str) ||
       atoi(str) == 1)
    {
    if (mail_param[0] == 0)
      strcpy(mail_param, "?");
    else
      strcat(mail_param, "&");
    sprintf(mail_param+strlen(mail_param), "mail%d=%s", (*n_mail)++, mail_to);
    }

  return 1;
}

/*------------------------------------------------------------------*/

void submit_elog(LOGBOOK *lbs)
{
char   str[256], file_name[256], error[1000], date[80],
       mail_list[MAX_N_LIST][NAME_LENGTH], list[10000],
       attrib[MAX_N_ATTR][NAME_LENGTH], subst_str[256], in_reply_to[80],
       reply_to[256], user[256], user_email[256], email_notify[256];
char   *buffer[MAX_ATTACHMENTS], mail_param[1000];
char   att_file[MAX_ATTACHMENTS][256];
char   slist[MAX_N_ATTR+10][NAME_LENGTH], svalue[MAX_N_ATTR+10][NAME_LENGTH];
int    i, j, n, missing, first, index, n_mail, suppress, message_id;

  /* check for required attributs */
  missing = 0;
  for (i=0 ; i<lbs->n_attr ; i++)
    if (attr_flags[i] & AF_REQUIRED)
      {
      if ((attr_flags[i] & AF_MULTI) == 0 && *getparam(attr_list[i]) == 0)
        {
        missing = 1;
        break;
        }
      if ((attr_flags[i] & AF_MULTI))
        {
        for (j=0 ; j<MAX_N_LIST ; j++)
          {
          sprintf(str, "%s%d", attr_list[i], j);
          if (getparam(str) && *getparam(str))
            break;
          }

        if (j == MAX_N_LIST)
          {
          missing = 1;
          break;
          }
        }
      }

  if (missing)
    {
    sprintf(error, "<i>");
    sprintf(error+strlen(error), loc("Error: Attribute <b>%s</b> not supplied"), attr_list[i]);
    sprintf(error+strlen(error), ".</i><p>\n");
    sprintf(error+strlen(error), loc("Please go back and enter the <b>%s</b> field"), attr_list[i]);
    strcat(error, ".\n");

    show_error(error);
    return;
    }

  /* check for valid attachment files */
  for (i=0 ; i<MAX_ATTACHMENTS ; i++)
    {
    buffer[i] = NULL;
    sprintf(str, "attachment%d", i);
    strcpy(att_file[i], getparam(str));
    if (att_file[i][0] && _attachment_size[i] == 0 && !equal_ustring(att_file[i], loc("<delete>")))
      {
      sprintf(error, loc("Error: Attachment file <i>%s</i> invalid, please bo back and enter a proper file name"), getparam(str));
      show_error(error);
      return;
      }
    }

  /* compile substitution list */
  n = build_subst_list(lbs, slist, svalue, NULL);

  /* retrieve attributes */
  for (i=0 ; i<lbs->n_attr ; i++)
    {
    if (attr_flags[i] & AF_MULTI)
      {
      attrib[i][0] = 0;
      first = 1;
      for (j=0 ; j<MAX_N_LIST ; j++)
        {
        sprintf(str, "%s%d", attr_list[i], j);
        if (getparam(str))
          {
          if (*getparam(str))
            {
            if (first)
              first = 0;
            else
              strcat(attrib[i], " | ");
            if (strlen(attrib[i]) + strlen(getparam(str)) < NAME_LENGTH-2)
              strcat(attrib[i], getparam(str));
            else
              break;
            }
          }
        else
          break;
        }
      }
    else
      {
      strncpy(attrib[i], getparam(attr_list[i]), NAME_LENGTH);
      attrib[i][NAME_LENGTH-1] = 0;
      }

    if (!*getparam("edit"))
      {
      sprintf(str, "Subst %s", attr_list[i]);
      if (getcfg(lbs->name, str, subst_str))
        {
        strsubst(subst_str, slist, svalue, n);
        strcpy(attrib[i], subst_str);
        }
      }
    }

  message_id = 0;
  reply_to[0] = 0;
  in_reply_to[0] = 0;
  date[0] = 0;

  if (*getparam("edit") &&
      *getparam("resubmit") &&
      atoi(getparam("resubmit")) == 1)
    {
    /* delete old message */
    el_delete_message(lbs, atoi(getparam("orig")), FALSE, att_file, TRUE);
    unsetparam("orig");
    strcpy(reply_to, "");
    strcpy(in_reply_to, "");
    date[0] = 0;
    }
  else
    {
    if (*getparam("edit"))
      {
      message_id = atoi(getparam("orig"));
      strcpy(in_reply_to, "<keep>");
      strcpy(reply_to, "<keep>");
      strcpy(date, "<keep>");
      }
    else
      strcpy(in_reply_to, getparam("orig"));
    }

  message_id = el_submit(lbs, message_id, date, attr_list, attrib, lbs->n_attr, getparam("text"),
                     in_reply_to, reply_to, *getparam("html") ? "HTML" : "plain",
                     att_file,
                     _attachment_buffer,
                     _attachment_size);

  if (message_id <= 0)
    {
    sprintf(str, loc("New message cannot be written to directory \"%s\""), lbs->data_dir);
    strcat(str, "\n<p>");
    strcat(str, loc("Please check that it exists and elogd has write access"));
    show_error(str);
    return;
    }

  /*---- email notifications ----*/

  suppress = atoi(getparam("suppress"));

  /* check for mail submissions */
  mail_param[0] = 0;
  n_mail = 0;

  if (suppress)
    {
    strcpy(mail_param, "?suppress=1");
    }
  else
    {
    if (!(*getparam("edit") && getcfg(lbs->name, "Suppress Email on edit", str) && atoi(str) == 1))
      {
      /* go throuch "Email xxx" in configuration file */
      for (index=0 ; index <= lbs->n_attr ; index++)
        {
        if (index < lbs->n_attr)
          {
          strcpy(str, "Email ");
          if (strchr(attr_list[index], ' '))
            sprintf(str+strlen(str), "\"%s\"", attr_list[index]);
          else
            strcat(str, attr_list[index]);
          strcat(str, " ");

          if (strchr(getparam(attr_list[index]), ' '))
            sprintf(str+strlen(str), "\"%s\"", getparam(attr_list[index]));
          else
            strcat(str, getparam(attr_list[index]));
          }
        else
          sprintf(str, "Email ALL");

        if (getcfg(lbs->name, str, list))
          {
          n = strbreak(list, mail_list, MAX_N_LIST);

          if (verbose)
            printf("\n%s to %s\n\n", str, list);

          for (i=0 ; i<n ; i++)
            if (!compose_mail(lbs, mail_list[i], message_id, attrib, mail_param, &n_mail))
              return;
          }
        }

      /* go through password file */
      for (index=0 ; ; index++)
        {
        if (!enum_user_line(lbs, index, user))
          break;

        get_user_line(lbs, user, NULL, NULL, user_email, email_notify);

        if (email_notify[0])
          if (!compose_mail(lbs, user_email, message_id, attrib, mail_param, &n_mail))
            return;
        }
      }
    }

  for (i=0 ; i<MAX_ATTACHMENTS ; i++)
    if (buffer[i])
      free(buffer[i]);

  if (getcfg(lbs->name, "Submit page", str))
    {
    strcpy(file_name, cfg_dir);
    strcat(file_name, str);
    send_file(file_name);
    return;
    }

  rsprintf("HTTP/1.1 302 Found\r\n");
  rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
  if (use_keepalive)
    {
    rsprintf("Connection: Keep-Alive\r\n");
    rsprintf("Keep-Alive: timeout=60, max=10\r\n");
    }

  /* bug for Konqueror */
  if (strstr(browser, "Konqueror"))
    rsprintf("Location: %s/%d%s\r\n\r\n<html>redir</html>\r\n",
              lbs->name_enc, message_id, mail_param);
  else
    rsprintf("Location: %d%s\r\n\r\n<html>redir</html>\r\n",
              message_id, mail_param);
}

/*------------------------------------------------------------------*/

void copy_to(LOGBOOK *lbs, int src_id, char *dest_logbook, int move)
{
int     size, i, status, fh, message_id;
char    str[256], file_name[256], attrib[MAX_N_ATTR][NAME_LENGTH];
char    date[80], text[TEXT_SIZE], msg_str[32], in_reply_to[80], reply_to[256],
        attachment[MAX_ATTACHMENTS][256], encoding[80];
LOGBOOK *lbs_dest;

  for (i=0 ; lb_list[i].name[0] ; i++)
    if (equal_ustring(lb_list[i].name, dest_logbook))
      break;
  if (!lb_list[i].name[0])
    return;
  lbs_dest = &lb_list[i];

  /* get message */
  size = sizeof(text);
  status = el_retrieve(lbs, src_id, date, attr_list, attrib, lbs->n_attr,
                       text, &size, in_reply_to, reply_to,
                       attachment, encoding);

  if (status != EL_SUCCESS)
    {
    sprintf(msg_str, "%d", src_id);
    sprintf(str, loc("Message %s cannot be read from logbook \"%s\""), msg_str, lbs->name);
    show_error(str);
    return;
    }

  /* read attachments */
  for (i=0 ; i<MAX_ATTACHMENTS ; i++)
    if (attachment[i][0])
      {
      strcpy(file_name, lbs->data_dir);
      strcat(file_name, attachment[i]);

      fh = open(file_name, O_RDONLY | O_BINARY);
      if (fh > 0)
        {
        lseek(fh, 0, SEEK_END);
        _attachment_size[i] = TELL(fh);
        lseek(fh, 0, SEEK_SET);

        _attachment_buffer[i] = malloc(_attachment_size[i]);

        if (_attachment_buffer[i])
          read(fh, _attachment_buffer[i], _attachment_size[i]);

        close(fh);
        }

      /* stip date/time from file name */
      strcpy(str, attachment[i]);
      strcpy(attachment[i], str+14);
      }

  /* submit in destination logbook without links */

  message_id = el_submit(lbs_dest, 0, date, attr_list, attrib, lbs_dest->n_attr, text,
                     "", "", encoding,
                     attachment,
                     _attachment_buffer,
                     _attachment_size);

  for (i=0 ; i<MAX_ATTACHMENTS ; i++)
    if (attachment[i][0])
      free(_attachment_buffer[i]);

  if (message_id <= 0)
    {
    sprintf(str, loc("New message cannot be written to directory \"%s\""), lbs_dest->data_dir);
    strcat(str, "\n<p>");
    strcat(str, loc("Please check that it exists and elogd has write access"));
    show_error(str);
    return;
    }

  /* delete original message for move */
  if (move)
    {
    el_delete_message(lbs, src_id, TRUE, NULL, TRUE);

    /* check if this was the last message */
    src_id = el_search_message(lbs, EL_NEXT, src_id, FALSE);

    /* if yes, force display of new last message */
    if (src_id <= 0)
      src_id = el_search_message(lbs, EL_LAST, 0, FALSE);
    }

  /* display status message */
  sprintf(str, "%d", src_id);
  show_standard_header(loc("Copy ELog entry"), str);

  rsprintf("<p><p><p><table border=%s width=50%% bgcolor=%s cellpadding=1 cellspacing=0 align=center>",
            gt("Border width"), gt("Frame color"));
  rsprintf("<tr><td><table cellpadding=5 cellspacing=0 border=0 width=100%% bgcolor=%s>\n", gt("Frame color"));

  rsprintf("<tr><td bgcolor=#80FF80 align=center><b>");
  if (move)
    rsprintf(loc("Message moved successfully from \"%s\" to \"%s\""), lbs->name, lbs_dest->name);
  else
    rsprintf(loc("Message copied successfully from \"%s\" to \"%s\""), lbs->name, lbs_dest->name);

  rsprintf("</b></tr>\n");
  rsprintf("<tr><td bgcolor=%s align=center>%s <a href=\"../%s/%d\">%s</td></tr>\n",
            gt("Cell BGColor"), loc("Go to"), lbs->name, src_id, lbs->name);
  rsprintf("<tr><td bgcolor=%s align=center>%s <a href=\"../%s/\">%s</td></tr>\n",
            gt("Cell BGColor"), loc("Go to"), lbs_dest->name, lbs_dest->name);

  rsprintf("</table></td></tr></table>\n");
  rsprintf("</body></html>\r\n");

  return;
}

/*------------------------------------------------------------------*/

void show_elog_page(LOGBOOK *lbs, char *dec_path)
{
int    size, i, j, len, n, status, fh, length, message_error, index;
int    message_id, orig_message_id;
char   str[256], command[80], ref[256], file_name[256], attrib[MAX_N_ATTR][NAME_LENGTH];
char   date[80], text[TEXT_SIZE], menu_str[1000], other_str[1000], cmd[256],
       orig_tag[80], reply_tag[80], attachment[MAX_ATTACHMENTS][256], encoding[80], att[256], lattr[256];
char   menu_item[MAX_N_LIST][NAME_LENGTH], format[80], admin_user[80],
       slist[MAX_N_ATTR+10][NAME_LENGTH], svalue[MAX_N_ATTR+10][NAME_LENGTH], *p;
FILE   *f;
BOOL   first;

  message_id = atoi(dec_path);

  if (getcfg(lbs->name, "Types", str))
    {
    show_upgrade_page(lbs);
    return;
    }

  message_error = EL_SUCCESS;

  /*---- interprete commands ---------------------------------------*/

  strcpy(command, getparam("cmd"));

  /* correct for image buttons */
  if (*getparam("cmd_first.x"))
    strcpy(command, loc("First"));
  if (*getparam("cmd_previous.x"))
    strcpy(command, loc("Previous"));
  if (*getparam("cmd_next.x"))
    strcpy(command, loc("Next"));
  if (*getparam("cmd_last.x"))
    strcpy(command, loc("Last"));

  /* check if command allowed for current user */
  if (!allow_user(lbs, command))
    return;

  /* check for guest access */
  if (!getcfg(lbs->name, "Guest Menu commands", menu_str) ||
      *getparam("unm") != 0)
    getcfg(lbs->name, "Menu commands", menu_str);

  /* default menu commands */
  if (menu_str[0] == 0)
    {
    strcpy(menu_str, loc("New"));
    strcat(menu_str, ", ");
    strcat(menu_str, loc("Edit"));
    strcat(menu_str, ", ");
    strcat(menu_str, loc("Delete"));
    strcat(menu_str, ", ");
    strcat(menu_str, loc("Reply"));
    strcat(menu_str, ", ");
    strcat(menu_str, loc("Find"));
    strcat(menu_str, ", ");
    strcat(menu_str, loc("Last day"));
    strcat(menu_str, ", ");
    strcat(menu_str, loc("Last 10"));
    strcat(menu_str, ", ");

    if (getcfg(lbs->name, "Password file", str))
      {
      if (getcfg(lbs->name, "Admin user", str) && 
          strstr(str, getparam("unm")) != 0)
        {
        strcat(menu_str, loc("Admin"));
        strcat(menu_str, ", ");
        }
      strcat(menu_str, loc("Config"));
      strcat(menu_str, ", ");
      strcat(menu_str, loc("Logout"));
      strcat(menu_str, ", ");
      }
    else
      {
      strcat(menu_str, loc("Config"));
      strcat(menu_str, ", ");
      }

    strcat(menu_str, loc("Help"));
    }
  else
    {
    /* localize menu commands */
    n = strbreak(menu_str, menu_item, MAX_N_LIST);
    menu_str[0] = 0;
    admin_user[0] = 0;
    getcfg(lbs->name, "Admin user", admin_user);
    for (i=0 ; i<n ; i++)
      {
      if (strcmp(menu_item[i], loc("Admin")) == 0)
        {
        if (strstr(admin_user, getparam("unm")) == NULL)
          continue;
        }
      strcat(menu_str, loc(menu_item[i]));
      if (i<n-1)
        strcat(menu_str, ", ");
      }
    }

  strcpy(other_str, loc("Submit"));
  strcat(other_str, " ");
  strcat(other_str, loc("Back"));
  strcat(other_str, " ");
  strcat(other_str, loc("Search"));
  strcat(other_str, " ");
  strcat(other_str, loc("Save"));
  strcat(other_str, " ");
  strcat(other_str, loc("Download"));
  strcat(other_str, " ");
  strcat(other_str, loc("Cancel"));
  strcat(other_str, " ");
  strcat(other_str, loc("First"));
  strcat(other_str, " ");
  strcat(other_str, loc("Last"));
  strcat(other_str, " ");
  strcat(other_str, loc("Previous"));
  strcat(other_str, " ");
  strcat(other_str, loc("Next"));

  /* add non-localized submit for elog utility */
  strcat(other_str, " ");
  strcat(other_str, "Submit");

  /* admin commands */
  if (getcfg(lbs->name, "Admin user", str) && 
      *getparam("unm") &&
      strstr(str, getparam("unm")) != 0)
    {
    strcat(other_str, loc("Remove user"));
    strcat(other_str, " ");
    strcat(other_str, loc("New user"));
    strcat(other_str, " ");
    }
  else
    if (getcfg(lbs->name, "Self register", str) &&
        atoi(str) == 1)
      {
      strcat(other_str, loc("Remove user"));
      strcat(other_str, " ");
      strcat(other_str, loc("New user"));
      strcat(other_str, " ");
      }

  /* allow change password if "config" possible */
  if (equal_ustring(command, loc("Change password")) &&
      strstr(menu_str, loc("Config")))
    {
    }
  /* check if command is present in the menu list */
  else if (command[0] && strstr(menu_str, command) == NULL &&
      strstr(other_str, command) == NULL)
    {
    sprintf(str, loc("Error: Command \"<b>%s</b>\" not allowed"), command);
    show_error(str);
    return;
    }

  if (equal_ustring(command, loc("Help")))
    {
    if (getcfg(lbs->name, "Help URL", str))
      {
      /* if file is given, add '/' to make absolute path */
      if (strchr(str, '/') == NULL)
        sprintf(ref, "/%s", str);
      else
        strcpy(ref, str);

      redirect(ref);
      return;
      }

    /* send local help file */
    strcpy(file_name, cfg_dir);
    strcat(file_name, "eloghelp_");

    if (getcfg("global", "Language", str))
      {
      str[2] = 0;
      strcat(file_name, str);
      }
    else
      strcat(file_name, "en");
    strcat(file_name, ".html");

    f = fopen(file_name, "r");
    if (f == NULL)
      redirect("http://midas.psi.ch/elog/eloghelp_en.html");
    else
      {
      fclose(f);
      send_file(file_name);
      }
    return;
    }

  if (equal_ustring(command, loc("New")))
    {
    show_elog_new(lbs, 0, FALSE);
    return;
    }

  if (equal_ustring(command, loc("Edit")))
    {
    if (message_id)
      {
      show_elog_new(lbs, message_id, TRUE);
      return;
      }
    }

  if (equal_ustring(command, loc("Reply")))
    {
    show_elog_new(lbs, message_id, FALSE);
    return;
    }

  if (equal_ustring(command, loc("Submit")) ||
      equal_ustring(command, "Submit"))
    {
    submit_elog(lbs);
    return;
    }

  if (equal_ustring(command, loc("Find")))
    {
    show_elog_find(lbs);
    return;
    }

  if (equal_ustring(command, loc("Search")))
    {
    if (dec_path[0] && atoi(dec_path) == 0 && strchr(dec_path, '/') != NULL)
      {
      sprintf(str, "Invalid URL: <b>%s</b>", dec_path);
      show_error(str);
      return;
      }

    show_elog_submit_find(lbs, 0, 0, 1);
    return;
    }

  if (equal_ustring(command, loc("Last day")))
    {
    redirect("past1");
    return;
    }

  if (equal_ustring(command, loc("Last 10")))
    {
    redirect("last10");
    return;
    }

  if (equal_ustring(command, loc("Copy to")))
    {
    copy_to(lbs, message_id, getparam("destc"), 0);
    return;
    }

  if (equal_ustring(command, loc("Move to")))
    {
    copy_to(lbs, message_id, getparam("destm"), 1);
    return;
    }

  if (equal_ustring(command, loc("Admin")))
    {
    show_admin_page(lbs);
    return;
    }

  if (equal_ustring(command, loc("Change Password")) ||
      (isparam("newpwd") && !equal_ustring(command, loc("Cancel")) && !equal_ustring(command, loc("Save"))))
    {
    show_change_pwd_page(lbs);
    return;
    }

  if (equal_ustring(command, loc("Save")))
    {
    if (isparam("config"))
      {
      /* change existing user */
      if (!save_user_config(lbs, getparam("config"), FALSE))
        return;
      }
    else if (isparam("new_user_name"))
      {
      /* new user */
      if (!save_user_config(lbs, getparam("new_user_name"), TRUE))
        return;

      /* login to logbook with new user */
      if (!isparam("unm"))
        {
        }
      }
    else if (!save_admin_config()) /* save cfg file */
      return;

    sprintf(str, "../%s/", lbs->name_enc);
    redirect(str);
    return;
    }

  if (equal_ustring(command, loc("Remove user")))
    {
    remove_user(lbs, getparam("config"));

    /* if removed user is current user, do logout */
    if (equal_ustring(getparam("config"), getparam("unm")))
      {
      /* log activity */
      logf("Logout of user \"%s\" from lbs->name \"%s\"",getparam("unm"),lbs->name);

      /* set cookies */
      set_login_cookies(lbs, "", "");
      }

    /* continue configuration as administrator */
    unsetparam("cfg_user");
    show_config_page(lbs);
    return;
    }

  if (equal_ustring(command, loc("New user")))
    {
    show_new_user_page(lbs);
    return;
    }

  if (equal_ustring(command, loc("Config")))
    {
    show_config_page(lbs);
    return;
    }

  if (equal_ustring(command, loc("Download")))
    {
    show_download_page(lbs, dec_path);
    return;
    }

  if (equal_ustring(command, loc("Logout")))
    {
    rsprintf("HTTP/1.1 302 Found\r\n");
    rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
    if (use_keepalive)
      {
      rsprintf("Connection: Keep-Alive\r\n");
      rsprintf("Keep-Alive: timeout=60, max=10\r\n");
      }

    /* log activity */
    logf("Logout of user \"%s\" from lbs->name \"%s\"",getparam("unm"),lbs->name);

    set_login_cookies(lbs, "", "");
    return;
    }

  if (equal_ustring(command, loc("Delete")))
    {
    show_elog_delete(lbs, message_id);
    return;
    }

  /*---- check next/previous message -------------------------------*/

  if (equal_ustring(command, loc("Next")) || equal_ustring(command, loc("Previous")) ||
      equal_ustring(command, loc("Last")) || equal_ustring(command, loc("First")))
    {
    orig_message_id = message_id;

    if (equal_ustring(command, loc("Last")))
      message_id = el_search_message(lbs, EL_LAST, 0, FALSE);

    if (equal_ustring(command, loc("First")))
      message_id = el_search_message(lbs, EL_FIRST, 0, FALSE);

    if (!message_id)
      {
      redirect("");
      return;
      }

    first = TRUE;
    do
      {
      if (equal_ustring(command, loc("Next")))
        message_id = el_search_message(lbs, EL_NEXT, message_id, FALSE);

      if (equal_ustring(command, loc("Previous")))
        message_id = el_search_message(lbs, EL_PREV, message_id, FALSE);

      if (!first)
        {
        if (equal_ustring(command, loc("First")))
          message_id = el_search_message(lbs, EL_NEXT, message_id, FALSE);


        if (equal_ustring(command, loc("Last")))
          message_id = el_search_message(lbs, EL_PREV, message_id, FALSE);
        }
      else
        first = FALSE;

      if (message_id == 0)
        {
        if (equal_ustring(command, loc("Next")))
          message_error = EL_LAST_MSG;
        else
          message_error = EL_FIRST_MSG;

        message_id = orig_message_id;
        break;
        }

      size = sizeof(text);
      el_retrieve(lbs, message_id, date, attr_list, attrib, lbs->n_attr,
                  text, &size, orig_tag, reply_tag,
                  attachment, encoding);

      /* check for locked attributes */
      for (i=0 ; i<lbs->n_attr ; i++)
        {
        sprintf(lattr, "l%s", attr_list[i]);
        if (*getparam(lattr) == '1' && !equal_ustring(getparam(attr_list[i]), attrib[i]))
          break;
        }
      if (i < lbs->n_attr)
        continue;

      /* check for attribute filter if not browsing */
      if (!*getparam("browsing"))
        {
        for (i=0 ; i<lbs->n_attr ; i++)
          {
          if (*getparam(attr_list[i]) && !equal_ustring(getparam(attr_list[i]), attrib[i]))
            break;
          }
        if (i < lbs->n_attr)
          continue;
        }

      sprintf(str, "%d", message_id);

      for (i=0 ; i<lbs->n_attr ; i++)
        {
        sprintf(lattr, "l%s", attr_list[i]);
        if (*getparam(lattr) == '1')
          {
          if (strchr(str, '?') == NULL)
            sprintf(str+strlen(str), "?%s=1", lattr);
          else
            sprintf(str+strlen(str), "&%s=1", lattr);
          }
        }

      redirect(str);
      return;

      } while (TRUE);
    }

  /*---- check for welcome page ------------------------------------*/

  if (!message_id && getcfg(lbs->name, "Welcome page", str) && str[0])
    {
    strcpy(file_name, cfg_dir);
    strcat(file_name, str);
    send_file(file_name);
    return;
    }

  /*---- check for start page --------------------------------------*/

  if (!message_id && getcfg(lbs->name, "Start page", str) && str[0])
    {
    redirect(str);
    return;
    }

  /*---- check for valid URL ---------------------------------------*/

  if (dec_path[0] && atoi(dec_path) == 0)
    {
    sprintf(str, "Invalid URL: <b>%s</b>", dec_path);
    show_error(str);
    return;
    }

  /*---- get current message ---------------------------------------*/

  if (message_id == 0)
    message_id = el_search_message(lbs, EL_LAST, 0, FALSE);

  if (message_id)
    {
    size = sizeof(text);
    status = el_retrieve(lbs, message_id, date, attr_list, attrib, lbs->n_attr,
                             text, &size, orig_tag, reply_tag,
                             attachment, encoding);

    if (status != EL_SUCCESS)
      message_error = status;
    }
  else
    message_error = EL_EMPTY;

  /*---- header ----*/

  /* header */
  if (status == EL_SUCCESS && message_error != EL_EMPTY)
    {
    str[0] = 0;

    if (getcfg(lbs->name, "Page Title", str))
      {
      i = build_subst_list(lbs, slist, svalue, attrib);
      strsubst(str, slist, svalue, i);
      }
    else
      strcpy(str, "ELOG");

    sprintf(ref, "%d", message_id);
    if (str[0])
      show_standard_header(str, ref);
    else
      show_standard_header(lbs->name, ref);
    }
  else
    show_standard_header("", "");

  /*---- title ----*/

  show_standard_title(lbs->name, "", 0);

  /*---- menu buttons ----*/

  rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Menu1 cellpadding"), gt("Frame color"));

  rsprintf("<tr><td align=%s bgcolor=%s>\n", gt("Menu1 Align"), gt("Menu1 BGColor"));

  n = strbreak(menu_str, menu_item, MAX_N_LIST);

  if (atoi(gt("Use buttons")) == 1)
    {
    for (i=0 ; i<n ; i++)
      {
      /* strip "logbook" from "move to / copy to" commands */
      strcpy(cmd, menu_item[i]);
      if (strchr(cmd, '\"'))
        *strchr(cmd, '\"') = 0;

      /* strip trailing blanks */
      while (cmd[strlen(cmd)-1] == ' ')
        cmd[strlen(cmd)-1] = 0;

      /* display menu item */
      rsprintf("<input type=submit name=cmd value=\"%s\">\n", cmd);

      if (equal_ustring(cmd, loc("Copy to")) ||
          equal_ustring(cmd, loc("Move to")))
        {
        /* put one link for each logbook except current one */
        if (equal_ustring(cmd, loc("Copy to")))
          rsprintf("<select name=destc>\n");
        else
          rsprintf("<select name=destm>\n");

        for (j=0 ;  ; j++)
          {
          if (!enumgrp(j, str))
            break;

          if (equal_ustring(str, "global"))
            continue;

          if (equal_ustring(str, lbs->name))
            continue;

          rsprintf("<option value=\"%s\">%s\n", str, str);
          }
        rsprintf("</select>\n");
        }
      }
    }
  else
    {
    rsprintf("<small>\n");

    for (i=0 ; i<n ; i++)
      {
      /* display menu item */

      /* strip "logbook" from "move to / copy to" commands */
      strcpy(cmd, loc(menu_item[i]));
      if (strchr(cmd, '\"'))
        *strchr(cmd, '\"') = 0;

      /* strip trailing blanks */
      while (cmd[strlen(cmd)-1] == ' ')
        cmd[strlen(cmd)-1] = 0;

      if (equal_ustring(cmd, loc("Copy to")) ||
          equal_ustring(cmd, loc("Move to")))
        {
        if (equal_ustring(cmd, loc("Copy to")))
          len = strlen(loc("Copy to"));
        else
          len = strlen(loc("Move to"));

        /* if logbook supplied, put a link to that logbook */
        if ((int)strlen(menu_item[i]) > len)
          {
          /* extract logbook */
          if (menu_item[i][len+1] == '"')
            strcpy(ref, menu_item[i]+len+2);
          else
            strcpy(ref, menu_item[i]+len+1);
          if (strchr(ref, '"'))
            *strchr(ref, '"') = 0;

          url_encode(ref);

          if (equal_ustring(cmd, loc("Copy to")))
            rsprintf("&nbsp;<a href=\"../%s/%d?cmd=%s&destc=%s\">%s</a>&nbsp|\n",
                      lbs->name_enc, message_id, loc("Copy to"), ref, menu_item[i]);
          else
            rsprintf("&nbsp;<a href=\"../%s/%d?cmd=%s&destm=%s\">%s</a>&nbsp|\n",
                      lbs->name_enc, message_id, loc("Move to"), ref, menu_item[i]);
          }
        else
          {
          /* put one link for each logbook except current one */
          for (j=0 ;  ; j++)
            {
            if (!enumgrp(j, str))
              break;

            if (equal_ustring(str, "global"))
              continue;

            if (equal_ustring(str, lbs->name))
              continue;

            strcpy(ref, str);
            url_encode(ref);
            if (equal_ustring(menu_item[i], loc("Copy to")))
              rsprintf("&nbsp;<a href=\"../%s/%d?cmd=%s&destc=%s\">%s \"%s\"</a>&nbsp|\n",
                        lbs->name_enc, message_id, loc("Copy to"), ref, loc("Copy to"), str);
            else
              rsprintf("&nbsp;<a href=\"../%s/%d?cmd=%s&destm=%s\">%s \"%s\"</a>&nbsp|\n",
                        lbs->name_enc, message_id, loc("Move to"), ref, loc("Move to"), str);
            }
          }
        }
      else
        {
        strcpy(str, menu_item[i]);
        url_encode(str);

        if (i < n-1)
          rsprintf("&nbsp;<a href=\"%d?cmd=%s\">%s</a>&nbsp;|\n", message_id, str, menu_item[i]);
        else
          rsprintf("&nbsp;<a href=\"%d?cmd=%s\">%s</a>&nbsp;\n", message_id, str, menu_item[i]);
        }
      }

    rsprintf("</small>\n");
    }

  rsprintf("</td>\n");

  if (atoi(gt("Merge menus")) != 1)
    {
    rsprintf("</tr>\n");
    rsprintf("</table></td></tr>\n\n");
    }

  /*---- next/previous buttons ----*/

  if (!getcfg(lbs->name, "Enable browsing", str) ||
       atoi(str) == 1)
    {
    if (atoi(gt("Merge menus")) != 1)
      {
      rsprintf("<tr><td><table width=100%% border=0 cellpadding=%s cellspacing=1 bgcolor=%s>\n",
               gt("Menu2 cellpadding"), gt("Frame color"));
      rsprintf("<tr><td valign=bottom align=%s bgcolor=%s>\n", gt("Menu2 Align"), gt("Menu2 BGColor"));
      }
    else
      rsprintf("<td width=10%% nowrap align=%s bgcolor=%s>\n", gt("Menu2 Align"), gt("Menu2 BGColor"));

    if (atoi(gt("Menu2 use images")) == 1)
      {
      rsprintf("<input type=image name=cmd_first border=0 alt=\"%s\" src=\"first.gif\">\n",
               loc("First entry"));
      rsprintf("<input type=image name=cmd_previous border=0 alt=\"%s\" src=\"previous.gif\">\n",
               loc("Previous entry"));
      rsprintf("<input type=image name=cmd_next border=0 alt=\"%s\" src=\"next.gif\">\n",
               loc("Next entry"));
      rsprintf("<input type=image name=cmd_last border=0 alt=\"%s\" src=\"last.gif\">\n",
               loc("Last entry"));
      }
    else
      {
      rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("First"));
      rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Previous"));
      rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Next"));
      rsprintf("<input type=submit name=cmd value=\"%s\">\n", loc("Last"));
      }

    rsprintf("</td></tr>\n");
    }

  rsprintf("</table></td></tr>\n\n");

  /*---- message ----*/

  /* overall table for message giving blue frame */
  rsprintf("<tr><td><table width=100%% border=%s cellpadding=%s cellspacing=1 bgcolor=%s>\n",
           gt("Categories border"), gt("Categories cellpadding"), gt("Frame color"));

  if (message_error == EL_EMPTY)
    rsprintf("<tr><td bgcolor=#FF8080 colspan=2 align=center><h1>%s</h1></tr>\n", loc("Logbook is empty"));
  else if (message_error == EL_NO_MSG)
    rsprintf("<tr><td bgcolor=#FF8080 colspan=2 align=center><h1>%s</h1></tr>\n", loc("This message has been deleted"));
  else
    {
    /* check for locked attributes */
    for (i=0 ; i<lbs->n_attr ; i++)
      {
      sprintf(lattr, "l%s", attr_list[i]);
      if (*getparam(lattr) == '1')
        break;
      }
    if (i < lbs->n_attr)
      sprintf(str, " %s <i>\"%s = %s\"</i>", loc("with"), attr_list[i], getparam(attr_list[i]));
    else
      str[0] = 0;

    if (message_error == EL_LAST_MSG)
      rsprintf("<tr><td bgcolor=#FF0000 colspan=2 align=center><b>%s %s</b></tr>\n",
               loc("This is the last entry"), str);

    if (message_error == EL_FIRST_MSG)
      rsprintf("<tr><td bgcolor=#FF0000 colspan=2 align=center><b>%s %s</b></tr>\n",
               loc("This is the first entry"), str);

    /* check for mail submissions */
    if (*getparam("suppress"))
      {
      if (getcfg(lbs->name, "Suppress default", str) && atoi(str) == 1)
        rsprintf("<tr><td colspan=2 bgcolor=#FFFFFF>%s</tr>\n", loc("Email notification suppressed"));
      else
        rsprintf("<tr><td colspan=2 bgcolor=#FF0000><b>%s</b></tr>\n", loc("Email notification suppressed"));
      i = 1;
      }
    else
      {
      for (i=0 ; ; i++)
        {
        sprintf(str, "mail%d", i);
        if (*getparam(str))
          {
          if (i==0)
            rsprintf("<tr><td colspan=2 bgcolor=#FFC020>");
          rsprintf("%s <b>%s</b><br>\n", loc("Mail sent to"), getparam(str));
          }
        else
          break;
        }
      }

    if (i>0)
      rsprintf("</tr>\n");

    /*---- display message ID ----*/

    rsprintf("<tr><td nowrap bgcolor=%s width=10%%><b>%s:</b></td><td bgcolor=%s>%d</td></tr>\n\n",
             gt("Categories bgcolor1"), loc("Message ID"), gt("Categories bgcolor2"), message_id);

    /*---- display date ----*/

    if (getcfg(lbs->name, "Date format", format))
      {
      struct tm ts;

      memset(&ts, 0, sizeof(ts));

      for (i=0 ; i<12 ; i++)
        if (strncmp(date+4, mname[i], 3) == 0)
          break;
      ts.tm_mon = i;

      ts.tm_mday = atoi(date+8);
      ts.tm_hour = atoi(date+11);
      ts.tm_min  = atoi(date+14);
      ts.tm_sec  = atoi(date+17);
      ts.tm_year = atoi(date+20)-1900;
      ts.tm_isdst = -1; /* let mktime compute DST */

      mktime(&ts);
      strftime(str, sizeof(str), format, &ts);

      rsprintf("<tr><td nowrap bgcolor=%s width=10%%><b>%s:</b></td><td bgcolor=%s>%s\n\n",
               gt("Categories bgcolor1"), loc("Entry date"), gt("Categories bgcolor2"), str);
      }
    else
      rsprintf("<tr><td nowrap bgcolor=%s width=10%%><b>%s:</b></td><td bgcolor=%s>%s\n\n",
               gt("Categories bgcolor1"), loc("Entry date"), gt("Categories bgcolor2"), date);

    for (i=0 ; i<lbs->n_attr ; i++)
      rsprintf("<input type=hidden name=\"%s\" value=\"%s\">\n", attr_list[i], attrib[i]);

    /* browsing flag to distinguish "/../<attr>=<value>" from browsing */
    rsprintf("<input type=hidden name=browsing value=1>\n");

    rsprintf("</td></tr>\n\n");

    /*---- link to original message or reply ----*/

    if (message_error != EL_FILE_ERROR && (reply_tag[0] || orig_tag[0]))
      {

      if (orig_tag[0])
        {
        rsprintf("<tr><td nowrap width=10%% bgcolor=%s>", gt("Categories bgcolor1"));
        sprintf(ref, "%s", orig_tag);
        rsprintf("<b>%s:</b></td><td bgcolor=%s>", loc("In reply to"), gt("Menu2 bgcolor"));
        rsprintf("<a href=\"%s\">%s</a></td></tr>\n", ref, orig_tag);
        }
      if (reply_tag[0])
        {
        rsprintf("<tr><td nowrap width=10%% bgcolor=%s>", gt("Categories bgcolor1"));
        rsprintf("<b>%s:</b></td><td bgcolor=%s>", loc("Reply to this"), gt("Menu2 bgcolor"));

        p = strtok(reply_tag, ",");
        do
          {
          rsprintf("<a href=\"%s\">%s</a>\n", p, p);

          p = strtok(NULL, ",");

          if (p)
            rsprintf("&nbsp&nbsp\n");

          } while (p);

        rsprintf("</td></tr>\n");
        }
      }

    /*---- display attributes ----*/

    for (i=0 ; i<lbs->n_attr ; i++)
      {
      sprintf(lattr, "l%s", attr_list[i]);
      rsprintf("<tr><td nowrap width=10%% bgcolor=%s>", gt("Categories bgcolor1"));

      if (!getcfg(lbs->name, "Filtered browsing", str) ||
          atoi(str) == 1)
        {
        if (*getparam(lattr) == '1')
          rsprintf("<input type=\"checkbox\" checked name=\"%s\" value=\"1\">&nbsp;", lattr);
        else
          rsprintf("<input alt=\"text\" type=\"checkbox\" name=\"%s\" value=\"1\">&nbsp;", lattr);
        }

      /* display checkbox for boolean attributes */
      if (equal_ustring(attr_options[i][0], "boolean"))
        {
        if (atoi(attrib[i]) == 1)
          rsprintf("<b>%s:</b></td><td bgcolor=%s><input type=checkbox checked disabled></td></tr>\n",
                   attr_list[i], gt("Categories bgcolor2"));
        else
          rsprintf("<b>%s:</b></td><td bgcolor=%s><input type=checkbox disabled></td></tr>\n",
                   attr_list[i], gt("Categories bgcolor2"));
        }
      /* display image for icon */
      else if (attr_flags[i] & AF_ICON)
        {
        rsprintf("<b>%s:</b></td><td bgcolor=%s>\n",
                 attr_list[i], gt("Categories bgcolor2"));
        if (attrib[i][0])
          rsprintf("<img src=\"icons/%s\">", attrib[i]);
        rsprintf("&nbsp</td></tr>\n");
        }
      else
        {
        rsprintf("<b>%s:</b></td><td bgcolor=%s>\n",
                 attr_list[i], gt("Categories bgcolor2"));
        rsputs2(attrib[i]);
        rsprintf("&nbsp</td></tr>\n");
        }
      }

    rsprintf("</td></tr>\n");
    rsputs("</table></td></tr>\n");

    /*---- message text ----*/

    if (!getcfg(lbs->name, "Show text", str) || atoi(str) == 1)
      {
      rsprintf("<tr><td><table width=100%% border=0 cellpadding=1 cellspacing=1 bgcolor=%s>\n", gt("Frame color"));

      if (*gt("BGTimage"))
        rsprintf("<tr><td background=\"%s\" bgcolor=%s>\n", gt("BGTimage"), gt("Text BGColor"));
      else
        rsprintf("<tr><td bgcolor=%s>\n", gt("Text BGColor"));

      if (equal_ustring(encoding, "plain"))
        {
        rsputs("<pre>");
        rsputs2(text);
        rsputs("</pre>");
        }
      else
        rsputs(text);

      rsputs("</td></tr>\n");
      rsputs("</table></td></tr>\n");
      }

    for (index = 0 ; index < MAX_ATTACHMENTS ; index++)
      {
      if (attachment[index][0])
        {
        for (i=0 ; i<(int)strlen(attachment[index]) ; i++)
          att[i] = toupper(attachment[index][i]);
        att[i] = 0;

        /* determine size of attachment */
        strcpy(file_name, lbs->data_dir);
        strcat(file_name, attachment[index]);

        length = 0;
        fh = open(file_name, O_RDONLY | O_BINARY);
        if (fh > 0)
          {
          lseek(fh, 0, SEEK_END);
          length = TELL(fh);
          close(fh);
          }

        strcpy(str, attachment[index]);
        str[13] = 0;
        sprintf(ref, "%s/%s", str, attachment[index]+14);

        rsprintf("<tr><td><table width=100%% border=0 cellpadding=0 cellspacing=1 bgcolor=%s>\n", gt("Frame color"));

        rsprintf("<tr><td nowrap width=10%% bgcolor=%s><b>&nbsp;%s %d:</b></td>",
                 gt("Categories bgcolor1"), loc("Attachment"), index+1);
        rsprintf("<td bgcolor=%s>&nbsp;<a href=\"%s\">%s</a>\n",
                 gt("Categories bgcolor2"), ref, attachment[index]+14);

        if (length < 1024)
          rsprintf("&nbsp;<small><b>%d Bytes</b></small>", length);
        else if (length < 1024*1024)
          rsprintf("&nbsp;<small><b>%d kB</b></small>", length/1024);
        else
          rsprintf("&nbsp;<small><b>%1.3lf MB</b></small>", length/1024.0/1024.0);

        rsprintf("</td></tr></table></td></tr>\n");

        if (!getcfg(lbs->name, "Show attachments", str) ||
            atoi(str) == 1)
          {
          if (strstr(att, ".GIF") ||
              strstr(att, ".JPG") ||
              strstr(att, ".JPEG") ||
              strstr(att, ".PNG"))
            {
            rsprintf("<tr><td><table width=100%% border=0 cellpadding=0 cellspacing=1 bgcolor=%s>\n", gt("Frame color"));
            rsprintf("<tr><td bgcolor=%s>", gt("Text bgcolor"));
            rsprintf("<img src=\"%s\"></td></tr>", ref);
            rsprintf("</table></td></tr>\n\n");
            }
          else
            {
            if (strstr(att, ".TXT") ||
                strstr(att, ".ASC") ||
                strchr(att, '.') == NULL)
              {
              /* display attachment */
              rsprintf("<tr><td><table width=100%% border=0 cellpadding=0 cellspacing=1 bgcolor=%s>\n", gt("Frame color"));
              rsprintf("<tr><td bgcolor=%s>", gt("Text bgcolor"));
              if (!strstr(att, ".HTML"))
                rsprintf("<br><pre>");

              strcpy(file_name, lbs->data_dir);
              strcat(file_name, attachment[index]);

              f = fopen(file_name, "rt");
              if (f != NULL)
                {
                while (!feof(f))
                  {
                  str[0] = 0;
                  fgets(str, sizeof(str), f);

                  if (!strstr(att, ".HTML"))
                    rsputs2(str);
                  else
                    rsputs(str);
                  }
                fclose(f);
                }

              if (!strstr(att, ".HTML"))
                rsprintf("</pre>");
              rsprintf("\n");
              rsprintf("</td></tr></table></td></tr>\n");
              }
            }
          }
        }
      }
    }

  /* table for message body */
  rsprintf("</td></tr></table></td></tr>\n\n");

  /* overall table */
  rsprintf("</td></tr></table></td></tr>\n");

  if (getcfg(lbs->name, "bottom text", str))
    {
    FILE *f;
    char file_name[256], *buf;

    strcpy(file_name, cfg_dir);
    strcat(file_name, str);

    f = fopen(file_name, "r");
    if (f != NULL)
      {
      fseek(f, 0, SEEK_END);
      size = TELL(fileno(f));
      fseek(f, 0, SEEK_SET);

      buf = malloc(size+1);
      fread(buf, 1, size, f);
      buf[size] = 0;
      fclose(f);

      rsputs(buf);
      }
    }
  else
    /* add little logo */
    rsprintf("<center><font size=1 color=#A0A0A0><a href=\"http://midas.psi.ch/elog/\">ELOG V%s</a></font></center>", VERSION);

  rsprintf("</body></html>\r\n");
}

/*------------------------------------------------------------------*/

BOOL check_password(LOGBOOK *lbs, char *name, char *password, char *redir)
{
char  str[256];

  /* get password from configuration file */
  if (getcfg(lbs->name, name, str))
    {
    if (strcmp(password, str) == 0)
      return TRUE;

    /* show web password page */
    show_standard_header(loc("ELOG password"), NULL);

    /* define hidden fields for current destination */
    if (redir[0])
      rsprintf("<input type=hidden name=redir value=\"%s\">\n", redir);

    rsprintf("<p><p><p><table border=%s width=50%% bgcolor=%s cellpadding=1 cellspacing=0 align=center>",
              gt("Border width"), gt("Frame color"));
    rsprintf("<tr><td><table cellpadding=5 cellspacing=0 border=0 width=100%% bgcolor=%s>\n", gt("Frame color"));

    if (password[0])
      rsprintf("<tr><th bgcolor=#FF0000>%s!</th></tr>\n", loc("Wrong password"));

    rsprintf("<tr><td align=center bgcolor=%s>\n", gt("Title bgcolor"));

    if (strcmp(name, "Write password") == 0)
      {
      rsprintf("<font color=%s>%s</font></td></tr>\n",
               gt("Title fontcolor"), loc("Please enter password to obtain write access"));
      rsprintf("<tr><td align=center bgcolor=%s><input type=password name=wpassword></td></tr>\n", gt("Cell BGColor"));
      }
    else
      {
      rsprintf("<font color=%s>%s</font></td></tr>\n",
               gt("Title fontcolor"), loc("Please enter password to obtain administration access"));
      rsprintf("<tr><td align=center bgcolor=%s><input type=password name=apassword></td></tr>\n", gt("Cell BGColor"));
      }

    rsprintf("<tr><td align=center bgcolor=%s><input type=submit value=\"%s\"></td></tr>", gt("Cell BGColor"), loc("Submit"));

    rsprintf("</table></td></tr></table>\n");

    rsprintf("</body></html>\r\n");

    return FALSE;
    }
  else
    return TRUE;
}

/*------------------------------------------------------------------*/

BOOL get_user_line(LOGBOOK *lbs, char *user, char *password, char *full_name, char *email, char *email_notify)
{
char  str[256], line[256], file_name[256], *p;
FILE  *f;
int   i;

  if (password) password[0] = 0;
  if (full_name) full_name[0] = 0;
  if (email) email[0] = 0;
  if (email_notify) email_notify[0] = 0;

  getcfg(lbs->name, "Password file", str);

  if (str[0] == DIR_SEPARATOR || str[1] == ':')
    strcpy(file_name, str);
  else
    {
    strcpy(file_name, cfg_dir);
    strcat(file_name, str);
    }

  f = fopen(file_name, "r");
  if (f != NULL)
    {
    if (!user[0])
      {
      fclose(f);
      return TRUE;
      }

    while (!feof(f))
      {
      line[0] = 0;
      fgets(line, sizeof(line), f);

      if (line[0] == ';' || line[0] == '#' || line[0] == 0)
        continue;

      strcpy(str, line);
      if (strchr(str, ':'))
        *strchr(str, ':') = 0;
      if (strcmp(str, user) == 0)
        break;
      }
    fclose(f);

    /* if user found, retrieve other info */
    p = line;

    for (i=0 ; i<4 ; i++)
      {
      if (strchr(p, ':') == NULL)
        break;
      p = strchr(p, ':')+1;
      
      while (*p && *p == ' ')
        p++;
      strncpy(str, p, sizeof(str)-1);
      if (strchr(str, ':'))
        *strchr(str, ':') = 0;

      while (str[strlen(str)-1] == ' ' ||
             str[strlen(str)-1] == '\r' ||
             str[strlen(str)-1] == '\n')
        str[strlen(str)-1] = 0;

      if (i==0 && password)
        strcpy(password, str);
      else if (i==1 && full_name)
        strcpy(full_name, str);
      else if (i==2 && email)
        strcpy(email, str);
      else if (i==3 && email_notify)
        strcpy(email_notify, str);
      }

    return TRUE;
    }
  else
    return FALSE;
}

/*------------------------------------------------------------------*/

BOOL enum_user_line(LOGBOOK *lbs, int n, char *user)
{
char  str[256], line[256], file_name[256];
FILE  *f;
int   i;

  getcfg(lbs->name, "Password file", str);

  if (str[0] == DIR_SEPARATOR || str[1] == ':')
    strcpy(file_name, str);
  else
    {
    strcpy(file_name, cfg_dir);
    strcat(file_name, str);
    }

  f = fopen(file_name, "r");
  i = 0;
  if (f != NULL)
    {
    while (!feof(f))
      {
      line[0] = 0;
      fgets(line, sizeof(line), f);

      if (line[0] == ';' || line[0] == '#' || line[0] == 0)
        continue;

      strcpy(str, line);
      if (strchr(str, ':'))
        *strchr(str, ':') = 0;

      if (i == n)
        {
        strcpy(user, str);
        fclose(f);
        return TRUE;
        }

      i++;
      }
    fclose(f);
    }

  return FALSE;
}

/*------------------------------------------------------------------*/

BOOL check_user_password(LOGBOOK *lbs, char *user, char *password, char *redir)
{
char  str[256], upwd[256], full_name[256], email[256];

  if (get_user_line(lbs, user, upwd, full_name, email, NULL))
    {
    if (user[0] && strcmp(password, upwd) == 0)
      {
      setparam("full_name", full_name);
      setparam("user_email", email);
      return TRUE;
      }

    /* show login password page */
    show_standard_header("ELOG login", NULL);

    /* define hidden fields for current destination */
    if (redir[0])
      rsprintf("<input type=hidden name=redir value=\"%s\">\n", redir);

    rsprintf("<p><p><p><table border=%s width=50%% bgcolor=%s cellpadding=1 cellspacing=0 align=center>",
              gt("Border width"), gt("Frame color"));
    rsprintf("<tr><td><table cellpadding=5 cellspacing=0 border=0 width=100%% bgcolor=%s>\n", gt("Frame color"));

    if (password[0])
      rsprintf("<tr><th bgcolor=#FF0000>%s!</th></tr>\n", loc("Wrong password"));

    rsprintf("<tr><td align=center bgcolor=%s>\n", gt("Title bgcolor"));

    rsprintf("<font color=%s>%s</font></td></tr>\n",
             gt("Title fontcolor"), loc("Please login"));
    rsprintf("<tr><td align=center bgcolor=%s>%s:&nbsp;&nbsp;&nbsp;<input type=text name=uname></td></tr>\n",
             gt("Cell BGColor"), loc("Username"));
    rsprintf("<tr><td align=center bgcolor=%s>%s:&nbsp;&nbsp;&nbsp;<input type=password name=upassword></td></tr>\n",
             gt("Cell BGColor"), loc("Password"));

    if (getcfg(lbs->name, "Self register", str) && atoi(str) == 1)
      rsprintf("<tr><td align=center bgcolor=%s><a href=\"?cmd=New+user\">%s</td></tr>", 
                gt("Cell BGColor"), loc("Register as new user"));

    rsprintf("<tr><td align=center bgcolor=%s><input type=submit value=\"%s\"></td></tr>", 
              gt("Cell BGColor"), loc("Submit"));

    rsprintf("</table></td></tr></table>\n");

    rsprintf("</body></html>\r\n");

    return FALSE;
    }
  else
    {
    getcfg(lbs->name, "Password file", str);
    sprintf(full_name, "Error: Password file \"%s\" not found", str);
    show_error(full_name);
    return FALSE;
    }
}

/*------------------------------------------------------------------*/

void show_selection_page()
{
int  i;
char str[10000];

  show_http_header();

  rsprintf("<html>\n");
  rsprintf("<head>\n");

 if (getcfg("global", "Page Title", str))
   {
   rsprintf("<title>");
   rsputs(str);
   rsprintf("</title>\n");
   }
 else
   rsprintf("<title>ELOG Logbook Selection</title>\n");

  rsprintf("</head>\n\n");

  rsprintf("<body>\n\n");

  rsprintf("<p><p><p><table border=0 bgcolor=#486090 cellpadding=0 cellspacing=0 align=center>");
  rsprintf("<tr><td><table cellpadding=5 cellspacing=1 border=0 width=100%% bgcolor=#486090>\n");

  rsprintf("<tr><td align=center colspan=3 bgcolor=#486090>\n");

  if (getcfg("global", "Welcome title", str))
    {
    rsputs(str);
    }
  else
    {
    rsprintf("<font size=5 color=#FFFFFF>\n");
    rsprintf("%s.<BR>\n", loc("Several logbooks are defined on this host"));
    rsprintf("%s:</font></td></tr>\n", loc("Please select the one to connect to"));
    }

  for (i=0 ;  ; i++)
    {
    if (!lb_list[i].name[0])
      break;

    rsprintf("<tr><td bgcolor=#CCCCFF><a href=\"%s/\">%s</a></td>", lb_list[i].name_enc, lb_list[i].name);

    str[0] = 0;
    getcfg(lb_list[i].name, "Comment", str);
    rsprintf("<td bgcolor=#DDEEBB>%s&nbsp;</td>\n", str);

    rsprintf("<td bgcolor=#FFFFB0>");
    rsprintf(loc("%d entries"), *lb_list[i].n_el_index);
    rsprintf("</td></tr>\n");
    }

  rsprintf("</table></td></tr></table></body>\n");
  rsprintf("</html>\r\n\r\n");

}

/*------------------------------------------------------------------*/

void get_password(char *password)
{
static char last_password[32];

  if (strncmp(password, "set=", 4) == 0)
    strcpy(last_password, password+4);
  else
    strcpy(password, last_password);
}

/*------------------------------------------------------------------*/

void interprete(char *lbook, char *path)
/********************************************************************\

  Routine: interprete

  Purpose: Interprete parametersand generate HTML output.

  Input:
    char *path              Message path

  <implicit>
    _param/_value array accessible via getparam()

\********************************************************************/
{
int     i, n, index, lb_index;
double  exp;
char    str[256], enc_pwd[80], file_name[256], data_dir[256];
char    enc_path[256], dec_path[256], logbook[256], logbook_enc[256];
char    *experiment, *command, *value, *group;
time_t  now;
struct  tm *gmt;
LOGBOOK *cur_lb;

  /* encode path for further usage */
  strcpy(dec_path, path);
  url_decode(dec_path);
  url_decode(dec_path); /* necessary for %2520 -> %20 -> ' ' */
  strcpy(enc_path, dec_path);
  url_encode(enc_path);

  experiment = getparam("exp");
  command = getparam("cmd");
  value = getparam("value");
  group = getparam("group");
  index = atoi(getparam("index"));

  /* if experiment given, use it as logbook (for elog!) */
  if (experiment && experiment[0])
    {
    strcpy(logbook_enc, experiment);
    strcpy(logbook, experiment);
    url_decode(logbook);
    }
  else
    {
    strcpy(logbook_enc, lbook);
    strcpy(logbook, lbook);
    url_decode(logbook);
    }

  /* check for global selection page if no logbook given */
  if (!logbook[0] && getcfg("global", "Selection page", str))
    {
    strcpy(file_name, cfg_dir);
    strcat(file_name, str);
    send_file(file_name);
    return;
    }

  /* if no logbook given, display logbook selection page */
  if (!logbook[0])
    {
    for (i=n=0 ; ; i++)
      {
      if (!enumgrp(i, str))
        break;
      if (!equal_ustring(str, "global"))
        {
        strcpy(logbook, str);
        n++;
        }
      }

    if (n > 1)
      {
      show_selection_page();
      return;
      }

    strcpy(logbook_enc, logbook);
    url_encode(logbook_enc);
    }

  /* get theme for logbook */
  if (getcfg(logbook, "Theme", str))
    loadtheme(str);
  else
    loadtheme(NULL); /* get default values */

  /* set up logbook entry if not existing */
  for (i=0 ; lb_list[i].name[0] ; i++)
    if (equal_ustring(logbook, lb_list[i].name))
      break;
  if (!lb_list[i].name[0])
    {
    lb_list = realloc(lb_list, sizeof(LOGBOOK)*(i+2));
    strcpy(lb_list[i].name, logbook);
    strcpy(lb_list[i].name_enc, logbook_enc);

    /* get data dir from configuration file */
    getcfg(logbook, "Data dir", str);
    if (str[0] == DIR_SEPARATOR || str[1] == ':')
      strcpy(data_dir, str);
    else
      {
      strcpy(data_dir, cfg_dir);
      strcat(data_dir, str);
      }

    if (data_dir[strlen(data_dir)-1] != DIR_SEPARATOR)
      strcat(data_dir, DIR_SEPARATOR_STR);

    strcpy(lb_list[i].data_dir, data_dir);
    lb_list[i].el_index = NULL;

    lb_list[i+1].name[0] = 0;
    }
  lb_index = i;
  cur_lb = lb_list+i;
  cur_lb->n_attr = scan_attributes(cur_lb->name);

  if (*getparam("wpassword"))
    {
    /* check if password correct */
    do_crypt(getparam("wpassword"), enc_pwd);

    if (!check_password(cur_lb, "Write password", enc_pwd, getparam("redir")))
      return;

    rsprintf("HTTP/1.1 302 Found\r\n");
    rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
    if (use_keepalive)
      {
      rsprintf("Connection: Keep-Alive\r\n");
      rsprintf("Keep-Alive: timeout=60, max=10\r\n");
      }

    /* get optional expriation from configuration file */
    exp = 0;
    if (getcfg(logbook, "Write password expiration", str))
      exp = atof(str);

    if (exp == 0)
      {
      if (getcfg("global", "Write password", str))
        rsprintf("Set-Cookie: wpwd=%s; path=/\r\n", enc_pwd);
      else
        rsprintf("Set-Cookie: wpwd=%s\r\n", enc_pwd);
      }
    else
      {
      time(&now);
      now += (int) (3600*exp);
      gmt = gmtime(&now);
      strftime(str, sizeof(str), "%A, %d-%b-%y %H:%M:%S GMT", gmt);

      if (getcfg("global", "Write password", str))
        rsprintf("Set-Cookie: wpwd=%s; path=/; expires=%s\r\n", enc_pwd, logbook_enc, str);
      else
        rsprintf("Set-Cookie: wpwd=%s; expires=%s\r\n", enc_pwd, logbook_enc, str);
      }

    sprintf(str, "%s", getparam("redir"));
    if (!str[0])
      sprintf(str, "../%s/", logbook_enc);

    rsprintf("Location: %s\r\n\r\n<html>redir</html>\r\n", str);
    return;
    }

  if (*getparam("apassword"))
    {
    /* check if password correct */
    do_crypt(getparam("apassword"), enc_pwd);

    if (!check_password(cur_lb, "Admin password", enc_pwd, getparam("redir")))
      return;

    rsprintf("HTTP/1.1 302 Found\r\n");
    rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
    if (use_keepalive)
      {
      rsprintf("Connection: Keep-Alive\r\n");
      rsprintf("Keep-Alive: timeout=60, max=10\r\n");
      }

    /* get optional expriation from configuration file */
    exp = 0;
    if (getcfg(logbook, "Admin password expiration", str))
      exp = atof(str);

    if (exp == 0)
      {
      if (getcfg("global", "Admin password", str))
        rsprintf("Set-Cookie: apwd=%s; path=/\r\n", enc_pwd);
      else
        rsprintf("Set-Cookie: apwd=%s\r\n", enc_pwd);
      }
    else
      {
      time(&now);
      now += (int) (3600*exp);
      gmt = gmtime(&now);
      strftime(str, sizeof(str), "%A, %d-%b-%y %H:%M:%S GMT", gmt);

      if (getcfg("global", "Admin password", str))
        rsprintf("Set-Cookie: apwd=%s; path=/; expires=%s\r\n", enc_pwd);
      else
        rsprintf("Set-Cookie: apwd=%s; expires=%s\r\n", enc_pwd);
      }

    sprintf(str, "%s", getparam("redir"));
    if (!str[0])
      sprintf(str, "../%s/", logbook_enc);

    rsprintf("Location: %s\r\n\r\n<html>redir</html>\r\n", str);
    return;
    }

  if (*getparam("uname") && getparam("upassword"))
    {
    /* check if password correct */
    do_crypt(getparam("upassword"), enc_pwd);

    /* log logins */
    logf("Login of user \"%s\" (attempt) for logbook \"%s\" ",getparam("uname"),logbook);

    if (!check_user_password(cur_lb, getparam("uname"), enc_pwd, getparam("redir")))
      return;

    logf("Login of user \"%s\" (successful)",getparam("uname"));

    /* set cookies */
    set_login_cookies(cur_lb, getparam("uname"), enc_pwd);

    return;
    }

  /*---- show ELog page --------------------------------------------*/


  /* if password file given, check password and user name */
  if (getcfg(logbook, "Password file", str))
    {
    /* check if guest access */
    if (getcfg(cur_lb->name, "Guest menu commands", str) && *getparam("unm") == 0)
      logf("Guest access");
    else
      {
      logf("Connection of user \"%s\"",getparam("unm"));
      if (!check_user_password(cur_lb, getparam("unm"), getparam("upwd"), path))
        return;
      }
    }

  if (equal_ustring(command, loc("Login")))
    {
    check_user_password(cur_lb, "", "", path);
    return;
    }

  if (equal_ustring(command, loc("New")) ||
      equal_ustring(command, loc("Edit")) ||
      equal_ustring(command, loc("Reply")) ||
      equal_ustring(command, loc("Delete")) ||
      equal_ustring(command, loc("Submit")))
    {
    sprintf(str, "%s?cmd=%s", path, command);
    if (!check_password(cur_lb, "Write password", getparam("wpwd"), str))
      return;
    }

  if (equal_ustring(command, loc("Delete"))  ||
      equal_ustring(command, loc("Config"))  ||
      equal_ustring(command, loc("Copy to")) ||
      equal_ustring(command, loc("Move to")))
    {
    sprintf(str, "%s?cmd=%s", path, command);
    if (!check_password(cur_lb, "Admin password", getparam("apwd"), str))
      return;
    }

  /* check for "Back" button */
  if (equal_ustring(command, loc("Back")) &&
      getcfg(cur_lb->name, "Back to main", str) &&
      atoi(str) == 1)
    {
    redirect("../");
    return;
    }

  if (equal_ustring(command, loc("Back")))
    {
    sprintf(str, "../%s/", logbook_enc);
    redirect(str);
    return;
    }

  /* check for "Last n*2 Entries" */
  strcpy(str, getparam("last"));
  if (strchr(str, ' '))
    {
    i = atoi(strchr(str, ' '));
    sprintf(str, "last%d", i);
    if (isparam("mode"))
      sprintf(str+strlen(str), "?mode=%s", getparam("mode"));
    redirect(str);
    return;
    }

  strcpy(str, getparam("past"));
  if (strchr(str, ' '))
    {
    i = atoi(strchr(str, ' '));
    sprintf(str, "past%d", i);
    redirect(str);
    return;
    }

  /* check for lastxx and pastxx and listxx */
  if (strncmp(path, "past", 4) == 0 &&
      *getparam("cmd") == 0)
    {
    show_elog_submit_find(cur_lb, atoi(path+4), 0, 0);
    return;
    }

  if (strncmp(path, "last", 4) == 0 && strstr(path, ".gif") == NULL &&
      !isparam("cmd") && !isparam("newpwd"))
    {
    show_elog_submit_find(cur_lb, 0, atoi(path+4), 0);
    return;
    }

  if (strncmp(path, "page", 4) == 0 &&
      *getparam("cmd") == 0)
    {
    if (!path[4])
      show_elog_submit_find(cur_lb, 0, 0, -1);
    else
      show_elog_submit_find(cur_lb, 0, 0, atoi(path+4));
    return;
    }

  /*---- check if file requested -----------------------------------*/

  if ((strlen(dec_path) > 13 && dec_path[6] == '_' && dec_path[13] == '_') ||
      (strlen(dec_path) > 13 && dec_path[6] == '_' && dec_path[13] == '/') ||
      strstr(dec_path, ".gif") || strstr(dec_path, ".jpg") ||
      strstr(dec_path, ".jpeg") || strstr(dec_path, ".png"))
    {
    if ((strlen(dec_path) > 13 && dec_path[6] == '_' && dec_path[13] == '_') ||
        (strlen(dec_path) > 13 && dec_path[6] == '_' && dec_path[13] == '/'))
      {
      if (dec_path[13] == '/')
        dec_path[13] = '_';

      /* file from data directory requested */
      strcpy(file_name, cur_lb->data_dir);
      strcat(file_name, dec_path);
      }
    else
      {
      /* file from theme directory requested */
      strcpy(file_name, cfg_dir);
      if (file_name[0])
        strcat(file_name, DIR_SEPARATOR_STR);
      strcat(file_name, "themes");
      strcat(file_name, DIR_SEPARATOR_STR);
      if (theme_name[0])
        {
        strcat(file_name, theme_name);
        strcat(file_name, DIR_SEPARATOR_STR);
        }
      strcat(file_name, dec_path);
      }

    send_file(file_name);
    return;
    }

  show_elog_page(cur_lb, dec_path);
  return;
}

/*------------------------------------------------------------------*/

void decode_get(char *logbook, char *string)
{
char path[256];
char *p, *pitem;

  setparam("cmdline", string);

  strncpy(path, string, sizeof(path));
  path[255] = 0;
  if (strchr(path, '?'))
    *strchr(path, '?') = 0;
  setparam("path", path);

  if (strchr(string, '?'))
    {
    p = strchr(string, '?')+1;

    /* cut trailing "/" from netscape */
    if (p[strlen(p)-1] == '/')
      p[strlen(p)-1] = 0;

    p = strtok(p, "&");
    while (p != NULL)
      {
      pitem = p;
      p = strchr(p,'=');
      if (p != NULL)
        {
        *p++ = 0;
        url_decode(pitem);
        url_decode(p);

        setparam(pitem, p);

        p = strtok(NULL, "&");
        }
      }
    }

  interprete(logbook, path);
}

/*------------------------------------------------------------------*/

void decode_post(char *logbook, char *string, char *boundary, int length)
{
char *pinit, *p, *ptmp, file_name[256], str[256], line[256], item[256];
int  i, n;

  for (i=0 ; i<MAX_ATTACHMENTS ; i++)
    _attachment_size[i]=  0;

  pinit = string;

  /* return if no boundary defined */
  if (!boundary[0])
    return;

  if (strstr(string, boundary))
    string = strstr(string, boundary) + strlen(boundary);

  do
    {
    if (strstr(string, "name="))
      {
      strncpy(line, strstr(string, "name=") + 5, sizeof(line)-1);
      line[sizeof(line)-1] = 0;

      if (strchr(line, '\r'))
        *strchr(line, '\r') = 0;

      if (strchr(line, '\n'))
        *strchr(line, '\n') = 0;

      strcpy(item, line);
      if (item[0] == '\"')
        {
        strcpy(item, line+1);

        if (strchr(item, '\"'))
          *strchr(item, '\"') = 0;
        }
      else
        if (strchr(item, ' '))
          *strchr(item, ' ') = 0;

      if (strncmp(item, "attfile", 7) == 0)
        {
        n = item[7] - '1';

        /* evaluate file attachment */
        if (strstr(string, "filename="))
          {
          p = strstr(string, "filename=")+9;

          if (*p == '\"')
            p++;
          if (strstr(p, "\r\n\r\n"))
            string = strstr(p, "\r\n\r\n")+4;
          else if (strstr(p, "\r\r\n\r\r\n"))
            string = strstr(p, "\r\r\n\r\r\n")+6;
          if (strchr(p, '\"'))
            *strchr(p, '\"') = 0;

          /* set attachment filename */
          strcpy(file_name, p);
          sprintf(str, "attachment%d", n);
          setparam(str, file_name);

          if (verbose)
            printf("decode_post: Found attachment %s\n", file_name);

          /* check filename for invalid characters */
          if (strpbrk(file_name, ",;"))
            {
            sprintf(str, "Error: Filename \"%s\" contains invalid character", file_name);
            show_error(str);
            return;
            }

          /* find next boundary */
          ptmp = string;
          do
            {
            while (*ptmp != '-')
              ptmp++;

            if ((p = strstr(ptmp, boundary)) != NULL)
              {
              if (*(p-1) == '-')
                p--;
              while (*p == '-')
                p--;
              if (*p == 10)
                p--;
              if (*p == 13)
                p--;
              p++;
              break;
              }
            else
              ptmp += strlen(ptmp);

            } while (TRUE);

          /* save pointer to file */
          if (file_name[0])
            {
            _attachment_buffer[n] = string;
            _attachment_size[n] = (int)(p - string);
            }
          string = strstr(p, boundary) + strlen(boundary);
          }
        else
          string = strstr(string, boundary) + strlen(boundary);

        }
      else
        {
        p = string;
        if (strstr(p, "\r\n\r\n"))
          p = strstr(p, "\r\n\r\n")+4;
        else if (strstr(p, "\r\r\n\r\r\n"))
          p = strstr(p, "\r\r\n\r\r\n")+6;

        if (strstr(p, boundary))
          {
          string = strstr(p, boundary) + strlen(boundary);
          *strstr(p, boundary) = 0;
          ptmp = p + (strlen(p) - 1);
          while (*ptmp == '-')
            *ptmp-- = 0;
          while (*ptmp == '\n' || *ptmp == '\r')
            *ptmp-- = 0;
          }

        if (setparam(item, p) == 0)
          return;
        }

      while (*string == '-' || *string == '\n' || *string == '\r')
        string++;
      }

    } while ((int)(string - pinit) < length);

  interprete(logbook, "");
}

/*------------------------------------------------------------------*/

BOOL _abort = FALSE;

void ctrlc_handler(int sig)
{
  _abort = TRUE;
}

/*------------------------------------------------------------------*/

char net_buffer[WEB_BUFFER_SIZE];

#define N_MAX_CONNECTION 10
#define KEEP_ALIVE_TIME  60

int ka_sock[N_MAX_CONNECTION];
int ka_time[N_MAX_CONNECTION];
struct in_addr remote_addr[N_MAX_CONNECTION];
char remote_host[N_MAX_CONNECTION][256];

void server_loop(int tcp_port, int daemon)
{
int                  status, i, n, n_error, authorized, min, i_min, i_conn, length;
struct sockaddr_in   serv_addr, acc_addr;
char                 pwd[256], str[256], url[256], cl_pwd[256], *p, *pd;
char                 cookie[256], boundary[256], list[1000],
                     host_list[MAX_N_LIST][NAME_LENGTH],
                     rem_host_ip[256], logbook[256], logbook_enc[256];
int                  lsock, len, flag, content_length, header_length;
struct hostent       *phe;
fd_set               readfds;
struct timeval       timeout;

#ifdef OS_WINNT
  {
  WSADATA WSAData;

  /* Start windows sockets */
  if ( WSAStartup(MAKEWORD(1,1), &WSAData) != 0)
    return;
  }
#endif

  /* create a new socket */
  lsock = socket(AF_INET, SOCK_STREAM, 0);

  if (lsock == -1)
    {
    printf("Cannot create socket\n");
    return;
    }

  /* bind local node name and port to socket */
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;

  /* if no hostname given with the -h flag, listen on any interface */
  if (tcp_hostname[0] == 0)
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  else
    {
    /* look up the given hostname. gethostbyname() will take a hostname
       or an IP address */
    phe = gethostbyname(tcp_hostname);
    if (!phe)
      {
      printf("Cannot find address for -h %s\n", tcp_hostname);
      return;
      }
    if (phe->h_addrtype != AF_INET)
      {
      printf("Non Internet address for -h %s\n", tcp_hostname);
      return;
      }
    memcpy(&serv_addr.sin_addr.s_addr, phe->h_addr_list[0], phe->h_length);
    }

  serv_addr.sin_port = htons((short) tcp_port);

  /* try reusing address */
  flag = 1;
  setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, (char *) &flag, sizeof(INT));

  status = bind(lsock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  if (status < 0)
    {
    printf("Cannot bind to port %d.\nPlease try later or use the \"-p\" flag to specify a different port\n", tcp_port);
    return;
    }

  /* get host name for mail notification */
  gethostname(host_name, sizeof(host_name));

  phe = gethostbyname(host_name);
  if (phe != NULL)
    phe = gethostbyaddr(phe->h_addr, sizeof(int), AF_INET);

  /* if domain name is not in host name, hope to get it from phe */
  if (strchr(host_name, '.') == NULL && phe != NULL)
    strcpy(host_name, phe->h_name);

  /* open configuration file */
  getcfg("dummy", "dummy", str);

  if (daemon)
    {
    printf("Becoming a daemon...\n");
    ss_daemon_init();
    }

#ifdef OS_UNIX
  /* crate /var/run/elogd.pid file */
  {
  int pid;
  FILE *f;

  pid = getpid();
  f = fopen("/var/run/elogd.pid", "w");
  if (f)
    {
    fprintf(f, "%d\n", pid);
    fclose(f);
    }
  }

  /* install signal handler */
  signal(SIGTERM, ctrlc_handler);
  signal(SIGINT, ctrlc_handler);

  /* give up root privilege */

  if (geteuid() == 0)
    {
    struct group  *gr;
    struct passwd *pw;

    if (getcfg("global", "Group", str))
      {
      gr = getgrnam(str);

      if (gr == NULL)
        printf("Group \"%s\" not found\n", str);
      else if (setgid(gr->gr_gid) < 0 || initgroups(gr->gr_name, gr->gr_gid) < 0)
        printf("Cannot set GID to group \"%s\"\n", gr->gr_name);
      }
    else
      setgid(getgid()); /* used for setuid programs */

    if (getcfg("global", "User", str))
      {
      pw = getpwnam(str);

      if (pw == NULL)
        printf("User \"%s\" not found\n", str);
      else if (setuid(pw->pw_uid) < 0)
        printf("Cannot set UID to user \"%s\\n", str);
      }
    else
      setuid(getuid()); /* used for setuid programs */

    }
#endif

  /* listen for connection */
  status = listen(lsock, SOMAXCONN);
  if (status < 0)
    {
    printf("Cannot listen\n");
    return;
    }

  printf("Server listening...\n");
  do
    {
    FD_ZERO(&readfds);
    FD_SET(lsock, &readfds);

    for (i=0 ; i<N_MAX_CONNECTION ; i++)
      if (ka_sock[i] > 0)
        FD_SET(ka_sock[i], &readfds);

    timeout.tv_sec  = 0;
    timeout.tv_usec = 100000;

    status = select(FD_SETSIZE, (void *) &readfds, NULL, NULL, (void *) &timeout);

    if (_abort)
      break;

    if (FD_ISSET(lsock, &readfds))
      {
      len = sizeof(acc_addr);
      _sock = accept(lsock, (struct sockaddr *) &acc_addr, &len);

      /* find new entry in socket table */
      for (i=0 ; i<N_MAX_CONNECTION ; i++)
        if (ka_sock[i] == 0)
          break;

      /* recycle last connection */
      if (i == N_MAX_CONNECTION)
        {
        for (i=i_min=0,min=ka_time[0] ; i<N_MAX_CONNECTION ; i++)
          if (ka_time[i] < min)
            {
            min = ka_time[i];
            i_min = i;
            }

        closesocket(ka_sock[i_min]);
        ka_sock[i_min] = 0;
        i = i_min;

#ifdef DEBUG_CONN
        printf("## close connection %d\n", i_min);
#endif
        }

      i_conn = i;
      ka_sock[i_conn] = _sock;
      ka_time[i_conn] = (int) time(NULL);

      /* save remote host address */
      memcpy(&remote_addr[i_conn], &(acc_addr.sin_addr), sizeof(rem_addr));
      memcpy(&rem_addr, &(acc_addr.sin_addr), sizeof(rem_addr));

      phe = gethostbyaddr((char *) &rem_addr, 4, PF_INET);
      if (phe != NULL)
        strcpy(remote_host[i_conn], phe->h_name);
      else
        strcpy(remote_host[i_conn], (char *)inet_ntoa(rem_addr));

#ifdef DEBUG_CONN
      printf("## open new connection %d\n", i_conn);
#endif
      }

    else
      {
      /* check if open connection received data */
      for (i= 0 ; i<N_MAX_CONNECTION ; i++)
        if (ka_sock[i] > 0 && FD_ISSET(ka_sock[i], &readfds))
          break;

      if (i == N_MAX_CONNECTION)
        {
        _sock = 0;
        }
      else
        {
        i_conn = i;
        _sock = ka_sock[i_conn];
        ka_time[i_conn] = (int) time(NULL);
        memcpy(&rem_addr, &remote_addr[i_conn], sizeof(rem_addr));
        strcpy(rem_host, remote_host[i_conn]);

#ifdef DEBUG_CONN
        printf("## received request on connection %d\n", i_conn);
#endif
        }
      }

    /* turn off keep_alive by default */
    keep_alive = FALSE;

    if (_sock > 0)
      {
      memset(net_buffer, 0, sizeof(net_buffer));
      len = 0;
      header_length = 0;
      n_error = 0;
      do
        {
        FD_ZERO(&readfds);
        FD_SET(_sock, &readfds);

        timeout.tv_sec  = 6;
        timeout.tv_usec = 0;

        status = select(FD_SETSIZE, (void *) &readfds, NULL, NULL, (void *) &timeout);

        if (FD_ISSET(_sock, &readfds))
          i = recv(_sock, net_buffer+len, sizeof(net_buffer)-len, 0);
        else
          goto error;

        /* abort if connection got broken */
        if (i<0)
          goto error;

        if (i>0)
          len += i;

        /* check if net_buffer too small */
        if (len >= sizeof(net_buffer))
          {
          /* drain incoming remaining data */
          do
            {
            FD_ZERO(&readfds);
            FD_SET(_sock, &readfds);

            timeout.tv_sec  = 2;
            timeout.tv_usec = 0;

            status = select(FD_SETSIZE, (void *) &readfds, NULL, NULL, (void *) &timeout);

            if (FD_ISSET(_sock, &readfds))
              i = recv(_sock, net_buffer, sizeof(net_buffer), 0);
            else
              break;
            } while (i);

          memset(return_buffer, 0, sizeof(return_buffer));
          strlen_retbuf = 0;
          return_length = 0;

          show_error("Submitted attachment too large, please increase WEB_BUFFER_SIZE in elogd.c and recompile");
          send(_sock, return_buffer, strlen_retbuf+1, 0);
          keep_alive = 0;
          if (verbose)
            {
            printf("==== Return ================================\n");
            puts(return_buffer);
            printf("\n\n");
            }
          goto error;
          }

        if (i == 0)
          {
          n_error++;
          if (n_error == 100)
            goto error;
          }

        /* finish when empty line received */
        if (strstr(net_buffer, "GET") != NULL && strstr(net_buffer, "POST") == NULL)
          {
          if (len>4 && strcmp(&net_buffer[len-4], "\r\n\r\n") == 0)
            break;
          if (len>6 && strcmp(&net_buffer[len-6], "\r\r\n\r\r\n") == 0)
            break;
          }
        else if (strstr(net_buffer, "POST") != NULL)
          {
          if (header_length == 0)
            {
            /* extract logbook */
            strncpy(str, net_buffer+6, sizeof(str));
            if (strstr(str, "HTTP"))
              *(strstr(str, "HTTP")-1) = 0;
            strcpy(logbook, str);
            strcpy(logbook_enc, str);
            url_decode(logbook);

            /* extract header and content length */
            if (strstr(net_buffer, "Content-Length:"))
              content_length = atoi(strstr(net_buffer, "Content-Length:") + 15);
            else if (strstr(net_buffer, "Content-length:"))
              content_length = atoi(strstr(net_buffer, "Content-length:") + 15);

            boundary[0] = 0;
            if (strstr(net_buffer, "boundary="))
              {
              strncpy(boundary, strstr(net_buffer, "boundary=")+9, sizeof(boundary));
              if (strchr(boundary, '\r'))
                *strchr(boundary, '\r') = 0;
              }

            if (strstr(net_buffer, "\r\n\r\n"))
              header_length = (INT)strstr(net_buffer, "\r\n\r\n") - (INT)net_buffer + 4;

            if (strstr(net_buffer, "\r\r\n\r\r\n"))
              header_length = (INT)strstr(net_buffer, "\r\r\n\r\r\n") - (INT)net_buffer + 6;

            if (header_length)
              net_buffer[header_length-1] = 0;
            }

          if (header_length > 0 && len >= header_length+content_length)
            break;
          }
        else if (strstr(net_buffer, "HEAD") != NULL)
          {
          /* just return header */
          rsprintf("HTTP/1.1 200 OK\r\n");
          rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
          rsprintf("Connection: close\r\n");
          rsprintf("Content-Type: text/html\r\n\r\n");

          keep_alive = FALSE;
          return_length = strlen_retbuf+1;
          send(_sock, return_buffer, return_length, 0);

          goto error;
          }
        else if (strstr(net_buffer, "OPTIONS") != NULL)
          goto error;
        else
          {
          printf(net_buffer);
          goto error;
          }

        } while (1);

      if (!strchr(net_buffer, '\r'))
        goto error;

      /* initialize parametr array */
      initparam();

      /* extract cookies */
      if ((p = strstr(net_buffer, "Cookie:")) != NULL)
        {
        p += 6;
        do
          {
          p++;
          while (*p && *p == ' ')
            p++;
          strncpy(str, p, sizeof(str));

          for (i=0 ; i<(int)strlen(str) ; i++)
            if (str[i] == '=' || str[i] == ';')
              break;

          if (str[i] == '=')
            {
            str[i] = 0;
            p += i+1;
            for (i=0 ; *p && *p != ';' && *p != '\r' && *p != '\n' ; i++)
              cookie[i] = *p++;
            cookie[i] = 0;
            }
          else
            {
            /* empty cookie */
            str[i] = 0;
            cookie[0] = 0;
            p += i;
            }

          /* store cookie as parameter */
          setparam(str, cookie);
          } while (*p && *p == ';');
        }

      /* extract referer */
      referer[0] = 0;
      if ((p = strstr(net_buffer, "Referer:")) != NULL)
        {
        p += 9;
        while (*p && *p == ' ')
          p++;
        strncpy(referer, p, sizeof(referer));
        if (strchr(referer, '\r'))
          *strchr(referer, '\r') = 0;
        if (strchr(referer, '?'))
          *strchr(referer, '?') = 0;
        for (p=referer+strlen(referer)-1 ; p>referer && *p != '/' ; p--)
          *p = 0;
        }

      /* extract browser */
      browser[0] = 0;
      if ((p = strstr(net_buffer, "User-Agent:")) != NULL)
        {
        p += 11;
        while (*p && *p == ' ')
          p++;
        strncpy(browser, p, sizeof(browser));
        if (strchr(browser, '\r'))
          *strchr(browser, '\r') = 0;
        }

      memset(return_buffer, 0, sizeof(return_buffer));
      strlen_retbuf = 0;

      if (strncmp(net_buffer, "GET", 3) != 0 &&
          strncmp(net_buffer, "POST", 4) != 0)
        goto error;

      return_length = 0;

      /* extract logbook */
      p = strchr(net_buffer, '/')+1;
      logbook[0] = 0;
      for (i=0 ; *p && *p != '/' && *p != '?' && *p != ' '; i++)
        logbook[i] = *p++;
      logbook[i] = 0;
      strcpy(logbook_enc, logbook);
      url_decode(logbook);

      /* check for trailing '/' after logbook */
      if (strstr(net_buffer, "POST") == NULL) // fix for konqueror
        {
        if (logbook[0] && *p == ' ')
          {
          sprintf(str, "%s/", logbook_enc);
          redirect(str);
          goto redir;
          }
        }

      /* check for trailing '/' after logbook/ID */
      if (logbook[0] && *p == '/' && *(p+1) != ' ')
        {
        sprintf(url, "%s", logbook_enc);
        pd = url+strlen(url);

        while (*p && *p != ' ')
          *pd++ = *p++;
        *pd = 0;

        if (*(p-1) == '/')
          {
          sprintf(str, "Invalid URL: %s", url);
          show_error(str);
          send(_sock, return_buffer, strlen_retbuf+1, 0);
          keep_alive = 0;
          if (verbose)
            {
            printf("==== Return ================================\n");
            puts(return_buffer);
            printf("\n\n");
            }
          goto error;
          }
        }

      /* check if logbook exists */
      for (i=0 ; ; i++)
        {
        if (!enumgrp(i, str))
          break;
        if (equal_ustring(logbook, str))
          break;
        }

      if (strstr(logbook, ".gif") || strstr(logbook, ".jpg") ||
          strstr(logbook, ".jpg") || strstr(logbook, ".png") ||
          strstr(logbook, ".htm"))
        {
        /* serve file directly */
        strcpy(str, cfg_dir);
        strcat(str, logbook);
        send_file(str);
        send(_sock, return_buffer, return_length, 0);

        goto error;
        }
      else
        {
        if (!equal_ustring(logbook, str) && logbook[0])
          {
          if (verbose)
            printf("\n\n\n%s\n", net_buffer);

          sprintf(str, "Error: logbook \"%s\" not defined in elogd.cfg", logbook);
          show_error(str);
          send(_sock, return_buffer, strlen(return_buffer), 0);

          if (verbose)
            {
            printf("==== Return ================================\n");
            puts(return_buffer);
            printf("\n\n");
            }
          goto error;
          }
        }

      /* if no logbook is given and only one logbook defined, use this one */
      if (!logbook[0])
        {
        for (i=n=0 ; ; i++)
          {
          if (!enumgrp(i, str))
            break;
          if (!equal_ustring(str, "global"))
            n++;
          }

        if (n == 1)
          {
          if (verbose)
            printf("\n\n\n%s\n", net_buffer);

          strcpy(logbook, str);
          strcpy(logbook_enc, logbook);
          url_encode(logbook_enc);
          strcat(logbook_enc, "/");

          /* redirect to logbook, necessary to get optional cookies for that logbook */
          redirect(logbook_enc);

          send(_sock, return_buffer, strlen(return_buffer), 0);

          if (verbose)
            {
            printf("==== Return ================================\n");
            puts(return_buffer);
            printf("\n\n");
            }
          goto error;
          }
        }

      /* force re-read configuration file */
      if (cfgbuffer)
        {
        free(cfgbuffer);
        cfgbuffer = NULL;
        }

      /*---- check "hosts deny" ----*/

      authorized = 1;
      if (getcfg(logbook, "Hosts deny", list))
        {
        strcpy(rem_host_ip, (char *)inet_ntoa(rem_addr));

        n = strbreak(list, host_list, MAX_N_LIST);

        /* check if current connection matches anyone on the list */
        for (i=0 ; i<n ; i++)
          {
          if (equal_ustring(rem_host, host_list[i]) ||
              equal_ustring(rem_host_ip, host_list[i]) ||
              equal_ustring(host_list[i], "all"))
            {
            if (verbose)
              printf("Remote host \"%s\" matches \"%s\" in \"Hosts deny\". Access denied.\n",
                      equal_ustring(rem_host_ip, host_list[i]) ? rem_host_ip : rem_host,
                      host_list[i]);
            authorized = 0;
            break;
            }
          if (host_list[i][0] == '.')
            {
            if (strlen(rem_host) > strlen(host_list[i]) &&
                equal_ustring(host_list[i], rem_host+strlen(rem_host)-strlen(host_list[i])))
              {
              if (verbose)
                printf("Remote host \"%s\" matches \"%s\" in \"Hosts deny\". Access denied.\n",
                        rem_host, host_list[i]);
              authorized = 0;
              break;
              }
            }
          if (host_list[i][strlen(host_list[i])-1] == '.')
            {
            strcpy(str, rem_host_ip);
            if (strlen(str) > strlen(host_list[i]))
              str[strlen(host_list[i])] = 0;

            if (equal_ustring(host_list[i], str))
              {
              if (verbose)
                printf("Remote host \"%s\" matches \"%s\" in \"Hosts deny\". Access denied.\n",
                        rem_host_ip, host_list[i]);
              authorized = 0;
              break;
              }
            }
          }
        }

      /*---- check "hosts allow" ----*/

      if (getcfg(logbook, "Hosts allow", list))
        {
        strcpy(rem_host_ip, (char *)inet_ntoa(acc_addr.sin_addr));

        n = strbreak(list, host_list, MAX_N_LIST);

        /* check if current connection matches anyone on the list */
        for (i=0 ; i<n ; i++)
          {
          if (equal_ustring(rem_host, host_list[i]) ||
              equal_ustring(rem_host_ip, host_list[i]) ||
              equal_ustring(host_list[i], "all"))
            {
            if (verbose)
              printf("Remote host \"%s\" matches \"%s\" in \"Hosts allow\". Access granted.\n",
                      equal_ustring(rem_host_ip, host_list[i]) ? rem_host_ip : rem_host,
                      host_list[i]);
            authorized = 1;
            break;
            }
          if (host_list[i][0] == '.')
            {
            if (strlen(rem_host) > strlen(host_list[i]) &&
                equal_ustring(host_list[i], rem_host+strlen(rem_host)-strlen(host_list[i])))
              {
              if (verbose)
                printf("Remote host \"%s\" matches \"%s\" in \"Hosts allow\". Access granted.\n",
                        rem_host, host_list[i]);
              authorized = 1;
              break;
              }
            }
          if (host_list[i][strlen(host_list[i])-1] == '.')
            {
            strcpy(str, rem_host_ip);
            if (strlen(str) > strlen(host_list[i]))
              str[strlen(host_list[i])] = 0;

            if (equal_ustring(host_list[i], str))
              {
              if (verbose)
                printf("Remote host \"%s\" matches \"%s\" in \"Hosts allow\". Access granted.\n",
                        rem_host_ip, host_list[i]);
              authorized = 1;
              break;
              }
            }
          }
        }

      if (!authorized)
        {
        keep_alive = 0;
        goto error;
        }

      /* ask for password if configured */
      authorized = 1;
      if (getcfg(logbook, "Read Password", pwd))
        {
        authorized = 0;

        /* decode authorization */
        if (strstr(net_buffer, "Authorization:"))
          {
          p = strstr(net_buffer, "Authorization:")+14;
          if (strstr(p, "Basic"))
            {
            p = strstr(p, "Basic")+6;
            while (*p == ' ')
              p++;
            i = 0;
            while (*p && *p != ' ' && *p != '\r')
              str[i++] = *p++;
            str[i] = 0;
            }
          base64_decode(str, cl_pwd);
          if (strchr(cl_pwd, ':'))
            {
            p = strchr(cl_pwd, ':')+1;
            do_crypt(p, str);
            strcpy(cl_pwd, str);

            /* check authorization */
            if (strcmp(str, pwd) == 0)
              authorized = 1;
            }
          }
        }

      /* check for Keep-alive */
      if (strstr(net_buffer, "Keep-Alive") != NULL && use_keepalive)
        keep_alive = TRUE;

      if (!authorized)
        {
        /* return request for authorization */
        rsprintf("HTTP/1.1 401 Authorization Required\r\n");
        rsprintf("Server: ELOG HTTP %s\r\n", VERSION);
        rsprintf("WWW-Authenticate: Basic realm=\"%s\"\r\n", logbook);
        rsprintf("Connection: close\r\n");
        rsprintf("Content-Type: text/html\r\n\r\n");

        rsprintf("<HTML><HEAD>\r\n");
        rsprintf("<TITLE>401 Authorization Required</TITLE>\r\n");
        rsprintf("</HEAD><BODY>\r\n");
        rsprintf("<H1>Authorization Required</H1>\r\n");
        rsprintf("This server could not verify that you\r\n");
        rsprintf("are authorized to access the document\r\n");
        rsprintf("requested. Either you supplied the wrong\r\n");
        rsprintf("credentials (e.g., bad password), or your\r\n");
        rsprintf("browser doesn't understand how to supply\r\n");
        rsprintf("the credentials required.<P>\r\n");
        rsprintf("</BODY></HTML>\r\n");

        keep_alive = FALSE;
        }
      else
        {
        if (verbose)
          printf("\n\n\n%s\n", net_buffer);

        if (strncmp(net_buffer, "GET", 3) == 0)
          {
          /* extract path and commands */
          *strchr(net_buffer, '\r') = 0;

          if (!strstr(net_buffer, "HTTP"))
            goto error;
          *(strstr(net_buffer, "HTTP")-1)=0;

          /* strip logbook from path */
          p = net_buffer+5;
          for (i=0 ; *p && *p != '/' && *p != '?'; p++);
          while (*p && *p == '/')
            p++;

          /* decode command and return answer */
          decode_get(logbook, p);
          }
        else if (strncmp(net_buffer, "POST", 4) == 0)
          {
          if (verbose)
            printf("%s\n", net_buffer+header_length);
          decode_post(logbook, net_buffer+header_length, boundary, content_length);
          }
        else
          {
          net_buffer[50] = 0;
          sprintf(str, "Unknown request:<p>%s", net_buffer);
          show_error(str);
          }
        }

redir:
      if (return_length != -1)
        {
        if (return_length == 0)
          return_length = strlen_retbuf+1;

        if (keep_alive && strstr(return_buffer, "Content-Length") == NULL ||
            strstr(return_buffer, "Content-Length") >
            strstr(return_buffer, "\r\n\r\n"))
          {
          /*---- add content-length ----*/

          p = strstr(return_buffer, "\r\n\r\n");

          if (p != NULL)
            {
            length = strlen(p+4);

            header_length = (int) (p - return_buffer);
            memcpy(header_buffer, return_buffer, header_length);

            sprintf(header_buffer+header_length, "\r\nContent-Length: %d\r\n\r\n", length);

            send(_sock, header_buffer, strlen(header_buffer), 0);
            send(_sock, p+4, length, 0);

            if (verbose)
              {
              printf("==== Return ================================\n");
              puts(header_buffer);
              puts(p+2);
              printf("\n");
              }
            }
          else
            printf("Internal error, no valid header!\n");
          }
        else
          {
          send(_sock, return_buffer, return_length, 0);

          if (verbose)
            {
            printf("==== Return ================================\n");
            puts(return_buffer);
            printf("\n\n");
            }
          }
  error:

        if (!keep_alive)
          {
          closesocket(_sock);
          ka_sock[i_conn] = 0;

#ifdef DEBUG_CONN
          printf("## close connection %d\n", i_conn);
#endif
          }
        }
      }

    } while (!_abort);

  printf("Server aborted.\n");
}

/*------------------------------------------------------------------*/

void create_password(char *logbook, char *name, char *pwd)
{
int  fh, length, i;
char *cfgbuffer, str[256], *p;

  fh = open(cfg_file, O_RDONLY);
  if (fh < 0)
    {
    /* create new file */
    fh = open(cfg_file, O_CREAT | O_WRONLY, 0640);
    if (fh < 0)
      {
      printf("Cannot create \"%s\".\n", cfg_file);
      return;
      }
    sprintf(str, "[%s]\n%s=%s\n", logbook, name, pwd);
    write(fh, str, strlen(str));
    close(fh);
    printf("File \"%s\" created with password in logbook \"%s\".\n", cfg_file, logbook);
    return;
    }

  /* read existing file and add password */
  length = lseek(fh, 0, SEEK_END);
  lseek(fh, 0, SEEK_SET);
  cfgbuffer = malloc(length+1);
  if (cfgbuffer == NULL)
    {
    close(fh);
    return;
    }
  length = read(fh, cfgbuffer, length);
  cfgbuffer[length] = 0;
  close(fh);

  fh = open(cfg_file, O_TRUNC | O_WRONLY, 0640);

  sprintf(str, "[%s]", logbook);

  /* check if logbook exists already */
  if (strstr(cfgbuffer, str))
    {
    p = strstr(cfgbuffer, str);

    /* search password in current logbook */
    do
      {
      while (*p && *p != '\n')
        p++;
      if (*p && *p == '\n')
        p++;

      if (strncmp(p, name, strlen(name)) == 0)
        {
        /* replace existing password */
        i = (int) (p - cfgbuffer);
        write(fh, cfgbuffer, i);
        sprintf(str, "%s=%s\n", name, pwd);
        write(fh, str, strlen(str));

        printf("Password replaced in logbook \"%s\".\n", logbook);

        while (*p && *p != '\n')
          p++;
        if (*p && *p == '\n')
          p++;

        /* write remainder of file */
        write(fh, p, strlen(p));

        free(cfgbuffer);
        close(fh);
        return;
        }

      } while (*p && *p != '[');

    if (!*p || *p == '[')
      {
      /* enter password into current logbook */
      p = strstr(cfgbuffer, str);
      while (*p && *p != '\n')
        p++;
      if (*p && *p == '\n')
        p++;

      i = (int) (p - cfgbuffer);
      write(fh, cfgbuffer, i);
      sprintf(str, "%s=%s\n", name, pwd);
      write(fh, str, strlen(str));

      printf("Password added to logbook \"%s\".\n", logbook);

      /* write remainder of file */
      write(fh, p, strlen(p));

      free(cfgbuffer);
      close(fh);
      return;
      }
    }
  else /* write new logbook entry */
    {
    write(fh, cfgbuffer, strlen(cfgbuffer));
    sprintf(str, "\n[%s]\n%s=%s\n\n", logbook, name, pwd);
    write(fh, str, strlen(str));

    printf("Password added to new logbook \"%s\".\n", logbook);
    }

  free(cfgbuffer);
  close(fh);
}

/*------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
int    i, n, status, fh, tcp_port_cl;
int    daemon = FALSE;
char   read_pwd[80], write_pwd[80], admin_pwd[80], str[80], logbook[256],
       data_dir[256];
time_t now;
struct tm *tms;

  tzset();

  read_pwd[0] = write_pwd[0] = admin_pwd[0] = logbook[0] = 0;
  tcp_port_cl = 0;

  strcpy(cfg_file, "elogd.cfg");

  use_keepalive = TRUE;

  /* parse command line parameters */
  for (i=1 ; i<argc ; i++)
    {
    if (argv[i][0] == '-' && argv[i][1] == 'D')
      daemon = TRUE;
    else if (argv[i][0] == '-' && argv[i][1] == 'v')
      verbose = TRUE;
    else if (argv[i][0] == '-' && argv[i][1] == 'k')
      use_keepalive = FALSE;
    else if (argv[i][1] == 't')
      {
      time(&now);
      tms = localtime(&now);
      printf("Actual date/time: %02d%02d%02d_%02d%02d%02d\n",
             tms->tm_year % 100, tms->tm_mon+1, tms->tm_mday,
             tms->tm_hour, tms->tm_min, tms->tm_sec);
      return 0;
      }
    else if (argv[i][0] == '-')
      {
      if (i+1 >= argc || argv[i+1][0] == '-')
        goto usage;
      if (argv[i][1] == 'p')
        tcp_port_cl = atoi(argv[++i]);
      else if (argv[i][1] == 'c')
        strcpy(cfg_file, argv[++i]);
      else if (argv[i][1] == 'r')
        strcpy(read_pwd, argv[++i]);
      else if (argv[i][1] == 'w')
        strcpy(write_pwd, argv[++i]);
      else if (argv[i][1] == 'a')
        strcpy(admin_pwd, argv[++i]);
      else if (argv[i][1] == 'l')
        strcpy(logbook, argv[++i]);
      else if (argv[i][1] == 'h')
        strncpy(tcp_hostname, argv[++i], sizeof(tcp_hostname));
      else
        {
usage:
        printf("usage: %s [-p port] [-h hostname] [-D] [-c file] [-r pwd] [-w pwd] [-a pwd] [-l logbook]\n\n", argv[0]);
        printf("       -p <port> TCP/IP port\n");
        printf("       -h <hostname> TCP/IP hostname\n");
        printf("       -D become a daemon\n");
        printf("       -c <file> specify configuration file\n");
        printf("       -v debugging output\n");
        printf("       -r create/overwrite read password in config file\n");
        printf("       -w create/overwrite write password in config file\n");
        printf("       -a create/overwrite admin password in config file\n");
        printf("       -l <logbook> specify logbook for -r and -w commands\n\n");
        printf("       -k do not use keep-alive\n\n");
        return 0;
        }
      }
    }

  if (read_pwd[0])
    {
    if (!logbook[0])
      {
      printf("Must specify a lookbook via the -l parameter.\n");
      return 0;
      }
    do_crypt(read_pwd, str);
    create_password(logbook, "Read Password", str);
    return 0;
    }

  if (write_pwd[0])
    {
    if (!logbook[0])
      {
      printf("Must specify a lookbook via the -l parameter.\n");
      return 0;
      }
    do_crypt(write_pwd, str);
    create_password(logbook, "Write Password", str);
    return 0;
    }

  if (admin_pwd[0])
    {
    if (!logbook[0])
      {
      printf("Must specify a lookbook via the -l parameter.\n");
      return 0;
      }
    do_crypt(admin_pwd, str);
    create_password(logbook, "Admin Password", str);
    return 0;
    }

  /* extract directory from configuration file */
  if (cfg_file[0] && strchr(cfg_file, DIR_SEPARATOR))
    {
    strcpy(cfg_dir, cfg_file);
    for (i=strlen(cfg_dir)-1 ; i>0 ; i--)
      {
      if (cfg_dir[i] == DIR_SEPARATOR)
        break;
      cfg_dir[i] = 0;
      }
    }

  /* check for configuration file */
  fh = open(cfg_file, O_RDONLY | O_BINARY);
  if (fh < 0)
    {
    printf("Configuration file \"%s\" not found.\n", cfg_file);
    return 1;
    }
  close(fh);

  /* count logbooks */
  for (i=n=0 ;  ; i++)
    {
    if (!enumgrp(i, str))
      break;

    if (equal_ustring(str, "global"))
      continue;

    n++;
    }

  /* build logbook indices */
  lb_list = calloc(sizeof(LOGBOOK), n+1);
  for (i=n=0 ;  ; i++)
    {
    if (!enumgrp(i, logbook))
      break;

    if (equal_ustring(logbook, "global"))
      continue;

    strcpy(lb_list[n].name, logbook);
    strcpy(lb_list[n].name_enc, logbook);
    url_encode(lb_list[n].name_enc);

    /* get data dir from configuration file */
    getcfg(logbook, "Data dir", str);
    if (str[0] == DIR_SEPARATOR || str[1] == ':')
      strcpy(data_dir, str);
    else
      {
      strcpy(data_dir, cfg_dir);
      strcat(data_dir, str);
      }

    if (data_dir[strlen(data_dir)-1] != DIR_SEPARATOR)
      strcat(data_dir, DIR_SEPARATOR_STR);

    strcpy(lb_list[n].data_dir, data_dir);
    lb_list[n].el_index = NULL;

    printf("Indexing logbook \"%s\"...\n", logbook);
    status = el_build_index(&lb_list[n], FALSE);

    if (status == EL_EMPTY)
      printf("Found empty logbook \"%s\"\n", logbook);
    else if (status == EL_UPGRADE)
      {
      printf("Please upgrade data files in \"%s\" with the elconv program.\n", data_dir);
      return 1;
      }
    else if (status != EL_SUCCESS)
      {
      printf("Error generating index.\n");
      return 1;
      }

    n++;
    }

  /* get port from configuration file */
  if (tcp_port_cl != 0)
    tcp_port = tcp_port_cl;
  else
    {
    if (getcfg("global", "Port", str))
      tcp_port = atoi(str);
    }

  server_loop(tcp_port, daemon);

#ifdef OS_UNIX
  unlink("/var/run/elogd.pid");
#endif

  return 0;
}
