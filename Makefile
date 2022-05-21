CC=clang
TARGET=mytools
OBJS=main.o
LIBS=-larray -lslist -lllist \
		-lstack -llinkstack -lqueue -llinkqueue \
		-lbst -lset -lunion_find  -ltrie \
		-lsort -lcommon -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O2

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) *.o $(TARGET)
# 	find . -name "*.o"  | xargs rm -f *.o

integration-test:
	$(MAKE) -C common test
	$(MAKE) -C sort test
	$(MAKE) -C array test
	$(MAKE) -C llist test
	$(MAKE) -C stack test
	$(MAKE) -C queue test
	$(MAKE) -C bst test
	$(MAKE) -C set test
	$(MAKE) -C trie test
	$(MAKE) -C union_find test

	$(MAKE) clean
	$(MAKE)
	./$(TARGET)