// Data contracts start here

struct tag
{
    const char *tag_id;
    const char *tag_name;

};

struct tags_list
{
    struct tag *tags;
    int tag_count;
};

// API functions start here
// One-time init function that initializes cURL globally internally
void habicurl_init();

struct tags_list* habicurl_get_tags(char* user_id, char* api_key);
