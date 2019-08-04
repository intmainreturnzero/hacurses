all: hacurses

hacurses: bin/hacurses 
	
bin/hacurses: hacurses/hacurses.c bin/libhabicurl.so
	gcc -g -I./habicurl -L./bin -lncurses -lcurl -ljson-c -lhabicurl -o bin/hacurses hacurses/hacurses.c 

bin/libhabicurl.so: bin/common.o bin/habicurl.o bin/tags.o bin/cron.o
	gcc -g -shared -o bin/libhabicurl.so bin/common.o bin/habicurl.o bin/tags.o bin/cron.o

bin/cron.o:  habicurl/common.h habicurl/habicurl_cron.h habicurl/habicurl_cron.c
	gcc -g -fPIC -c -lcurl -ljson-c -o bin/cron.o habicurl/habicurl_cron.c

bin/tags.o: habicurl/common.h habicurl/habicurl_tags.h habicurl/habicurl_tags.c
	gcc -g -fPIC -c -lcurl -ljson-c -o bin/tags.o habicurl/habicurl_tags.c

bin/habicurl.o: habicurl/habicurl.h habicurl/habicurl.c
	gcc -g -fPIC -c -lcurl -o bin/habicurl.o habicurl/habicurl.c

bin/common.o: habicurl/common.h habicurl/common.c
	gcc -g -fPIC -c -lcurl -o bin/common.o habicurl/common.c

prepare:
	mkdir -p bin

clean:
	rm -r ./bin
