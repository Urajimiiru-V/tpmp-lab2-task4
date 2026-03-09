CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -I./src
TARGET=abiturient_program
SRCDIR=src
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f data/result.txt

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
