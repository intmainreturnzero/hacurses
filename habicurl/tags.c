#include <curl/curl.h>
#include <stdlib.h>
#include <json-c/json.h>

#include "common.h"
#include "tags.h"

// GET tags
struct tags_list* habicurl_get_tags(char* user_id, char* api_key) 
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
        struct json_object *data_array;

        json_pointer_get(jobj, "/data", &data_array);

        struct array_list *tags_array_list = json_object_get_array(data_array);
        size_t length = tags_array_list->length;
        struct tags_list *tags_to_return= malloc(sizeof(struct tags_list));
        struct tag *tags = malloc(length * sizeof(struct tag));

        for (int i = 0; i < length; i++)
        {
            json_object *array_elem = (struct json_object *)(array_list_get_idx(tags_array_list, i));
            struct json_object *id_ptr, *name_ptr;
            json_pointer_get(array_elem, "/id", &id_ptr);
            json_pointer_get(array_elem, "/name", &name_ptr);
            const char *tag_id = json_object_get_string(id_ptr);
            const char *tag_name = json_object_get_string(name_ptr);
            
            tags[i].tag_id = tag_id;
            tags[i].tag_name = tag_name;
        }

        array_list_free(tags_array_list);

        tags_to_return->tags = tags;
        tags_to_return->tag_count = length;

        free(chunk.memory);

        return tags_to_return;
    }
}
