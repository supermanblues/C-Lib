CC=clang
OBJS=main.o bst.o ../array/array.o ../sort/sort.o \
			../stack/linkstack.o ../queue/linkqueue.o ../llist/slist.o \
			../common/test-utils.o
CFLAGS+=-std=c11 -c -Wall -O2

main:$(OBJS)
	$(CC) $^ -o $@

bst.o:bst.c
	$(CC) $(CFLAGS) $^ -o $@ # -DBST_TRAVEL_ITER_IMPL

%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS) *.a main

package:
	$(MAKE) clean
	$(MAKE)
	
	ar -r libbst.a bst.o
	cp bst.h /usr/local/include/
	cp libbst.a /usr/local/lib/

# 	ar -r libarray.a ../array/array.o
# 	ar -r libsort.a ../sort/sort.o
# 	ar -r liblinkstack.a ../stack/linkstack.o
# 	ar -r liblinkqueue.a ../queue/linkqueue.o
# 	ar -r libslist.a ../llist/slist.o

# 	cp bst.h ../array/array.h ../sort/sort.h ../stack/linkstack.h ../queue/linkqueue.h ../llist/slist.h /usr/local/include/
# 	cp libbst.a libarray.a libsort.a liblinkstack.a liblinkqueue.a libslist.a /usr/local/lib/