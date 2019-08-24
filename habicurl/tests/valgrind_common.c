#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <common.h>

void common_json_object_add_string_not_null()
{
    json_object *test_obj = json_object_new_object();

    json_object_add_string_not_null(test_obj, "test_key", "test_string");

    json_object_put(test_obj);
}

void common_json_object_add_array_from_null_term_list()
{
    json_object *test_obj = json_object_new_object();
    char **test_list = calloc(4, sizeof(char*));
    test_list[0] = "test1";
    test_list[1] = "test2";
    test_list[2] = "test3";

    json_object_add_array_from_null_term_list(test_obj, "attr", test_list);

    free(test_list);
    json_object_put(test_obj);
}

void common_get_new_string()
{
    char *test_string = get_new_string("some string", 12);

    free(test_string);
}

void common_get_null_term_string_array_from_array_list()
{
   char *json_str = "{\"test\":[\"bar\", \"baz\"]}";

   json_object *json_obj = json_tokener_parse(json_str);
   json_object *array_ptr;
   json_pointer_get(json_obj, "/test", &array_ptr);

   char** ret_val = get_null_term_string_array_from_array_list(array_ptr, 10);

   json_object_put(json_obj);
   int i = 0;
   while(ret_val[i] != NULL)
   {
       free(ret_val[i]);
       i++;
   }
   free(ret_val);
}

int main()
{
    common_json_object_add_string_not_null();
    common_json_object_add_array_from_null_term_list();
    common_get_new_string();
    common_get_null_term_string_array_from_array_list();
}
