CC:=clang
TARGET:=main
OBJS:=$(patsubst %.c, %.o, $(wildcard ../common/test*.c *.c))
CFLAGS+=-std=c11 -g -Wall -O2

default:test

$(TARGET):$(OBJS)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJS) *.a *.so $(TARGET)

.PHONY: test
test:
	@$(MAKE) clean
	@$(MAKE) $(TARGET)
	@./$(TARGET)

.PHONY: package
package:
	@$(MAKE) test
	
	$(AR) -r libslist.a slist.o
	$(AR) -r libllist.a llist.o
	$(CC) -shared -fpic -o libslist.so slist.o
	$(CC) -shared -fpic -o libllist.so llist.o

.PHONY: install
install:
	$(MAKE) package

	cp slist.h llist.h /usr/local/include/
	cp libslist.a libllist.a libslist.so libllist.so /usr/local/lib/
