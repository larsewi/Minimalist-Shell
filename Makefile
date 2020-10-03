
CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wconversion -DNDEBUG=1
LDFLAGS = 

.PHONY: all obj clean run leakcheck

all: minish

minish: obj/main.o obj/logger.o obj/minish.o obj/strarray.o
	$(CC) $^ -o $@ $(LDFLAGS)

obj/main.o: src/main.c obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/logger.o: src/logger.c obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/minish.o: src/minish.c obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/strarray.o: src/strarray.c obj 
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj
	rm -f minish

run: minish 
	./minish

leakcheck: minish
	valgrind --leak-check=full ./minish
