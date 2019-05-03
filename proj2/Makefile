TARGET=proj
SOURCE=proj.cpp
FLAGS= -std=c++11 -Wall -lm
DEBUGFLAGS = -g
PRODFLAGS = -O3
PROFILE= -pg
CC=g++

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(SOURCE) $(FLAGS) $(DEBUGFLAGS) -o $(TARGET)
	cp $(TARGET) tests/
	cp $(TARGET) student-tests/

clean:
	rm $(TARGET)

prod: $(SOURCE)
	$(CC) $(SOURCE) $(FLAGS) $(PRODFLAGS) -o $(TARGET)

profile: $(SOURCE) 
	$(CC) $(SOURCE) $(FLAGS) $(PROFILE) -o $(TARGET)
