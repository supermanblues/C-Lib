CC=clang
OBJS=main.o array.o ../sort/sort.o ../common/test-utils.o
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

	ar -r libarray.a array.o
	ar -r libsort.a ../sort/sort.o

	cp array.h ../sort/sort.h /usr/local/include/
	cp libarray.a libsort.a /usr/local/lib/