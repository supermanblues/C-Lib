CC=clang
TARGET=main
OBJS=main.o union_find.o
LIBS=-larray -ltest-utils
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

	$(AR) -r libunion_find.a union_find.o
	$(CC) -shared -fpic -o libunion_find.so union_find.o ../array/array.c
	
install:
	$(MAKE) package

	cp union_find.h /usr/local/include/
	cp libunion_find.a libunion_find.so /usr/local/lib/