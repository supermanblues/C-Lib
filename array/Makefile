CC=clang
TARGET=main
OBJS= ../common/test-utils.o array.o main.o
#LIBS=-ltest-utils
CFLAGS+=-std=c11 -g -Wall -O0

default:test

$(TARGET):$(OBJS)
	$(CC) -o $@ $^

clean:
	$(RM) $(OBJS) *.a *.so $(TARGET)

test:
	@$(MAKE) clean
	@$(MAKE) $(TARGET)
	@./$(TARGET)

package:
	@$(MAKE) test

	$(AR) -r libarray.a array.o
	$(CC) -shared -fpic -o libarray.so array.o

install:
	$(MAKE) package

	cp array.h /usr/local/include/
	cp libarray.a libarray.so /usr/local/lib/
