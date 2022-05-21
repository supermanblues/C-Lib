CC=clang
TARGET=main
OBJS=main.o sort.o
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

	$(AR) -r libsort.a sort.o
	$(CC) -shared -fpic -o libsort.so sort.o

install:
	@$(MAKE) package

	cp sort.h /usr/local/include/
	cp libsort.a libsort.so /usr/local/lib/