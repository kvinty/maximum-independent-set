CC = gcc
CFLAGS = -I"src" -std=c99 -O3 -Wall -Wextra -pedantic

OBJLIST = obj/main.o obj/array.o obj/graph.o obj/mis.o

.PHONY: all
all: bin/mis

.PHONY: clean
clean:
	rm obj/*
	rm bin/*

bin/mis : $(OBJLIST)
	mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS)

obj/%.o : src/%.c
	@mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS)
