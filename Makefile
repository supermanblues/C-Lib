CC=clang
OBJS=main.o array/array.o llist/slist.o llist/llist.o \
		stack/stack.o stack/linkstack.o \
		queue/queue.o queue/linkqueue.o \
		bst/bst.o union_find/union_find.o sort/sort.o common/test-utils.o

CFLAGS+=-std=c11 -c -Wall -O2

mytools:$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -f $(OBJS) mytools
# 	find . -name "*.o"  | xargs rm -f *.o
	
