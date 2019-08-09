#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "habicurl_tasks.h"

int is_valid_task_type(char* type)
{
    if (type == NULL)
    {
        return 0;
    }
    else if (strncmp(type, TASK_TYPE_HABIT, 5) == 0 ||
            strncmp(type, TASK_TYPE_DAILY, 5) == 0 ||
            strncmp(type, TASK_TYPE_TODO, 4) == 0 ||
            strncmp(type, TASK_TYPE_REWARD, 6))
    {
        return 1;
    }
    return 0;
}

struct task* task_create_task(char *text, char *type)
{
    if (text != NULL && !is_valid_task_type(type))
    {
        return NULL;
    }

    struct task *task_obj = calloc(1, sizeof(struct task));
   
    task_obj->text = get_new_string(text, TASK_SIZE_TEXT);
    task_obj->type = get_new_string(type, TASK_SIZE_TYPE);
    task_obj->tags = NULL;

    return task_obj;
}

struct task* task_create_empty_task()
{
    struct task *task_obj = calloc(1, sizeof(struct task));

    task_obj->tags = NULL;

    return task_obj;
}

void task_add_tag(struct task *task_obj, char *tag_uuid)
{
    if (task_obj == NULL || tag_uuid == NULL)
    {
        return; 
    }

    int curr_size = 0;
    char **new_list;
    if (task_obj->tags == NULL)
    {
        new_list = calloc(2, sizeof(char*));
    }
    else
    {
        while (task_obj->tags[curr_size] != NULL)
        {
            curr_size++;
        }

        new_list = calloc((curr_size + 2), sizeof(char*));
        memcpy(new_list, task_obj->tags, curr_size * sizeof(char*));
    }
    new_list[curr_size] = get_new_string(tag_uuid, UUID_SIZE_WITH_NULL);
    new_list[curr_size + 1] = NULL;

    free(task_obj->tags);
    task_obj->tags = new_list;
}

void task_add_alias(struct task *task_obj, char *alias)
{
    if (task_obj == NULL || alias == NULL)
    {
        return;
    }

    task_obj->alias = get_new_string(alias, TASK_SIZE_ALIAS);
}

void task_free_object(struct task *task_ptr)
{
    if (task_ptr == NULL)
    {
        return;
    }

    free(task_ptr->text);
    free(task_ptr->type);

    int offset = 0;
    if (task_ptr->tags != NULL) 
    {
        while (task_ptr->tags[offset] != NULL)
        {
            free(task_ptr->tags[offset]);
            offset++;
        }
        free(task_ptr->tags);
    }
    
    free(task_ptr->alias);
    free(task_ptr->attribute);
    free(task_ptr->notes);
    free(task_ptr->date);

    offset = 0;
    if (task_ptr->reminders != NULL)
    {
        while (task_ptr->reminders[offset] != NULL)
        {
            free(task_ptr->reminders[offset]);
            offset++;
        }
        free(task_ptr->reminders);
    }

    free(task_ptr->frequency);
    free(task_ptr->repeat);
    free(task_ptr->start_date);

    free(task_ptr);
    
}
