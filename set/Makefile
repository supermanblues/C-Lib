CC=clang
TARGET=main
OBJS=main.o set.o
LIBS=-lbst -llinkqueue -lslist -ltest-utils
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
	
	$(AR) -r libset.a set.o
	$(CC) -shared -fpic -o libset.so set.o ../bst/bst.c ../queue/linkqueue.c ../llist/slist.c

install:
	$(MAKE) package

	cp set.h /usr/local/include/
	cp libset.a libset.so /usr/local/lib/