CC=clang
TARGET=main
OBJS=main.o array.o
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

	$(AR) -r libarray.a array.o
	$(CC) -shared -fpic -o libarray.so array.o

install:
	$(MAKE) package

	cp array.h /usr/local/include/
	cp libarray.a libarray.so /usr/local/lib/