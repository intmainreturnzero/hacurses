#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>

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

    snprintf(user_id_header, 37, "x-api-user: %s\0", user_id);
    snprintf(api_key_header, 37, "x-api-key: %s\0", api_key);

    headers = curl_slist_append(headers, user_id_header);
    headers = curl_slist_append(headers, api_key_header);

    return headers;
}

void habicurl_get_tags(char* user_id, char* api_key) 
{
    CURL* curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://habitica.com/api/v3/tags");

        curl_easy_cleanup(curl);
    }
}
