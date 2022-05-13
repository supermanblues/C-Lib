CC=clang
OBJS=main.o array.o ../sort/sort.o ../common/test-utils.o
CFLAGS+=-std=c11 -c -Wall

main:$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS) main