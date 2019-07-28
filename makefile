all: hacurses

rebuild: clean all

hacurses: hacurses.c libhabicurl
	gcc -g -I. -L. -lncurses -lcurl -ljson-c -lhabicurl hacurses.c -o hacurses 

libhabicurl: habicurl.c
	gcc -g -fPIC -c -lcurl -ljson-c -o habicurl.o habicurl.c
	gcc -g -shared -o libhabicurl.so habicurl.o

clean:
	rm *.o
	rm *.so
	rm hacurses
