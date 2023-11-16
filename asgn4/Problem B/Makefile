CC = gcc
CFLAGS=-Wall -Wextra -Wpedantic

TARGET=growing_arrays

OBJ=growing_arrays.o main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

growing_arrays.o: growing_arrays.c growing_arrays.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c growing_arrays.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJ)
