/********************************************************************\

  Name:         auth.c
  Created by:   Stefan Ritt

  Contents:     Authentication subroutines. Currently supported:

                - password file authentication
                - kerberos5 password authentication

  $Id: elog.c 2350 2010-12-23 10:45:10Z ritt $

\********************************************************************/

#include "elogd.h"

#ifdef HAVE_KRB5
#include <krb5.h>
#endif

extern LOGBOOK *lb_list;

/* ========================================================================== */

/*---- Kerberos5 routines ------------------------------------------*/

#ifdef HAVE_KRB5

int auth_verify_password_krb5(LOGBOOK *lbs, const char *user, const char *password, char *error_str, int error_size)
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
	 			      (char *)password, NULL,
				      NULL, 0, NULL, &options);

   krb5_free_cred_contents(context, &creds);
   krb5_get_init_creds_opt_free(context, &options);
   krb5_free_context(context);

   if (error && error != KRB5KDC_ERR_PREAUTH_FAILED &&
                error != KRB5KDC_ERR_C_PRINCIPAL_UNKNOWN) {
      strlcpy(error_str, "<b>Kerberos error:</b><br>", error_size);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   if (error)
      return FALSE;

   return TRUE;
}

int auth_change_password_krb5(LOGBOOK *lbs, const char *user, const char *old_pwd, const char *new_pwd, char *error_str, int error_size)
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
	 			      (char *)old_pwd, NULL,
				      NULL, 0, "kadmin/changepw", &options);
   if (error) {
      strlcpy(error_str, "<b>Kerberos error:</b><br>", error_size);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   error = krb5_set_password(context, &creds, (char *)new_pwd, princ,
					  &result_code,
					  &result_code_string,
					  &result_string);
   if (error) {
      strlcpy(error_str, "<b>Kerberos error:</b><br>", error_size);
      strlcat(error_str, krb5_get_error_message(context, error), error_size);
      strlcat(error_str, ".<br>Please check your Kerberos configuration.", error_size);
      return FALSE;
   }

   if (result_code > 0) {
      if (result_code_string.length > 0) {
         strlcpy(error_str, result_code_string.data, error_size);
         if ((int)result_code_string.length < error_size)
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

/*---- local password file routines --------------------------------*/

int auth_verify_password_file(LOGBOOK *lbs, const char *user, const char *password, char *error_str, int error_size)
{
   char upwd[256], enc_pwd[256];

   get_user_line(lbs, (char*)user, upwd, NULL, NULL, NULL, NULL, NULL);
   do_crypt(password, enc_pwd, sizeof(enc_pwd));

   return strcmp(enc_pwd, upwd) == 0;
}

int auth_change_password_file(LOGBOOK *lbs, const char *user, const char *old_pwd, const char *new_pwd, char *error_str, int error_size)
{
   char str[256], file_name[256], enc_pwd[256];
   PMXML_NODE node;

   if (lbs == NULL)
      lbs = &lb_list[0];

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

int auth_verify_password(LOGBOOK *lbs, const char *user, const char *password, char *error_str, int error_size)
{
   char str[256];
   BOOL verified;

   error_str[0] = 0;
   verified = FALSE;
   getcfg(lbs->name, "Authentication", str, sizeof(str));

#ifdef HAVE_KRB5
   if (stristr(str, "Kerberos"))
      verified = auth_verify_password_krb5(lbs, user, password, error_str, error_size);
   if (verified)
      return TRUE;
#endif

   if (str[0] == 0 || stristr(str, "File"))
      verified = auth_verify_password_file(lbs, user, password, error_str, error_size);

   return verified;
}

int auth_change_password(LOGBOOK *lbs, const char *user, const char *old_pwd, const char *new_pwd, char *error_str, int error_size)
{
   int status;
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
