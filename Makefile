CC=gcc
CFLAGS=-I./src -Wall
TARGET=abiturient_program
SOURCES=src/main.c src/server.c
HEADERS=src/interfaces.h

all: clean $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) src/*.o

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
