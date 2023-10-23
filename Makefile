CC := gcc
CFLAGS := -g -Wall -std=c99 -I./common -I./utils/mem -I./utils/slist \
		  -DCMPRSS_DEBUG

BIN := build
TEXT_DIR := text
COMMON_DIR := common
UTILS_DIR := utils

MEM_DIR := $(UTILS_DIR)/mem
MEM_SRC := mem

mem: $(MEM_DIR)/$(MEM_SRC).*
	mkdir -p $(BIN)/$(MEM_DIR)
	$(CC) $(CFLAGS) -o $(BIN)/$(MEM_DIR)/$(MEM_SRC).o \
		-c $(MEM_DIR)/$(MEM_SRC).c

SLIST_DIR := $(UTILS_DIR)/slist
	SLIST_SRC := slist

slist: $(SLIST_DIR)/$(SLIST_SRC).*
	mkdir -p $(BIN)/$(SLIST_DIR)
	$(CC) $(CFLAGS) -o $(BIN)/$(SLIST_DIR)/$(SLIST_SRC).o \
		-c $(SLIST_DIR)/$(SLIST_SRC).c

HUFFMAN_TEXT_DIR := $(TEXT_DIR)/huffman
HUFFMAN_TEXT_SRC := huffman_txt

huffman_text: mem slist $(HUFFMAN_TEXT_DIR)/$(HUFFMAN_TEXT_SRC).*
	mkdir -p $(BIN)/$(HUFFMAN_TEXT_DIR)
	$(CC) $(CFLAGS) -o $(BIN)/$(HUFFMAN_TEXT_DIR)/$(HUFFMAN_TEXT_SRC).o \
		-c $(HUFFMAN_TEXT_DIR)/$(HUFFMAN_TEXT_SRC).c
	ar rcs $(BIN)/$(HUFFMAN_TEXT_DIR)/libcmprss.a \
		$(BIN)/$(HUFFMAN_TEXT_DIR)/*.o $(BIN)/$(MEM_DIR)/*.o \
		$(BIN)/$(SLIST_DIR)/*.o

clean:
	rm -rf $(BIN)
