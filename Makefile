BINDIR=build
SRC_FILES=main.c debug_heap.c

all: dirs
	gcc $(SRC_FILES) -o $(BINDIR)/main

run:
	./$(BINDIR)/main

dirs:
	mkdir -p $(BINDIR)
