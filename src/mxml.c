/********************************************************************\

   Name:         mxml.c
   Created by:   Stefan Ritt

   Contents:     Midas XML Library

   $Log$
   Revision 1.4  2005/03/03 15:36:05  ritt
   Fixed compiler warnings

   Revision 1.3  2005/03/03 15:34:21  ritt
   Implemented mxml_debug_tree()

   Revision 1.2  2005/03/01 23:55:43  ritt
   Fixed compiler warnings

   Revision 1.1  2005/03/01 23:48:18  ritt
   Implemented MXML for password file

\********************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER

#include <windows.h>
#include <io.h>
#include <time.h>

#else

#define TRUE 1
#define FALSE 0

typedef int BOOL;

#define O_TEXT 0
#define O_BINARY 0

#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>

#endif

#include "mxml.h"

/*------------------------------------------------------------------*/

/* should come from midas.c, elogd.c etc. */
extern size_t strlcpy(char *dst, const char *src, size_t size);
extern size_t strlcat(char *dst, const char *src, size_t size);

/*------------------------------------------------------------------*/

MXML_WRITER *mxml_open_document(const char *file_name) 
/* open a file and write XML header */
{
   char str[256], line[1000];
   time_t now;
   MXML_WRITER *writer;

   writer = malloc(sizeof(MXML_WRITER));

   writer->fh = open(file_name, O_WRONLY | O_CREAT | O_TRUNC | O_TEXT, 0644);

   if (writer->fh == -1) {
      sprintf(line, "Unable to open file \"%s\": ", file_name);
      perror(line);
      free(writer);
      return NULL;
   }

   /* write XML header */
   strcpy(line, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
   write(writer->fh, line, strlen(line));
   time(&now);
   strcpy(str, ctime(&now));
   str[24] = 0;
   sprintf(line, "<!-- created by MXML on %s -->\n", str);
   write(writer->fh, line, strlen(line));

   /* initialize stack */
   writer->level = 0;
   writer->element_is_open = 0;

   return writer;
}

/*------------------------------------------------------------------*/

void mxml_encode(char *src, int size)
/* convert '<' '>' '&' '"' ''' into &xx; */
{
   char *dst, *ps, *pd;

   assert(size);
   dst = (char*) malloc(size);
   ps = src;
   pd = dst;
   for (ps = src ; *ps && (size_t)pd - (size_t)dst < (size_t)(size-10) ; ps++) {
      switch (*ps) {
      case '<':
         strcpy(pd, "&lt;");
         pd += 4;
         break;
      case '>':
         strcpy(pd, "&gt;");
         pd += 4;
         break;
      case '&':
         strcpy(pd, "&amp;");
         pd += 5;
         break;
      case '\"':
         strcpy(pd, "&quot;");
         pd += 6;
         break;
      case '\'':
         strcpy(pd, "&apos;");
         pd += 6;
         break;
      default:
         *pd++ = *ps;
      }
   }
   *pd = 0;

   strlcpy(src, dst, size);
   free(dst);
}

/*------------------------------------------------------------------*/

void mxml_decode(char *str)
/* reverse of mxml_encode, strip leading or trailing '"' */
{
   char *p;

   p = str;
   while ((p = strchr(p, '&')) != NULL) {
      if (strncmp(p, "&lt;", 4) == 0) {
         *(p++) = '<';
         strcpy(p, p+3);
      }
      if (strncmp(p, "&gt;", 4) == 0) {
         *(p++) = '>';
         strcpy(p, p+3);
      }
      if (strncmp(p, "&amp;", 5) == 0) {
         *(p++) = '&';
         strcpy(p, p+4);
      }
      if (strncmp(p, "&quot;", 6) == 0) {
         *(p++) = '\"';
         strcpy(p, p+5);
      }
      if (strncmp(p, "&apos;", 6) == 0) {
         *(p++) = '\'';
         strcpy(p, p+5);
      }
   }

   if (str[0] == '\"' && str[strlen(str)-1] == '\"') {
      strcpy(str, str+1);
      str[strlen(str)-1] = 0;
   }
}

/*------------------------------------------------------------------*/

BOOL mxml_start_element(MXML_WRITER *writer, const char *name)
/* start a new XML element, must be followed by mxml_end_elemnt */
{
   int i;
   char line[1000], name_enc[1000];

   if (writer->element_is_open) {
      write(writer->fh, ">\n", 2);
      writer->element_is_open = FALSE;
   }

   line[0] = 0;
   for (i=0 ; i<writer->level ; i++)
      strlcat(line, "     ", sizeof(line));
   strlcat(line, "<", sizeof(line));
   strlcpy(name_enc, name, sizeof(name_enc));
   mxml_encode(name_enc, sizeof(name_enc));
   strlcat(line, name_enc, sizeof(line));

   /* put element on stack */
   if (writer->level == 0)
      writer->stack = malloc(sizeof(char *));
   else
      writer->stack = realloc(writer->stack, sizeof(char *)*(writer->level+1));
   
   writer->stack[writer->level] = (char *) malloc(strlen(name_enc)+1);
   strcpy(writer->stack[writer->level], name_enc);
   writer->level++;
   writer->element_is_open = TRUE;
   writer->data_was_written = FALSE;

   return write(writer->fh, line, strlen(line)) == (int)strlen(line);
}

/*------------------------------------------------------------------*/

BOOL mxml_end_element(MXML_WRITER *writer)
/* close an open XML element */
{
   int i;
   char line[1000];

   if (writer->level == 0)
      return 0;
   
   writer->level--;

   if (writer->element_is_open) {
      writer->element_is_open = FALSE;
      free(writer->stack[writer->level]);
      if (writer->level == 0)
         free(writer->stack);
      if (write(writer->fh, "/>\n", 3) != 3)
         return FALSE;
      return TRUE;
   }

   line[0] = 0;
   if (!writer->data_was_written) {
      for (i=0 ; i<writer->level ; i++)
         strlcat(line, "     ", sizeof(line));
   }

   strlcat(line, "</", sizeof(line));
   strlcat(line, writer->stack[writer->level], sizeof(line));
   free(writer->stack[writer->level]);
   if (writer->level == 0)
      free(writer->stack);
   strlcat(line, ">\n", sizeof(line));
   writer->data_was_written = FALSE;

   return write(writer->fh, line, strlen(line)) == (int)strlen(line);
}

/*------------------------------------------------------------------*/

BOOL mxml_write_attribute(MXML_WRITER *writer, const char *name, const char *value)
/* write an attribute to the currently open XML element */
{
   char name_enc[1000];

   if (!writer->element_is_open)
      return FALSE;

   write(writer->fh, " ", 1);
   strcpy(name_enc, name);
   mxml_encode(name_enc, sizeof(name_enc));
   write(writer->fh, name_enc, strlen(name_enc));
   write(writer->fh, "=\"", 2);

   strcpy(name_enc, value);
   mxml_encode(name_enc, sizeof(name_enc));
   write(writer->fh, name_enc, strlen(name_enc));
   write(writer->fh, "\"", 1);

   return TRUE;
}

/*------------------------------------------------------------------*/

BOOL mxml_write_value(MXML_WRITER *writer, const char *data)
/* write value of an XML element, like <[name]>[value]</[name]> */
{
   int i, j;
   static char *data_enc;
   static int data_size = 0;

   if (!writer->element_is_open)
      return FALSE;

   if (write(writer->fh, ">", 1) != 1)
      return FALSE;
   writer->element_is_open = FALSE;
   writer->data_was_written = TRUE;

   if (data_size == 0) {
      data_enc = malloc(1000);
      data_size = 1000;
   } else if ((int)strlen(data)*2+1000 > data_size) {
      data_size = 1000+strlen(data)*2;
      data_enc = realloc(data_enc, data_size);
   }

   strcpy(data_enc, data);
   mxml_encode(data_enc, data_size);
   j = strlen(data_enc);
   i = write(writer->fh, data_enc, j);

   return i == j;
}

/*------------------------------------------------------------------*/

BOOL mxml_close_document(MXML_WRITER *writer)
/* close a file opened with mxml_open_writer */
{
   int i;

   if (writer->element_is_open) {
      writer->element_is_open = FALSE;
      if (write(writer->fh, ">\n", 2) != 2)
         return FALSE;
   }

   /* close remaining open levels */
   for (i = 0 ; i<writer->level ; i++)
      mxml_end_element(writer);

   close(writer->fh);
   free(writer);
   return TRUE;
}

/*------------------------------------------------------------------*/

PMXML_NODE mxml_create_root_node()
/* create root node of an XML tree */
{
   PMXML_NODE root;

   root = (PMXML_NODE)calloc(sizeof(MXML_NODE), 1);
   strcpy(root->name, "root");

   return root;
}

/*------------------------------------------------------------------*/

PMXML_NODE mxml_add_node(PMXML_NODE parent, char *node_name, char *value)
/* add a subnode (child) to an existing parent node */
{
   PMXML_NODE pnode, pchild;
   int i, j;

   assert(parent);
   if (parent->n_children == 0)
      parent->child = malloc(sizeof(MXML_NODE));
   else {
      pchild = parent->child;
      parent->child = realloc(parent->child, sizeof(MXML_NODE)*(parent->n_children+1));

      if (parent->child != pchild) {
         /* correct parent pointer for children */
         for (i=0 ; i<parent->n_children ; i++) {
            pchild = parent->child+i;
            for (j=0 ; j<pchild->n_children ; j++)
               pchild->child[j].parent = pchild;
         }
      }
   }
   assert(parent->child);
   pnode = &parent->child[parent->n_children];
   memset(pnode, 0, sizeof(MXML_NODE));
   strlcpy(pnode->name, node_name, sizeof(pnode->name));
   pnode->parent = parent;
   parent->n_children++;

   if (value) {
      pnode->value = malloc(strlen(value)+1);
      assert(pnode->value);
      strcpy(pnode->value, value);
   }

   return pnode;
}

/*------------------------------------------------------------------*/

BOOL mxml_add_attribute(PMXML_NODE pnode, char *attrib_name, char *attrib_value)
/* add an attribute to an existing node */
{
   if (pnode->n_attributes == 0) {
      pnode->attribute_name  = malloc(MXML_NAME_LENGTH);
      pnode->attribute_value = malloc(sizeof(char *));
   } else {
      pnode->attribute_name  = realloc(pnode->attribute_name,  MXML_NAME_LENGTH*(pnode->n_attributes+1));
      pnode->attribute_value = realloc(pnode->attribute_value, sizeof(char *)*(pnode->n_attributes+1));
   }

   strlcpy(pnode->attribute_name+pnode->n_attributes*MXML_NAME_LENGTH, attrib_name, MXML_NAME_LENGTH);
   pnode->attribute_value[pnode->n_attributes] = malloc(strlen(attrib_value)+1);
   strcpy(pnode->attribute_value[pnode->n_attributes], attrib_value);
   pnode->n_attributes++;

   return TRUE;
}

/*------------------------------------------------------------------*/

int mxml_get_number_of_children(PMXML_NODE pnode)
/* return number of subnodes (children) of a node */
{
   assert(pnode);
   return pnode->n_children;
}

/*------------------------------------------------------------------*/

PMXML_NODE mxml_subnode(PMXML_NODE pnode, int index)
/* return number of subnodes (children) of a node */
{
   assert(pnode);
   if (index < pnode->n_children)
      return &pnode->child[index];
   return NULL;
}

/*------------------------------------------------------------------*/

PMXML_NODE mxml_find_node(PMXML_NODE tree, char *xml_path)
/*
   Search for a specific XML node with a subset of XPATH specifications.
   Following elemets are possible

   /<node>/<node>/..../<node>          Find a node in the tree hierarchy
   /<node>[index]                      Find child #[index] of node
   /<node>[index]/<node>               Find subnode of the above
   /<node>[<subnode>=<value>]          Find a node which has a specific subnode
   /<node>[<subnode>=<value>]/<node>   Find subnode of the above
*/
{
   PMXML_NODE pnode;
   char *p1, *p2, *p3, node_name[256], condition[256], subnode[256], value[256];
   int i, j, index;
   size_t len;

   p1 = xml_path;
   pnode = tree;

   /* skip leading '/' */
   if (*p1 && *p1 == '/')
      p1++;

   do {
      p2 = p1;
      while (*p2 && *p2 != '/' && *p2 != '[')
         p2++;
      len = (size_t)p2 - (size_t)p1;
      if (len >= sizeof(node_name))
         return NULL;

      memcpy(node_name, p1, len);
      node_name[len] = 0;
      index = 0;
      subnode[0] = value[0] = 0;
      if (*p2 == '[') {
         p2++;
         if (isdigit(*p2)) {
            /* evaluate [index] */
            index = atoi(p2);
            p2 = strchr(p2, ']');
            if (p2 == NULL)
               return NULL;
            p2++;
         } else {
            /* evaluate [<subnode>=<value>] */
            while (*p2 && isspace(*p2))
               p2++;
            strlcpy(condition, p2, sizeof(condition));
            if (strchr(condition, ']'))
               *strchr(condition, ']') = 0;
            else
               return NULL;
            p2 = strchr(p2, ']')+1;
            if ((p3 = strchr(condition, '=')) != NULL) {
               strlcpy(subnode, condition, sizeof(subnode));
               *strchr(subnode, '=') = 0;
               while (subnode[0] && isspace(subnode[strlen(subnode)-1]))
                  subnode[strlen(subnode)-1] = 0;
               p3++;
               while (*p3 && isspace(*p3))
                  p3++;
               strlcpy(value, p3, sizeof(value));
               while (value[0] && isspace(value[strlen(value)-1]))
                  value[strlen(value)-1] = 0;
            }
         }
      }

      for (i=j=0 ; i<pnode->n_children ; i++) {
         if (subnode[0]) {
            /* search subnode */
            for (j=0 ; j<pnode->child[i].n_children ; j++)
               if (strcmp(pnode->child[i].child[j].name, subnode) == 0)
                  break;
            if (j == pnode->child[i].n_children)
               return NULL;
            if (strcmp(pnode->child[i].child[j].value, value) == 0)
               break;
         } else {
            if (strcmp(pnode->child[i].name, node_name) == 0)
               if (j++ == index)
                  break;
         }
      }

      if (i == pnode->n_children)
         return NULL;

      pnode = &pnode->child[i];
      p1 = p2;
      if (*p1 == '/')
         p1++;

   } while (*p2);

   return pnode;
}

/*------------------------------------------------------------------*/

char *mxml_get_value(PMXML_NODE pnode)
{
   assert(pnode);
   return pnode->value;
}

/*------------------------------------------------------------------*/

char *mxml_get_attribute(PMXML_NODE pnode, char *name)
{
   int i;

   assert(pnode);
   for (i=0 ; i<pnode->n_attributes ; i++) 
      if (strcmp(pnode->attribute_name+i*MXML_NAME_LENGTH, name) == 0)
         return pnode->attribute_value[i];

   return NULL;
}

/*------------------------------------------------------------------*/

BOOL mxml_replace_node_name(PMXML_NODE pnode, char *name)
{
   strlcpy(pnode->name, name, sizeof(pnode->name));
   return TRUE;
}

/*------------------------------------------------------------------*/

BOOL mxml_replace_node_value(PMXML_NODE pnode, char *value)
{
   if (pnode->value)
      pnode->value = realloc(pnode->value, strlen(value)+1);
   else
      pnode->value = malloc(strlen(value)+1);
   
   strcpy(pnode->value, value);
   return TRUE;
}

/*------------------------------------------------------------------*/

BOOL mxml_replace_subvalue(PMXML_NODE pnode, char *name, char *value)
/* 
   replace value os a subnode, like

   <parent>
     <child>value</child>
   </parent>

   if pnode=parent, and "name"="child", then "value" gets replaced
*/
{
   int i;

   for (i=0 ; i<pnode->n_children ; i++) 
      if (strcmp(pnode->child[i].name, name) == 0)
         break;

   if (i == pnode->n_children)
      return FALSE;

   return mxml_replace_node_value(&pnode->child[i], value);
}

/*------------------------------------------------------------------*/

BOOL mxml_replace_attribute_name(PMXML_NODE pnode, char *old_name, char *new_name)
/* change the name of an attribute, keep its value */
{
   int i;

   for (i=0 ; i<pnode->n_attributes ; i++) 
      if (strcmp(pnode->attribute_name+i*MXML_NAME_LENGTH, old_name) == 0)
         break;

   if (i == pnode->n_attributes)
      return FALSE;

   strlcpy(pnode->attribute_name+i*MXML_NAME_LENGTH, new_name, MXML_NAME_LENGTH);
   return TRUE;
}

/*------------------------------------------------------------------*/

BOOL mxml_replace_attribute_value(PMXML_NODE pnode, char *attrib_name, char *attrib_value)
/* change the value of an attribute */
{
   int i;

   for (i=0 ; i<pnode->n_attributes ; i++) 
      if (strcmp(pnode->attribute_name+i*MXML_NAME_LENGTH, attrib_name) == 0)
         break;

   if (i == pnode->n_attributes)
      return FALSE;

   pnode->attribute_value[i] = realloc(pnode->attribute_value[i], strlen(attrib_value)+1);
   strcpy(pnode->attribute_value[i], attrib_value);
   return TRUE;
}

/*------------------------------------------------------------------*/

BOOL mxml_delete_node(PMXML_NODE pnode)
/* free memory of a node and remove it from the parent's child list */
{
   PMXML_NODE parent;
   int i, j;

   /* remove node from parent's list */
   parent = pnode->parent;

   if (parent) {
      for (i=0 ; i<parent->n_children ; i++)
         if (&parent->child[i] == pnode)
            break;

      /* free allocated node memory recursively */
      mxml_free_tree(pnode);

      if (i < parent->n_children) {
         for (j=i ; j<parent->n_children-1 ; j++)
            memcpy(&parent->child[j], &parent->child[j+1], sizeof(MXML_NODE));
         parent->n_children--;
         if (parent->n_children)
            parent->child = realloc(parent->child, sizeof(MXML_NODE)*(parent->n_children));
         else
            free(parent->child);
      }
   } else 
      mxml_free_tree(pnode);

   return TRUE;
}

/*------------------------------------------------------------------*/

BOOL mxml_delete_attribute(PMXML_NODE pnode, char *attrib_name)
{
   int i, j;

   for (i=0 ; i<pnode->n_attributes ; i++) 
      if (strcmp(pnode->attribute_name+i*MXML_NAME_LENGTH, attrib_name) == 0)
         break;

   if (i == pnode->n_attributes)
      return FALSE;

   free(pnode->attribute_value[i]);
   for (j=i ; j<pnode->n_attributes-1 ; j++) {
      strcpy(pnode->attribute_name+j*MXML_NAME_LENGTH, pnode->attribute_name+(j+1)*MXML_NAME_LENGTH);
      pnode->attribute_value[j] = pnode->attribute_value[j+1];
   }

   if (pnode->n_attributes > 0) {
      pnode->attribute_name  = realloc(pnode->attribute_name,  MXML_NAME_LENGTH*(pnode->n_attributes-1));
      pnode->attribute_value = realloc(pnode->attribute_value, sizeof(char *)*(pnode->n_attributes-1));
   } else {
      free(pnode->attribute_name);
      free(pnode->attribute_value);
   }

   return TRUE;
}

/*------------------------------------------------------------------*/

#define HERE root, file_name, line_number, error, error_size

PMXML_NODE read_error(PMXML_NODE root, char *file_name, int line_number, char *error, int error_size, char *format, ...)
/* used inside mxml_parse_file for reporting errors */
{
   char *msg, str[1000];
   va_list argptr;

   sprintf(str, "XML read error in file \"%s\", line %d: ", file_name, line_number);
   msg = malloc(error_size);
   strlcpy(error, str, error_size);

   va_start(argptr, format);
   vsprintf(str, (char *) format, argptr);
   va_end(argptr);

   strlcat(error, str, error_size);
   free(msg);
   mxml_free_tree(root);

   return NULL;
}

/*------------------------------------------------------------------*/

PMXML_NODE mxml_parse_file(char *file_name, char *error, int error_size)
/* parse a XML file and convert it into a tree of MXML_NODE's. Return NULL
   in case of an error, return error description */
{
   char line[1000], node_name[256], attrib_name[256], attrib_value[1000];
   char *buf, *p, *pv;
   int i, fh, length, line_number;
   PMXML_NODE root, ptree, pnew;
   BOOL end_element;
   size_t len;

   fh = open(file_name, O_RDONLY | O_TEXT, 0644);

   if (fh == -1) {
      sprintf(line, "Unable to open file \"%s\": ", file_name);
      strlcat(line, strerror(errno), sizeof(line));
      strlcpy(error, line, error_size);
      return NULL;
   }

   length = lseek(fh, 0, SEEK_END);
   lseek(fh, 0, SEEK_SET);
   buf = malloc(length+1);
   if (buf == NULL) {
      close(fh);
      sprintf(line, "Cannot allocate buffer: ");
      strlcat(line, strerror(errno), sizeof(line));
      strlcpy(error, line, error_size);
      return NULL;
   }

   /* read complete file at once */
   length = read(fh, buf, length);
   buf[length] = 0;
   close(fh);

   p = buf;
   line_number = 1;

   root = mxml_create_root_node();
   ptree = root;

   /* store filename in attribute */
   mxml_add_attribute(root, "filename", file_name);

   /* parse file contents */
   do {
      if (*p == '<') {

         end_element = FALSE;

         /* found new element */
         *p++;
         while (*p && isspace(*p)) {
            if (*p == '\n')
               line_number++;
            p++;
         }
         if (!*p)
            return read_error(HERE, "Unexpected end of file");

         if (strncmp(p, "!--", 3) == 0) {
            
            /* found comment */
            p += 3;
            if (strstr(p, "-->") == NULL)
               return read_error(HERE, "Unterminated comment");
            
            while (strncmp(p, "-->", 3) != 0) {
               if (*p == '\n')
                  line_number++;
               p++;
            }
            p += 3;

         } else if (*p == '?') {

            /* found ?...? element */
            p++;
            if (strstr(p, "?>") == NULL)
               return read_error(HERE, "Unterminated ?...? element");
            
            while (strncmp(p, "?>", 2) != 0) {
               if (*p == '\n')
                  line_number++;
               p++;
            }
            p += 2;

         } else {
            
            /* found normal element */
            if (*p == '/') {
               end_element = TRUE;
               p++;
               while (*p && isspace(*p)) {
                  if (*p == '\n')
                     line_number++;
                  p++;
               }
               if (!*p)
                  return read_error(HERE, "Unexpected end of file");
            }

            /* extract node name */
            i = 0;
            node_name[i] = 0;
            while (*p && !isspace(*p) && *p != '/' && *p != '>' && *p != '<')
               node_name[i++] = *p++;
            node_name[i] = 0;
            if (!*p)
               return read_error(HERE, "Unexpected end of file");
            if (*p == '<')
               return read_error(HERE, "Unexpected \'<\' inside element \"%s\"", node_name);

            mxml_decode(node_name);

            if (end_element) {

               /* close previously opened element */
               if (strcmp(ptree->name, node_name) != 0)
                  return read_error(HERE, "Found </%s>, expected </%s>", node_name, ptree->name);
            
               /* go up one level on the tree */
               ptree = ptree->parent;

            } else {
            
               /* allocate new element structure in parent tree */
               pnew = mxml_add_node(ptree, node_name, NULL);

               while (*p && isspace(*p)) {
                  if (*p == '\n')
                     line_number++;
                  p++;
               }
               if (!*p)
                  return read_error(HERE, "Unexpected end of file");

               while (*p != '>' && *p != '/') {

                  /* found attribute */
                  pv = p;
                  while (*pv && !isspace(*pv) && *pv != '=' && *pv != '<' && *pv != '>')
                     pv++;
                  if (!*pv)
                     return read_error(HERE, "Unexpected end of file");
                  if (*pv == '<' || *pv == '>')
                     return read_error(HERE, "Unexpected \'%c\' inside element \"%s\"", *pv, node_name);

                  /* extract attribute name */
                  len = (size_t)pv - (size_t)p;
                  if (len > sizeof(attrib_name)-1)
                     len = sizeof(attrib_name)-1;
                  memcpy(attrib_name, p, len);
                  attrib_name[len] = 0;

                  p = pv;
                  while (*p && isspace(*p)) {
                     if (*p == '\n')
                        line_number++;
                     p++;
                  }
                  if (!*p)
                     return read_error(HERE, "Unexpected end of file");
                  if (*p != '=')
                     return read_error(HERE, "Expect \"=\" here");

                  p++;
                  while (*p && isspace(*p)) {
                     if (*p == '\n')
                        line_number++;
                     p++;
                  }
                  if (!*p)
                     return read_error(HERE, "Unexpected end of file");
                  if (*p != '\"')
                     return read_error(HERE, "Expect \'\"\' here");
                  p++;

                  /* extract attribute value */
                  pv = p;
                  while (*pv && *pv != '\"' && *pv != '<' && *pv != '>')
                     pv++;
                  if (!*pv)
                     return read_error(HERE, "Unexpected end of file");
                  if (*pv == '<' || *pv == '>')
                     return read_error(HERE, "Unexpected \'%c\' inside attribute value \"%s\" of element \"%s\"",
                        *pv, attrib_name, node_name);

                  len = (size_t)pv - (size_t)p;
                  if (len > sizeof(attrib_value)-1)
                     len = sizeof(attrib_value)-1;
                  memcpy(attrib_value, p, len);
                  attrib_value[len] = 0;

                  /* add attribute to current node */
                  mxml_add_attribute(pnew, attrib_name, attrib_value);

                  p = pv+1;
                  while (*p && isspace(*p)) {
                     if (*p == '\n')
                        line_number++;
                     p++;
                  }
                  if (!*p)
                     return read_error(HERE, "Unexpected end of file");
               }

               if (*p == '/') {

                  /* found empty node, like <node/>, just skip closing bracket */
                  p++;

                  while (*p && isspace(*p)) {
                     if (*p == '\n')
                        line_number++;
                     p++;
                  }
                  if (!*p)
                     return read_error(HERE, "Unexpected end of file");
                  if (*p != '>')
                     return read_error(HERE, "Expected \">\" after \"/\"");
                  p++;
               }

               if (*p == '>') {

                  p++;

                  /* check if we have sub-element or value */
                  pv = p;
                  while (*pv && isspace(*pv)) {
                     if (*pv == '\n')
                        line_number++;
                     pv++;
                  }
                  if (!*pv)
                     return read_error(HERE, "Unexpected end of file");

                  if (*pv == '<') {

                     /* start new subtree */
                     ptree = pnew;
                     p = pv;

                  } else {

                     /* extract value */
                     while (*pv && *pv != '<' && *pv != '>') {
                        if (*pv == '\n')
                           line_number++;
                        pv++;
                     }
                     if (!*pv)
                        return read_error(HERE, "Unexpected end of file");
                     if (*pv == '>')
                        return read_error(HERE, "Unexpected \'>\' inside element \"%s\"", node_name);

                     len = (size_t)pv - (size_t)p;
                     pnew->value = malloc(len+1);
                     memcpy(pnew->value, p, len);
                     pnew->value[len] = 0;
                     mxml_decode(pnew->value);
                     p = pv;

                     ptree = pnew;
                  }
               }
            }
         }
      }

      /* go to next element */
      while (*p && *p != '<') {
         if (*p == '\n')
            line_number++;
         p++;
      }
   } while (*p);

   return root;
}

/*------------------------------------------------------------------*/

BOOL mxml_write_subtree(MXML_WRITER *writer, PMXML_NODE tree)
/* write complete subtree recursively into file opened with mxml_open_document() */
{
   int i;

   mxml_start_element(writer, tree->name);
   for (i=0 ; i<tree->n_attributes ; i++)
      if (!mxml_write_attribute(writer, tree->attribute_name+i*MXML_NAME_LENGTH, tree->attribute_value[i]))
         return FALSE;
   if (tree->value) {
      if (!mxml_write_value(writer, tree->value))
         return FALSE;
   } else {
      for (i=0 ; i<tree->n_children ; i++)
         if (!mxml_write_subtree(writer, &tree->child[i]))
            return FALSE;
   }

   return mxml_end_element(writer);
}

/*------------------------------------------------------------------*/

BOOL mxml_write_tree(char *file_name, PMXML_NODE tree)
/* write a complete XML tree to a file */
{
   MXML_WRITER *writer;
   int i;

   assert(tree);
   writer = mxml_open_document(file_name);
   if (!writer)
      return FALSE;

   for (i=0 ; i<tree->n_children ; i++)
      if (!mxml_write_subtree(writer, &tree->child[i]))
         return FALSE;

   if (!mxml_close_document(writer))
      return FALSE;

   return TRUE;
}

/*------------------------------------------------------------------*/

void mxml_debug_tree(PMXML_NODE tree, int level)
/* print XML tree for debugging */
{
   int i;

   for (i=0 ; i<level ; i++)
      printf("  ");
   printf("Name: %s\n", tree->name);
   for (i=0 ; i<level ; i++)
      printf("  ");
   printf("Addr: %08X\n", (size_t)tree);
   for (i=0 ; i<level ; i++)
      printf("  ");
   printf("Prnt: %08X\n", (size_t)tree->parent);
   for (i=0 ; i<level ; i++)
      printf("  ");
   printf("NCld: %d\n", tree->n_children);

   for (i=0 ; i<tree->n_children ; i++)
      mxml_debug_tree(tree->child+i, level+1);

   if (level == 0)
      printf("\n");
}

/*------------------------------------------------------------------*/

void mxml_free_tree(PMXML_NODE tree)
/* free memory of XML tree, must be called after any 
   mxml_create_root_node() or mxml_parse_file() */
{
   int i;

   /* first free children recursively */
   for (i=0 ; i<tree->n_children ; i++)
      mxml_free_tree(&tree->child[i]);
   if (tree->n_children)
      free(tree->child);

   /* now free dynamic data */
   for (i=0 ; i<tree->n_attributes ; i++)
      free(tree->attribute_value[i]);

   if (tree->n_attributes) {
      free(tree->attribute_name);
      free(tree->attribute_value);
   }
   
   if (tree->value)
      free(tree->value);

   /* if we are the root node, free it */
   if (tree->parent == NULL)
      free(tree);
}

/*------------------------------------------------------------------*/

