#include <curl/curl.h>
#include <stdlib.h>
#include <json-c/json.h>

#include "common.h"
#include "habicurl_cron.h"

// POST cron
int habicurl_run_cron(char* user_id, char* api_key)
{
    CURL *curl = curl_easy_init();
    CURLcode res;

    struct memory_struct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    json_bool success_value;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://habitica.com/api/v3/cron");

        // Set user ID and API key headers
        struct curl_slist* headers = add_auth_headers(user_id, api_key);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // Set method to POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            return -1; // Failure
        }
        else
        {
            json_object *jobj = json_tokener_parse(chunk.memory);
            struct json_object *success_prop;

            json_pointer_get(jobj, "/success", &success_prop);
            success_value = json_object_get_boolean(success_prop);
        }
    }

    curl_easy_cleanup(curl);
    free(chunk.memory);

    if (success_value == 1)
    {
        return 0; // Success
    }

    return -1; // Failure
}
