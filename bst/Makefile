CC=clang
TARGET=main
OBJS=main.o bst.o
LIBS=-larray -llinkstack -llinkqueue -lslist -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# -DBST_TRAVEL_ITER_IMPL
bst.o:bst.c
	$(CC) $(CFLAGS)   -c -o $@ $^

clean:
	$(RM) $(OBJS) *.a $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)
	
	$(AR) -r libbst.a bst.o
	cp bst.h /usr/local/include/
	cp libbst.a /usr/local/lib/