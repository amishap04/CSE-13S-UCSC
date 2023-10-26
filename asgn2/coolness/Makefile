CC = gcc

SOURCES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SOURCES))

.PHONY: clean

all : coolness 

coolness : coolness.o
	$(CC) -o coolness $(OBJECTS) 

%.o : %.c
	$(CC) -c $<