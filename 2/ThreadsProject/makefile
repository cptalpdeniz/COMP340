CC = gcc
CPPFLAGS =-std=c11
HDRS = gui2.h display.h
OBJS = gui2.o display.o

main: $(OBJS) $(HDRS)
	$(CC) $(CPPFLAGS) -lpthread -O2 -o time time.c $(OBJS)

%.o: %.c %.h

.PHONY: clean

clean:
	rm $(OBJS) time