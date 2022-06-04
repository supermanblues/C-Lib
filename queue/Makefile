CC:=clang
TARGET:=main
OBJS:=queue.o linkqueue.o main.o
OBJS:=$(patsubst %.c, %.o, $(wildcard ../common/test*.c ../list/slist.c *.c))
CFLAGS+=-std=c11 -g -Wall -O0

default:test

$(TARGET):$(OBJS)
	$(CC) -o $@ $^

.PHONY:clean
clean:
	$(RM) $(OBJS) *.i *.a *.so $(TARGET)

.PHONY:test
test:
	@$(MAKE) clean
	@$(MAKE) $(TARGET)
	@./$(TARGET)

.PHONY:package
package:
	@$(MAKE) test

	$(AR) -r libqueue.a queue.o
	$(AR) -r liblinkqueue.a linkqueue.o
	$(CC) -shared -fpic -o libqueue.so queue.o
	$(CC) -shared -fpic -o liblinkqueue.so linkqueue.o ../list/slist.c

.PHONY:install
install:
	@$(MAKE) package

	cp queue.h linkqueue.h /usr/local/include/
	cp libqueue.a liblinkqueue.a libqueue.so liblinkqueue.so /usr/local/lib/
