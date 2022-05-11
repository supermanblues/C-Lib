CC=clang
OBJS=main.o common.o test-utils.o
CFLAGS+=-std=c11 -c -Wall

main:$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS) main