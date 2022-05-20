CC=clang
TARGET=main
OBJS=main.o common.o test-utils.o
CFLAGS+=-std=c11 -g -Wall -O2

${TARGET}:$(OBJS)
	$(CC) $^ -o $@

clean:
	$(RM) $(OBJS) *.a ${TARGET}

package:
	$(MAKE) clean
	$(MAKE)

	${AR} -r libcommon.a common.o
	${AR} -r libtest-utils.a test-utils.o

	cp common.h test-utils.h /usr/local/include/
	cp libcommon.a libtest-utils.a /usr/local/lib/