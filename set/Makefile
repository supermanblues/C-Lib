CC:=clang
TARGET:=main
OBJS:=$(patsubst %.c, %.o, $(wildcard *.c))
LIBS:=-lbst -llinkqueue -lslist -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O0

default:test

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBS)

.PHONY:clean
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
	
	$(AR) -r libset.a set.o
	$(CC) -shared -fpic -o libset.so set.o ../bst/bst.c ../queue/linkqueue.c ../list/slist.c

.PHONY:install
install:
	$(MAKE) package

	cp set.h /usr/local/include/
	cp libset.a libset.so /usr/local/lib/
