CC = gcc
LFLAGS=-Wall -Wextra -Wpedantic

SOURCES = ll_cycle.c test_ll_cycle.c
OBJECTS = ll_cycle.o test_ll_cycle.o
HEADER = ll_cycle.h


check_cycle : ${OBJ} ${HEADER}
	$(CC) $(OBJ) $(LFLAGS) -o check_cycle 

%.o : %.c $(HEADER)
	$(CC) $< -c

clean:
	rm -rf check_cycle
	rm -rf *.o
