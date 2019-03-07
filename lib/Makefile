CFLAGS = -g -Wall
SOURCES = $(wildcard *.c)
OBJS = $(SOURCES:%.c=%.o)
CC = gcc
TARGET = test
LDFLAGS = -lm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

vector_unit_test.o: vector_unit_test.c
vector.o: vector.c vector.h
item.o: item.c item.h


$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJS) $(TARGET)
