CC=clang
TARGET=main
OBJS=main.o trie.o
LIBS=-ltest-utils
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

	$(AR) -r libtrie.a trie.o
	$(CC) -shared -fpic -o libtrie.so trie.o

install:
	$(MAKE) package

	cp trie.h /usr/local/include/
	cp libtrie.a libtrie.so /usr/local/lib/