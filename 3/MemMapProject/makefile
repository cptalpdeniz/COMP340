CC = gcc
CPPFLAGS = -O3 -std=c11 -lpthread
HDRS = 
OBJS = 

main:
		$(CC) $(CPPFLAGS) -o memory_map memory_map.c $(OBJS)

%.o: %.c %.h

.PHONY: clean

clean:
	rm $(OBJS) memory_map && rm -rf memory_map.dSYM