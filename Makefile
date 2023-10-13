CC := gcc
CFLAGS := -g -Wall -std=c99 -I./common

BIN := build

TEXT := text

MKBUILD: 
	mkdir $(BIN)

HUFFMAN := huffman
HUFFMAN_SRC := $(TEXT)/$(HUFFMAN)/$(HUFFMAN).c

huffman_text: MKBUILD $(HUFFMAN_SRC)
	$(CC) $(CFLAGS) -o $(BIN)/$(HUFFMAN).o -c $(HUFFMAN_SRC)
	ar rcs $(BIN)/libcmprss.a $(BIN)/*.o

clean:
	rm -rf $(BIN)
