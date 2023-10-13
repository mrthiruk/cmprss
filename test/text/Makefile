CC := gcc
CFLAGS := -g -Wall -std=c99 -I../../text/huffman -I../../common \
		  -L../../build
VALGRIND_FLAGS := -s --show-leak-kinds=all --leak-check=full \
				  --track-origins=yes

HUFFMAN := test_huffman

huffman: $(HUFFMAN).c
	$(CC) $(CFLAGS) -o $(HUFFMAN).out $(HUFFMAN).c -lcmprss

check: $(HUFFMAN).out
	valgrind $(VALGRIND_FLAGS) ./$(HUFFMAN).out
