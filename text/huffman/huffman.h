#ifndef _CMPRSS_HUFFMAN_H_
#define _CMPRSS_HUFFMAN_H_

status_ct cmprss_huffman_encode(char *in, uint32 in_len, 
		char **out, uint32 *out_len);
status_ct cmprss_huffman_decode(char *in, uint32 in_len, 
		char **out, uint32 *out_len);

#endif
