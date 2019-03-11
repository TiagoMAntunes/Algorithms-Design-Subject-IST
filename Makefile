TARGET = proj1
CFLAGS = -g -Wall
LDFLAGS = -lm
CC = gcc

all:
	cd lib && make
	make proj1
	cp proj1 tests/

proj1: proj1.c lib/item.o lib/net.o
	$(CC) $(CFLAGS) $(wildcard lib/*.o) $< -o $(TARGET) $(LDFLAGS)

prod:
	python3 enfiatudo.py . lib/

clean:
	cd lib && make clean
	rm proj1