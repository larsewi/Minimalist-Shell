
CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wconversion -pedantic -DNDEBUG=1
LDFLAGS = 

.PHONY: all obj clean run debug

all: minish

minish: obj/main.o
	$(CC) $^ -o $@ $(LDFLAGS)

obj/main.o: src/main.c obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj
	rm -f minish

run: minish 
	./minish

debug: 
	gdb minish
