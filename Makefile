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
	$(RM) $(OBJS) $(TARGET)
# 	find . -name "*.o"  | xargs rm -f *.o
	
