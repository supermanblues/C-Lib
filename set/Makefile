CC=clang
TARGET=main
OBJS=main.o set.o
LIBS=-lbst -llinkqueue -lslist -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) *.a $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)
	
	$(AR) -r libset.a set.o
	cp set.h /usr/local/include/
	cp libset.a /usr/local/lib/