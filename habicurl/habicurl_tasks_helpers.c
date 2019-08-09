#include <stdlib.h>
#include <string.h>

#include "habicurl_tasks.h"

struct todo* todo_create_todo(char *text)
{
    struct todo *todo_obj = calloc(1, sizeof(struct todo));

    todo_obj->text = text;
    todo_obj->type = TASK_TYPE_TODO;
    todo_obj->tags = NULL;

    return todo_obj;
}

struct todo* todo_create_empty_todo()
{
    struct todo *todo_obj = calloc(1, sizeof(struct todo));

    todo_obj->tags = NULL;

    return todo_obj;
}

void todo_add_tag(struct todo *todo_obj, char *tag_uuid)
{
    if (todo_obj == NULL || tag_uuid == NULL)
    {
        return; 
    }

    int curr_size = 0;
    char **new_list;
    if (todo_obj->tags == NULL)
    {
        new_list = malloc(2 * sizeof(char*));
    }
    else
    {
        while (todo_obj->tags[curr_size] != NULL)
        {
            curr_size++;
        }

        new_list = malloc((curr_size + 2) * sizeof(char*));
        memcpy(new_list, todo_obj->tags, curr_size * sizeof(char*));
    }
    new_list[curr_size] = tag_uuid;
    new_list[curr_size + 1] = NULL;

    free(todo_obj->tags);
    todo_obj->tags = new_list;
}
