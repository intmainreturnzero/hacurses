CFLAGS=-g
CC=gcc

all: hacurses

hacurses: bin/hacurses 
	
bin/hacurses: hacurses/hacurses.c bin/libhabicurl.so
	$(CC) $(CFLAGS) -I./habicurl -L./bin -lncurses -lcurl -ljson-c -lhabicurl hacurses/hacurses.c -o bin/hacurses 

bin/libhabicurl.so: bin/common.o bin/habicurl.o bin/tags.o bin/cron.o bin/tasks.o bin/tasks_helpers.o
	$(CC) $(CFLAGS) -shared -o bin/libhabicurl.so bin/common.o bin/habicurl.o bin/tags.o bin/cron.o bin/tasks.o bin/tasks_helpers.o

bin/tasks_helpers.o: habicurl/common.h habicurl/habicurl_tasks.h habicurl/habicurl_tasks_helpers.c
	$(CC) $(CFLAGS) -fPIC -c -lcurl -ljson-c habicurl/habicurl_tasks_helpers.c -o bin/tasks_helpers.o

bin/tasks.o: habicurl/common.h habicurl/habicurl_user.h habicurl/habicurl_tasks.h habicurl/habicurl_tasks.c
	$(CC) $(CFLAGS) -fPIC -c -lcurl -ljson-c habicurl/habicurl_tasks.c -o bin/tasks.o 

bin/cron.o:  habicurl/common.h habicurl/habicurl_cron.h habicurl/habicurl_cron.c
	$(CC) $(CFLAGS) -fPIC -c -lcurl -ljson-c habicurl/habicurl_cron.c -o bin/cron.o 

bin/tags.o: habicurl/common.h habicurl/habicurl_tags.h habicurl/habicurl_tags.c
	$(CC) $(CFLAGS) -fPIC -c -lcurl -ljson-c habicurl/habicurl_tags.c -o bin/tags.o 

bin/habicurl.o: habicurl/habicurl.h habicurl/habicurl.c
	$(CC) $(CFLAGS) -fPIC -c -lcurl habicurl/habicurl.c -o bin/habicurl.o 

bin/common.o: habicurl/common.h habicurl/common.c
	$(CC) $(CFLAGS) -fPIC -c -lcurl habicurl/common.c -o bin/common.o 

prepare:
	mkdir -p bin
	mkdir -p testbin

clean:
	rm -r ./bin
	rm -r ./testbin

tests: testbin/valgrind_common

testbin/common_get_new_string: habicurl/common.c habicurl/tests/common_get_new_string_tests.c
	gcc -lcmocka -lcurl -ljson-c habicurl/common.c habicurl/tests/common_get_new_string_tests.c -o testbin/common_get_new_string
	gcc -g -lcmocka -lcurl -Wl,--wrap=json_object_new_array,--wrap=json_object_object_add,--wrap=json_object_new_string,--wrap=json_object_array_add,--wrap=array_list_get_idx,--wrap=json_object_get_string habicurl/common.c habicurl/tests/common_get_new_string_tests.c -o testbin/common_get_new_string

testbin/common_json_object_add_array: habicurl/common.c habicurl/tests/common_json_object_add_array.c
	gcc -g -lcmocka -lcurl -Wl,--wrap=json_object_new_array,--wrap=json_object_object_add,--wrap=json_object_new_string,--wrap=json_object_array_add,--wrap=array_list_get_idx,--wrap=json_object_get_string habicurl/common.c habicurl/tests/common_json_object_add_array.c -o testbin/common_json_object_add_array

testbin/valgrind_common: habicurl/common.c habicurl/tests/valgrind_common.c
	gcc -g -I./habicurl -ljson-c -lcurl habicurl/common.c habicurl/tests/valgrind_common.c -o testbin/valgrind_common 
