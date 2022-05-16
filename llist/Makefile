CC=clang
OBJS=main.o slist.o llist.o ../common/test-utils.o
CFLAGS+=-std=c11 -c -Wall -O2

main:$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS) *.a main

package:
	$(MAKE) clean
	$(MAKE)
	
	ar -r libslist.a ../llist/slist.o
	ar -r libllist.a ../llist/llist.o

	cp slist.h llist.h /usr/local/include/
	cp libslist.a libllist.a /usr/local/lib/