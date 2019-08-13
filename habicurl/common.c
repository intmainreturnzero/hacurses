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

struct memory_struct* get_memory_struct_chunk()
{
    struct memory_struct *chunk = malloc(sizeof(struct memory_struct));
    chunk->memory = malloc(1);
    chunk->size = 0;

    return chunk;
}

void free_memory_struct_chunk(struct memory_struct *chunk)
{
    free(chunk->memory);
    free(chunk);
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

    free(user_id_header);
    free(api_key_header);

    return headers;
}

struct curl_slist* add_content_type_header(struct curl_slist *headers)
{
    return curl_slist_append(headers, "Content-Type: application/json"); 
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

char* get_new_string(char *string_to_copy, size_t size_max)
{
    if (string_to_copy == NULL)
    { 
        return NULL;
    }

    char *new_string = calloc(size_max, sizeof(char));   
    snprintf(new_string, size_max, string_to_copy);

    return new_string;
}

char** get_null_term_string_array_from_array_list(array_list *list_ptr, size_t string_size_max)
{
    if (list_ptr == NULL)
    {
        return NULL;
    }
    
    size_t length = list_ptr->length;
    char **list = calloc(length + 1, sizeof(char*));

    for (int i = 0; i < length; i++)
    {
        list[i] = calloc(string_size_max, sizeof(char));

        json_object *array_elem = (struct json_object *)(array_list_get_idx(list_ptr, i));
        list[i] = get_new_string(json_object_get_string(array_elem), string_size_max);
    }

    list[length] = NULL;

    return list;
}
