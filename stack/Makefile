CC=clang
TARGET=main 
OBJS=main.o stack.o linkstack.o
LIBS=-larray -lslist -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) *.a $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)
	
	$(AR) -r libstack.a stack.o
	$(AR) -r liblinkstack.a linkstack.o

	cp stack.h linkstack.h /usr/local/include/
	cp libstack.a liblinkstack.a /usr/local/lib/