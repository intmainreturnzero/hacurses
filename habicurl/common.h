// Struct required for constucting CURL reponse in-memory
// Refer https://curl.haxx.se/libcurl/c/getinmemory.html

struct memory_struct
{
    char *memory;
    size_t size;
};

size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp);

struct curl_slist* add_auth_headers(char* user_id, char* api_key);
