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

clean:
	rm -r ./bin
