/********************************************************************\

  Name:         elog.c
  Created by:   Stefan Ritt
  Copyright 2000 + Stefan Ritt

  ELOG is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ELOG is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ELOG.  If not, see <http://www.gnu.org/licenses/>.


  Contents:     Electronic logbook utility

\********************************************************************/

#include "elog-version.h"
#include "git-revision.h"
const char *_git_revision = GIT_REVISION;


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

/* SSL includes */
#ifdef HAVE_SSL
#include <openssl/ssl.h>
#endif

#include "strlcpy.h"

typedef int INT;

#define MAX_ATTACHMENTS  50
#define NAME_LENGTH     500
#define MAX_N_ATTR       50

#define TEXT_SIZE    100000

int verbose;

char text[TEXT_SIZE], old_text[TEXT_SIZE], new_text[TEXT_SIZE];

/*------------------------------------------------------------------*/


const char *git_revision()
{
   const char *p = _git_revision;
   if (strrchr(p, '-'))
      p = strrchr(p, '-')+2;
   return p;
}

/*------------------------------------------------------------------*/

char *map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(unsigned char *s, unsigned char *d, int size)
{
   unsigned int t, pad;
   unsigned char *p;

   pad = 3 - strlen((char *) s) % 3;
   if (pad == 3)
      pad = 0;
   p = d;
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
      if (d - p >= size - 3)
         return;
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

char *sha256_crypt(const char *key, const char *salt);

void do_crypt(char *s, char *d, int size)
{
   strlcpy(d, sha256_crypt(s, "$5$") + 4, size);
}

/*-------------------------------------------------------------------*/

void stou(char *str)
/* convert all special characters to underscores in a string */
{
   int i;

   for (i = 0; i < (int) strlen(str); i++)
      if (str[i] == ' ' || str[i] == '.' || str[i] == '/' ||
          str[i] == '\\' || str[i] == '-' || str[i] == '(' || str[i] == ')')
         str[i] = '_';
}

/*------------------------------------------------------------------*/

void url_encode(char *ps, int size)
/********************************************************************\
Encode the given string in-place by adding %XX escapes
\********************************************************************/
{
   unsigned char *pd, *p;
   unsigned char str[NAME_LENGTH];

   pd = (unsigned char *) str;
   p = (unsigned char *) ps;
   while (*p && pd < str + 250) {
      if (strchr("%&=#?+", *p) || *p > 127) {
         sprintf((char *) pd, "%%%02X", *p);
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
   strlcpy(ps, (char *) str, size);
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

void add_crlf(char *buffer, int bufsize)
{
   char *p;
   char *tmpbuf;

   tmpbuf = (char *)malloc(bufsize);

   /* convert \n -> \r\n */
   p = buffer;
   while ((p = strstr(p, "\n")) != NULL) {

      if (p > buffer && *(p - 1) == '\r') {
         p++;
         continue;
      }

      if ((int) strlen(buffer) + 2 >= bufsize) {
         free(tmpbuf);
         return;
      }

      strlcpy(tmpbuf, p, bufsize);
      *(p++) = '\r';
      strlcpy(p, tmpbuf, bufsize - (p - buffer));
      p++;
   }

   free(tmpbuf);
}

/*------------------------------------------------------------------*/

void convert_crlf(char *buffer, int bufsize)
{
   char *p;

   /* convert '\n' -> \r\n */
   p = buffer;
   while ((p = strstr(p, "\\n")) != NULL) {

      if (p - buffer < bufsize - 2) {
         *(p++) = '\r';
         *(p++) = '\n';
      }
   }
}

/*------------------------------------------------------------------*/

int elog_connect(char *host, int port)
{
   int status, sock;
   struct hostent *phe;
   struct sockaddr_in bind_addr;

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

   return sock;
}

/*------------------------------------------------------------------*/

#ifdef HAVE_SSL
int ssl_connect(int sock, SSL ** ssl_con)
{
   SSL_METHOD *meth;
   SSL_CTX *ctx;
   X509 *cert = NULL;
   int i;
   
   SSL_library_init();
   SSL_load_error_strings();
   
   meth = (SSL_METHOD *) TLSv1_method();
   ctx = SSL_CTX_new(meth);
   
   *ssl_con = SSL_new(ctx);
   SSL_set_fd(*ssl_con, sock);
   if (SSL_connect(*ssl_con) <= 0)
      return -1;
   
   cert = SSL_get_peer_certificate(*ssl_con);
   if (cert == NULL)
      return -1;
   
   i = SSL_get_verify_result(*ssl_con);
   if (i != X509_V_OK)
      printf("Possibly invalid certificate, continue on your own risk!\n");
   
   return 0;
}
#endif

/*------------------------------------------------------------------*/

char request[100000], response[100000], *content;

INT retrieve_elog(char *host, int port, char *subdir, int ssl, char *experiment,
                  char *uname, char *upwd, int message_id,
                  char attrib_name[MAX_N_ATTR][NAME_LENGTH], char attrib[MAX_N_ATTR][NAME_LENGTH], char *text)
/********************************************************************\

  Routine: retrive_elog

  Purpose: Retrive an ELog entry for edit/reply

  Input:
    char   *host            Host name where ELog server runs
    int    port             ELog server port number
    char   *subdir          Subdirectoy to elog server
    int    ssl              Flag for using SSL layer
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
   int i, n, first, index, sock;
   char str[256], encrypted_passwd[256], *ph, *ps;
#ifdef HAVE_SSL
   SSL *ssl_con = NULL;
#endif

   if (ssl)                     /* avoid compiler warning */
      sock = 0;

   sock = elog_connect(host, port);
   if (sock < 0)
      return sock;

#ifdef HAVE_SSL
   if (ssl)
      if (ssl_connect(sock, &ssl_con) < 0) {
         printf("elogd server does not run SSL protocol\n");
         return -1;
      }
#endif

   /* compose request */
   strcpy(request, "GET /");
   strlcpy(str, experiment, sizeof(str));
   url_encode(str, sizeof(str));
   if (subdir[0] && experiment[0])
      sprintf(request + strlen(request), "%s/%s/%d?cmd=download", subdir, str, message_id);
   else if (subdir[0])
      sprintf(request + strlen(request), "%s/%d?cmd=download", subdir, message_id);
   else if (experiment[0])
      sprintf(request + strlen(request), "%s/%d?cmd=download", str, message_id);
   strcat(request, " HTTP/1.0\r\n");

   sprintf(request + strlen(request), "User-Agent: ELOG\r\n");

   first = 1;

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

      do_crypt(upwd, encrypted_passwd, sizeof(encrypted_passwd));
      sprintf(request + strlen(request), "upwd=%s;", encrypted_passwd);
   }

   /* finish cookie line */
   if (!first)
      strcat(request, "\r\n");

   strcat(request, "\r\n");

   /* send request */
#ifdef HAVE_SSL
   if (ssl)
      SSL_write(ssl_con, request, strlen(request));
   else
#endif
      send(sock, request, strlen(request), 0);
   if (verbose) {
      printf("Request sent to host:\n");
      puts(request);
   }

   /* receive response */
   memset(response, 0, sizeof(response));
#ifdef HAVE_SSL
   if (ssl)
      i = SSL_read(ssl_con, response, sizeof(response) - 1);
   else
#endif
      i = recv(sock, response, sizeof(response) - 1, 0);
   if (i < 0) {
      perror("Cannot receive response");
      return -1;
   }

   n = i;
   while (i > 0) {
#ifdef HAVE_SSL
      if (ssl)
         i = SSL_read(ssl_con, response + n, sizeof(response) - 1 - n);
      else
#endif
         i = recv(sock, response + n, sizeof(response) - 1 - n, 0);
      if (i > 0)
         n += i;
   }
   response[n] = 0;

#ifdef HAVE_SSL
   if (ssl) {
      SSL_shutdown(ssl_con);
      SSL_free(ssl_con);
   }
#endif

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
         if (strstr(response, "fail"))
            printf("Error: Invalid user name or password\n");
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

INT submit_elog(char *host, int port, int ssl, char *subdir, char *experiment,
                char *uname, char *upwd,
                int reply,
                int quote_on_reply,
                int edit,
                int download,
                int suppress,
                int encoding,
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
    int    ssl              SSL flag
    char   *subdir          Subdirectoy to elog server
    char   *uname           User name
    char   *upwd            User password
    int    reply            Reply to existing message
    int    edit             Edit existing message
    int    download         Download existing message
    int    suppress         Suppress Email notification
    int    encoding         0:ELCode,1:plain,2:HTML
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
   char host_name[256], boundary[80], str[80], encrypted_passwd[256], *p, *old_encoding;
   char old_attrib_name[MAX_N_ATTR+1][NAME_LENGTH], old_attrib[MAX_N_ATTR+1][NAME_LENGTH];
   struct hostent *phe;
#ifdef HAVE_SSL
   SSL *ssl_con = NULL;
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

   if (edit || download) {
      if (edit)
         status = retrieve_elog(host, port, subdir, ssl, experiment, uname, upwd, edit,
                                old_attrib_name, old_attrib, old_text);
      else
         status = retrieve_elog(host, port, subdir, ssl, experiment, uname, upwd, download,
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
   
   if (download) {
      if (strstr(response, "$@MID@$:"))
         printf("%s", strstr(response, "$@MID@$:"));
      else
         printf("%s", response);
      return 1;
   }

   if (reply) {
      status =
          retrieve_elog(host, port, subdir, ssl, experiment, uname, upwd, reply,
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
         if (equal_ustring(old_attrib_name[i], "Reply to") || equal_ustring(old_attrib_name[i], "Date")) {
            attrib_name[i][0] = 0;
            attrib[i][0] = 0;
         } else {
            strlcpy(attrib_name[i], old_attrib_name[i], NAME_LENGTH);
            strlcpy(attrib[i], old_attrib[i], NAME_LENGTH);
         }
      }

      n_attr = i;

      /* check encoding */
      old_encoding = "plain";

      for (i = 0; i < n_attr; i++)
         if (equal_ustring(attrib_name[i], "encoding"))
            break;

      if (i < n_attr)
         old_encoding = attrib[i];

      if (quote_on_reply) {
         strlcpy(new_text, text, sizeof(new_text));

         /* precede old text with "> " */
         text[0] = 0;
         p = old_text;

         do {
            if (strchr(p, '\n')) {
               *strchr(p, '\n') = 0;

               if (old_encoding[0] == 'H') {
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
               if (old_encoding[0] == 'H') {
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
   }

   sock = elog_connect(host, port);
   if (sock < 0)
      return sock;

#ifdef HAVE_SSL
   if (ssl)
      if (ssl_connect(sock, &ssl_con) < 0) {
         printf("elogd server does not run SSL protocol\n");
         return -1;
      }
#endif

   content_length = 100000;
   for (i = 0; i < MAX_ATTACHMENTS; i++)
      if (afilename[i][0])
         content_length += buffer_size[i];
   content = (char *)malloc(content_length);
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
      do_crypt(upwd, encrypted_passwd, sizeof(encrypted_passwd));
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"upwd\"\r\n\r\n%s\r\n", boundary,
              encrypted_passwd);
   }

   if (experiment[0])
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"exp\"\r\n\r\n%s\r\n", boundary, experiment);

   if (reply)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"reply_to\"\r\n\r\n%d\r\n", boundary, reply);

   if (edit) {
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"edit_id\"\r\n\r\n%d\r\n", boundary, edit);
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"skiplock\"\r\n\r\n1\r\n", boundary);
   }

   if (suppress)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"suppress\"\r\n\r\n1\r\n", boundary);

   if (encoding == 0)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"encoding\"\r\n\r\nELCode\r\n", boundary);
   else if (encoding == 1)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"encoding\"\r\n\r\nplain\r\n", boundary);
   else if (encoding == 2)
      sprintf(content + strlen(content),
              "%s\r\nContent-Disposition: form-data; name=\"encoding\"\r\n\r\nHTML\r\n", boundary);

   for (i = 0; i < n_attr; i++) {
      strcpy(str, attrib_name[i]);
      if (str[0]) {
         stou(str);
         sprintf(content + strlen(content),
                 "%s\r\nContent-Disposition: form-data; name=\"%s\"\r\n\r\n%s\r\n", boundary, str, attrib[i]);
      }
   }

   if (text[0])
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
   if (port != 80)
      sprintf(str, "%s:%d", host, port);
   else
      sprintf(str, "%s", host);
   sprintf(request + strlen(request), "Host: %s\r\n", str);
   sprintf(request + strlen(request), "User-Agent: ELOG\r\n");
   sprintf(request + strlen(request), "Content-Length: %d\r\n", content_length);

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
#ifdef HAVE_SSL
   if (ssl)
      SSL_write(ssl_con, request, header_length);
   else
#endif
      send(sock, request, header_length, 0);
   if (verbose) {
      printf("Request sent to host:\n");
      puts(request);
   }

   /* send content */
#ifdef HAVE_SSL
   if (ssl)
      SSL_write(ssl_con, content, content_length);
   else
#endif
      send(sock, content, content_length, 0);
   if (verbose) {
      printf("Content sent to host:\n");
      puts(content);
   }

   /* receive response */
   memset(response, 0, sizeof(response));
#ifdef HAVE_SSL
   if (ssl)
      i = SSL_read(ssl_con, response, sizeof(response) - 1);
   else
#endif
      i = recv(sock, response, sizeof(response) - 1, 0);
   if (i < 0) {
      perror("Cannot receive response");
      return -1;
   }

   /* discard remainder of response */
   n = i;
   while (i > 0) {
#ifdef HAVE_SSL
      if (ssl)
         i = SSL_read(ssl_con, response + n, sizeof(response) - 1 - n);
      else
#endif
         i = recv(sock, response + n, sizeof(response) - 1 - n, 0);
      if (i > 0)
         n += i;
   }
   response[n] = 0;

#ifdef HAVE_SSL
   if (ssl) {
      SSL_shutdown(ssl_con);
      SSL_free(ssl_con);
   }
#endif

   closesocket(sock);

   if (verbose) {
      printf("Response received:\n");
      puts(response);
   }

   /* check response status */
   if (strstr(response, "302 Found")) {
      if (strstr(response, "Location:")) {
         if (strstr(response, "has moved"))
            printf("Error: elogd server has moved to another location\n");
         else if (strstr(response, "fail"))
            printf("Error: Invalid user name or password\n");
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
   else if (strstr(response, "Error: Attribute")) {
      if (strstr(response, "not existing")) {
         strncpy(str, strstr(response, "Error: Attribute") + 27, sizeof(str));
         if (strchr(str, '<'))
            *strchr(str, '<') = 0;
         printf("Error: Non existing attribute option \"%s\"\n", str);
      } else {
         strncpy(str, strstr(response, "Error: Attribute") + 20, sizeof(str));
         if (strchr(str, '<'))
            *strchr(str, '<') = 0;
         printf("Error: Missing required attribute \"%s\"\n", str);
      }
   }
   else if (strstr(response, "form name=form1"))
      printf("Error: Missing or invalid user name/password\n");
   else
      printf("Error transmitting message\n");

   return 1;
}

/*------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
   char str[1000], uname[80], upwd[80];
   char host_name[256], logbook[32], textfile[256], subdir[256];
   char *buffer[MAX_ATTACHMENTS], attachment[MAX_ATTACHMENTS][256];
   INT att_size[MAX_ATTACHMENTS];
   INT i, n, fh, n_att, n_attr, port, reply, quote_on_reply, edit, download, encoding, suppress, size, ssl,
       text_flag;
   char attr_name[MAX_N_ATTR][NAME_LENGTH], attrib[MAX_N_ATTR][NAME_LENGTH];

   text[0] = textfile[0] = uname[0] = upwd[0] = suppress = quote_on_reply = 0;
   host_name[0] = logbook[0] = subdir[0] = 0;
   n_att = n_attr = reply = edit = download = encoding = 0;
   port = 80;
   ssl = 0;
   text_flag = 0;

   for (i = 0; i < MAX_ATTACHMENTS; i++) {
      attachment[i][0] = 0;
      buffer[i] = NULL;
      att_size[i] = 0;
   }

   /* parse command line parameters */
   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'v')
         verbose = 1;
      else if (argv[i][0] == '-' && argv[i][1] == 's')
         ssl = 1;
      else if (argv[i][0] == '-' && argv[i][1] == 'q')
         quote_on_reply = 1;
      else if (argv[i][0] == '-' && argv[i][1] == 'x')
         suppress = 1;
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
            else if (argv[i][1] == 'd')
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
            else if (argv[i][1] == 'w') {
               if (argv[i+1][0] == 'l')
                  download = -1;
               else
                  download = atoi(argv[++i]);
            } else if (argv[i][1] == 'n')
               encoding = atoi(argv[++i]);
            else if (argv[i][1] == 'm') {
               strcpy(textfile, argv[++i]);
               text_flag = 1;
            } else {
             usage:
               printf("%s ", ELOGID);
               printf("revision %s\n", git_revision());
               printf("\nusage: elog\n");
               printf("elog -h <hostname> [-p port] [-d subdir]\n");
               printf("                              Location where elogd is running\n");
               printf("     -l logbook/experiment    Name of logbook or experiment\n");
               printf("     -s                       Use SSL for communication\n");
               printf("     [-v]                     For verbose output\n");
               printf("     [-u username password]   Wser name and password\n");
               printf("     [-f <attachment>]        (up to %d attachments)\n", MAX_ATTACHMENTS);
               printf("     -a <attribute>=<value>   (up to %d attributes)\n", MAX_N_ATTR);
               printf("     [-r <id>]                Reply to existing message\n");
               printf("     [-q]                     Quote original text on reply\n");
               printf("     [-e <id>]                Edit existing message\n");
               printf("     [-w <id>|last]           Download existing message (last message)\n");
               printf("     [-x]                     Suppress email notification\n");
               printf("     [-n 0|1|2]               Encoding: 0:ELcode,1:plain,2:HTML\n");
               printf("     -m <textfile>] | <text>\n");
               printf("\nArguments with blanks must be enclosed in quotes\n");
               printf("The elog message can either be submitted on the command line, piped in like\n");
               printf("\"cat text | elog -h ... -l ... -a ...\" or in a file with the -m flag.\n");
               printf("Multiple attributes and attachments can be supplied\n");
               return 1;
            }
         } else {
            strcpy(text, argv[i]);
            convert_crlf(text, sizeof(text));
            text_flag = 1;
         }
      }
   }

#ifndef HAVE_SSL
   if (ssl) {
      printf("SLL support not compiled into this program\n");
      return 1;
   }
#endif

#if defined( _MSC_VER )
   {
      WSADATA WSAData;

      /* Start windows sockets */
      if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
         return -1;
   }
#endif

   if (host_name[0] == 0) {
      printf("Please specify hostname.\n");
      return 1;
   }

   if (logbook[0] == 0) {
      printf("Please specify logbook with the \"-l\" flag.\n");
      return 1;
   }

   if (n_attr == 0 && !edit && !reply && !download) {
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

      size = (INT) lseek(fh, 0, SEEK_END);
      lseek(fh, 0, SEEK_SET);

      if (size > (INT) (sizeof(text) - 1)) {
         printf("Message file \"%s\" is too long (%zd bytes max).\n", textfile, sizeof(text));
         return 1;
      }

      i = read(fh, text, size);

      if (i < size) {
         printf("Cannot fully read message from file %s.\n", textfile);
         return 1;
      }

      close(fh);
   }

   if (text_flag == 0 && !edit && !download) {
      /* read from stdin */

      n = 0;

      do {
         i = getchar();

         text[n++] = i;

      } while (i != EOF);

      if (n > 0)
         text[n - 1] = 0;
   }

   /* change CR -> CRLF for unix text files */
   add_crlf(text, sizeof(text));

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

      buffer[i] = (char *)malloc(att_size[i] + 1);

      n = read(fh, buffer[i], att_size[i]);
      if (n < att_size[i]) {
         printf("Cannot fully read attachment file \"%s\".\n", attachment[i]);
         return 1;
      }
      buffer[i][n] = 0;

      close(fh);
   }

   /* now submit message */
   submit_elog(host_name, port, ssl, subdir, logbook,
               uname, upwd, reply, quote_on_reply, edit, download, suppress, encoding, attr_name, attrib, n_attr, text,
               attachment, buffer, att_size);

   for (i = 0; i < MAX_ATTACHMENTS; i++)
      if (buffer[i])
         free(buffer[i]);

   return 0;
}
