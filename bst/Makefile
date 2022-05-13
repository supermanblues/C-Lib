CC=clang
OBJS=main.o bst.o ../array/array.o ../sort/sort.o ../llist/llist.o \
			../stack/linkstack.o ../queue/linkqueue.o ../common/test-utils.o
CFLAGS+=-std=c11 -c -Wall

main:$(OBJS)
	$(CC) $^ -o $@

bst.o:bst.c
	$(CC) $(CFLAGS) $^ -o $@ -D__bst_preorder_iter_impl -D__bst_inorder_iter_impl -D__bst_postorder_iter_impl

%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS) main