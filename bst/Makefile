CC=clang
TARGET=main
OBJS=bst.o main.o 
LIBS=-larray -llinkstack -llinkqueue -lslist -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# -DBST_TRAVEL_ITER_IMPL
bst.o:bst.c
	$(CC) $(CFLAGS)   -c -o $@ $^

clean:
	$(RM) *.o *.a *.so $(TARGET)

test:
	@$(MAKE) clean
	@$(MAKE)
	@./$(TARGET)

package:
	@$(MAKE) test

	$(AR) -r libbst.a bst.o
	$(CC) -shared -fpic -o libbst.so bst.o ../queue/linkqueue.c ../llist/slist.c

install:
	@$(MAKE) package

	cp bst.h /usr/local/include/
	cp libbst.a libbst.so /usr/local/lib/