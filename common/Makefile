CC=clang
TARGET=main
OBJS=common.o test-utils.o main.o
CFLAGS+=-std=c11 -g -Wall -O0

default:test

${TARGET}:$(OBJS)
	$(CC) $^ -o $@

clean:
	$(RM) *.o *.a *.so ${TARGET}

test:
	@$(MAKE) clean
	@$(MAKE) $(TARGET)
	@./$(TARGET)

package:
	@$(MAKE) test
	
	${AR} -r libcommon.a common.o
	${AR} -r libtest-utils.a test-utils.o

	$(CC) -shared -fpic -o libcommon.so common.o
	$(CC) -shared -fpic -o libtest-utils.so test-utils.o

install:
	$(MAKE) package

	cp common.h test-utils.h /usr/local/include/
	cp libcommon.a libtest-utils.a libcommon.so libtest-utils.so /usr/local/lib/
