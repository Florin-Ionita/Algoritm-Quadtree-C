.phony: build run clean

TEST = quadtree.c
HEADERS = $(wildcard *.h)
CC = gcc
CC_FLAGS = -std=c9x -g -O0 -o
EXEC = quadtree
build: $(EXEC) $(TEST)
	$(CC) $(CC_FLAGS) $(EXEC) $(TEST)
run: $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

clean:
	rm -f $(EXEC)
