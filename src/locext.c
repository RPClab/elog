/********************************************************************\

  Name:         locext.c
  Created by:   Stefan Ritt

  Contents:     Extract all localization strings from elogd and put
                them into eloglang.xxxx

  $Log$
  Revision 1.1  2004/01/15 14:22:38  midas
  Initial revision


\********************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifdef _MSC_VER
#include <windows.h>
#include <io.h>
#else
#define O_BINARY 0
#include <unistd.h>
#endif

void read_buf(char *filename, char **buf)
{
   int fh, size, i;

   fh = open(filename, O_RDONLY | O_BINARY);
   if (fh < 0) {
      printf("Cannot open file \"%s\"\n", filename);
      exit(1);
   }

   size = lseek(fh, 0, SEEK_END);
   lseek(fh, 0, SEEK_SET);

   *buf = malloc(size);
   assert(*buf);

   i = read(fh, *buf, size);
   assert(i == size);
   close(fh);
}

/*------------------------------------------------------------------*/

int scan_file(char *infile, char *outfile)
{
   int fho, size;
   char *buf, *bufout, *p, *p2, str[1000], line[1000];

   read_buf(infile, &buf);

   p = buf;

   do {
      p = strstr(p, "loc(\"");
      if (!p)
         break;

      /* check that we did not find "malloc(" */
      if (isalpha(*(p-1))) {
         p++;
         continue;
      }

      p += 5;
      p2 = p;
      while (*p2) {
         if (*p2 == '"' && *(p2-1) != '\\')
            break;
         p2++;
      }
      
      size = (int)p2 - (int)p;
      if (size >= sizeof(str)) {
         printf("Error: string too long\n");
         free(buf);
         return 1;
      }

      memset(str, 0, sizeof(str));
      memcpy(str, p, size);

      /* convert \" to " */
      for (p2 = str ; *p2 ; p2++)
         if (*p2 == '\\')
            strcpy(p2, p2+1);

      /* check if string exists in output file */
      read_buf(outfile, &bufout);
      p2 = strstr(bufout, str);
      free(bufout);

      if (p2 == NULL) {
         /* append string to output file */
         fho = open(outfile, O_CREAT | O_WRONLY | O_APPEND | O_BINARY);
         if (fho < 0) {
            printf("Cannot open file \"%s\" for append\n", outfile);
            return 1;
         }

         sprintf(line, "%s = \r\n", str);
         write(fho, line, strlen(line));
         close(fho);

         printf("Added string: ");
         puts(str);
      }


   } while (1);

   free(buf);
   return 0;
}

/*------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
   if (argc != 3) {
      printf("Usage: %s <file.c> <language file>\n", argv[0]);
      return 1;
   }

   return scan_file(argv[1], argv[2]);
}