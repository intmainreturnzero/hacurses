#include <ncurses.h>
#include <stdlib.h>

#include <habicurl.h>
#include <habicurl_tags.h>
#include <habicurl_cron.h>
#include <habicurl_tasks.h>

int g_ymax, g_xmax;
char *g_api_token, *g_api_user_id;

int check_api_requirements()
{
   g_api_token = getenv("HABITICA_API_TOKEN");
   g_api_user_id = getenv("HABITICA_API_USER_ID");

   return g_api_token != NULL && g_api_user_id != NULL;
} 

void print_api_key_absent()
{
    mvprintw((g_ymax/2)-1, 0, "No API token found.\n Please set the environment variable HABITICA_API_TOKEN to begin.");
}

void start()
{
    // Initialize habicurl
    habicurl_init();

    // struct tags_list *tags = habicurl_get_tags(g_api_user_id, g_api_token);
    // int return_code = habicurl_run_cron(g_api_user_id, g_api_token);
    struct task *task_ptr = task_create_task("some text", TASK_TYPE_TODO);
    task_add_tag(task_ptr, "d0d368ee-5f92-4c7a-9b2f-7bacabca0e30");
    task_add_tag(task_ptr, "3511f23f-2f9c-452d-8f4f-981e219f795a");
    habicurl_create_task_for_user(g_api_user_id, g_api_token, task_ptr);
}

int main() 
{
    // Do initialization and ncurses-related settings
    initscr();
    raw();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, g_ymax, g_xmax);

    int reqs_met = check_api_requirements();
    if (reqs_met == 0) 
    {
       print_api_key_absent();
    }

    start();
    getch();
    endwin();
    
    return 0;
}
