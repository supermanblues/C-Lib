CC:=clang
TARGET:=main 
OBJS:=stack.o linkstack.o main.o
OBJS:=$(patsubst %.c, %.o, \
	  $(wildcard ../array/array.c ../list/slist.c ../common/test*.c *.c))
CFLAGS+=-std=c11 -g -Wall -O0

default:test

$(TARGET):$(OBJS)
	$(CC) -o $@ $^

clean:
	$(RM) $(OBJS) *.i *.a *.so $(TARGET)

.PHONY:test
test:
	@$(MAKE) clean
	@$(MAKE) $(TARGET)
	@./$(TARGET)

.PHONY:package
package:
	@$(MAKE) test
	
	$(AR) -r libstack.a stack.o
	$(AR) -r liblinkstack.a linkstack.o
	$(CC) -shared -fpic -o libstack.so stack.o ../array/array.c
	$(CC) -shared -fpic -o liblinkstack.so linkstack.o ../list/slist.c

.PHONY:install
install:
	@$(MAKE) package

	cp stack.h linkstack.h /usr/local/include/
	cp libstack.a liblinkstack.a libstack.so liblinkstack.so /usr/local/lib/
