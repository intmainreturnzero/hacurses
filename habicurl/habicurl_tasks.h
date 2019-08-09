#include <stdbool.h>

#include "habicurl_user.h"

// Common macros/structs related to tasks
#define TASK_TYPE_HABIT "habit"
#define TASK_TYPE_DAILY "daily"
#define TASK_TYPE_TODO "todo"
#define TASK_TYPE_REWARD "reward"

#define TASK_PRIORITY_TRIVIAL 0.1
#define TASK_PRIORITY_EASY 1
#define TASK_PRIORITY_MEDIUM 1.5
#define TASK_PRIORITY_HARD 2

struct reminder
{
    char *uuid;
    char *start_date;
    char *time;
};

// Structs related to todos

struct todo
{
    char *text;
    char *type; // One of TASK_TYPE_* macro values
    // Optional parameters below
    char **tags; // NULL-terminated list of tag UUIDs
    char *alias;
    char *attribute; // One of USER_ATTR_* macro values
    bool collapse_check_list;
    char *notes;
    char *date; // TODO: Improve the date format?
    float priority; // One of TASK_PRIORITY macro values
    struct reminder **reminders; // NULL-terminated list of reminders
};

// Helper methods for todos
struct todo* todo_create_todo(char *text);
struct todo* todo_create_empty_todo();
// TODO: Mark below methods to return int with proper error code handling
void todo_add_tag(struct todo *todo_obj, char *tag_uuid);
void todo_set_alias(struct todo *todo_obj, char *alias);
void todo_set_collapse_check_list(struct todo *todo_obj, bool collapse_check_list);
void todo_set_notes(struct todo *todo_obj, char *notes);
void todo_set_priority(struct todo *todo_obj, float priority);
void todo_free_object(struct todo *todo_obj);
