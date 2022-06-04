CC:=clang
TARGET:=main
OBJS:=$(patsubst %.c, %.o, $(wildcard *.c))
CFLAGS+=-std=c11 -g -Wall -O0

default:test

${TARGET}:$(OBJS)
	$(CC) $^ -o $@

.PHONY: clean 
clean:
	$(RM) $(OBJS) *.a *.so ${TARGET}

.PHONY: test
test:
	@$(MAKE) clean
	@$(MAKE) $(TARGET)
	@./$(TARGET)

.PHONY: package 
package:
	@$(MAKE) test
	
	${AR} -r libcommon.a common.o
	${AR} -r libtest-utils.a test-utils.o

	$(CC) -shared -fpic -o libcommon.so common.o
	$(CC) -shared -fpic -o libtest-utils.so test-utils.o

.PHONY: install 
install:
	$(MAKE) package

	cp common.h test-utils.h /usr/local/include/
	cp libcommon.a libtest-utils.a libcommon.so libtest-utils.so /usr/local/lib/
