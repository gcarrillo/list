PROG=test
CC=gcc
CFLAGS=-Wall -ggdb3 -O0
DEPS=list.h
OBJS=main.o list.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(OBJS) $(PROG)
