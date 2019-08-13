#include <json-c/json.h>

#include "habicurl_user.h"

// Common macros/structs related to tasks
// TODO: Following lengths need to be verified
#define TASK_SIZE_TEXT 51
#define TASK_SIZE_TYPE 7
#define TASK_SIZE_TAG 51
#define TASK_SIZE_ALIAS 51
#define TASK_SIZE_NOTES 101
#define TASK_SIZE_DATE 51 // TODO: Clean this

#define TASK_TYPE_HABIT "habit"
#define TASK_TYPE_DAILY "daily"
#define TASK_TYPE_TODO "todo"
#define TASK_TYPE_REWARD "reward"

#define TASK_PRIORITY_TRIVIAL 0.1
#define TASK_PRIORITY_EASY 1
#define TASK_PRIORITY_MEDIUM 1.5
#define TASK_PRIORITY_HARD 2

#define TASK_FREQUENCY_DAILY "daily"
#define TASK_FREQUENCY_WEEKLY "weekly"

#define TASK_REPEAT_DAY_SUN "su"
#define TASK_REPEAT_DAY_MON "m"
#define TASK_REPEAT_DAY_TUE "t"
#define TASK_REPEAT_DAY_WED "w"
#define TASK_REPEAT_DAY_THU "th"
#define TASK_REPEAT_DAY_FRI "f"
#define TASK_REPEAT_DAY_SAT "s"

#define TASK_ATTR_TEXT "text"
#define TASK_ATTR_TYPE "type"
#define TASK_ATTR_TAGS "tags"
#define TASK_ATTR_ALIAS "alias"
#define TASK_ATTR_ATTRIBUTE "attribute"
#define TASK_ATTR_COLLAPSE_CHECKLIST "collapseChecklist"
#define TASK_ATTR_NOTES "notes"
#define TASK_ATTR_DATE "date"
#define TASK_ATTR_PRIORITY "priority"
#define TASK_ATTR_REMINDERS "reminders"
#define TASK_ATTR_FREQUENCY "frequency"
#define TASK_ATTR_REPEAT "repeat"
#define TASK_ATTR_EVERYX "everyX"
#define TASK_ATTR_STREAK "streak"
#define TASK_ATTR_START_DATE "startDate"
#define TASK_ATTR_UP "up"
#define TASK_ATTR_DOWN "down"
#define TASK_ATTR_VALUE "value"

// Structs related to tasks

struct task_reminder
{
    char *uuid;
    char *start_date;
    char *time;
};

struct task_repeat
{
    int sunday;
    int monday;
    int tuesday;
    int wednesday;
    int thursday;
    int friday;
    int saturday;
};

struct task
{
    char *text;
    char *type; // One of TASK_TYPE_* macro values
    // Optional parameters below
    char **tags; // NULL-terminated list of tag UUIDs
    char *alias;
    char *attribute; // One of USER_ATTR_* macro values
    int collapse_check_list;
    char *notes;
    char *date; // TODO: Improve the date format?
    float priority; // One of TASK_PRIORITY macro values
    struct task_reminder **reminders; // NULL-terminated list of reminders
    char *frequency;
    struct task_repeat *repeat;
    int every_x;
    int streak;
    char *start_date;
    int up;
    int down;
    double value;
};

struct tasks_list
{
    struct task *tasks;
    int length;
};

// Helper methods for tasks
struct task* task_create_task(char *text, char *type);
struct task* task_create_empty_task();
// TODO: Mark below methods to return int with proper error code handling
void task_add_tag(struct task *task_obj, char *tag_uuid);
void task_set_alias(struct task *task_obj, char *alias);
void task_set_collapse_check_list(struct task *task_obj, int collapse_check_list);
void task_set_notes(struct task *task_obj, char *notes);
void task_set_priority(struct task *task_obj, float priority);
void task_free_object(struct task *task_ptr);

// Possibly internal helper methods, but related to tasks
// TODO: Can be moved to a separate internal header file
char* get_plural_task_type(char *task_type);
struct task* get_task_from_json_object(json_object *jobj);

// API calls
void habicurl_create_task_for_user(char *user_id, char *api_key, struct task* task_to_create);
struct task_list* habicurl_get_tasks_for_user(char *user_id, char *api_token, char *task_type);
