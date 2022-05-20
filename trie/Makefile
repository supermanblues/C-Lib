CC=clang
TARGET=main
OBJS=main.o trie.o
LIBS=-ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET)

package:
	$(MAKE) clean
	$(MAKE)

	$(AR) -r libtrie.a trie.o
	cp trie.h /usr/local/include/
	cp libtrie.a /usr/local/lib/