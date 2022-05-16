CC=clang
OBJS=main.o stack.o ../array/array.o ../sort/sort.o linkstack.o ../llist/slist.o ../common/test-utils.o
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
	
	ar -r libstack.a stack.o
	ar -r libarray.a ../array/array.o
	ar -r libsort.a ../sort/sort.o
	ar -r liblinkstack.a ../stack/linkstack.o
	ar -r libslist.a ../llist/slist.o

	cp stack.h ../array/array.h ../sort/sort.h ../stack/linkstack.h ../llist/slist.h /usr/local/include/
	cp libstack.a libarray.a libsort.a liblinkstack.a libslist.a /usr/local/lib/