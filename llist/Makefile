CC=clang
OBJS=main.o slist.o llist.o ../common/test-utils.o
CFLAGS+=-std=c11 -c -Wall -O2

main:$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS) main