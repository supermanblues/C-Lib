CC=clang
TARGET=main
OBJS=main.o slist.o llist.o
LIBS=-ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) *.a $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)
	
	$(AR) -r libslist.a slist.o
	$(AR) -r libllist.a llist.o

	cp slist.h llist.h /usr/local/include/
	cp libslist.a libllist.a /usr/local/lib/