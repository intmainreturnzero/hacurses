#include <stddef.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

#include <json-c/json.h>
#include "../common.h"

int __wrap_json_object_object_add(struct json_object *obj, const char *key, struct json_object *val)
{
    return 0;
}

struct json_object* __wrap_json_object_new_string(const char *s)
{
    return NULL;
}

struct json_object* __wrap_json_object_new_array(void)
{
    return NULL;
}

int __wrap_json_object_array_add(struct json_object *obj, struct json_object *val)
{
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

void verify_get_new_string(void **state)
{
    (void) state;

    char *ret = get_new_string("test", 5);
    assert_string_equal("test", ret);

    ret = get_new_string(NULL, 10);
    assert_null(ret);

    ret = get_new_string("some_long_string", 5);
    assert_string_equal("some", ret);
}

int main(void)
{
    const struct CMUnitTest tests[] = 
    {
        cmocka_unit_test(verify_get_new_string)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
