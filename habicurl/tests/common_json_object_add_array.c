#include <stddef.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

#include <json-c/json.h>
#include "../common.h"

int __wrap_json_object_object_add(struct json_object *obj, const char *key, struct json_object *val)
{
    function_called();
    check_expected(obj);
    check_expected(key);
    check_expected(val);
    return 0;
}

struct json_object* __wrap_json_object_new_string(const char *s)
{
    // char *test_val = mock();
    function_called();
    check_expected(s);
    return mock_ptr_type(json_object *);
}

struct json_object* __wrap_json_object_new_array(void)
{
    json_object *jobj = mock_ptr_type(json_object *);
    function_called();
    return jobj;
}

int __wrap_json_object_array_add(struct json_object *obj, struct json_object *val)
{
    function_called();
    check_expected(obj);
    check_expected(val);
    return 0;
}

int __wrap_array_list_get_idx(struct array_list *al, size_t i)
{
    return 0;
}

const char* __wrap_json_object_get_string(struct json_object *obj)
{
    return "test";
}

void test_1()
{
    char *array_ptr;
    char **new_string_ptrs = malloc(3 * sizeof(char*));
    char **list = calloc(4, sizeof(char*));
    list[0] = malloc(10 * sizeof(char));
    list[0] = "test1";
    list[1] = malloc(10 * sizeof(char));
    list[1] = "test_abc";
    list[2] = malloc(10 * sizeof(char));
    list[2] = "test_!@#";

    will_return(__wrap_json_object_new_array, array_ptr);
    
    will_return(__wrap_json_object_new_string, new_string_ptrs[0]);
    will_return(__wrap_json_object_new_string, new_string_ptrs[1]);
    will_return(__wrap_json_object_new_string, new_string_ptrs[2]);
    
    expect_function_calls(__wrap_json_object_new_array, 1);
    for (int i = 0; i < 3; i++)
    {
        expect_function_calls(__wrap_json_object_new_string, 1);
        expect_value(__wrap_json_object_new_string, s, list[i]);
        expect_function_calls(__wrap_json_object_array_add, 1);
        expect_value(__wrap_json_object_array_add, obj, array_ptr);
        expect_value(__wrap_json_object_array_add, val, new_string_ptrs[i]);
    }
    expect_function_calls(__wrap_json_object_object_add, 1);
    expect_value(__wrap_json_object_object_add, obj, array_ptr);
    expect_string(__wrap_json_object_object_add, key, "test");
    expect_value(__wrap_json_object_object_add, val, array_ptr);


    json_object_add_array_from_null_term_list((json_object*) array_ptr, "test", list);
}

int main(void)
{
    const struct CMUnitTest tests[] = 
    {
        cmocka_unit_test(test_1)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
