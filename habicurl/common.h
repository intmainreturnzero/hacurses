#include <json-c/json.h>

#define UUID_SIZE_WITH_NULL 38

// Struct required for constucting CURL reponse in-memory
// Refer https://curl.haxx.se/libcurl/c/getinmemory.html

struct memory_struct
{
    char *memory;
    size_t size;
};

size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp);

struct memory_struct* get_memory_struct_chunk();

void free_memory_struct_chunk(struct memory_struct *chunk);

struct curl_slist* add_auth_headers(char* user_id, char* api_key);

struct curl_slist* add_content_type_header(struct curl_slist *headers);

void json_object_add_string_not_null(json_object *jobj, char *key, char *string_to_add);

void json_object_add_array_from_null_term_list(json_object *jobj, char *key, char **list);

char* get_new_string(char *string_to_copy, size_t size_max);

char** get_null_term_string_array_from_array_list(array_list *list_ptr, size_t string_size_max);
