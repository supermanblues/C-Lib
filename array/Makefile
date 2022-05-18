CC=clang
OBJS=main.o array.o ../common/test-utils.o
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

	cp array.h /usr/local/include/
	cp libarray.a /usr/local/lib/