CC=clang
OBJS=main.o common.o test-utils.o
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

	ar -r libcommon.a common.o

	cp common.h /usr/local/include/
	cp libcommon.a /usr/local/lib/