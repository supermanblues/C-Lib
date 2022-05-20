CC=clang
TARGET=main
OBJS=main.o union_find.o
LIBS=-larray -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)

	$(AR) -r libunion_find.a union_find.o
	cp union_find.h /usr/local/include/
	cp libunion_find.a /usr/local/lib/