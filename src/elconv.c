/********************************************************************\

  Name:         elconv.c
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



  Contents:     Conversion program for ELOG messages

  $Id$

\********************************************************************/

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
#include <direct.h>
#else

#define OS_UNIX

#define TRUE 1
#define FALSE 0

#define DIR_SEPARATOR '/'
#define DIR_SEPARATOR_STR "/"

#define __USE_XOPEN             /* needed for crypt() */

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

#ifndef O_BINARY
#define O_BINARY 0
#endif
#endif

typedef int INT;

#define TELL(fh) lseek(fh, 0, SEEK_CUR)

#define NAME_LENGTH 256
#define SUCCESS       1
#define MAX_PATH_LENGTH 256

#define EL_SUCCESS    1
#define EL_FIRST_MSG  2
#define EL_LAST_MSG   3
#define EL_NO_MSG     4
#define EL_FILE_ERROR 5

#define MAX_GROUPS       32
#define MAX_PARAM       100
#define MAX_ATTACHMENTS  10
#define MAX_N_LIST      100
#define MAX_N_ATTR       50
#define VALUE_SIZE      256
#define PARAM_LENGTH    256
#define TEXT_SIZE     50000
#define MAX_PATH_LENGTH 256

char attr_list[MAX_N_ATTR][NAME_LENGTH];
char data_dir[256];
int verbose;

typedef struct {
   char v1_tag[16];
   int message_id;
   char in_reply_to[16];
   char reply[16];
} THREAD;

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

/*------------------------------------------------------------------*/

void el_decode(char *message, char *key, char *result)
{
   char *pc;

   if (result == NULL)
      return;

   *result = 0;

   if (strstr(message, key)) {
      for (pc = strstr(message, key) + strlen(key); *pc != '\n' && *pc != '\r';)
         *result++ = *pc++;
      *result = 0;
   }
}

/*------------------------------------------------------------------*/

/* Simplified copy of fnmatch() for Cygwin where fnmatch is not defined */

#define EOS '\0'

int fnmatch1(const char *pattern, const char *string)
{
   char c, test;

   for (;;)
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
         while ((test = *string) != EOS) {
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
    char  **plist           pointer to the lfile list

  Function value:
    int                     Number of files matching request

\********************************************************************/
{
   int i;

#ifdef OS_UNIX
   DIR *dir_pointer;
   struct dirent *dp;

   if ((dir_pointer = opendir(path)) == NULL)
      return 0;
   *plist = (char *) malloc(MAX_PATH_LENGTH);
   i = 0;
   for (dp = readdir(dir_pointer); dp != NULL; dp = readdir(dir_pointer)) {
      if (fnmatch1(pattern, dp->d_name) == 0) {
         *plist = (char *) realloc(*plist, (i + 1) * MAX_PATH_LENGTH);
         strncpy(*plist + (i * MAX_PATH_LENGTH), dp->d_name, strlen(dp->d_name));
         *(*plist + (i * MAX_PATH_LENGTH) + strlen(dp->d_name)) = '\0';
         i++;
         seekdir(dir_pointer, telldir(dir_pointer));
      }
   }
   closedir(dir_pointer);
#endif

#ifdef OS_WINNT
   HANDLE pffile;
   LPWIN32_FIND_DATA lpfdata;
   char str[255];
   int first;

   strcpy(str, path);
   strcat(str, "\\");
   strcat(str, pattern);
   first = 1;
   i = 0;
   lpfdata = malloc(sizeof(WIN32_FIND_DATA));
   *plist = (char *) malloc(MAX_PATH_LENGTH);
   pffile = FindFirstFile(str, lpfdata);
   if (pffile == INVALID_HANDLE_VALUE)
      return 0;
   first = 0;
   *plist = (char *) realloc(*plist, (i + 1) * MAX_PATH_LENGTH);
   strncpy(*plist + (i * MAX_PATH_LENGTH), lpfdata->cFileName, strlen(lpfdata->cFileName));
   *(*plist + (i * MAX_PATH_LENGTH) + strlen(lpfdata->cFileName)) = '\0';
   i++;
   while (FindNextFile(pffile, lpfdata)) {
      *plist = (char *) realloc(*plist, (i + 1) * MAX_PATH_LENGTH);
      strncpy(*plist + (i * MAX_PATH_LENGTH), lpfdata->cFileName, strlen(lpfdata->cFileName));
      *(*plist + (i * MAX_PATH_LENGTH) + strlen(lpfdata->cFileName)) = '\0';
      i++;
   }
   free(lpfdata);
#endif
   return i;
}

/*------------------------------------------------------------------*/

INT el_search_message(char *tag, int *fh, BOOL walk, BOOL first)
{
   int lfh, i, n, d, min, max, size, offset, direction, status, did_walk;
   struct tm *tms, ltms;
   time_t lt, ltime, lact;
   char str[256], file_name[256], dir[256];
   char *file_list, *tag_dir;

   did_walk = 0;
   ltime = lfh = 0;

   /* get data directory */
   strcpy(dir, data_dir);

   /* check tag for direction */
   direction = 0;
   tag_dir = strpbrk(tag, "+-");
   if (tag_dir) {
      direction = atoi(tag_dir);
      *tag_dir = 0;
   }

   /* if tag is given, open file directly */
   if (tag[0]) {
      /* extract time structure from tag */
      tms = &ltms;
      memset(tms, 0, sizeof(struct tm));
      tms->tm_year = (tag[0] - '0') * 10 + (tag[1] - '0');
      tms->tm_mon = (tag[2] - '0') * 10 + (tag[3] - '0') - 1;
      tms->tm_mday = (tag[4] - '0') * 10 + (tag[5] - '0');
      tms->tm_hour = 12;

      if (tms->tm_year < 90)
         tms->tm_year += 100;
      ltime = lt = mktime(tms);

      if (ltime < 0)
         return -1;

      strcpy(str, tag);
      if (strchr(str, '.')) {
         offset = atoi(strchr(str, '.') + 1);
         *strchr(str, '.') = 0;
      } else
         return -1;

      do {
         tms = localtime(&ltime);

         sprintf(file_name, "%s%02d%02d%02d.log", dir, tms->tm_year % 100, tms->tm_mon + 1, tms->tm_mday);
         lfh = open(file_name, O_RDWR | O_BINARY, 0644);

         if (lfh < 0) {
            if (!walk)
               return EL_FILE_ERROR;

            did_walk = 1;

            if (direction == -1)
               ltime -= 3600 * 24;      /* one day back */
            else
               ltime += 3600 * 24;      /* go forward one day */

            /* set new tag */
            tms = localtime(&ltime);
            sprintf(tag, "%02d%02d%02d.0", tms->tm_year % 100, tms->tm_mon + 1, tms->tm_mday);
         }

         /* in forward direction, stop today */
         if (direction != -1 && ltime > (time_t) (time(NULL) + 3600 * 24))
            break;

         /* in backward direction, go back 10 years */
         if (direction == -1 && abs((int) (lt - ltime)) > 3600 * 24 * 365 * 10)
            break;

      } while (lfh < 0);

      if (lfh < 0)
         return EL_FILE_ERROR;

      if (direction == -1 && did_walk)
         lseek(lfh, 0, SEEK_END);
      else
         lseek(lfh, offset, SEEK_SET);
   }

   /* open most recent file if no tag given */
   if (tag[0] == 0) {
      if (first) {
         /* go through whole directory, find first file */

         file_list = NULL;
         n = ss_file_find(dir, "??????.log", &file_list);
         if (n == 0) {
            if (file_list)
               free(file_list);
            return EL_FILE_ERROR;
         }

         for (i = 0, min = 9999999; i < n; i++) {
            d = atoi(file_list + i * MAX_PATH_LENGTH);
            if (d == 0)
               continue;

            if (d < 900000)
               d += 1000000;    /* last century */

            if (d < min)
               min = d;
         }
         free(file_list);
         sprintf(file_name, "%s%06d.log", dir, min % 1000000);
         lfh = open(file_name, O_RDWR | O_BINARY, 0644);
         if (lfh < 0)
            return EL_FILE_ERROR;

         /* remember tag */
         sprintf(tag, "%06d.0", min % 1000000);

         /* on tag "+1", don't go to next message */
         if (direction == 1)
            direction = 0;
      } else {
         /* go through whole directory, find last file */

         file_list = NULL;
         n = ss_file_find(dir, "??????.log", &file_list);
         if (n == 0) {
            if (file_list)
               free(file_list);
            return EL_NO_MSG;
         }

         for (i = 0, max = 0; i < n; i++) {
            d = atoi(file_list + i * MAX_PATH_LENGTH);
            if (d < 900000)
               d += 1000000;    /* last century */

            if (d > max)
               max = d;
         }
         free(file_list);
         sprintf(file_name, "%s%06d.log", dir, max % 1000000);
         lfh = open(file_name, O_RDWR | O_BINARY, 0644);
         if (lfh < 0)
            return EL_FILE_ERROR;

         lseek(lfh, 0, SEEK_END);

         /* remember tag */
         sprintf(tag, "%06d.%d", (int) (max % 1000000), (int) (TELL(lfh)));
      }
   }

   if (direction == -1) {
      /* seek previous message */

      if (TELL(lfh) == 0) {
         /* go back one day */
         close(lfh);

         lt = ltime;
         do {
            lt -= 3600 * 24;
            tms = localtime(&lt);
            sprintf(str, "%02d%02d%02d.0", tms->tm_year % 100, tms->tm_mon + 1, tms->tm_mday);

            status = el_search_message(str, &lfh, FALSE, FALSE);

         } while (status != SUCCESS && (INT) ltime - (INT) lt < 3600 * 24 * 365);

         if (status != EL_SUCCESS) {
            if (fh)
               *fh = lfh;
            else
               close(lfh);
            return EL_FIRST_MSG;
         }

         /* adjust tag */
         strcpy(tag, str);

         /* go to end of current file */
         lseek(lfh, 0, SEEK_END);
      }

      /* read previous message size */
      lseek(lfh, -17, SEEK_CUR);
      i = read(lfh, str, 17);
      if (i <= 0) {
         close(lfh);
         return EL_FILE_ERROR;
      }

      if (strncmp(str, "$End$: ", 7) == 0) {
         size = atoi(str + 7);
         lseek(lfh, -size, SEEK_CUR);
      } else {
         close(lfh);
         return EL_FILE_ERROR;
      }

      /* adjust tag */
      sprintf(strchr(tag, '.') + 1, "%d", (int) (TELL(lfh)));
   }

   if (direction == 1) {
      /* seek next message */

      /* read current message size */
      i = read(lfh, str, 15);
      if (i <= 0) {
         close(lfh);
         return EL_FILE_ERROR;
      }
      str[15] = 0;
      lseek(lfh, -15, SEEK_CUR);

      if (strncmp(str, "$Start$: ", 9) == 0) {
         size = atoi(str + 9);
         lseek(lfh, size, SEEK_CUR);
      } else {
         close(lfh);
         return EL_FILE_ERROR;
      }

      /* if EOF, goto next day */
      i = read(lfh, str, 15);
      if (i < 15) {
         close(lfh);
         time(&lact);

         lt = ltime;
         do {
            lt += 3600 * 24;
            tms = localtime(&lt);
            sprintf(str, "%02d%02d%02d.0", tms->tm_year % 100, tms->tm_mon + 1, tms->tm_mday);

            status = el_search_message(str, &lfh, FALSE, FALSE);

         } while (status != EL_SUCCESS && (INT) lt - (INT) lact < 3600 * 24);

         if (status != EL_SUCCESS) {
            if (fh)
               *fh = lfh;
            else
               close(lfh);
            return EL_LAST_MSG;
         }

         /* adjust tag */
         strcpy(tag, str);

         /* go to beginning of current file */
         lseek(lfh, 0, SEEK_SET);
      } else
         lseek(lfh, -15, SEEK_CUR);

      /* adjust tag */
      sprintf(strchr(tag, '.') + 1, "%d", (int) (TELL(lfh)));
   }

   if (fh)
      *fh = lfh;
   else
      close(lfh);

   return EL_SUCCESS;
}

/*------------------------------------------------------------------*/

INT el_submit(char attr_name[MAX_N_ATTR][NAME_LENGTH],
              char attr_value[MAX_N_ATTR][NAME_LENGTH],
              int n_attr, char *text, char *reply_to, char *encoding,
              char afilename[MAX_ATTACHMENTS][256],
              char *buffer[MAX_ATTACHMENTS], INT buffer_size[MAX_ATTACHMENTS], char *tag)
/********************************************************************\

  Routine: el_submit

  Purpose: Submit an ELog entry

  Input:
    char   attr_name[][]    Name of attributes
    char   attr_value[][]   Value of attributes
    int    n_attr           Number of attributes

    char   *text            Message text
    char   *reply_to        In reply to this message
    char   *encoding        Text encoding, either HTML or plain

    char   *afilename[]     File name of attachments
    char   *buffer[]        Attachment contents
    INT    *buffer_size[]   Size of attachment in bytes
    char   *tag             If given, edit existing message
    INT    *tag_size        Maximum size of tag

  Output:
    char   *tag             Message tag in the form YYMMDD.offset
    INT    *tag_size        Size of returned tag

  Function value:
    EL_SUCCESS              Successful completion

\********************************************************************/
{
   INT n, i, size, fh, status, index, offset, tail_size;
   struct tm *tms;
   char file_name[256], afile_name[MAX_ATTACHMENTS][256], dir[256],
       str[256], start_str[80], end_str[80], last[80], date[80], thread[80],
       attachment_all[64 * MAX_ATTACHMENTS];
   time_t now;
   char message[TEXT_SIZE + 100], *p;
   BOOL bedit;

   bedit = (tag[0] != 0);

   for (index = 0; index < MAX_ATTACHMENTS; index++) {
      /* generate filename for attachment */
      afile_name[index][0] = file_name[0] = 0;

      if (afilename[index][0] && buffer_size[index] == 0) {
         /* resubmission of existing attachment */
         strcpy(afile_name[index], afilename[index]);
      } else {
         if (afilename[index][0]) {
            /* strip directory, add date and time to filename */

            strcpy(file_name, afilename[index]);
            p = file_name;
            while (strchr(p, ':'))
               p = strchr(p, ':') + 1;
            while (strchr(p, '\\'))
               p = strchr(p, '\\') + 1; /* NT */
            while (strchr(p, '/'))
               p = strchr(p, '/') + 1;  /* Unix */

            /* assemble ELog filename */
            if (p[0]) {
               strcpy(dir, data_dir);

               time(&now);
               tms = localtime(&now);

               strcpy(str, p);
               sprintf(afile_name[index], "%02d%02d%02d_%02d%02d%02d_%s",
                       tms->tm_year % 100, tms->tm_mon + 1, tms->tm_mday, tms->tm_hour,
                       tms->tm_min, tms->tm_sec, str);
               sprintf(file_name, "%s%02d%02d%02d_%02d%02d%02d_%s", dir,
                       tms->tm_year % 100, tms->tm_mon + 1, tms->tm_mday, tms->tm_hour,
                       tms->tm_min, tms->tm_sec, str);

               /* save attachment */
               fh = open(file_name, O_CREAT | O_RDWR | O_BINARY, 0644);
               if (fh < 0) {
                  printf("Cannot write attachment file \"%s\"", file_name);
               } else {
                  write(fh, buffer[index], buffer_size[index]);
                  close(fh);
               }
            }
         }
      }
   }

   /* generate new file name YYMMDD.log in data directory */
   strcpy(dir, data_dir);

   offset = tail_size = 0;
   tms = NULL;
   p = NULL;
   if (bedit) {
      /* edit existing message */
      strcpy(str, tag);
      if (strchr(str, '.')) {
         offset = atoi(strchr(str, '.') + 1);
         *strchr(str, '.') = 0;
      }
      sprintf(file_name, "%s%s.log", dir, str);
      fh = open(file_name, O_CREAT | O_RDWR | O_BINARY, 0644);
      if (fh < 0)
         return -1;

      lseek(fh, offset, SEEK_SET);
      read(fh, str, 16);
      size = atoi(str + 9);
      read(fh, message, size);

      el_decode(message, "Date: ", date);
      el_decode(message, "Thread: ", thread);
      el_decode(message, "Attachment: ", attachment_all);

      /* buffer tail of logfile */
      lseek(fh, 0, SEEK_END);
      tail_size = TELL(fh) - (offset + size);

      if (tail_size > 0) {
         buffer = malloc(tail_size);
         if (buffer == NULL) {
            close(fh);
            return -1;
         }

         lseek(fh, offset + size, SEEK_SET);
         n = read(fh, buffer, tail_size);
      }
      lseek(fh, offset, SEEK_SET);
   } else {
      /* create new message */
      time(&now);
      tms = localtime(&now);

      sprintf(file_name, "%s%02d%02d%02d.log", dir, tms->tm_year % 100, tms->tm_mon + 1, tms->tm_mday);

      fh = open(file_name, O_CREAT | O_RDWR | O_BINARY, 0644);
      if (fh < 0)
         return -1;

      strcpy(date, ctime(&now));
      date[24] = 0;

      if (reply_to[0])
         sprintf(thread, "%16s %16s", reply_to, "0");
      else
         sprintf(thread, "%16s %16s", "0", "0");

      lseek(fh, 0, SEEK_END);
   }

   /* compose message */

   sprintf(message, "Date: %s\n", date);
   sprintf(message + strlen(message), "Thread: %s\n", thread);

   for (i = 0; i < n_attr; i++)
      sprintf(message + strlen(message), "%s: %s\n", attr_name[i], attr_value[i]);

   /* keep original attachment if edit and no new attachment */

   if (bedit) {
      for (i = n = 0; i < MAX_ATTACHMENTS; i++) {
         if (i == 0)
            p = strtok(attachment_all, ",");
         else if (p != NULL)
            p = strtok(NULL, ",");

         if (p && (afile_name[i][0])) {
            /* delete old attachment */
            strcpy(str, data_dir);
            strcat(str, p);
            remove(str);
         }

         if (afile_name[i][0]) {
            if (n == 0) {
               sprintf(message + strlen(message), "Attachment: %s", afile_name[i]);
               n++;
            } else
               sprintf(message + strlen(message), ",%s", afile_name[i]);
         }

         else if (p) {
            if (n == 0) {
               sprintf(message + strlen(message), "Attachment: %s", p);
               n++;
            } else
               sprintf(message + strlen(message), ",%s", p);
         }

      }
   } else {
      sprintf(message + strlen(message), "Attachment: %s", afile_name[0]);
      for (i = 1; i < MAX_ATTACHMENTS; i++)
         if (afile_name[i][0])
            sprintf(message + strlen(message), ",%s", afile_name[i]);
   }
   sprintf(message + strlen(message), "\n");

   sprintf(message + strlen(message), "Encoding: %s\n", encoding);
   sprintf(message + strlen(message), "========================================\n");
   strcat(message, text);

   size = 0;
   sprintf(start_str, "$Start$: %6d\n", size);
   sprintf(end_str, "$End$:   %6d\n\f", size);

   size = strlen(message) + strlen(start_str) + strlen(end_str);

   if (tag != NULL && !bedit)
      sprintf(tag, "%02d%02d%02d.%d", tms->tm_year % 100, tms->tm_mon + 1, tms->tm_mday, (int) (TELL(fh)));

   sprintf(start_str, "$Start$: %6d\n", size);
   sprintf(end_str, "$End$:   %6d\n\f", size);

   write(fh, start_str, strlen(start_str));
   write(fh, message, strlen(message));
   write(fh, end_str, strlen(end_str));

   if (bedit) {
      if (tail_size > 0) {
         n = write(fh, buffer, tail_size);
         free(buffer);
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
   if (reply_to[0] && !bedit) {
      strcpy(last, reply_to);
      do {
         status = el_search_message(last, &fh, FALSE, FALSE);
         if (status == EL_SUCCESS) {
            /* position to next thread location */
            lseek(fh, 72, SEEK_CUR);
            memset(str, 0, sizeof(str));
            read(fh, str, 16);
            lseek(fh, -16, SEEK_CUR);

            /* if no reply yet, set it */
            if (atoi(str) == 0) {
               sprintf(str, "%16s", tag);
               write(fh, str, 16);
               close(fh);
               break;
            } else {
               /* if reply set, find last one in chain */
               strcpy(last, strtok(str, " "));
               close(fh);
            }
         } else
            /* stop on error */
            break;

      } while (TRUE);
   }

   return EL_SUCCESS;
}

/*------------------------------------------------------------------*/

INT el_get_v1(char *tag, char *message, int *bufsize)
/********************************************************************\

  Routine: el_get_v1

  Purpose: Retrieve in ELog entry in format 1

  Input:
    char   *tag             tag in the form YYMMDD.offset
    int    size             Size of message buffer

  Output:
    char   *tag             tag of retrieved message
    char   *message         Message attributes and body

  Function value:
    EL_SUCCESS              Successful completion
    EL_NO_MSG               No message in log
    EL_LAST_MSG             Last message in log
    EL_FILE_ERROR           Internal error

\********************************************************************/
{
   int i, size, fh, search_status;
   char str[256];

   if (tag[0]) {
      search_status = el_search_message(tag, &fh, TRUE, FALSE);
      if (search_status != EL_SUCCESS)
         return search_status;
   } else {
      /* open most recent message */
      strcpy(tag, "-1");
      search_status = el_search_message(tag, &fh, TRUE, FALSE);
      if (search_status != EL_SUCCESS)
         return search_status;
   }

   /* extract message size */
   i = read(fh, str, 16);
   if (i <= 0) {
      close(fh);
      return EL_FILE_ERROR;
   }

   if (strncmp(str, "$Start$: ", 9) == 0)
      size = atoi(str + 9);
   else {
      close(fh);
      return EL_FILE_ERROR;
   }

   /* read message */
   memset(message, 0, *bufsize);
   read(fh, message, size);
   close(fh);

   *bufsize = size;

   return EL_SUCCESS;
}


/*------------------------------------------------------------------*/

void scan_messages()
{
   int size, status, fh, message_id, i, n, n_messages;
   char file_name[256], tag[256], str[256], last_file[256];
   char message[TEXT_SIZE + 1000];
   char *ps, *pd, *file_list;
   THREAD *thread_list;

   tag[0] = 0;
   message_id = 1;
   thread_list = malloc(sizeof(THREAD));

   /* search first message */
   status = el_search_message(tag, NULL, TRUE, TRUE);

   if (status == EL_FILE_ERROR) {
      printf("Cannot find any ??????.log file in this directory.\n");
      return;
   }

   /* delete previous files */
   file_list = NULL;
   getcwd(str, sizeof(str));
   n = ss_file_find(str, "??????a.log", &file_list);
   for (i = 0; i < n; i++)
      unlink(file_list + i * MAX_PATH_LENGTH);
   if (file_list)
      free(file_list);

   /* build thread_list */
   do {
      size = sizeof(message);
      status = el_get_v1(tag, message, &size);

      if (verbose)
         printf("Scan %s\n", tag);

      if (status == EL_LAST_MSG)
         break;

      strcpy(thread_list[message_id - 1].v1_tag, tag);
      thread_list[message_id - 1].message_id = message_id;

      /* extract thread */
      if (strstr(message, "Thread:")) {
         ps = strstr(message, "Thread:") + 7;
         while (*ps && !isdigit(*ps))
            ps++;

         pd = thread_list[message_id - 1].in_reply_to;
         while (isdigit(*ps) || ispunct(*ps))
            *pd++ = *ps++;
         *pd = 0;

         while (*ps && !isdigit(*ps))
            ps++;

         pd = thread_list[message_id - 1].reply;
         while (isdigit(*ps) || ispunct(*ps))
            *pd++ = *ps++;
         *pd = 0;
      }

      message_id++;
      strcat(tag, "+1");
      thread_list = realloc(thread_list, sizeof(THREAD) * message_id);

   } while (1);

   n_messages = message_id;

   /* convert messages */

   tag[0] = 0;
   last_file[0] = 0;
   message_id = 1;

   /* search first message */
   status = el_search_message(tag, NULL, TRUE, TRUE);

   do {
      size = sizeof(message);
      status = el_get_v1(tag, message, &size);

      if (status == EL_LAST_MSG)
         break;

      strcpy(str, tag);
      str[6] = 0;
      sprintf(file_name, "%s%sa.log", data_dir, str);

      if (verbose)
         printf("Converting %s -> %s, ID %d\n", tag, str, message_id);
      else {
         if (!equal_ustring(str, last_file)) {
            printf("Converting %s.log to %sa.log\n", str, str);
            strcpy(last_file, str);
         }
      }

      fh = open(file_name, O_CREAT | O_RDWR | O_BINARY, 0644);
      if (fh < 0) {
         printf("Error: Cannot open file %s for writing.\n", file_name);
         free(thread_list);
         return;
      }

      lseek(fh, 0, SEEK_END);

      /* write new message header */
      sprintf(str, "$@MID@$: %d\n", message_id);
      write(fh, str, strlen(str));

      /* write reply-to and in-reply-to */
      if (atoi(thread_list[message_id - 1].reply) > 0) {
         /* search id for reply */
         for (i = 0; i < n_messages; i++)
            if (strstr(thread_list[i].v1_tag, thread_list[message_id - 1].reply))
               break;

         if (i < n_messages) {
            sprintf(str, "Reply to: %d\n", thread_list[i].message_id);
            write(fh, str, strlen(str));
         }
      }

      if (atoi(thread_list[message_id - 1].in_reply_to) > 0) {
         /* search id for reply */
         for (i = 0; i < n_messages; i++)
            if (strstr(thread_list[i].v1_tag, thread_list[message_id - 1].in_reply_to))
               break;

         if (i < n_messages) {
            sprintf(str, "In reply to: %d\n", thread_list[i].message_id);
            write(fh, str, strlen(str));
         }
      }

      /* strip $end$ */
      if (strstr(message, "$End$"))
         *strstr(message, "$End$") = 0;

      if (message[strlen(message) - 1] != '\n')
         strcat(message, "\n");
      write(fh, message, strlen(message));

      close(fh);

      message_id++;
      strcat(tag, "+1");

   } while (1);

   free(thread_list);
}

/*------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
   int i;

   /* parse command line parameters */
   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'v')
         verbose = TRUE;
      else if (argv[i][0] == '-') {
         if (i + 1 >= argc || argv[i + 1][0] == '-')
            goto usage;
         else {
          usage:
            printf("usage: %s ", argv[0]);
            printf("       -v debugging output\n");
            return 0;
         }
      }
   }

   /* use current directory as working directory */
   getcwd(data_dir, sizeof(data_dir));
   strcat(data_dir, DIR_SEPARATOR_STR);

   if (verbose)
      printf("Scanning directory \"%s\"\n", data_dir);

   scan_messages();

   return 0;
}
