TARGET=proj
SOURCE=proj.cpp
FLAGS= -Wall
CC=g++

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(SOURCE) $(FLAGS) -o $(TARGET)
	cp $(TARGET) tests/

clean:
	rm $(TARGET)