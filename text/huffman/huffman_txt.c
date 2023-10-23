#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmprss_common.h"
#include "mem.h"
#include "slist.h"
#include "huffman_txt.h"

#define ASCII_SIZE				128

typedef struct freq_tree_ct freq_tree_ct;
struct freq_tree_ct {
	char chr;
	uint32 freq;
	freq_tree_ct *left;
	freq_tree_ct *right;
};

// Internal function declarations
static status_ct cmp_cback(void *data, void *datb);
static void del_cback(void *dat);
static void print_cback(void *dat);
static void i_print_tree(freq_tree_ct *root);
static void i_del_tree(freq_tree_ct *root);

status_ct 
cmprss_huffman_txt_encode(char *in, uint32 in_len, 
		char **out, uint32 *out_len)
{
	// Only supports ASCII text for now
	uint32 freq_table[ASCII_SIZE] = {0};
	status_ct ret = CMPRSS_SUCCESS;
	for (uint32 i = 0; i < in_len; i++) {
		// TODO Check for ASCII compliance
		freq_table[(uint8)in[i]]++;
	}
	slist_ct *chr_list_head = NULL;
	uint16 count = 0;
	// Build Initial list
	for (uint8 i = 0; i < ASCII_SIZE; i++) {
		if (freq_table[i]) {
			count++;
			freq_tree_ct *data = mem_calloc(sizeof(freq_tree_ct));
			data->chr = (char) i;
			data->freq = freq_table[i];
			slist_insert_at_tail(&chr_list_head, (void *) data);
		}
	}
	printf("count: %u\n\n", count);
	slist_sort(&chr_list_head, cmp_cback);
	printf("\n\nAfter sorting:\n");
	slist_print(&chr_list_head, print_cback);
	
	printf("\n\n\n\n");
#if 1
	count = 0;
	freq_tree_ct *mina = NULL, 
				 *minb = NULL, 
				 *node = NULL;
	while(chr_list_head && chr_list_head->next) {
		count++;
		mina = chr_list_head->dat;
		minb = chr_list_head->next->dat;
		node = mem_calloc(sizeof(freq_tree_ct));
		node->chr = 0;
		node->freq = mina->freq + minb->freq;
		node->left = mina;
		node->right = minb;
		slist_delete(&chr_list_head, mina, cmp_cback, del_cback, false, true);
		slist_delete(&chr_list_head, minb, cmp_cback, del_cback, false, true);
		slist_insert_after(&chr_list_head, node, cmp_cback);
		printf("Count: %u\n", count);
		printf("---------------------\n");
		slist_print(&chr_list_head, print_cback);
		printf("---------------------\n\n");
	}
	i_print_tree(node);
	i_del_tree(node);
#endif
	slist_delete_list(&chr_list_head, del_cback, false);
	return ret;
}

status_ct 
cmprss_huffman_txt_decode(char *in, uint32 in_len, 
		char **out, uint32 *out_len)
{
	status_ct ret = CMPRSS_SUCCESS;
	return ret;
}

static status_ct 
cmp_cback(void *data, void *datb)
{
	status_ct ret;
	freq_tree_ct *freqa = (freq_tree_ct *) data, 
			*freqb = (freq_tree_ct *) datb;
	if (freqa->freq == freqb->freq) {
		ret = CMPRSS_EQ;
	} else if (freqa->freq > freqb->freq) {
		ret = CMPRSS_GREAT;
	} else {
		ret = CMPRSS_LESS;
	}
	return ret;
}

static 
void del_cback(void *dat)
{
	mem_free((freq_tree_ct *) dat);
}

#ifdef CMPRSS_DEBUG
static 
void print_cback(void *dat)
{
	freq_tree_ct *freq = (freq_tree_ct *) dat;
	printf("chr : %c\tfreq: %u\n", freq->chr, freq->freq);
}
#endif

static void 
i_del_tree(freq_tree_ct *root)
{
	if (!root) {
		return;
	}
	i_del_tree(root->left);
	i_del_tree(root->right);
	printf("deleting node...\n");
	mem_free(root);
}

static void 
i_print_tree(freq_tree_ct *root)
{
	if (!root) {
		return;
	}
	static uint8 depth;
	depth++;
	i_print_tree(root->left);
	depth--;
	for (uint8 i = 0; i < depth; i++) {
		printf("\t");
	}
	printf("%u\n", root->freq);
	depth++;
	i_print_tree(root->right);
	depth--;

}
