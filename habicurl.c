#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

struct memory_struct
{
    char *memory;
    size_t size;
};

static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp)
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

const char* habitica_base_url = "https://habitica.com/api/v3/";

void habicurl_init()
{
    curl_global_init(CURL_GLOBAL_SSL);
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

void habicurl_get_tags(char* user_id, char* api_key) 
{
    CURL* curl = curl_easy_init();
    CURLcode res;

    struct memory_struct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://habitica.com/api/v3/tags");

        // Set user ID and API key headers
        struct curl_slist* headers = add_auth_headers(user_id, api_key);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl); 

        if (res != CURLE_OK)
        {
        }
        else
        {
        }

        curl_easy_cleanup(curl);

        json_object *jobj = json_tokener_parse(chunk.memory);
        struct json_object  *tag1obj;

        json_pointer_get(jobj, "/data/0/id", &tag1obj);
        char* tag1id1 = json_object_get_string(tag1obj);

        free(chunk.memory);
    }
}
