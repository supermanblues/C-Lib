CC=clang
TARGET=main
OBJS=queue.o linkqueue.o main.o
LIBS=-lslist -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) *.o *.a *.so $(TARGET)

test:
	@$(MAKE) clean
	@$(MAKE)
	@./$(TARGET)

package:
	@$(MAKE) test

	$(AR) -r libqueue.a queue.o
	$(AR) -r liblinkqueue.a linkqueue.o
	$(CC) -shared -fpic -o libqueue.so queue.o
	$(CC) -shared -fpic -o liblinkqueue.so linkqueue.o ../llist/slist.c

install:
	@$(MAKE) package

	cp queue.h linkqueue.h /usr/local/include/
	cp libqueue.a liblinkqueue.a libqueue.so liblinkqueue.so /usr/local/lib/