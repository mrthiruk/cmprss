#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmprss_common.h"
#include "huffman.h"

#define ASCII_SIZE				128

// Only supports ASCII text for now
static uint32 g_freq_table[ASCII_SIZE];

status_ct 
cmprss_huffman_encode(char *in, uint32 in_len, 
		char **out, uint32 *out_len)
{
	status_ct ret = CMPRSS_SUCCESS;
	for (uint32 i = 0; i < in_len; i++) {
		// TODO Check for ASCII compliance
		g_freq_table[(int)in[i]]++;
	}
	for (uint32 i = 0; i < ASCII_SIZE; i++) {
		printf("%u: %u\n", i, g_freq_table[i]);
	}
	return ret;
}

status_ct 
cmprss_huffman_decode(char *in, uint32 in_len, 
		char **out, uint32 *out_len)
{
	status_ct ret = CMPRSS_SUCCESS;
	return ret;
}
