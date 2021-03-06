
CC=clang
TARGET=mytools
OBJS=main.o
LIBS=-larray -lslist -lllist \
		-lstack -llinkstack -lqueue -llinkqueue \
		-lbst -lset -lunion_find  -ltrie \
		-lsort -lcommon -ltest-utils
CFLAGS+=-std=c11 -g -Wall -O0

.PHONY: integration-test
defalult:integration-test

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	$(RM) *.o $(TARGET)

test:
	$(MAKE) clean
	$(MAKE) $(TARGET)
	./$(TARGET)

install:
	$(MAKE) -C common install
	$(MAKE) -C sort install
	$(MAKE) -C array install
	$(MAKE) -C list install
	$(MAKE) -C stack install
	$(MAKE) -C queue install
	$(MAKE) -C bst install
	$(MAKE) -C set install
	$(MAKE) -C trie install
	$(MAKE) -C union_find install

integration-test:
	$(MAKE) -C common test
	$(MAKE) -C sort test
	$(MAKE) -C array test
	$(MAKE) -C list test
	$(MAKE) -C stack test
	$(MAKE) -C queue test
	$(MAKE) -C bst test
	$(MAKE) -C set test
	$(MAKE) -C trie test
	$(MAKE) -C union_find test

	$(MAKE) test
