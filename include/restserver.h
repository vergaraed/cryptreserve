#ifndef RESTSRV_HEADER_FILE
#define RESTSRV_HEADER_FILE

#include <stdio.h>
#include <gnutls/gnutls.h>
#include <gnutls/x509.h>

#include <ulfius.h>
#include "dbcache.h"
#include "cryptreservesecureapi.h"
#include "jwthelper.h"

#define PORT 2884
#define PREFIX "/auth"

#define USER "test"
#define PASSWORD "testpassword"


char * read_file(const char * filename);
int callback_auth_basic_body (const struct _u_request * request, struct _u_response * response, void * user_data);
int callback_auth_basic (const struct _u_request * request, struct _u_response * response, void * user_data);

//Users
int callback_create_user (const struct _u_request * request, struct _u_response * response, void * user_data);
//int callback_create_user_login (const struct _u_request * request, struct _u_response * response, void * user_data);
int callback_user_logon(const struct _u_request * request, struct _u_response * response, void * user_data);
int callback_create_passport(const struct _u_request * request, struct _u_response * response, void * user_data);


//Issuers
int callback_issuer_logon(const struct _u_request * request, struct _u_response * response, void * user_data);
int callback_create_issuer_account(const struct _u_request * request, struct _u_response * response, void * user_data);
int callback_get_passport(const struct _u_request * request, struct _u_response * response, void * user_data);


#ifndef U_DISABLE_GNUTLS
/**
 * Callback function on client certificate authentication
 */
int callback_auth_client_cert (const struct _u_request * request, struct _u_response * response, void * user_data);
#endif

int StartRestServer(int argc, char **argv);


#endif