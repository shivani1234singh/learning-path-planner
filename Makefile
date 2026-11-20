
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

TARGET = learning_planner

SRC = src/main.c src/planner.c src/algorithms.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
