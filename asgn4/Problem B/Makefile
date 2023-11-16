CC = gcc
LFLAGS=-Wall -Wextra -Wpedantic

SOURCES = growing_arrays.c test_growing_arrays.c
OBJECTS = growing_arrays.o test_growing_arrays.o
HEADER = growing_arrays.h


growing_array : ${OBJ} ${HEADER}
        $(CC) $(OBJ) $(LFLAGS) -o growing_array

%.o : %.c $(HEADER)
        $(CC) $< -c

clean:
        rm -rf growing_array
        rm -rf *.o
