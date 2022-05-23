CC=clang
TARGET=main
OBJS=slist.o llist.o main.o
LIBS=-ltest-utils
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
	
	$(AR) -r libslist.a slist.o
	$(AR) -r libllist.a llist.o
	$(CC) -shared -fpic -o libslist.so slist.o
	$(CC) -shared -fpic -o libllist.so llist.o

install:
	$(MAKE) package

	cp slist.h llist.h /usr/local/include/
	cp libslist.a libllist.a libslist.so libllist.so /usr/local/lib/