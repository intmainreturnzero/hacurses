// Struct required for constucting CURL reponse in-memory
// Refer https://curl.haxx.se/libcurl/c/getinmemory.html

struct memory_struct
{
    char *memory;
    size_t size;
};

size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp);

struct curl_slist* add_auth_headers(char* user_id, char* api_key);

void json_object_add_string_not_null(json_object *jobj, char *key, char *string_to_add);

void json_object_add_array_from_null_term_list(json_object *jobj, char *key, char **list);

