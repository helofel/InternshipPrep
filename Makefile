CC = gcc
OBJS = prep.c 

prep: $(OBJS)
	$(CC) $^ -o $@ -Wall -Wextra -Werror
	$(CC) -g $^ -o prep.debug
clean:
	rm -f prep *.o