/********************************************************************\

  Name:         auth.c
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


  Contents:     Authentication subroutines. Currently supported:

                - password file authentication
                - kerberos5 password authentication

  $Id: elog.c 2350 2010-12-23 10:45:10Z ritt $

\********************************************************************/

#include "elogd.h"

#ifdef HAVE_KRB5
#include <krb5.h>
#endif

#ifdef HAVE_LDAP
#include <ldap.h>

LDAP *ldap_ld;
char ldap_login_attr[64];
char ldap_userbase[256];
char ldap_bindDN[512];
#endif  /* HAVE_LDAP */

extern LOGBOOK *lb_list;

/*==================================================================*/

/*---- Kerberos5 routines ------------------------------------------*/

#ifdef HAVE_KRB5

int auth_verify_password_krb5(LOGBOOK * lbs, const char *user, const char *password, char *error_str,
                              int error_size)
{
   char *princ_name, str[256], realm[256];
   krb5_error_code error;
   krb5_principal princ;
   krb5_context context;
   krb5_creds creds;
   krb5_get_init_creds_opt options;

   if (krb5_init_context(&context) < 0)
      return FALSE;

   strlcpy(str, user, sizeof(str));
   if (getcfg(lbs->name, "Kerberos Realm", realm, sizeof(realm))) {
      strlcat(str, "@", sizeof(str));
      strlcat(str, realm, sizeof(str));
   }
   if ((error = krb5_parse_name(context, str, &princ)) != 0) {
      strlcpy(error_str, "<b>Kerberos error:</b><br>", error_size);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   error = krb5_unparse_name(context, princ, &princ_name);
   if (error) {
      strlcpy(error_str, "<b>Kerberos error:</b><br>", error_size);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   sprintf(str, "Using %s as server principal for authentication", princ_name);
   write_logfile(lbs, str);

   memset(&options, 0, sizeof(options));
   krb5_get_init_creds_opt_init(&options);
   memset(&creds, 0, sizeof(creds));
   error = krb5_get_init_creds_password(context, &creds, princ,
                                        (char *) password, NULL, NULL, 0, NULL, &options);

   krb5_free_context(context);

   if (error && error != KRB5KDC_ERR_PREAUTH_FAILED && error != KRB5KDC_ERR_C_PRINCIPAL_UNKNOWN) {
      sprintf(error_str, "<b>Kerberos error %d:</b><br>", error);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   if (error)
      return FALSE;

   return TRUE;
}

int auth_change_password_krb5(LOGBOOK * lbs, const char *user, const char *old_pwd, const char *new_pwd,
                              char *error_str, int error_size)
{
   char *princ_name, str[256], realm[256];
   int result_code, n;
   krb5_error_code error;
   krb5_data result_code_string, result_string;
   krb5_principal princ;
   krb5_context context;
   krb5_creds creds;
   krb5_get_init_creds_opt options;

   if (krb5_init_context(&context) < 0)
      return FALSE;

   strlcpy(str, user, sizeof(str));
   if (getcfg(lbs->name, "Kerberos Realm", realm, sizeof(realm))) {
      strlcat(str, "@", sizeof(str));
      strlcat(str, realm, sizeof(str));
   }
   if ((error = krb5_parse_name(context, str, &princ)) != 0) {
      strlcpy(error_str, "<b>Kerberos error:</b><br>", error_size);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   error = krb5_unparse_name(context, princ, &princ_name);

   sprintf(str, "Using %s as server principal for authentication", princ_name);
   write_logfile(lbs, str);

   memset(&options, 0, sizeof(options));
   krb5_get_init_creds_opt_init(&options);
   krb5_get_init_creds_opt_set_tkt_life(&options, 300);
   krb5_get_init_creds_opt_set_forwardable(&options, FALSE);
   krb5_get_init_creds_opt_set_proxiable(&options, FALSE);

   memset(&creds, 0, sizeof(creds));
   error = krb5_get_init_creds_password(context, &creds, princ,
                                        (char *) old_pwd, NULL, NULL, 0, "kadmin/changepw", &options);
   if (error) {
      strlcpy(error_str, "<b>Kerberos error:</b><br>", error_size);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   error = krb5_set_password(context, &creds, (char *) new_pwd, princ,
                             &result_code, &result_code_string, &result_string);
   if (error) {
      strlcpy(error_str, "<b>Kerberos error:</b><br>", error_size);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   if (result_code > 0) {
      if (result_code_string.length > 0) {
         strlcpy(error_str, result_code_string.data, error_size);
         if ((int) result_code_string.length < error_size)
            error_str[result_code_string.length] = 0;
      }
      if (result_string.length > 0) {
         strlcat(error_str, ": ", error_size);
         n = strlen(error_str) + result_string.length;
         strlcat(error_str, result_string.data, error_size);
         if (n < error_size)
            error_str[n] = 0;
      }
   }

   krb5_free_data_contents(context, &result_code_string);
   krb5_free_data_contents(context, &result_string);
   krb5_free_cred_contents(context, &creds);
   krb5_get_init_creds_opt_free(context, &options);
   krb5_free_context(context);

   if (result_code > 0)
      return FALSE;

   return TRUE;
}
#endif

/*---- LDAP routines ------------------------------------------*/

#ifdef HAVE_LDAP

int ldap_init(LOGBOOK *lbs, char *error_str, int error_size)
{
   char str[512], ldap_server[256];
   int ii, version;
   
   // Read Config file
   if (getcfg(lbs->name, "LDAP server", ldap_server, sizeof(ldap_server))) {
      strlcpy(str, ldap_server, sizeof(str));
   }
   else   {
      strlcpy(error_str, "<b>LDAP initialization error</b><br>", error_size);
      strlcat(error_str, "<br>Please check your LDAP configuration.", error_size);
      strlcat(str, "ERR: Cannot find LDAP server entry!", sizeof(str));
      write_logfile(lbs, str);
      return FALSE;
   }
   
   if (!getcfg(lbs->name, "LDAP userbase", ldap_userbase, sizeof(ldap_userbase))) {
      strlcpy(error_str, "<b>LDAP initialization error</b><br>", error_size);
      strlcat(error_str, "<br>Please check your LDAP configuration.", error_size);
      strlcat(str, ", ERR: Cannot find LDAP userbase (e.g. \'ou=People,dc=example,dc=org\')!", sizeof(str));
      write_logfile(lbs, str);
      return FALSE;
   }
   
   if (!getcfg(lbs->name, "LDAP login attribute", ldap_login_attr, sizeof(ldap_login_attr))) {
      strlcpy(error_str, "<b>LDAP initialization error</b><br>", error_size);
      strlcat(error_str, "<br>Please check your LDAP configuration.", error_size);
      strlcat(str, ", ERR: Cannot find LDAP login attribute (e.g. uid, cn, ...)!", sizeof(str));
      write_logfile(lbs, str);
      return FALSE;
   }
   
   // Initialize/open LDAP connection
   if(ldap_initialize( &ldap_ld, ldap_server )) {
      perror("ldap_initialize");
      strlcpy(error_str, "<b>LDAP initialization error</b><br>", error_size);
      strlcat(error_str, "<br>Please check your LDAP configuration.", error_size);
      return FALSE;
   }
   
   // Use the LDAP_OPT_PROTOCOL_VERSION session preference to specify that the client is LDAPv3 client
   version = LDAP_VERSION3;
   ldap_set_option(ldap_ld, LDAP_OPT_PROTOCOL_VERSION, &version);
   
   write_logfile(lbs, str);
   
   return TRUE;
}

int auth_verify_password_ldap(LOGBOOK *lbs, const char *user, const char *password, char *error_str,
                              int error_size)
{  LDAPMessage *result, *err;
   int bind=0, ii;
   char str[512];
   
   ldap_ld = NULL;
   memset(&ldap_bindDN[0], 0, sizeof(ldap_bindDN));
   
   if(!ldap_init(lbs,error_str,error_size)) {
      strlcpy(error_str, "<b>LDAP initialization error</b><br>", error_size);
      strlcat(error_str, "<br>Please check your LDAP configuration.", error_size);
      return FALSE;
   }
   
   // Form LDAP bind DN (distinguished name):
   // login_attr=user,ldap_userbase, e.g. uid=tuser,ou=People,dc=example,dc=org
   sprintf(ldap_bindDN,"%s=%s,%s",ldap_login_attr,user,ldap_userbase);
   
   strlcat(str, "Connecting as: ", sizeof(str));
   strlcat(str, ldap_bindDN, sizeof(str));
   write_logfile(lbs, str);
   
   // User authentication (bind)
   bind = ldap_simple_bind_s(ldap_ld, ldap_bindDN, password);
   if( bind != LDAP_SUCCESS ) {
      strlcpy(error_str, "<b>LDAP authentication error:</b><br>", error_size);
      strlcat(error_str, ldap_err2string(bind), error_size);
      strlcat(error_str, ".<br>Please check your user/password or LDAP configuration.", error_size);
      strlcpy(str, "LDAP Authentication: FAILED!", sizeof(str));
      write_logfile(lbs, str);
      ldap_unbind(ldap_ld);
      return FALSE;
   }
   
   strlcpy(str, "LDAP Authentication: Success!", sizeof(str));
   ldap_unbind(ldap_ld);
   
   write_logfile(lbs, str);
   return TRUE;
}


int ldap_adduser_file(LOGBOOK *lbs, const char *user, const char *password, char *error_str,
                      int error_size)
{  LDAPMessage *result, *entry;
   char *attribute, **values;
   char str[512], filter[512];
   BerElement *ber;
   int bind=0, rc=0, i;
   
   char lbs_str[256], user_str[256], user_enc[256], fullname[256], usergn[128], usersn[128], useremail[256];
   PMXML_NODE node, npwd;
   
   struct timeval timeOut = {3,0}; // 3 second connection/search timeout
                                   // zerotime.tv_sec = zerotime.tv_usec = 0L;
   
   write_logfile(lbs, "New user: getting userdata from LDAP...");
   
   if(!ldap_init(lbs,error_str,error_size)) {
      return FALSE;
   }
   
   // User authentication (bind)
   bind = ldap_simple_bind_s(ldap_ld, ldap_bindDN, password);
   if( bind != LDAP_SUCCESS ) {
      strlcpy(error_str, "<b>LDAP authentication error:</b><br>", error_size);
      strlcat(error_str, ldap_err2string(bind), error_size);
      strlcat(error_str, ".<br>Please check your user/password or LDAP configuration.", error_size);
      strlcat(str, "LDAP Authentication: FAILED!", sizeof(str));
      write_logfile(lbs, str);
      ldap_unbind(ldap_ld);
      return FALSE;
   }
   
   // form LDAP filter to find the user;
   sprintf(filter, "(%s=%s)", ldap_login_attr, user);
   
   // below based on: http://www.djack.com.pl/modules.php?name=FAQ&myfaq=yes&xmyfaq=yes&id_cat=7&id=183 (code errors!)
   // AND on: http://www-archive.mozilla.org/directory/csdk-docs/example.htm
   
   // Get user's first name, surname and email from LDAP
   rc = ldap_search_ext_s(
                          ldap_ld,		         // LDAP session handle
                          ldap_userbase,	      // Search Base
                          LDAP_SCOPE_SUBTREE,	// Search Scope – everything below o=Acme
                          filter,               // Search Filter – only inetOrgPerson objects
                          NULL,	               // returnAllAttributes – NULL means Yes
                          0,		               // attributesOnly – False means we want values
                          NULL,	               // Server controls – There are none
                          NULL,	               // Client controls – There are none
                          &timeOut,	            // search Timeout
                          LDAP_NO_LIMIT,	      // no size limit
                          &result);
   
   if (rc != LDAP_SUCCESS) {
      strlcat(str, "LDAP search returned error: ", sizeof(str));
      strlcat(str, ldap_err2string(rc), sizeof(str));
      write_logfile(lbs, str);
      ldap_unbind(ldap_ld);
      return FALSE;
   }
   
   for(entry = ldap_first_entry(ldap_ld,result);
       entry != NULL;
       entry = ldap_next_entry(ldap_ld,entry) ) {
      for(attribute = ldap_first_attribute(ldap_ld,entry,&ber);
          attribute != NULL;
          attribute = ldap_next_attribute(ldap_ld,entry,ber) ) {
         // For each attribute, print the attribute name and values. //
         if((values = ldap_get_values(ldap_ld,entry,attribute)) != NULL ) {
            for(i=0; values[i] != NULL; i++) {
               if(strcmp(attribute,"givenName")==0 || strcmp(attribute,"gn")==0)
                  strlcpy(usergn, values[i], sizeof(usergn));
               if(strcmp(attribute,"sn")==0 || strcmp(attribute,"surname")==0)
                  strlcpy(usersn, values[i], sizeof(usersn));
               if(strcmp(attribute,"mail")==0 || strcmp(attribute,"rfc822Mailbox")==0)
                  strlcpy(useremail, values[i], sizeof(useremail));
            }
            ldap_value_free(values);
         }
         ldap_memfree(attribute);
      }
      if(ber != NULL) ber_free(ber,0);
   }
   
   ldap_msgfree(result);
   ldap_unbind(ldap_ld);
   
   sprintf(fullname, "%s %s", usergn, usersn);
   
   // Add user from LDAP in the local password file
   // do not allow HTML in user name
   strencode2(user_enc, user, sizeof(user_enc));
   
   sprintf(lbs_str, "/list/user[name=%s]", user_enc);
   node = mxml_find_node(lbs->pwd_xml_tree, lbs_str);
   node = mxml_find_node(lbs->pwd_xml_tree, "/list");
   if (!node) {
      show_error(loc("Error accessing password file"));
      return 0;
   }
   node = mxml_add_node(node, "user", NULL);
   mxml_add_node(node, "name", user_enc); // add user login from LDAP;
   
   do_crypt(password, user_str, sizeof(str));
   npwd = mxml_add_node(node, "password", user_str); // add user password;
   
   if (npwd) mxml_add_attribute(npwd, "encoding", "SHA256"); // user password is encoded;
   
   strencode2(user_str, fullname, sizeof(str));  // add full user name from LDAP;
   mxml_add_node(node, "full_name", user_str);
   
   mxml_add_node(node, "last_logout", "0");      // last logout;
   mxml_add_node(node, "last_activity", "0");    // last activity;
   
   mxml_add_node(node, "email", useremail);      // add user email from LDAP;
   mxml_add_node(node, "inactive", "0");
   
   sprintf(str,"New user: %s, %s added", user_enc, useremail);
   write_logfile(lbs, str);
   return TRUE;
}

/*---- clear ldap_ld and ldap_bindDN ----*/
int ldap_clear () 
{
   ldap_ld = NULL;
   memset(&ldap_bindDN[0], 0, sizeof(ldap_bindDN)); 
   
   return TRUE;
}

#endif  /* LDAP */

/*---- local password file routines --------------------------------*/

int auth_verify_password_file(LOGBOOK * lbs, const char *user, const char *password, char *error_str,
                              int error_size)
{
   char upwd[256], enc_pwd[256];

   get_user_line(lbs, (char *) user, upwd, NULL, NULL, NULL, NULL, NULL);
   do_crypt(password, enc_pwd, sizeof(enc_pwd));

   return strcmp(enc_pwd, upwd) == 0;
}

int auth_change_password_file(LOGBOOK * lbs, const char *user, const char *old_pwd, const char *new_pwd,
                              char *error_str, int error_size)
{
   char str[256], file_name[256], enc_pwd[256];
   PMXML_NODE node;

   if (lbs == NULL)
      lbs = get_first_lbs_with_global_passwd();

   if (!lbs->pwd_xml_tree)
      return FALSE;

   sprintf(str, "/list/user[name=%s]/password", user);
   node = mxml_find_node(lbs->pwd_xml_tree, str);
   if (node == NULL)
      return FALSE;

   do_crypt(new_pwd, enc_pwd, sizeof(enc_pwd));
   mxml_replace_node_value(node, enc_pwd);

   if (get_password_file(lbs, file_name, sizeof(file_name)))
      mxml_write_tree(file_name, lbs->pwd_xml_tree);

   return TRUE;
}

/*---- common function entry points --------------------------------*/

int auth_verify_password(LOGBOOK * lbs, const char *user, const char *password, char *error_str,
                         int error_size)
{
   char str[256];
   BOOL verified;

   error_str[0] = 0;
   verified = FALSE;

   /* otherwise calls with null lbs which make this procedure crash */
   if (lbs == NULL)
      lbs = get_first_lbs_with_global_passwd();

   if (lbs == NULL)
      return FALSE;
   getcfg(lbs->name, "Authentication", str, sizeof(str));

#ifdef HAVE_KRB5
   if (stristr(str, "Kerberos"))
      verified = auth_verify_password_krb5(lbs, user, password, error_str, error_size);
   if (verified)
      return TRUE;
#endif

#ifdef HAVE_LDAP
   if (stristr(str, "LDAP")) {
      verified = auth_verify_password_ldap(lbs, user, password, error_str, error_size);
      
      // if user not in password file (external authentication!) and "LDAP register" is allowed (>0),
      // obtain user info from LDAP and add locally
      if (verified) {
         if (get_user_line(lbs, user, NULL, NULL, NULL, NULL, NULL, NULL) == 2) {
            if (getcfg(lbs->name, "LDAP register", str, sizeof(str)) && atoi(str) > 0)
               ldap_adduser_file(lbs, user, password, error_str, error_size);
         }
      }
      
      ldap_clear();
   }
   if (verified)
      return TRUE;
#endif

   if (str[0] == 0 || stristr(str, "File"))
      verified = auth_verify_password_file(lbs, user, password, error_str, error_size);

   return verified;
}

int auth_change_password(LOGBOOK * lbs, const char *user, const char *old_pwd, const char *new_pwd,
                         char *error_str, int error_size)
{
   int status = 0;
   char str[256];

   error_str[0] = 0;
   getcfg(lbs->name, "Authentication", str, sizeof(str));

   if (str[0] == 0 || stristr(str, "File"))
      status = auth_change_password_file(lbs, user, old_pwd, new_pwd, error_str, error_size);

#ifdef HAVE_KRB5
   if (stristr(str, "Kerberos"))
      status = auth_change_password_krb5(lbs, user, old_pwd, new_pwd, error_str, error_size);
#endif

   return status;
}
