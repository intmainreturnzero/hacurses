#include <curl/curl.h>
#include <stdlib.h>
#include <json-c/json.h>

#include "common.h"
#include "habicurl_tasks.h"

// POST /tasks/user
void habicurl_create_task_for_user(char *user_id, char *api_key, struct task* task_to_create)
{
    CURL *curl = curl_easy_init();
    CURLcode res;

    struct memory_struct *chunk = get_memory_struct_chunk();

    json_bool success_value;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://habitica.com/api/v3/tasks/user");

        // Set user headers
        struct curl_slist *headers = add_auth_headers(user_id, api_key);
        headers = add_content_type_header(headers);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)chunk);

        // Set method to POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        json_object *task_json = json_object_new_object();

        // Form the task JSON object
        json_object_object_add(task_json, "text", json_object_new_string(task_to_create->text));
        json_object_object_add(task_json, "type", json_object_new_string(task_to_create->type));
        // add tags array
        json_object_add_array_from_null_term_list(task_json, "tags", task_to_create->tags);
        json_object_add_string_not_null(task_json, "alias", task_to_create->alias);
        json_object_add_string_not_null(task_json, "attribute", task_to_create->attribute);
        json_object_object_add(task_json, "collapse_check_list", json_object_new_boolean(task_to_create->collapse_check_list));
        json_object_add_string_not_null(task_json, "notes", task_to_create->notes);
        
        const char *json_body = json_object_to_json_string(task_json);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            return;
        }
        else
        {
            json_object *jobj = json_tokener_parse(chunk->memory);
            struct json_object *success_prop;

            json_pointer_get(jobj, "/success", &success_prop);
            success_value = json_object_get_boolean(success_prop);
        }

        curl_slist_free_all(headers);
        json_object_put(task_json);
    }

    curl_easy_cleanup(curl);
    free_memory_struct_chunk(chunk);

    return;
}

// GET /tasks/user
struct task_list* habicurl_get_tasks_for_user(char *user_id, char *api_token, char *task_type)
{
    // Habitica API requires this API call to be passed with a plural value of task_type
    char *plural_task_type = get_plural_task_type(task_type);

    if (plural_task_type == NULL)
    {
        return NULL;
    }

    CURL *curl = curl_easy_init();
    CURLcode res;

    struct memory_struct *chunk = get_memory_struct_chunk();

    json_bool success_value;
    
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://habitica.com/api/v3/tasks/user");

        // Set user headers
        struct curl_slist *headers = add_auth_headers(user_id, api_token);
        headers = add_content_type_header(headers);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)chunk);
        
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            return;
        }
        else
        {
            json_object *jobj = json_tokener_parse(chunk->memory);
            struct json_object *success_prop;

            json_pointer_get(jobj, "/success", &success_prop);
            success_value = json_object_get_boolean(success_prop);

            if (success_value)
            {
                struct json_object *data_array;
                json_pointer_get(jobj, "/data", &data_array);

                struct array_list *tasks_list = json_object_get_array(data_array);
                size_t length = tasks_list->length;
                struct tasks_list *task_list = calloc(1, sizeof(struct tasks_list));
                struct task *tasks = calloc(length, sizeof(struct task));
                
                for(int i = 0; i < length; i++)
                {
                    json_object *array_elem = (struct json_object *)(array_list_get_idx(tasks_list, i));


                }
                return task_list;

            }
        }

    }

}
