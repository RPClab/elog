/********************************************************************\

  Name:         elog.c
  Created by:   Stefan Ritt

  Contents:     Electronic logbook utility

  $Log$
  Revision 1.23  2005/01/15 17:05:09  midas
  Changed comment

  Revision 1.22  2004/11/02 16:46:55  midas
  Added -H flag for HTML submit

  Revision 1.21  2004/09/18 04:42:46  midas
  Fixed bug with not displaying inline images

  Revision 1.20  2004/03/28 10:41:05  midas
  Fixed problem with logbooks containing blanks

  Revision 1.19  2004/03/26 08:28:29  midas
  Version 2.5.2

  Revision 1.18  2004/03/25 19:47:48  midas
  Fixed problem with attributes containing spaces

  Revision 1.17  2004/03/14 16:43:29  midas
  Implemented option 'guest display'

  Revision 1.16  2004/02/19 08:18:31  midas
  Changed '-p' for email suppress to '-x'

  Revision 1.15  2004/02/17 11:17:03  midas
  Fixed compiler warnings

  Revision 1.14  2004/02/13 20:58:21  midas
  Changed email suppression flag from '-s' to '-p'

  Revision 1.13  2004/01/07 11:14:53  midas
  Changed line length

  Revision 1.12  2004/01/06 13:21:34  midas
  Changed indent style

  Revision 1.11  2003/11/11 12:31:34  midas
  Added '-s' flag for email suppression

  Revision 1.10  2003/07/15 12:17:45  midas
  Removed BOOL

  Revision 1.9  2003/07/15 12:17:13  midas
  Removed FALSE/TRUE

  Revision 1.8  2003/07/15 12:16:52  midas
  Removed FALSE/TRUE

  Revision 1.7  2003/07/15 11:19:45  midas
  Added -e flag, reply now quotes original text

  Revision 1.6  2003/06/25 15:25:13  midas
  Fixed bug with 'reply_to'

  Revision 1.5  2003/06/05 07:16:36  midas
  Creat boundary randomly

  Revision 1.4  2003/06/04 14:26:59  midas
  elog utility can read text from stdin

  Revision 1.3  2003/06/03 13:18:00  midas
  Fixed bug in base64_encode

  Revision 1.2  2003/03/01 16:07:02  midas
  Show error if wrong username/password

  Revision 1.1  2003/01/30 14:45:07  midas
  Moved files to src/ subdirectory

  Revision 1.10  2002/10/14 08:26:26  midas
  Made attachment size variable

  Revision 1.9  2002/08/02 11:01:34  midas
  Added -r for replies

  Revision 1.8  2002/07/23 11:31:08  midas
  Fixed problems with password cookie

  Revision 1.7  2002/07/08 08:39:38  midas
  Fixed return code

  Revision 1.6  2002/06/12 07:52:41  midas
  Increased text size

  Revision 1.5  2002/06/11 12:01:45  midas
  Added -s for subdirectory

  Revision 1.4  2002/02/25 15:28:01  midas
  Require -l flag, output better error messages

  Revision 1.3  2001/12/21 15:28:51  midas
  Initial version as separate package, corresponds to V1.3.2


\********************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#ifdef _MSC_VER
#include <windows.h>
#include <io.h>
#else
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#define closesocket(s) close(s)
#ifndef O_BINARY
#define O_BINARY 0
#endif
#endif

typedef int INT;

#define MAX_ATTACHMENTS  50
#define NAME_LENGTH     500
#define MAX_N_ATTR       50

#define TEXT_SIZE    100000

int verbose;

char text[TEXT_SIZE], old_text[TEXT_SIZE], new_text[TEXT_SIZE];

/*------------------------------------------------------------------*/

char *map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(char *s, char *d)
{
   unsigned int t, pad;

   pad = 3 - strlen(s) % 3;
   if (pad == 3)
      pad = 0;
   while (*s) {
      t = (*s++) << 16;
      if (*s)
         t |= (*s++) << 8;
      if (*s)
         t |= (*s++) << 0;

      *(d + 3) = map[t & 63];
      t >>= 6;
      *(d + 2) = map[t & 63];
      t >>= 6;
      *(d + 1) = map[t & 63];
      t >>= 6;
      *(d + 0) = map[t & 63];

      d += 4;
   }
   *d = 0;
   while (pad--)
      *(--d) = '=';
}

/*---- string comparison -------------------------------------------*/

int equal_ustring(char *str1, char *str2)
{
   if (str1 == NULL && str2 != NULL)
      return 0;
   if (str1 != NULL && str2 == NULL)
      return 0;
   if (str1 == NULL && str2 == NULL)
      return 1;

   while (*str1)
      if (toupper(*str1++) != toupper(*str2++))
         return 0;

   if (*str2)
      return 0;

   return 1;
}

/*---- strlcpy and strlcat to avoid buffer overflow ----------------*/

/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless size == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
size_t strlcpy(char *dst, const char *src, size_t size)
{
   char *d = dst;
   const char *s = src;
   size_t n = size;

   /* Copy as many bytes as will fit */
   if (n != 0 && --n != 0) {
      do {
         if ((*d++ = *s++) == 0)
            break;
      } while (--n != 0);
   }

   /* Not enough room in dst, add NUL and traverse rest of src */
   if (n == 0) {
      if (size != 0)
         *d = '\0';             /* NUL-terminate dst */
      while (*s++);
   }

   return (s - src - 1);        /* count does not include NUL */
}

/*
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless size <= strlen(dst)).
 * Returns strlen(src) + MIN(size, strlen(initial dst)).
 * If retval >= size, truncation occurred.
 */
size_t strlcat(char *dst, const char *src, size_t size)
{
   char *d = dst;
   const char *s = src;
   size_t n = size;
   size_t dlen;

   /* Find the end of dst and adjust bytes left but don't go past end */
   while (n-- != 0 && *d != '\0')
      d++;
   dlen = d - dst;
   n = size - dlen;

   if (n == 0)
      return (dlen + strlen(s));
   while (*s != '\0') {
      if (n != 1) {
         *d++ = *s;
         n--;
      }
      s++;
   }
   *d = '\0';

   return (dlen + (s - src));   /* count does not include NUL */
}

/*-------------------------------------------------------------------*/

void btou(char *str)
/* convert all blanks to underscores in a string */
{
   int i;

   for (i = 0; i < (int) strlen(str); i++)
      if (str[i] == ' ')
         str[i] = '_';
}

/*------------------------------------------------------------------*/

void url_encode(char *ps, int size)
/********************************************************************\
Encode the given string in-place by adding %XX escapes
\********************************************************************/
{
   unsigned char *pd, *p, str[NAME_LENGTH];

   pd = str;
   p = ps;
   while (*p && (int) pd < (int) str + 250) {
      if (strchr("%&=#?+", *p) || *p > 127) {
         sprintf(pd, "%%%02X", *p);
         pd += 3;
         p++;
      } else if (*p == ' ') {
         *pd++ = '+';
         p++;
      } else {
         *pd++ = *p++;
      }
   }
   *pd = '\0';
   strlcpy(ps, str, size);
}

/*------------------------------------------------------------------*/

void sgets(char *string, int size)
{
   char *p;

   do {
      p = fgets(string, size, stdin);
   } while (p == NULL);

   if (strlen(p) > 0 && p[strlen(p) - 1] == '\n')
      p[strlen(p) - 1] = 0;
}

/*------------------------------------------------------------------*/

char request[100000], response[100000], *content;

INT retrieve_elog(char *host, int port, char *subdir, char *experiment,
                  char *passwd, char *uname, char *upwd, int message_id,
                  char attrib_name[MAX_N_ATTR][NAME_LENGTH], char attrib[MAX_N_ATTR][NAME_LENGTH], char *text)
/********************************************************************\

  Routine: retrive_elog

  Purpose: Retrive an ELog entry for edit/reply

  Input:
    char   *host            Host name where ELog server runs
    in     port             ELog server port number
    char   *subdir          Subdirectoy to elog server
    char   *passwd          Write password
    char   *uname           User name
    char   *upwd            User password
    int    message_id       Message to retrieve
    char   *attrib_name     Attribute names
    char   *attrib          Attribute values
    char   *text            Message text

  Function value:
    EL_SUCCESS              Successful completion

\********************************************************************/
{
   int status, sock, i, n, first, index;
   struct hostent *phe;
   struct sockaddr_in bind_addr;
   char host_name[256], str[80], *ph, *ps;

#if defined( _MSC_VER )
   {
      WSADATA WSAData;

      /* Start windows sockets */
      if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
         return -1;
   }
#endif

   /* get local host name */
   gethostname(host_name, sizeof(host_name));

   phe = gethostbyname(host_name);
   if (phe == NULL) {
      perror("Cannot retrieve host name");
      return -1;
   }
   phe = gethostbyaddr(phe->h_addr, sizeof(int), AF_INET);
   if (phe == NULL) {
      perror("Cannot retrieve host name");
      return -1;
   }

   /* if domain name is not in host name, hope to get it from phe */
   if (strchr(host_name, '.') == NULL)
      strcpy(host_name, phe->h_name);

   /* create socket */
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("cannot create socket");
      return -1;
   }

   /* compose remote address */
   memset(&bind_addr, 0, sizeof(bind_addr));
   bind_addr.sin_family = AF_INET;
   bind_addr.sin_addr.s_addr = 0;
   bind_addr.sin_port = htons((unsigned short) port);

   phe = gethostbyname(host);
   if (phe == NULL) {
      perror("cannot get host name");
      return -1;
   }
   memcpy((char *) &(bind_addr.sin_addr), phe->h_addr, phe->h_length);

   /* connect to server */
   status = connect(sock, (void *) &bind_addr, sizeof(bind_addr));
   if (status != 0) {
      printf("Cannot connect to host %s, port %d\n", host, port);
      return -1;
   }

   if (verbose)
      printf("Successfully connected to host %s, port %d\n", host, port);

   /* compose request */
   strcpy(request, "GET /");
   if (subdir[0])
      sprintf(request + strlen(request), "%s/%d?cmd=download", subdir, message_id);
   if (experiment[0])
      sprintf(request + strlen(request), "%s/%d?cmd=download", experiment, message_id);
   strcat(request, " HTTP/1.0\r\n");

   sprintf(request + strlen(request), "Host: %s\r\n", host_name);
   sprintf(request + strlen(request), "User-Agent: ELOG\r\n");

   first = 1;
   if (passwd[0]) {
      if (first)
         sprintf(request + strlen(request), "Cookie: ");
      first = 0;

      base64_encode(passwd, str);
      sprintf(request + strlen(request), "wpwd=%s;", str);
   }

   if (uname[0]) {
      if (first)
         sprintf(request + strlen(request), "Cookie: ");
      first = 0;

      sprintf(request + strlen(request), "unm=%s;", uname);
   }

   if (upwd[0]) {
      if (first)
         sprintf(request + strlen(request), "Cookie: ");
      first = 0;

      base64_encode(upwd, str);
      sprintf(request + strlen(request), "upwd=%s;", str);
   }

   /* finish cookie line */
   if (!first)
      strcat(request, "\r\n");

   strcat(request, "\r\n");

   /* send request */
   send(sock, request, strlen(request), 0);
   if (verbose) {
      printf("Request sent to host:\n");
      puts(request);
   }

   /* receive response */
   i = recv(sock, response, sizeof(response), 0);
   if (i < 0) {
      perror("Cannot receive response");
      return -1;
   }

   n = i;
   while (i > 0) {
      i = recv(sock, response + n, sizeof(response) - n, 0);
      if (i > 0)
         n += i;
   }
   response[n] = 0;

   closesocket(sock);

   if (verbose) {
      printf("Response received:\n");
      puts(response);
   }

   /* check response status */
   if (strstr(response, "$@MID@$:")) {
      /* separate attributes and message */

      ph = strstr(response, "========================================\n");

      /* skip first line */
      ps = strstr(response, "$@MID@$:");
      while (*ps && *ps != '\n')
         ps++;
      while (*ps && (*ps == '\n' || *ps == '\r'))
         ps++;

      for (index = 0; index < MAX_N_ATTR; index++) {
         if (ps >= ph)
            break;

         strlcpy(attrib_name[index], ps, NAME_LENGTH);
         if (strchr(attrib_name[index], ':'))
            *(strchr(attrib_name[index], ':')) = 0;

         ps += strlen(attrib_name[index]) + 2;
         strlcpy(attrib[index], ps, NAME_LENGTH);

         for (i = 0; i < NAME_LENGTH; i++) {
            if (attrib[index][i] == '\r' || attrib[index][i] == '\n')
               attrib[index][i] = 0;

            if (attrib[index][i] == 0)
               break;
         }

         ps += strlen(attrib[index]);
         while (*ps && (*ps == '\n' || *ps == '\r'))
            ps++;
      }

      attrib_name[index][0] = 0;
      attrib[index][0] = 0;

      ph = strchr(ph, '\n') + 1;
      if (*ph == '\r')
         ph++;

      strlcpy(text, ph, TEXT_SIZE);

      return 1;
   }

   if (strstr(response, "302 Found")) {
      if (strstr(response, "Location:")) {
         if (strstr(response, "wpwd"))
            printf("Error: Invalid password\n");
         else if (strstr(response, "wusr"))
            printf("Error: Invalid user name\n");
         else {
            strncpy(str, strstr(response, "Location:") + 10, sizeof(str));
            if (strchr(str, '?'))
               *strchr(str, '?') = 0;
            if (strchr(str, '\n'))
               *strchr(str, '\n') = 0;
            if (strchr(str, '\r'))
               *strchr(str, '\r') = 0;

            if (strrchr(str, '/'))
               printf("Message successfully transmitted, ID=%s\n", strrchr(str, '/') + 1);
            else
               printf("Message successfully transmitted, ID=%s\n", str);
         }
      }
   } else if (strstr(response, "Logbook Selection"))
      printf("Error: No logbook specified\n");
   else if (strstr(response, "enter password"))
      printf("Error: Missing or invalid password\n");
   else if (strstr(response, "form name=form1"))
      printf("Error: Missing or invalid user name/password\n");
   else
      printf("Error transmitting message\n");

   return 0;
}

/*------------------------------------------------------------------*/

INT submit_elog(char *host, int port, char *subdir, char *experiment,
                char *passwd,
                char *uname, char *upwd,
                int reply,
                int edit,
                int suppress,
                int html,
                char attrib_name[MAX_N_ATTR][NAME_LENGTH],
                char attrib[MAX_N_ATTR][NAME_LENGTH],
                int n_attr,
                char *text, char afilename[MAX_ATTACHMENTS][256],
                char *buffer[MAX_ATTACHMENTS], INT buffer_size[MAX_ATTACHMENTS])
/********************************************************************\

  Routine: submit_elog

  Purpose: Submit an ELog entry

  Input:
    char   *host            Host name where ELog server runs
    in     port             ELog server port number
    char   *subdir          Subdirectoy to elog server
    char   *passwd          Write password
    char   *uname           User name
    char   *upwd            User password
    int    reply            Reply to existing message
    int    edit             Edit existing message
    int    suppress         Suppress Email notification
    int    html             Submit as HTML
    char   *attrib_name     Attribute names
    char   *attrib          Attribute values
    char   *text            Message text

    char   afilename[]      File names of attachments
    char   *buffer[]        Attachment contents
    INT    buffer_size[]    Size of buffer in bytes

  Function value:
    EL_SUCCESS              Successful completion

\********************************************************************/
{
   int status, sock, i, n, header_length, content_length, index;
   struct hostent *phe;
   struct sockaddr_in bind_addr;
   char host_name[256], boundary[80], str[80], *encoding, *p;
   char old_attrib_name[MAX_N_ATTR][NAME_LENGTH], old_attrib[MAX_N_ATTR][NAME_LENGTH];

#if defined( _MSC_VER )
   {
      WSADATA WSAData;

      /* Start windows sockets */
      if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
         return -1;
   }
#endif

   if (edit) {
      status =
          retrieve_elog(host, port, subdir, experiment, passwd, uname, upwd, edit,
                        old_attrib_name, old_attrib, old_text);

      if (status != 1)
         return status;

      /* update attributes */
      for (index = 0; index < n_attr; index++) {
         for (i = 0; i < MAX_N_ATTR && old_attrib_name[i][0]; i++)
            if (equal_ustring(attrib_name[index], old_attrib_name[i]))
               break;

         if (old_attrib_name[i][0])
            strlcpy(old_attrib[i], attrib[index], NAME_LENGTH);
      }

      /* copy attributes */
      for (i = 0; i < MAX_N_ATTR && old_attrib_name[i][0]; i++) {
         strlcpy(attrib_name[i], old_attrib_name[i], NAME_LENGTH);
         strlcpy(attrib[i], old_attrib[i], NAME_LENGTH);
      }

      n_attr = i;

      if (text[0] == 0)
         strlcpy(text, old_text, TEXT_SIZE);
   }

   if (reply) {
      status =
          retrieve_elog(host, port, subdir, experiment, passwd, uname, upwd, reply,
                        old_attrib_name, old_attrib, old_text);

      if (status != 1)
         return status;

      /* update attributes */
      for (index = 0; index < n_attr; index++) {
         for (i = 0; i < MAX_N_ATTR && old_attrib_name[i][0]; i++)
            if (equal_ustring(attrib_name[index], old_attrib_name[i]))
               break;

         if (old_attrib_name[i][0])
            strlcpy(old_attrib[i], attrib[index], NAME_LENGTH);
      }

      /* copy attributes */
      for (i = 0; i < MAX_N_ATTR && old_attrib_name[i][0]; i++) {
         strlcpy(attrib_name[i], old_attrib_name[i], NAME_LENGTH);
         strlcpy(attrib[i], old_attrib[i], NAME_LENGTH);
      }

      n_attr = i;

      /* check encoding */
      encoding = "plain";

      for (i = 0; i < n_attr; i++)
         if (equal_ustring(attrib_name[i], "encoding"))
            break;

      if (i < n_attr)
         encoding = attrib[i];

      strlcpy(new_text, text, sizeof(new_text));

      /* precede old text with "> " */
      text[0] = 0;
      p = old_text;

      do {
         if (strchr(p, '\n')) {
            *strchr(p, '\n') = 0;

            if (encoding[0] == 'H') {
               strlcat(text, "> ", TEXT_SIZE);
               strlcat(text, p, TEXT_SIZE);
               strlcat(text, "<br>\n", TEXT_SIZE);
            } else {
               strlcat(text, "> ", TEXT_SIZE);
               strlcat(text, p, TEXT_SIZE);
               strlcat(text, "\n", TEXT_SIZE);
            }

            p += strlen(p) + 1;
            if (*p == '\n')
               p++;
         } else {
            if (encoding[0] == 'H') {
               strlcat(text, "> ", TEXT_SIZE);
               strlcat(text, p, TEXT_SIZE);
               strlcat(text, "<p>\n", TEXT_SIZE);
            } else {
               strlcat(text, "> ", TEXT_SIZE);
               strlcat(text, p, TEXT_SIZE);
               strlcat(text, "\n\n", TEXT_SIZE);
            }

            break;
         }

      } while (1);

      strlcat(text, new_text, TEXT_SIZE);
   }

   /* get local host name */
   gethostname(host_name, sizeof(host_name));

   phe = gethostbyname(host_name);
   if (phe == NULL) {
      perror("Cannot retrieve host name");
      return -1;
   }
   phe = gethostbyaddr(phe->h_addr, sizeof(int), AF_INET);
   if (phe == NULL) {
      perror("Cannot retrieve host name");
      return -1;
   }

   /* if domain name is not in host name, hope to get it from phe */
   if (strchr(host_name, '.') == NULL)
      strcpy(host_name, phe->h_name);

   /* create socket */
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("cannot create socket");
      return -1;
   }

   /* compose remote address */
   memset(&bind_addr, 0, sizeof(bind_addr));
   bind_addr.sin_family = AF_INET;
   bind_addr.sin_addr.s_addr = 0;
   bind_addr.sin_port = htons((unsigned short) port);

   phe = gethostbyname(host);
   if (phe == NULL) {
      perror("cannot get host name");
      return -1;
   }
   memcpy((char *) &(bind_addr.sin_addr), phe->h_addr, phe->h_length);

   /* connect to server */
   status = connect(sock, (void *) &bind_addr, sizeof(bind_addr));
   if (status != 0) {
      printf("Cannot connect to host %s, port %d\n", host, port);
      return -1;
   }

   if (verbose)
      printf("Successfully connected to host %s, port %d\n", host, port);

   content_length = 100000;
   for (i = 0; i < MAX_ATTACHMENTS; i++)
      if (afilename[i][0])
         content_length += buffer_size[i];
   content = malloc(content_length);
   if (content == NULL) {
      printf("Not enough memory\n");
      return -1;
   }

   /* compose content */
   srand((unsigned) time(NULL));
   sprintf(boundary, "---------------------------%04X%04X%04X", rand(), rand(), rand());
   strcpy(content, boundary);
   strcat(content, "\r\nContent-Disposition: form-data; name=\"cmd\"\r\n\r\nSubmit\r\n");

   if (uname[0])
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"unm\"\r\n\r\n%s\r\n", boundary, uname);

   if (upwd[0]) {
      base64_encode(upwd, str);
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"upwd\"\r\n\r\n%s\r\n", boundary, str);
   }

   if (experiment[0])
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"exp\"\r\n\r\n%s\r\n", boundary, experiment);

   if (reply)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"reply_to\"\r\n\r\n%d\r\n", boundary, reply);

   if (edit)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"edit_id\"\r\n\r\n%d\r\n", boundary, edit);

   if (suppress)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"suppress\"\r\n\r\n1\r\n", boundary);

   if (html)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"html\"\r\n\r\n1\r\n", boundary);

   for (i = 0; i < n_attr; i++) {
      strcpy(str, attrib_name[i]);
      btou(str);
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"%s\"\r\n\r\n%s\r\n", boundary, str, attrib[i]);
   }

   sprintf(content + strlen(content),
           "%s\r\nContent-Disposition: form-data; name=\"Text\"\r\n\r\n%s\r\n%s\r\n",
           boundary, text, boundary);

   content_length = strlen(content);
   p = content + content_length;

   for (i = 0; i < MAX_ATTACHMENTS; i++)
      if (afilename[i][0]) {
         sprintf(p,
                 "Content-Disposition: form-data; name=\"attfile%d\"; filename=\"%s\"\r\n\r\n",
                 i + 1, afilename[i]);

         content_length += strlen(p);
         p += strlen(p);
         memcpy(p, buffer[i], buffer_size[i]);
         p += buffer_size[i];
         strcpy(p, boundary);
         strcat(p, "\r\n");

         content_length += buffer_size[i] + strlen(p);
         p += strlen(p);
      }

   /* compose request */
   strcpy(request, "POST /");
   if (subdir[0])
      sprintf(request + strlen(request), "%s/", subdir);
   if (experiment[0]) {
      strcpy(str, experiment);
      url_encode(str, sizeof(str));
      sprintf(request + strlen(request), "%s/", str);
   }
   strcat(request, " HTTP/1.0\r\n");

   sprintf(request + strlen(request), "Content-Type: multipart/form-data; boundary=%s\r\n", boundary);
   sprintf(request + strlen(request), "Host: %s\r\n", host_name);
   sprintf(request + strlen(request), "User-Agent: ELOG\r\n");
   sprintf(request + strlen(request), "Content-Length: %d\r\n", content_length);

   if (passwd[0]) {
      base64_encode(passwd, str);
      sprintf(request + strlen(request), "Cookie: wpwd=%s\r\n", str);
   }

   strcat(request, "\r\n");

   header_length = strlen(request);

   /*
      {
      FILE *f;
      f = fopen("elog.log", "w");
      fwrite(request, header_length+content_length, 1, f);
      fclose(f);
      }
    */

   /* send request */
   send(sock, request, header_length, 0);
   if (verbose) {
      printf("Request sent to host:\n");
      puts(request);
   }

   /* send content */
   send(sock, content, content_length, 0);
   if (verbose)
      printf("Content sent to host.\n");

   /* receive response */
   i = recv(sock, response, 10000, 0);
   if (i < 0) {
      perror("Cannot receive response");
      return -1;
   }

   /* discard remainder of response */
   n = i;
   while (i > 0) {
      i = recv(sock, response + n, 10000, 0);
      if (i > 0)
         n += i;
   }
   response[n] = 0;

   closesocket(sock);

   if (verbose) {
      printf("Response received:\n");
      puts(response);
   }

   /* check response status */
   if (strstr(response, "302 Found")) {
      if (strstr(response, "Location:")) {
         if (strstr(response, "wpwd"))
            printf("Error: Invalid password\n");
         else if (strstr(response, "wusr"))
            printf("Error: Invalid user name\n");
         else {
            strncpy(str, strstr(response, "Location:") + 10, sizeof(str));
            if (strchr(str, '?'))
               *strchr(str, '?') = 0;
            if (strchr(str, '\n'))
               *strchr(str, '\n') = 0;
            if (strchr(str, '\r'))
               *strchr(str, '\r') = 0;

            if (strrchr(str, '/'))
               printf("Message successfully transmitted, ID=%s\n", strrchr(str, '/') + 1);
            else
               printf("Message successfully transmitted, ID=%s\n", str);
         }
      } else
         printf("Message successfully transmitted\n");
   } else if (strstr(response, "Logbook Selection"))
      printf("Error: No logbook specified\n");
   else if (strstr(response, "enter password"))
      printf("Error: Missing or invalid password\n");
   else if (strstr(response, "form name=form1"))
      printf("Error: Missing or invalid user name/password\n");
   else if (strstr(response, "Error: Attribute")) {
      strncpy(str, strstr(response, "Error: Attribute") + 20, sizeof(str));
      if (strchr(str, '<'))
         *strchr(str, '<') = 0;
      printf("Error: Missing required attribute \"%s\"\n", str);
   } else
      printf("Error transmitting message\n");

   return 1;
}

/*------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
   char str[1000], uname[80], upwd[80];
   char host_name[256], logbook[32], textfile[256], password[80], subdir[256];
   char *buffer[MAX_ATTACHMENTS], attachment[MAX_ATTACHMENTS][256];
   INT att_size[MAX_ATTACHMENTS];
   INT i, n, fh, n_att, n_attr, size, port, reply, edit, suppress, html;
   char attr_name[MAX_N_ATTR][NAME_LENGTH], attrib[MAX_N_ATTR][NAME_LENGTH];

   text[0] = textfile[0] = uname[0] = upwd[0] = suppress = 0;
   host_name[0] = logbook[0] = password[0] = subdir[0] = 0;
   n_att = n_attr = reply = edit = html = 0;
   port = 80;

   for (i = 0; i < MAX_ATTACHMENTS; i++) {
      attachment[i][0] = 0;
      buffer[i] = NULL;
      att_size[i] = 0;
   }

   /* parse command line parameters */
   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'v')
         verbose = 1;
      else if (argv[i][0] == '-' && argv[i][1] == 'x')
         suppress = 1;
      else if (argv[i][0] == '-' && argv[i][1] == 'H')
         html = 1;
      else {
         if (argv[i][0] == '-') {
            if (i + 1 >= argc || argv[i + 1][0] == '-')
               goto usage;
            if (argv[i][1] == 'h')
               strcpy(host_name, argv[++i]);
            else if (argv[i][1] == 'p')
               port = atoi(argv[++i]);
            else if (argv[i][1] == 'l')
               strcpy(logbook, argv[++i]);
            else if (argv[i][1] == 'w')
               strcpy(password, argv[++i]);
            else if (argv[i][1] == 's')
               strcpy(subdir, argv[++i]);
            else if (argv[i][1] == 'u') {
               strcpy(uname, argv[++i]);
               strcpy(upwd, argv[++i]);
            } else if (argv[i][1] == 'a') {
               strcpy(str, argv[++i]);
               if (strchr(str, '=')) {
                  strcpy(attrib[n_attr], strchr(str, '=') + 1);
                  *strchr(str, '=') = 0;
                  strcpy(attr_name[n_attr], str);
                  n_attr++;
               } else {
                  printf("Error: Attributes must be supplied in the form \"-a <attribute>=<value>\".\n");
                  return 1;
               }
            } else if (argv[i][1] == 'f')
               strcpy(attachment[n_att++], argv[++i]);
            else if (argv[i][1] == 'r')
               reply = atoi(argv[++i]);
            else if (argv[i][1] == 'e')
               edit = atoi(argv[++i]);
            else if (argv[i][1] == 'm')
               strcpy(textfile, argv[++i]);
            else {
             usage:
               printf("\nusage: elog\n");
               printf("           -h <hostname> [-p port] [-s subdir]\n");
               printf("                                    Location where elogd is running\n");
               printf("           -l logbook/experiment    Name of logbook or experiment\n");
               printf("           [-v]                     for verbose output\n");
               printf("           [-w password]            write password defined on server\n");
               printf("           [-u username password]   user name and password\n");
               printf("           [-f <attachment>]        (up to %d times)\n", MAX_ATTACHMENTS);
               printf("           -a <attribute>=<value>   (up to %d times)\n", MAX_N_ATTR);
               printf("           [-r <id>]                Reply to existing message\n");
               printf("           [-e <id>]                Edit existing message\n");
               printf("           [-x]                     Suppress email notification\n");
               printf("           [-H]                     Submit entry in HTML format\n");
               printf("           -m <textfile>] | <text>\n");
               printf("\nArguments with blanks must be enclosed in quotes\n");
               printf("The elog message can either be submitted on the command line, piped in like\n");
               printf("\"cat text | elog -h ... -l ... -a ...\" or in a file with the -m flag.\n");
               printf("Multiple attributes and attachments can be supplied\n");
               return 1;
            }
         } else
            strcpy(text, argv[i]);
      }
   }

   if (host_name[0] == 0) {
      printf("Please specify hostname.\n");
      return 1;
   }

   if (logbook[0] == 0) {
      printf("Please specify logbook with the \"-l\" flag.\n");
      return 1;
   }

   if (n_attr == 0 && !edit && !reply) {
      printf("Please specify attribute(s) with the \"-a\" flag.\n");
      return 1;
   }

   fh = -1;

   if (textfile[0]) {
      fh = open(textfile, O_RDONLY | O_BINARY);
      if (fh < 0) {
         printf("Message file \"%s\" does not exist.\n", textfile);
         return 1;
      }

      size = lseek(fh, 0, SEEK_END);
      lseek(fh, 0, SEEK_SET);

      if (size > (int) sizeof(text) - 1) {
         printf("Message file \"%s\" is too long (%d bytes max).\n", textfile, sizeof(text));
         return 1;
      }

      i = read(fh, text, size);

      if (i < size) {
         printf("Cannot fully read message from file %s.\n", textfile);
         return 1;
      }

      close(fh);
   }

   if (text[0] == 0 && textfile[0] == 0 && !edit) {
      /* read from stdin */

      n = 0;

      do {
         i = getchar();

         text[n++] = i;

      } while (i != EOF);

      if (n > 0)
         text[n - 1] = 0;
   }

   /*---- open attachment file ----*/

   for (i = 0; i < MAX_ATTACHMENTS; i++) {
      if (!attachment[i][0])
         break;

      fh = open(attachment[i], O_RDONLY | O_BINARY);
      if (fh < 0) {
         printf("Attachment file \"%s\" does not exist.\n", attachment[i]);
         return 1;
      }

      att_size[i] = lseek(fh, 0, SEEK_END);
      lseek(fh, 0, SEEK_SET);

      buffer[i] = malloc(att_size[i] + 1);

      n = read(fh, buffer[i], att_size[i]);
      if (n < att_size[i]) {
         printf("Cannot fully read attachment file \"%s\".\n", attachment[i]);
         return 1;
      }
      buffer[i][n] = 0;

      close(fh);
   }

   /* now submit message */
   submit_elog(host_name, port, subdir, logbook, password,
               uname, upwd, reply, edit, suppress, html, attr_name, attrib, n_attr, text,
               attachment, buffer, att_size);

   for (i = 0; i < MAX_ATTACHMENTS; i++)
      if (buffer[i])
         free(buffer[i]);

   return 0;
}
