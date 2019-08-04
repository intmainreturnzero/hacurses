// Structs related to tags

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

// API functions related to tags
struct tags_list* habicurl_get_tags(char* user_id, char* api_key);
