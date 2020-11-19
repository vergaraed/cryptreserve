#include <string.h>
#include <stdio.h>
#include <jansson.h>
//#include "../../include/jsonparser.h"
#include "jsonparser.h"

/*
const char *to_json_string(json_object *obj, int flags)
{
	int length;
	char *copy;
	const char *result;

	result = json_object_to_json_string_length(obj, flags, &length);
	copy = strdup(result);
	if (copy == NULL)
		printf("to_json_string: Allocation failed!\n");
	else {
		result = json_object_to_json_string_ext(obj, flags);
		if (length != strlen(result))
			printf("to_json_string: Length mismatch!\n");
		if (strcmp(copy, result) != 0)
			printf("to_json_string: Comparison Failed!\n");
		free(copy);
	}
	return result;
}
*/

int json_to_user(char *Json, pUser pusr)
{
	json_t *json;
	json_error_t error;

	printf("json_to_user %s n", pusr->name);
	json = json_loads(Json, 0, &error);
//	json = json_load_file(*Json, JSON_DISABLE_EOF_CHECK, &error);
	if (json == NULL)
	{
	//	y_log_message(Y_LOG_LEVEL_INFO, "CreateUserLogin - \n\tk=%s \n\tvalue=%s", key, val);
	//  LOG_PRINT(LOGLEVEL_ERROR, "Loading json string failed: %s - %s; pos=%u\n",
	  //                           error.text, error.source, error.position);
		printf("Loading json string failed: %s - %s; pos=%u\n",
	    		error.text, error.source, error.position);
	  return 1;
	}

	printf("Parse Json Name \n");
	//Name
	json_t *name = NULL;
	name = json_object_get(json, "Name");
	if (!name || !json_is_string(name))
	{
	  //status = ERROR;
	  printf("Parse Json Name Error!\n");
	  return 1;
	}
	//pusr->name=(char *)malloc((strlen(json_object_get_string(name)) + 1) * sizeof(char));
	pusr->name=(char *)malloc((strlen(json_string_value(name)) + 1) * sizeof(char));
	strcpy(pusr->name, json_string_value(name));
	json_decref(name);
	printf("Parsed Json Name %s\n", pusr->name);

	//Password
	json_t *password = NULL;
	password = json_object_get(json, "Password");
	if (!password || !json_is_string(password))
	{
		//status = ERROR;
		printf("Parse Json Password Error!\n");
		return 2;
	}

	//pusr->password=(char *)malloc((strlen(json_object_get_string(password)) + 1) * sizeof(char));
	pusr->password=(char *)malloc((strlen(json_string_value(password)) + 1) * sizeof(char));
	strcpy(pusr->password, json_string_value(password));
	json_decref(password);
	printf("Parsed Json Password %s\n", pusr->password);

	// Email
    json_t *email = NULL;
	email = json_object_get(json, "Email");
	if (!email || !json_is_string(email))
	{
		//status = ERROR;
		printf("Parse Json Email Error!\n");
		return 3;
	}
	pusr->email=(char *)malloc((strlen(json_string_value(email)) + 1) * sizeof(char));
	strcpy(pusr->email, json_string_value(email));
	json_decref(email);
	printf("Parsed Json Email %s\n", pusr->email);
	
	// ID - Wallet Address 
	// prove you own it or 
	// we will create one for you (not ideal/safe)
	/*json_t *id = 0;
	id = json_object_get(json, "Id");
	if (!id  || !json_is_integer(id))
	{
		//status = ERROR;
		return 4;
	}
	// id now equal to json_t object of type int.
	pusr->id = json_integer_value(id);
*/
	if (pusr->name!=0)
		printf("Name: %s\n", pusr->name);
	//printf("Id: %d\n", pusr->id);
	if (pusr->password!=0)
		printf("Password: %s\n", pusr->password);
	if (pusr->email!=0) 
		printf("Email: %s\n", pusr->email);

	return 0;
}

int user_to_json(pUser pUsr, const char *json)
{
	char *s = NULL;
	json_t *root = json_object();

	if (pUsr->name)
		json_object_set_new( root, "name", json_string( pUsr->name ));
	if (pUsr->password)
		json_object_set_new( root, "password", json_string( pUsr->password ));
  	if (pUsr->id)
	  	json_object_set_new( root, "id", json_integer( pUsr->id ));
	if (pUsr->email)
		json_object_set_new( root, "email", json_string( pUsr->email ));
		
  	s = json_dumps(root, NULL);
	printf("user_to_json = %s",s);
  	puts(s);
	json = malloc ( strlen(s)  +1);
	sprintf(json, "%s", s);
	free(s);
	printf("user_to_json json = %s", json);
	return 0;
}

static void *secure_malloc(size_t size)
{
    /* Store the memory area size in the beginning of the block */
    void *ptr = malloc(size + 8);
    *((size_t *)ptr) = size;
    return ptr + 8;
}

static void secure_free(void *ptr)
{
    size_t size;

    ptr -= 8;
    size = *((size_t *)ptr);

//    guaranteed_memset(ptr, 0, size + 8);
    free(ptr);
}

