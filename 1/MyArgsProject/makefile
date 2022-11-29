CC = gcc
CPPFLAGS = -g -Wall -fsanitize=address -std=c17
HDRS = linked_list.h graph.h
OBJS = linked_list.o graph.o

main: $(OBJS) $(HDRS)
	$(CC) $(CPPFLAGS) -o checkGraph checkGraph.c $(OBJS)

%.o: %.c %.h

.PHONY: clean

clean:
	rm $(OBJS) main