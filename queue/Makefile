CC=clang
TARGET=main
OBJS=main.o queue.o linkqueue.o
LIBS=-lslist -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) *.a $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)

	$(AR) -r libqueue.a queue.o
	$(AR) -r liblinkqueue.a linkqueue.o

	cp queue.h linkqueue.h /usr/local/include/
	cp libqueue.a liblinkqueue.a /usr/local/lib/

