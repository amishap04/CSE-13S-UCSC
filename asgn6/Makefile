CC = gcc
LFLAGS=-Wall -Wextra -Wpedantic -g -lcurl

SOURCE=bag.c curl.c url.c hashtable.c pagedir.c crawler.c
OBJ=set.o curl.o url.o hashtable.o pagedir.o crawler.o
HEADER=crawler.h


crawler: ${OBJ} ${HEADER}
	$(CC) $(OBJ) $(LFLAGS) -o crawler

%.o: %.c $(HEADER)
	$(CC) $< -c

clean:
	rm -rf crawler
	rm -rf *.o
