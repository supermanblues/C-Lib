CC=clang
TARGET=main
OBJS=main.o array.o
LIBS=-ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) *.a $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)

	$(AR) -r libarray.a array.o

	cp array.h /usr/local/include/
	cp libarray.a /usr/local/lib/