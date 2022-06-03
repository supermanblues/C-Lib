CC=clang
TARGET=main
OBJS=../common/test-utils.o bst.o main.o 
LIBS=-larray -llinkstack -llinkqueue -lslist
CFLAGS+=-std=c11 -g -Wall -O2

default:test

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# -DBST_TRAVEL_ITER_IMPL
bst.o:bst.c
	$(CC) $(CFLAGS)   -c -o $@ $^

clean:
	$(RM) $(OBJS) *.a *.so $(TARGET)

test:
	@$(MAKE) clean
	@$(MAKE) $(TARGET)
	@./$(TARGET)

package:
	@$(MAKE) test

	$(AR) -r libbst.a bst.o
	$(CC) -shared -fpic -o libbst.so bst.o ../queue/linkqueue.c ../llist/slist.c

install:
	@$(MAKE) package

	cp bst.h /usr/local/include/
	cp libbst.a libbst.so /usr/local/lib/
