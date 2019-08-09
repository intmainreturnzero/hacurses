#include <curl/curl.h>
#include <stdlib.h>
#include <json-c/json.h>

#include "common.h"
#include "habicurl_tasks.h"

// POST /tasks/user
void habicurl_create_todo_for_user(char *user_id, char *api_key, struct todo* todo_to_create)
{
    CURL *curl = curl_easy_init();
    CURLcode res;

    struct memory_struct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://habitica.com/api/v3/tasks/user");

        // Set user ID and API key headers
        struct curl_slist* headers = add_auth_headers(user_id, api_key);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set method to POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        json_object *todo_json = json_object_new_object();

        // Form the todo JSON object
        json_object_object_add(todo_json, "text", json_object_new_string(todo_to_create->text));
        json_object_object_add(todo_json, "type", json_object_new_string(todo_to_create->type));
        // add tags array
        json_object_add_array_from_null_term_list(todo_json, "tags", todo_to_create->tags);
        json_object_add_string_not_null(todo_json, "alias", todo_to_create->alias);
        
    }

}
