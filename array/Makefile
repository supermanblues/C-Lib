CC:=clang
TARGET:=main
OBJS:=$(patsubst %.c, %.o, $(wildcard ../common/test*.c *.c))
CFLAGS+=-std=c11 -g -Wall -O0

default:test

$(TARGET):$(OBJS)
	$(CC) -o $@ $^

.PHONY:clean
clean:
	$(RM) $(OBJS) *.a *.so $(TARGET)

.PHONY:test
test:
	@$(MAKE) clean
	@$(MAKE) $(TARGET)
	@./$(TARGET)

.PHONY:package
package:
	@$(MAKE) test

	$(AR) -r libarray.a array.o
	$(CC) -shared -fpic -o libarray.so array.o

.PHONY:install
install:
	$(MAKE) package

	cp array.h /usr/local/include/
	cp libarray.a libarray.so /usr/local/lib/

