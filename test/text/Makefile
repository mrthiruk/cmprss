ROOT := ../..
CC := gcc
CFLAGS := -g -Wall -std=c99 -I$(ROOT)/text/huffman -I$(ROOT)/common \
		  -L$(ROOT)/build/text/huffman
VALGRIND_FLAGS := -s --show-leak-kinds=all --leak-check=full \
				  --track-origins=yes

HUFFMAN := test_huffman

huffman: $(HUFFMAN).c
	$(CC) $(CFLAGS) -o $(HUFFMAN).out $(HUFFMAN).c -lcmprss

check: $(HUFFMAN).out
	valgrind $(VALGRIND_FLAGS) ./$(HUFFMAN).out
