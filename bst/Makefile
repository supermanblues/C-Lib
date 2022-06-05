CC:=clang
TARGET:=main
OBJS:=$(patsubst %.c, %.o, $(wildcard *.c))
LIBS=-larray -llinkstack -llinkqueue -lslist -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O0

default:test

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBS)

# -DBST_TRAVEL_ITER_IMPL
bst.o:bst.c
	$(CC) $(CFLAGS)   -c -o $@ $^

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

	$(AR) -r libbst.a bst.o
	$(CC) -shared -fpic -o libbst.so bst.o ../queue/linkqueue.c ../list/slist.c

.PHONY:install
install:
	@$(MAKE) package

	cp bst.h /usr/local/include/
	cp libbst.a libbst.so /usr/local/lib/
