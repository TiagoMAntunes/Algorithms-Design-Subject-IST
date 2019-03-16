CFLAGS = -Wall -ansi -g
SOURCES = $(wildcard *.c)
OBJS = $(SOURCES:%.c=%.o)
CC = gcc
TARGET = test
LDFLAGS = -lm

all: $(TARGET)

$(TARGET): $(OBJS)

vector.o: vector.c vector.h
list.o: list.c list.h
item.o: item.c item.h
net.o: net.c net.h

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJS)
