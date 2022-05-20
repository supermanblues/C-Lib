CC=clang
TARGET=main
OBJS=main.o sort.o
LIBS=-ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)
	
	$(AR) -r libsort.a sort.o
	cp sort.h /usr/local/include/
	cp libsort.a /usr/local/lib/