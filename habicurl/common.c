#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

#include "common.h"

size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    struct memory_struct *mem = (struct memory_struct *)userp;

    char *ptr = realloc(mem->memory, mem->size + real_size + 1);
    if (ptr == NULL)
    {
        // out of memory
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, real_size);
    mem->size += real_size;
    mem->memory[mem->size] = 0;

    return real_size;
}

struct curl_slist* add_auth_headers(char* user_id, char* api_key)
{
    struct curl_slist *headers = NULL;

    char *user_id_header = calloc(50, sizeof(char));
    char *api_key_header = calloc(49, sizeof(char));

    snprintf(user_id_header, 50, "x-api-user: %s", user_id);
    snprintf(api_key_header, 49, "x-api-key: %s", api_key);

    headers = curl_slist_append(headers, user_id_header);
    headers = curl_slist_append(headers, api_key_header);

    return headers;
}

void json_object_add_string_not_null(json_object *jobj, char *key, char *string_to_add)
{
    if (string_to_add != NULL)
    {
        json_object_object_add(jobj, key, json_object_new_string(string_to_add));
    }
}

void json_object_add_array_from_null_term_list(json_object *jobj, char *key, char **list)
{
    if (list != NULL)
        {
        // list is non-null, add the array
        json_object *array_json = json_object_new_array();

        int i = 0;
        while (list[i] != NULL)
        {
            json_object *element_json = json_object_new_string(list[i]);
            json_object_array_add(array_json, element_json);

            i++;
        }

        json_object_object_add(jobj, key, array_json);
    }
}
